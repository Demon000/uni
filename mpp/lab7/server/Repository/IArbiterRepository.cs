using server.Domain;

namespace server.Repository
{
    public interface IArbiterRepository
    {
        void Add(Arbiter arbiter);
        Arbiter FindByNameAndPassword(string name, string password);
    }
}
