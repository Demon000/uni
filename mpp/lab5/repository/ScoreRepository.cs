using lab5.domain;
using System;
using System.Collections.Generic;
using System.Data.Common;
using lab5.utils;
using log4net;

namespace lab5.repository
{
    public class ScoreRepository : IScoreRepository
    {
        private static readonly ILog Logger = LogManager.GetLogger("ParticipantRepository");
        
        private DbConnection Connection { get; }

        public ScoreRepository(DbConnection connection)
        {
            Connection = connection;
            CreateTable();
        }

        private void CreateTable()
        {
            var command = Connection.CreateCommand(
                @"
                    create table if not exists Scores (
                        ParticipantId integer not null,
                        ScoreType integer not null,
                        ScoreValue integer not null,
                        primary key(ParticipantId, ScoreType),
                        foreign key(ParticipantId) references Participants(ParticipantId)
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

        public void Add(int participantId, ScoreType type, int value)
        {
            var command = Connection.CreateCommand(
                @"
                    insert into Scores (
                        ParticipantId,
                        ScoreType,
                        ScoreValue
                    ) values (
                        @ParticipantId,
                        @ScoreType,
                        @ScoreValue
                    );
                ");
            command.AddParameterWithValue("@ParticipantId", participantId);
            command.AddParameterWithValue("@ScoreType", (int)type);
            command.AddParameterWithValue("@ScoreValue", value);
            try
            {
                command.ExecuteNonQuery();
            }
            catch (DbException e)
            {
                Logger.Error("Failed to add score", e);
                Logger.Error(command.CommandText);
                Logger.Error(e);
                throw new RepositoryError("Failed to add score", e);
            }
            
            Logger.Info("Added score");
            Logger.Info(command.CommandText);
        }

        public List<Score> FindByTypeSortedDescending(ScoreType type)
        {
            var command = Connection.CreateCommand(
                @"
                    select
                        P.ParticipantId,
                        P.ParticipantName,
                        S.ScoreValue
                    from Scores S
                    inner join Participants P on S.ParticipantId=P.ParticipantId
                    where S.ScoreType=@ScoreType and S.ScoreValue is not 0
                    order by S.ScoreValue desc
                    ;
                ");
            command.AddParameterWithValue("@ScoreType", (int)type);

            DbDataReader reader;
            try
            {
                reader = command.ExecuteReader();
            }
            catch (DbException e)
            {
                Logger.Error("Failed to find scores by type", e);
                Logger.Error(command.CommandText);
                Logger.Error(e);
                throw new RepositoryError("Failed to find scores by type", e);
            }

            Logger.Info("Found scores by type");
            Logger.Info(command.CommandText);
            
            var scores = new List<Score>();
            while (reader.Read())
            {
                var participantId = reader.GetInt32(0);
                var participantName = reader.GetString(1);
                var participant = new Participant(participantId, participantName);
                var score = new Score(participant);
                
                score.SetScore(type, reader.GetInt32(2));
                
                scores.Add(score);
            }

            return scores;
        }

        public List<Score> FindSortedByName()
        {
            var command = Connection.CreateCommand(
                @"
                    select
                        P.ParticipantId,
                        P.ParticipantName,
                        sum(case when S.ScoreType=@CyclingScoreType then S.ScoreValue else 0 end),
                        sum(case when S.ScoreType=@RunningScoreType then S.ScoreValue else 0 end),
                        sum(case when S.ScoreType=@SwimmingScoreType then S.ScoreValue else 0 end)
                    from Participants P
                    left outer join Scores S on S.ParticipantId=P.ParticipantId
                    group by P.ParticipantId, P.ParticipantName
                    order by P.ParticipantName
                    ;
                ");
            command.AddParameterWithValue("@CyclingScoreType", (int)ScoreType.Cycling);
            command.AddParameterWithValue("@RunningScoreType", (int)ScoreType.Running);
            command.AddParameterWithValue("@SwimmingScoreType", (int)ScoreType.Swimming);

            DbDataReader reader;
            try
            {
                reader = command.ExecuteReader();
            }
            catch (DbException e)
            {
                Logger.Error("Failed to find scores", e);
                Logger.Error(command.CommandText);
                Logger.Error(e);
                throw new RepositoryError("Failed to find scores", e);
            }
            
            Logger.Info("Found scores");
            Logger.Info(command.CommandText);
            
            var scores = new List<Score>();
            while (reader.Read())
            {
                var participantId = reader.GetInt32(0);
                var participantName = reader.GetString(1);
                var participant = new Participant(participantId, participantName);
                var score = new Score(participant);
                
                score.SetScore(ScoreType.Cycling, reader.GetInt32(2));
                score.SetScore(ScoreType.Running, reader.GetInt32(3));
                score.SetScore(ScoreType.Swimming, reader.GetInt32(4));
                
                scores.Add(score);
            }

            return scores;
        }

        public Score Get(int participantId)
        {
            var command = Connection.CreateCommand(
                @"
                    select
                        P.ParticipantName,
                        sum(case when S.ScoreType=@CyclingScoreType then S.ScoreValue else 0 end),
                        sum(case when S.ScoreType=@RunningScoreType then S.ScoreValue else 0 end),
                        sum(case when S.ScoreType=@SwimmingScoreType then S.ScoreValue else 0 end)
                    from Participants P
                    left outer join Scores S on S.ParticipantId=P.ParticipantId
                    where P.ParticipantId=@ParticipantId
                    ;
                ");
            command.AddParameterWithValue("@ParticipantId", participantId);
            command.AddParameterWithValue("@CyclingScoreType", (int)ScoreType.Cycling);
            command.AddParameterWithValue("@RunningScoreType", (int)ScoreType.Running);
            command.AddParameterWithValue("@SwimmingScoreType", (int)ScoreType.Swimming);

            DbDataReader reader;
            try
            {
                reader = command.ExecuteReader();
            }
            catch (DbException e)
            {
                Logger.Error("Failed to retrieve total score by id");
                Logger.Error(command.CommandText);
                Logger.Error(e);
                throw new RepositoryError("Failed to retrieve total score by id", e);
            }
            
            if (!reader.Read())
            {
                Logger.Error("Failed to retrieve total score by id");
                Logger.Error(command.CommandText);
                throw new RepositoryError("Failed to retrieve total score by id");
            }
            
            Logger.Info("Retrieved total score by id");
            Logger.Info(command.CommandText);
            
            var participantName = reader.GetString(0);
            var participant = new Participant(participantId, participantName);
            var score = new Score(participant);
            
            score.SetScore(ScoreType.Cycling, reader.GetInt32(1));
            score.SetScore(ScoreType.Running, reader.GetInt32(2));
            score.SetScore(ScoreType.Swimming, reader.GetInt32(3));

            return score;
        }

        public void Set(int participantId, ScoreType type, int value)
        {
            try
            {
                Add(participantId, type, value);
            }
            catch (RepositoryError)
            {
                Update(participantId, type, value);
            }
        }

        public void Update(int participantId, ScoreType type, int value)
        {
            var command = Connection.CreateCommand(
                @"
                    update Scores set
                        ScoreValue=@ScoreValue
                    where
                        ParticipantId=@ParticipantId and
                        ScoreType=@ScoreType
                    ;
                ");
            command.AddParameterWithValue("@ScoreValue", value);
            command.AddParameterWithValue("@ParticipantId", participantId);
            command.AddParameterWithValue("@ScoreType", (int)type);

            try
            {
                command.ExecuteNonQuery();
            }
            catch (DbException e)
            {
                Logger.Error("Failed to update score");
                Logger.Error(command.CommandText);
                Logger.Error(e);
                throw new RepositoryError("Failed to update score", e);
            }
            
            Logger.Info("Updated score");
            Logger.Info(command.CommandText);
        }
    }
}
