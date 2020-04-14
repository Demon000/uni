using System;
using System.Collections.Generic;
using lab5.domain;
using lab5.repository;

namespace lab5.service
{
    public class Service
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
        return ScoreRepository.Get(participantId);
        }

        public List<Score> GetScores() {
            return ScoreRepository.FindSortedByName();
        }
        
        public List<Score> GetScoresForType(ScoreType type) {
            return ScoreRepository.FindByTypeSortedDescending(type);
        }
    }
}