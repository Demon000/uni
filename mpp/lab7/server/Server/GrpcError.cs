using System;
using Triathlon;

namespace server.Server
{
    public class GrpcError : Exception
    {
        public ErrorNumber ErrorNumber { get; set; }

        public GrpcError(ErrorNumber errorNumber) : base(errorNumber.ToString())
        {
            ErrorNumber = errorNumber;
        }
    }
}