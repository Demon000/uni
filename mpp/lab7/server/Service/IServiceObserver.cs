using server.Domain;

namespace server.Service
{
    public interface IServiceObserver
    {
        public void OnSetScore(Score score);
    }
}