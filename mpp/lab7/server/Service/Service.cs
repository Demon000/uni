using System.Collections.Generic;
using server.Domain;
using server.Repository;

namespace server.Service
{
    public class Service : BaseService
    {
        private IParticipantRepository ParticipantRepository { get; }
        private IArbiterRepository ArbiterRepository { get; }
        private IScoreRepository ScoreRepository { get; }

        public Service(IParticipantRepository participantRepository,
            IArbiterRepository arbiterRepository,
            IScoreRepository scoreRepository)
        {
            ParticipantRepository = participantRepository;
            ArbiterRepository = arbiterRepository;
            ScoreRepository = scoreRepository;
        }
        
        public Arbiter LoginArbiter(string name, string password) {
            return ArbiterRepository.FindByNameAndPassword(name, password);
        }

        public Score SetScoreValue(int participantId, ScoreType type, int value) {
            ScoreRepository.Set(participantId, type, value);
            var score = ScoreRepository.Get(participantId);
            ObserverSetScore(score);
            return score;
        }

        public List<Score> GetScores() {
            return ScoreRepository.FindSortedByName();
        }
        
        public List<Score> GetRankings(ScoreType type) {
            return ScoreRepository.FindByTypeSortedDescending(type);
        }
    }
}