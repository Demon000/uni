namespace lab8.domain
{
    public abstract class Entity<TId>
        where TId : class
    {
        public TId Id { get; set;  }

        protected Entity() {}
        
        protected Entity(TId id)
        {
            Id = id;
        }
    }
}
