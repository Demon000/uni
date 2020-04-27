using System.Collections.Generic;
using System.Linq;
using Triathlon;

namespace server.Domain
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

        public ScoreProto ToProto()
        {
            var protoScores = new Dictionary<int, int>();
            foreach (var (type, value) in Scores)
            {
                protoScores.Add((int) type, value);
            }
            
            return new ScoreProto { Participant = Participant.ToProto(), Scores = { protoScores }};
        }
    }
}
