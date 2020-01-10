using System.Collections.Generic;
using System.IO;
using System.Xml.Serialization;
using lab8.domain;

namespace lab8.repository
{
    public class XmlRepository<TId, TEntity> : Repository<TId, TEntity>
        where TEntity : Entity<TId>
        where TId : class
    {
        private readonly XmlSerializer _serializer = new XmlSerializer(typeof(List<TEntity>));
        private string Filename { get; }

        public XmlRepository(string filename)
        {
            Filename = filename;
        }
        public override TEntity Get(TId id)
        {
            Load();
            return base.Get(id);
        }

        public override List<TEntity> Get()
        {
            Load();
            return base.Get();
        }

        public override void Add(TEntity entity)
        {
            Load();
            base.Add(entity);
            Save();
        }

        public override void Update(TEntity entity)
        {
            Load();
            base.Update(entity);
            Save();
        }

        public override void Delete(TId id)
        {
            Load();
            base.Delete(id);
            Save();
        }

        public override void Clear()
        {
            base.Clear();
            Save();
        }

        private void Load()
        {
            try
            {
                using (TextReader reader = new StreamReader(Filename))
                {
                    Entities = (List<TEntity>) _serializer.Deserialize(reader);
                }
            }
            catch (FileNotFoundException)
            {
                Entities = new List<TEntity>();
            }

        }

        private void Save()
        {
            using (TextWriter writer = new StreamWriter(Filename))
            {
                _serializer.Serialize(writer, Entities);
            }
        }
    }
}
