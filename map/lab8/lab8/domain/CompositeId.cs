using System.Collections.Generic;
using System.Linq;

namespace lab8.domain
{
    public class CompositeId<TId>
        where TId : class
    {
        private bool Equals(CompositeId<TId> other)
        {
            return _ids == other._ids;
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
            return (_ids != null ? _ids.GetHashCode() : 0);
        }

        private readonly List<TId> _ids;

        public CompositeId(params TId[] ids)
        {
            _ids = new List<TId>(ids);
        }
        public TId Part(int i)
        {
            return _ids[i];
        }

        public static bool operator ==(CompositeId<TId> first, CompositeId<TId> second)
        {
            return second != null && first != null && first._ids.SequenceEqual(second._ids);
        }

        public static bool operator !=(CompositeId<TId> first, CompositeId<TId> second)
        {
            return !(first == second);
        }
    }
}
