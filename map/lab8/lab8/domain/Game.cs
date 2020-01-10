using System;

namespace lab8.domain
{
    public class Game<TId> : Entity<TId>
        where TId : class
    {
        public string FirstTeamId { get; }
        public string SecondTeamId { get; }
        public DateTime Date { get; }

        public Game() {}
        
        public Game(TId gameId, string firstTeamId, string secondTeamId, DateTime date) : base(gameId)
        {
            FirstTeamId = firstTeamId;
            SecondTeamId = secondTeamId;
            Date = date;
        }
    }
}
