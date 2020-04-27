using System;
using System.Configuration;
using System.Data.Common;
using System.Data.SQLite;
using System.IO;
using Grpc.Core;
using log4net.Config;
using server.Domain;
using server.Repository;
using server.Server;
using Triathlon;

namespace server
{
    internal static class Program
    {
        private static DbConnection _connection;
        private static IParticipantRepository _participantRepository;
        private static IArbiterRepository _arbiterRepository;
        private static IScoreRepository _scoreRepository;
        private static Service.Service _service;
        private static GrpcServer _grpcServer;
        private static Grpc.Core.Server _server;
        private static Auth _auth;

        private static string GetConfig(string key, string value)
        {
            return ConfigurationManager.AppSettings[key] ?? value;
        }

        private static int GetIntegerConfig(string key, int value)
        {
            return ConfigurationManager.AppSettings[key] != null ?
                int.Parse(ConfigurationManager.AppSettings[key]) : value;
        }
        
        private static void TryAddParticipant(Participant participant)
        {
            try
            {
                _participantRepository.Add(participant);
            }
            catch (RepositoryError)
            {
            }
        }

        private static void TryAddArbiter(Arbiter arbiter) {
            try {
                _arbiterRepository.Add(arbiter);
            } catch (RepositoryError) {
            }
        }

        private static void TrySetScore(int participantId, ScoreType type, int score) {
            try {
                _service.SetScoreValue(participantId, type, score);
            } catch (RepositoryError) {
            }
        }

        private static void TryLogin(String name, String password) {
            try
            {
                var arbiter = _service.LoginArbiter(name, password);
                Console.WriteLine(arbiter);
            } catch (RepositoryError) {
            }
        }

        private static void TryPrintScoresSortedByName() {
            try
            {
                var scores = _service.GetScores();
                Console.WriteLine("Total scores sorted by name");
                scores.ForEach(Console.WriteLine);
                Console.WriteLine();
            } catch (RepositoryError) {
            }
        }

        private static void TryPrintScoresForTypeSortedDescending(ScoreType type)
        {
            try
            {
                var scores = _service.GetRankings(type);
                Console.WriteLine($"Scores for {type.ToString()} sorted descending");
                scores.ForEach(Console.WriteLine);
                Console.WriteLine();
            } catch (RepositoryError) {
            }
        }

        private static void ConfigureLogger()
        {
            XmlConfigurator.Configure(new FileInfo("Log4Net.config"));
        }

        private static void CreateAuth()
        {
            _auth = new Auth(GetConfig("securityKeySecret", ""),
                GetConfig("securityKeyIssuer", ""));
        }

        private static void CreateServer()
        {
            _grpcServer = new GrpcServer(_service, _auth);
            _server = new Grpc.Core.Server
            {
                Services = { TriathlonService.BindService(_grpcServer) },
                Ports = { new ServerPort(GetConfig("serverHost", "localhost"),
                    GetIntegerConfig("serverPort", 8000),
                    ServerCredentials.Insecure) }
            };
        }
        
        private static void StartServer()
        {
            _server.Start();
            _service.AddObserver(_grpcServer);
        }

        private static void WaitForShutdown()
        {
            Console.WriteLine("Press any key to stop the server...");
            Console.ReadKey();

        }
        
        private static void StopServer()
        {
            _service.RemoveObserver(_grpcServer);
            _server.ShutdownAsync().Wait();
        }

        
        [STAThread]
        public static void Main()
        {
            ConfigureLogger();
            
            _connection = new SQLiteConnection(ConfigurationManager.AppSettings["databaseConnection"]);
            _connection.Open();
            _participantRepository = new ParticipantRepository(_connection);
            _arbiterRepository = new ArbiterRepository(_connection);
            _scoreRepository = new ScoreRepository(_connection);
            _service = new Service.Service(_participantRepository, _arbiterRepository, _scoreRepository);
            
            TryAddParticipant(new Participant("Christian Tatoiu"));
            TryAddParticipant(new Participant("Radu Stefanescu"));
            TryAddParticipant(new Participant("Nicu Serte"));
            TryAddParticipant(new Participant("Alexandra Suciu"));
            TryAddParticipant(new Participant("Silvia Suciu"));
            TryAddParticipant(new Participant("Adrian Sopterean"));
            
            TryAddArbiter(new Arbiter("Cosmin Tanislav", "passwordcosmin", ScoreType.Cycling));
            TryAddArbiter(new Arbiter("Mihai Solcan", "passwordsolcan", ScoreType.Running));
            TryAddArbiter(new Arbiter("Teodor Spiridon", "passwordrunning", ScoreType.Swimming));
            TryLogin("Cosmin Tanislav", "passwordcosmin");

            TrySetScore(1, ScoreType.Cycling, 20);
            TrySetScore(1, ScoreType.Running, 20);
            TrySetScore(1, ScoreType.Swimming, 10);
            TrySetScore(2, ScoreType.Cycling, 10);
            TrySetScore(2, ScoreType.Running, 10);
            TrySetScore(2, ScoreType.Swimming, 10);
            TrySetScore(3, ScoreType.Cycling, 10);
            TrySetScore(3, ScoreType.Running, 5);
            TrySetScore(3, ScoreType.Swimming, 5);
            
            // TryPrintScoresSortedByName();
            // TryPrintScoresForTypeSortedDescending(ScoreType.Cycling);
            // TryPrintScoresForTypeSortedDescending(ScoreType.Running);
            // TryPrintScoresForTypeSortedDescending(ScoreType.Swimming);

            CreateAuth();
            CreateServer();
            StartServer();
            WaitForShutdown();
            StopServer();
        }
    }
}
