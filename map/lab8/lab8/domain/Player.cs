using System;
using System.Xml.Serialization;

namespace lab8.domain
{
    public class Player<TId> : Student<TId>
        where TId : class
    {
        public TId TeamId { get; set; }

        public Player() {}
        
        public Player(TId studentId, TId teamId, string name)
            : base(studentId, name)
        {
            TeamId = teamId;
        }
    }
}
