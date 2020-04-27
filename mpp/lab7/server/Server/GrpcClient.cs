using System.Collections.Concurrent;
using System.Threading;
using log4net;
using server.Domain;

namespace server.Server
{
    public class GrpcClient
    {
        private static ILog _log;

        public Arbiter Arbiter { get; }

        private BlockingCollection<Score> _scores;

        public GrpcClient(Arbiter arbiter)
        {
            _log = LogManager.GetLogger($"Client {arbiter}");
            Arbiter = arbiter;
        }

        public void SubscribeSetScore()
        {
            if (_scores == null || _scores.IsAddingCompleted)
            {
                _log.Info("Subscribed to set score events");
                _scores = new BlockingCollection<Score>();
            }
        }

        public void UnsubscribeSetScore()
        {
            if (_scores != null && !_scores.IsAddingCompleted)
            {
                _log.Info("Unsubscribed from set score events");
                _scores.CompleteAdding();
            }
        }

        public void PushScore(Score score)
        {
            if (_scores != null && !_scores.IsAddingCompleted)
            {
                _scores.TryAdd(score);
            }
        }

        private const int ScoreWaitTimeout = 10000;
        public bool GetPushedScore(out Score score, CancellationToken token)
        {
            var took = _scores.TryTake(out score, ScoreWaitTimeout, token);
            if (_scores.IsAddingCompleted || token.IsCancellationRequested)
            {
                _log.Info("Wait for set score events cancelled");
                return true;
            }
            
            if (!took)
            {
                score = null;
                return true;
            }

            return true;
        }
    }
}
