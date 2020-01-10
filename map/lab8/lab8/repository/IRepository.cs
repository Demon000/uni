using System.Collections.Generic;
using lab8.domain;

namespace lab8.repository
{
    public interface IRepository<in TId, TEntity>
        where TEntity : Entity<TId>
        where TId : class
    {
        TEntity Get(TId id);
        List<TEntity> Get();
        void Add(TEntity entity);
        void Update(TEntity entity);
        void Delete(TId id);
    }
}
