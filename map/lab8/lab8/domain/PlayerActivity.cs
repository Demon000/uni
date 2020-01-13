namespace lab8.domain
{
    public class PlayerActivity<TId> : Entity<CompositeId<TId>>
        where TId : class
    {
        public int Points { get; set;  }
        public ActivityType Type { get; set; }

        public TId PlayerId => Id.Part(0);

        public TId GameId => Id.Part(1);

        public enum ActivityType
        {
            Reserve,
            Playing,
            Unused
        }
        
        PlayerActivity() {}

        public PlayerActivity(TId playerId, TId gameId, int points, ActivityType type) : base(new CompositeId<TId>(playerId, gameId))
        {
            Points = points;
            Type = type;
        }
    }
}
