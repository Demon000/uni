namespace lab8.domain
{
    public class Team<TId> : Entity<TId>
        where TId : class
    {
        public string Name { get; set;  }
        public string SchoolName { get; set; }

        public Team() {}
        
        public Team(TId id, string name, string schoolName) : base(id)
        {
            Name = name;
            SchoolName = schoolName;
        }
    }
}
