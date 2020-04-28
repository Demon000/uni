using System.Collections.Concurrent;
using System.Threading;
using log4net;
using server.Domain;

namespace server.Server
{
    public class GrpcClient
    {
        private readonly ILog _log;

        public Arbiter Arbiter { get; }

        public bool IsSubscribed => _scores != null && !_scores.IsAddingCompleted;

        private BlockingCollection<Score> _scores;

        public GrpcClient(Arbiter arbiter)
        {
            _log = LogManager.GetLogger($"Client {arbiter}");
            Arbiter = arbiter;
        }

        public void SubscribeSetScore()
        {
            if (IsSubscribed)
            {
                _log.Info("Client is already subscribed to set score events");
                return;
            }
            _log.Info("Subscribed to set score events");
            _scores = new BlockingCollection<Score>();
        }

        public void UnsubscribeSetScore()
        {
            if (!IsSubscribed)
            {
                _log.Info("Client is already unsubscribed to set score events");
                return;
            }
            _log.Info("Unsubscribed from set score events");
            _scores.CompleteAdding();
        }

        public void PushScore(Score score)
        {
            if (!IsSubscribed) return;
            _scores.TryAdd(score);
        }

        private const int ScoreWaitTimeout = 10000;
        public bool GetPushedScore(out Score score, CancellationToken token)
        {
            var took = _scores.TryTake(out score, ScoreWaitTimeout, token);
            if (!IsSubscribed || token.IsCancellationRequested)
            {
                _log.Info("Wait for set score events cancelled");
                return false;
            }

            if (took) return true;
            score = null;
            return true;
        }
    }
}
