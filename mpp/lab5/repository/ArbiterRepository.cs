using lab5.domain;
using lab5.utils;
using System.Data.Common;
using log4net;

namespace lab5.repository
{
    public class ArbiterRepository : IArbiterRepository
    {
        private static readonly ILog Logger = LogManager.GetLogger("ParticipantRepository");
        
        private DbConnection Connection { get; }

        public ArbiterRepository(DbConnection connection)
        {
            Connection = connection;
            CreateTable();
        }

        private void CreateTable()
        {
            var command = Connection.CreateCommand(
                @"
                    create table if not exists Arbiters (
                        ArbiterId integer primary key autoincrement,
                        ArbiterName nvarchar(255) not null unique,
                        ArbiterPassword nvarchar(255) not null,
                        ArbiterType integer not null
                    );
                ");
            try
            {
                command.ExecuteNonQuery();
            }
            catch (DbException e)
            {
                Logger.Error("Failed to create table", e);
                Logger.Error(command.CommandText);
                Logger.Error(e);
                throw new RepositoryError("Failed to create table", e);
            }
            
            Logger.Info("Created table or already existing");
            Logger.Info(command.CommandText);
        }

        public void Add(Arbiter arbiter)
        {
            var command = Connection.CreateCommand(
                @"
                    insert into Arbiters(
                        ArbiterName,
                        ArbiterPassword,
                        ArbiterType
                    ) values (
                        @ArbiterName,
                        @ArbiterPassword,
                        @ArbiterType
                    );
                ");
            command.AddParameterWithValue("@ArbiterName", arbiter.Name);
            command.AddParameterWithValue("@ArbiterPassword", arbiter.Password);
            command.AddParameterWithValue("@ArbiterType", (int)arbiter.Type);
            try
            {
                command.ExecuteNonQuery();
            }
            catch (DbException e)
            {
                Logger.Error("Failed to add arbiter", e);
                Logger.Error(command.CommandText);
                Logger.Error(e);
                throw new RepositoryError("Failed to add arbiter", e);
            }
            
            Logger.Info("Added arbiter");
            Logger.Info(command.CommandText);

            command = Connection.CreateCommand(
                @"
                    select
                        max(ArbiterId)
                    from Arbiters where
                        ArbiterName=@ArbiterName and
                        ArbiterPassword=@ArbiterPassword
                    ;
                ");

            command.AddParameterWithValue("@ArbiterName", arbiter.Name);
            command.AddParameterWithValue("@ArbiterPassword", arbiter.Password);

            DbDataReader reader;
            try
            {
                reader = command.ExecuteReader();
            }
            catch (DbException e)
            {
                Logger.Error("Failed to retrieve arbiter id");
                Logger.Error(command.CommandText);
                Logger.Error(e);
                throw new RepositoryError("Failed to retrieve arbiter id", e);
            }

            if (!reader.Read())
            {
                Logger.Error("Failed to retrieve arbiter id");
                Logger.Error(command.CommandText);
                throw new RepositoryError("Failed to retrieve arbiter id");
            }
            else
            {
                arbiter.Id = reader.GetInt32(0);
            }

            Logger.Info("Retrieved arbiter id");
            Logger.Info(command.CommandText);
        }

        public Arbiter FindByNameAndPassword(string name, string password)
        {
            var command = Connection.CreateCommand(
                @"
                    select
                        ArbiterId,
                        ArbiterType
                    from Arbiters where
                        ArbiterName=@ArbiterName and
                        ArbiterPassword=@ArbiterPassword
                    ;
                ");
            command.AddParameterWithValue("@ArbiterName", name);
            command.AddParameterWithValue("@ArbiterPassword", password);

            DbDataReader reader;
            try
            {
                reader = command.ExecuteReader();
            }
            catch (DbException e)
            {
                Logger.Error("Failed to retrieve arbiter by name and password");
                Logger.Error(command.CommandText);
                throw new RepositoryError("Failed to retrieve arbiter by name and password", e);
            }
            
            if (!reader.Read())
            {
                Logger.Error("Failed to retrieve arbiter by name and password");
                Logger.Error(command.CommandText);
                throw new RepositoryError("Failed to retrieve arbiter by name and password");
            }
            
            Logger.Info("Retrieved arbiter by name and password");
            Logger.Info(command.CommandText);
            
            var id = reader.GetInt32(0);
            var type = (ScoreType)reader.GetInt32(1);
            return new Arbiter(id, name, password, type);

        }
    }
}
