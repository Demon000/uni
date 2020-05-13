using System;
using System.Collections.Generic;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;
using Grpc.Core;
using Microsoft.IdentityModel.Tokens;
using server.Domain;
using Triathlon;

namespace server.Server
{
    public class Auth
    {
        private readonly string _securityKeyIssuer;
        private readonly SigningCredentials _credentials;
        private readonly JwtSecurityTokenHandler _securityTokenHandler;
        private readonly TokenValidationParameters _tokenValidationParameters;

        public Auth(string securityKeySecret, string securityKeyIssuer)
        {
            _securityKeyIssuer = securityKeyIssuer;
            var securityKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(securityKeySecret));
            _credentials = new SigningCredentials(securityKey, SecurityAlgorithms.HmacSha256);
            _securityTokenHandler = new JwtSecurityTokenHandler();
            _tokenValidationParameters = new TokenValidationParameters
            {
                ValidateIssuerSigningKey = true,
                IssuerSigningKey = securityKey,
                ValidateIssuer = true,
                ValidIssuer = securityKeyIssuer,
                ValidateAudience = true,
                ValidAudience = securityKeyIssuer,
                ValidateLifetime = true,
            };
        }

        private string CreateToken(int id)
        {
            var claims = new[] {  
                new Claim(ClaimTypes.Sid, id.ToString()),  
            };  
  
            var token = new JwtSecurityToken(_securityKeyIssuer,  
                _securityKeyIssuer,  
                claims,  
                expires: DateTime.Now.AddDays(1),  
                signingCredentials: _credentials);  
  
            return _securityTokenHandler.WriteToken(token); 
        }

        private int DecodeToken(string tokenString)
        {
            var claims = _securityTokenHandler.ValidateToken(tokenString, _tokenValidationParameters, out _);
            return int.Parse(claims.FindFirst(ClaimTypes.Sid).Value);
        }
        
        
        private readonly Dictionary<string, GrpcClient> _clients = new Dictionary<string, GrpcClient>();
        private const string AuthorizationHeaderKey = "authorization";
        private const string AuthorizationHeaderPrefix = "Bearer ";

        private static string GetTokenString(ServerCallContext context)
        {
            string tokenString = null;

            foreach (var entry in context.RequestHeaders)
            {
                if (entry.Key == AuthorizationHeaderKey &&
                    entry.Value.StartsWith(AuthorizationHeaderPrefix))
                {
                    tokenString = entry.Value.Substring(AuthorizationHeaderPrefix.Length);
                    break;
                }
            }

            return tokenString;
        }

        private static void SetTokenString(ServerCallContext context, string tokenString)
        {
            context.WriteResponseHeadersAsync(new Metadata
            {
                new Metadata.Entry(AuthorizationHeaderKey, $"{AuthorizationHeaderPrefix}{tokenString}"),
            });
        }

        public GrpcClient GetClient(ServerCallContext context)
        {
            var tokenString = GetTokenString(context);
            if (tokenString == null)
            {
                throw new GrpcError(ErrorNumber.BearerMissing);
            }

            int id;
            try
            {
                id = DecodeToken(tokenString);
            }
            catch
            {
                throw new GrpcError(ErrorNumber.BearerInvalid);
            }

            lock (_clients)
            {
                if (!_clients.ContainsKey(tokenString))
                {
                    throw new GrpcError(ErrorNumber.BearerNotAuthorized);
                }

                var client = _clients[tokenString];
                if (client.Arbiter.Id != id)
                {
                    throw new GrpcError(ErrorNumber.BearerNotAuthorized);
                }
            
                return _clients[tokenString];
            }
        }

        public void CreateClient(ServerCallContext context, Arbiter arbiter)
        {
            var tokenString = CreateToken(arbiter.Id);
            var client = new GrpcClient(arbiter);
            lock (_clients)
            {
                _clients.Add(tokenString, client);
            }
            SetTokenString(context, tokenString);
        }

        public void RemoveClient(ServerCallContext context)
        {
            var tokenString = GetTokenString(context);
            if (tokenString == null)
            {
                throw new GrpcError(ErrorNumber.BearerMissing);
            }
            
            lock (_clients)
            {
                if (!_clients.ContainsKey(tokenString))
                {
                    throw new GrpcError(ErrorNumber.BearerNotAuthorized);
                }

                _clients.Remove(tokenString);
            }
        }
    }
}
