using System;
using System.Configuration;  
using System.Data.Common;
using System.Windows.Forms;
using lab5.domain;
using lab5.repository;
using System.Data.SQLite;
using System.Runtime.InteropServices;
using lab5.service;

namespace lab5
{
    static class Program
    {
        private static DbConnection _connection;
        private static IParticipantRepository _participantRepository;
        private static IArbiterRepository _arbiterRepository;
        private static IScoreRepository _scoreRepository;
        private static Service _service;

        public static void TryAddParticipant(Participant participant)
        {
            try
            {
                _participantRepository.Add(participant);
            }
            catch (RepositoryError)
            {
            }
        }
        
        public static void TryAddArbiter(Arbiter arbiter) {
            try {
                _arbiterRepository.Add(arbiter);
            } catch (RepositoryError) {
            }
        }

        public static void TrySetScore(int participantId, ScoreType type, int score) {
            try {
                _service.SetScoreValue(participantId, type, score);
            } catch (RepositoryError) {
            }
        }
        
        public static void TryLogin(String name, String password) {
            try
            {
                var arbiter = _service.LoginArbiter(name, password);
                Console.WriteLine(arbiter);
            } catch (RepositoryError) {
            }
        }

        public static void TryPrintScoresSortedByName() {
            try
            {
                var scores = _service.GetScores();
                Console.WriteLine("Total scores sorted by name");
                scores.ForEach(Console.WriteLine);
                Console.WriteLine();
            } catch (RepositoryError) {
            }
        }

        public static void TryPrintScoresForTypeSortedDescending(ScoreType type)
        {
            try
            {
                var scores = _service.GetScoresForType(type);
                Console.WriteLine($"Scores for {type.ToString()} sorted descending");
                scores.ForEach(Console.WriteLine);
                Console.WriteLine();
            } catch (RepositoryError) {
            }
        }

        [DllImport("Kernel32")]
        public static extern void AllocConsole();

        [DllImport("Kernel32")]
        public static extern void FreeConsole();
        
        [STAThread]
        public static void Main()
        {
            AllocConsole();

            _connection = new SQLiteConnection(ConfigurationManager.AppSettings["databaseConnection"]);
            _connection.Open();
            _participantRepository = new ParticipantRepository(_connection);
            _arbiterRepository = new ArbiterRepository(_connection);
            _scoreRepository = new ScoreRepository(_connection);
            _service = new Service(_participantRepository, _arbiterRepository, _scoreRepository);
            
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
            TryPrintScoresSortedByName();
            TryPrintScoresForTypeSortedDescending(ScoreType.Cycling);
            TryPrintScoresForTypeSortedDescending(ScoreType.Running);
            TryPrintScoresForTypeSortedDescending(ScoreType.Swimming);
            
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());

            FreeConsole();
        }
    }
}
