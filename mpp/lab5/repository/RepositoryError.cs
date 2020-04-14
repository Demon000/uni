using System;
using System.Runtime.Serialization;

namespace lab5.repository
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

        protected RepositoryError(SerializationInfo info, StreamingContext context) : base(info, context)
        {
        }
    }
}