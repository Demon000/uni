using System.Xml.Serialization;

namespace lab8.domain
{
    public class Player<TId> : Student<TId>
        where TId : class
    {
        public TId TeamId { get; set; }

        public Player() {}
        
        public Player(TId playerId, TId teamId, string name)
            : base(playerId, name)
        {
            TeamId = teamId;
        }

        public override string ToString()
        {
            return $"Player => Id: {Id}, Team Id: {TeamId}, Name: {Name}";
        }
    }
}
