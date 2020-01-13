using System.Collections.Generic;
using System.Linq;

namespace lab8.domain
{
    public class CompositeId<TId>
        where TId : class
    {
        public List<TId> Ids { get; set; }

        public CompositeId()
        {
        }
        
        public CompositeId(params TId[] ids)
        {
            Ids = new List<TId>(ids);
        }
        
        public TId Part(int i)
        {
            return Ids[i];
        }

        private bool Equals(CompositeId<TId> other)
        {
            return Ids == other.Ids;
        }

        public override bool Equals(object other)
        {
            if (ReferenceEquals(null, other)) return false;
            if (ReferenceEquals(this, other)) return true;
            if (GetType() != other.GetType()) return false;
            return Equals((CompositeId<TId>) other);
        }

        public override int GetHashCode()
        {
            return (Ids != null ? Ids.GetHashCode() : 0);
        }
        
        public static bool operator ==(CompositeId<TId> first, CompositeId<TId> second)
        {
            return second != null && first != null && first.Ids.SequenceEqual(second.Ids);
        }

        public static bool operator !=(CompositeId<TId> first, CompositeId<TId> second)
        {
            return !(first == second);
        }
    }
}
