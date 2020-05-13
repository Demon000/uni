using server.Domain;

namespace server.Server
{
    public class GrpcClient
    {
        public Arbiter Arbiter { get; }
        
        public GrpcClient(Arbiter arbiter)
        {
            Arbiter = arbiter;
        }
    }
}
