using lab5.domain;
using System.Collections.Generic;

namespace lab5.repository
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
