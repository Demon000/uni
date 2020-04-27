using System.Collections.Generic;
using server.Domain;

namespace server.Repository
{
    public interface IScoreRepository
    {
        void Add(int participantId, ScoreType type, int value);
        Score Get(int participantId);
        void Update(int participantId, ScoreType type, int value);
        void Set(int participantId, ScoreType type, int value);
        List<Score> FindByTypeSortedDescending(ScoreType type);
        List<Score> FindSortedByName();
    }
}
