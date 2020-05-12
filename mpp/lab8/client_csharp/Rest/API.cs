using System;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Net.Mime;

namespace client_csharp.Rest
{
    public class API
    {
        public readonly HttpClient Client;
        
        public API(string host, int port)
        {
            Client = new HttpClient {BaseAddress = new Uri($"{host}:{port}/api/")};
            Client.DefaultRequestHeaders.Accept.Clear();
            Client.DefaultRequestHeaders.Accept.Add(
                new MediaTypeWithQualityHeaderValue(MediaTypeNames.Application.Json));
        }
    }
}