using System.Data.Common;
using lab5.utils;
using log4net;
using server.Domain;

namespace server.Repository
{
    public class ParticipantRepository : IParticipantRepository
    {
        private static readonly ILog Logger = LogManager.GetLogger("ParticipantRepository");
        
        private DbConnection Connection { get; }

        public ParticipantRepository(DbConnection connection)
        {
            Connection = connection;
            CreateTable();
        }

        private void CreateTable()
        {
            var command = Connection.CreateCommand(
                @"
                    create table if not exists Participants (
                        ParticipantId integer primary key autoincrement,
                        ParticipantName nvarchar(255) not null unique
                    );
                ");
            try
            {
                command.ExecuteNonQuery();
            }
            catch (DbException e)
            {
                Logger.Error("Failed to create table");
                Logger.Error(command.CommandText);
                Logger.Error(e);
                throw new RepositoryError("Failed to create table", e);
            }
            
            Logger.Info("Created table or already existing");
            Logger.Info(command.CommandText);
        }

        public void Add(Participant participant)
        {
            var command = Connection.CreateCommand(
                @"
                    insert into Participants (
                        ParticipantName
                    ) values (
                        @ParticipantName
                    );
                ");
            command.AddParameterWithValue("@ParticipantName", participant.Name);
            try
            {
                command.ExecuteNonQuery();
            }
            catch (DbException e)
            {
                Logger.Error("Failed to add participant");
                Logger.Error(command.CommandText);
                Logger.Error(e);
                throw new RepositoryError("Failed to add participant", e);
            }

            Logger.Info("Added participant");
            Logger.Info(command.CommandText);
            
            command = Connection.CreateCommand(
                @"
                    select
                        max(ParticipantId)
                    from Participants where
                        ParticipantName=@ParticipantName
                    ;
                ");

            command.AddParameterWithValue("@ParticipantName", participant.Name);

            DbDataReader reader;
            try
            {
                reader = command.ExecuteReader();
            }
            catch (DbException e)
            {
                Logger.Error("Failed to retrieve participant id");
                Logger.Error(command.CommandText);
                Logger.Error(e);
                throw new RepositoryError("Failed to retrieve participant id", e);
            }

            if (!reader.Read())
            {
                Logger.Error("Failed to retrieve participant id");
                Logger.Error(command.CommandText);
                throw new RepositoryError("Failed to retrieve participant id");
            }
            
            participant.Id = reader.GetInt32(0);

            Logger.Info("Retrieved participant id");
            Logger.Info(command.CommandText);
        }
    }
}
