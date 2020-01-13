using System;
using System.Collections.Generic;
using System.Linq;
using lab8.domain;

namespace lab8.repository
{
    public class Repository<TId, TEntity> : IRepository<TId, TEntity>
        where TId : class
        where TEntity : Entity<TId>
    {
        protected List<TEntity> Entities = new List<TEntity>();
        
        public virtual TEntity Get(TId id)
        {
            var entity = Entities.FirstOrDefault(e => e.Id.Equals(id));
            if (entity == null)
            {
                throw new Exception($"Entity with id: {id} does not exist");
            }

            return entity;
        }

        public virtual List<TEntity> Get()
        {
            return Entities;
        }

        public virtual void Add(TEntity entity)
        {
            var other = Entities.FirstOrDefault(e => e.Id.Equals(entity.Id));
            if (other != null)
            {
                throw new Exception($"Entity with id: {entity.Id} already exists");
            }
            
            Entities.Add(entity);
        }

        public virtual void Update(TEntity entity)
        {
            var index = Entities.FindIndex(e => e.Id.Equals(entity.Id));
            if (index < 0)
            {
                throw new Exception($"Entity with id: {entity.Id} does not exist");
            }
            
            Entities[index] = entity;
        }

        public virtual void Delete(TId id)
        {
            var index = Entities.FindIndex(e => e.Id.Equals(id));
            if (index < 0)
            {
                throw new Exception($"Entity with id: {id} does not exist");
            }

            Entities.RemoveAt(index);
        }

        public virtual void Clear()
        {
            Entities.Clear();
        }
    }
}
