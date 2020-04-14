using lab5.domain;

namespace lab5.repository
{
    public interface IArbiterRepository
    {
        void Add(Arbiter arbiter);
        Arbiter FindByNameAndPassword(string name, string password);
    }
}
