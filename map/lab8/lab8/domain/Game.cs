using System;

namespace lab8.domain
{
    public class Game<TId> : Entity<TId>
        where TId : class
    {
        public string FirstTeamId { get; set; }
        public string SecondTeamId { get; set; }
        public DateTime Date { get; set; }

        public Game() {}
        
        public Game(TId gameId, string firstTeamId, string secondTeamId, DateTime date) : base(gameId)
        {
            FirstTeamId = firstTeamId;
            SecondTeamId = secondTeamId;
            Date = date;
        }
        
        public override string ToString()
        {
            return $"Game => First Team Id: {FirstTeamId}, Second Team Id: {SecondTeamId}, Date: {Date}";
        }
    }
}
