using System.Collections.Generic;
using server.Domain;

namespace server.Service
{
    public class BaseService
    {
        private readonly List<IServiceObserver> _observers = new List<IServiceObserver>();

        protected void ObserverSetScore(Score score) {
            _observers.ForEach(observer => {
                observer.OnSetScore(score);
            });
        }

        public void AddObserver(IServiceObserver observer)
        {
            _observers.Add(observer);
        }

        public void RemoveObserver(IServiceObserver observer)
        {
            _observers.Remove(observer);
        }
    }
}