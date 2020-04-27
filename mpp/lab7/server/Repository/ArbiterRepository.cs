using System.Data.Common;
using System.IO;
using lab5.utils;
using log4net;
using log4net.Config;
using server.Domain;

namespace server.Repository
{
    public class ArbiterRepository : IArbiterRepository
    {
        private static readonly ILog Log = LogManager.GetLogger("ArbiterRepository");

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
                Log.Error("Failed to create table", e);
                Log.Error(command.CommandText);
                throw new RepositoryError("Failed to create table", e);
            }
            
            Log.Info("Created table or already existing");
            Log.Info(command.CommandText);
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
                Log.Error("Failed to add arbiter", e);
                Log.Error(command.CommandText);
                throw new RepositoryError("Failed to add arbiter", e);
            }
            
            Log.Info("Added arbiter");
            Log.Info(command.CommandText);

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
                Log.Error("Failed to retrieve arbiter id", e);
                Log.Error(command.CommandText);
                throw new RepositoryError("Failed to retrieve arbiter id", e);
            }

            if (!reader.Read())
            {
                Log.Error("Failed to retrieve arbiter id");
                Log.Error(command.CommandText);
                throw new RepositoryError("Failed to retrieve arbiter id");
            }

            arbiter.Id = reader.GetInt32(0);

            Log.Info("Retrieved arbiter id");
            Log.Info(command.CommandText);
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
                Log.Error("Failed to retrieve arbiter by name and password", e);
                Log.Error(command.CommandText);
                throw new RepositoryError("Failed to retrieve arbiter by name and password", e);
            }
            
            if (!reader.Read())
            {
                Log.Error("Failed to retrieve arbiter by name and password");
                Log.Error(command.CommandText);
                throw new RepositoryError("Failed to retrieve arbiter by name and password");
            }
            
            Log.Info("Retrieved arbiter by name and password");
            Log.Info(command.CommandText);
            
            var id = reader.GetInt32(0);
            var type = (ScoreType)reader.GetInt32(1);
            return new Arbiter(id, name, password, type);
        }
    }
}
