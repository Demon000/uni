using System.Collections.Generic;
using System.Linq;

namespace lab5.domain
{
    public class Score
    {
        public Participant Participant { get; set; }
        public Dictionary<ScoreType, int> Scores { get; set; } = new Dictionary<ScoreType, int>();

        public Score(Participant participant)
        {
            Participant = participant;
        }

        public int GetScore(ScoreType type)
        {
            Scores.TryGetValue(type, out var value);
            return value;
        }

        public void SetScore(ScoreType type, int value)
        {
            Scores[type] = value;
        }

        public int GetTotalScore()
        {
            return Scores.Sum(score => score.Value);
        }

        public override string ToString()
        {
            return $"Score{{Participant={Participant}, TotalScore={GetTotalScore()}}}";
        }
    }
}
