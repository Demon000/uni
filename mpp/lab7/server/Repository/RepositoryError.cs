using System;
using System.Runtime.Serialization;

namespace server.Repository
{
    [Serializable]
    internal class RepositoryError : Exception
    {
        public RepositoryError()
        {
        }

        public RepositoryError(string message) : base(message)
        {
        }

        public RepositoryError(string message, Exception innerException) : base(message, innerException)
        {
        }
    }
}