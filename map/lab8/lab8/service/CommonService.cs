using System;
using System.Collections.Generic;
using System.Linq;
using lab8.domain;
using lab8.repository;

namespace lab8.service
{
    public class CommonService
    {
        public Repository<string, Team<string>> TeamRepository { get; }
        public Repository<string, Player<string>> PlayerRepository { get; }
        public Repository<string, Game<string>> GameRepository { get; }
        public Repository<CompositeId<string>, PlayerActivity<string>> PlayerActivityRepository { get; }

        public CommonService(Repository<string, Team<string>> teamRepository,
            Repository<string, Player<string>> playerRepository,
            Repository<string, Game<string>> gameRepository,
            Repository<CompositeId<string>, PlayerActivity<string>> playerActivityRepository)
        {
            TeamRepository = teamRepository;
            PlayerRepository = playerRepository;
            GameRepository = gameRepository;
            PlayerActivityRepository = playerActivityRepository;
        }

        public Game<string> GetGameById(string gameId)
        {
            return GameRepository.Get(gameId);
        }

        public Player<string> GetPlayerById(string playerId)
        {
            return PlayerRepository.Get(playerId);
        }

        public Team<string> GetTeamById(string teamId)
        {
            return TeamRepository.Get(teamId);
        }
        
        public List<Player<string>> GetPlayersForTeamId(string teamId)
        {
            return PlayerRepository
                .Get()
                .Where(p => p.TeamId == teamId)
                .ToList();
        }

        public List<Player<string>> GetActivePlayersForGameIdAtTeam(string gameId, string teamId)
        {
            return PlayerActivityRepository
                .Get()
                .Where(a => a.GameId == gameId)
                .Where(a => a.Type == PlayerActivity<string>.ActivityType.Playing)
                .Select(a => GetPlayerById(a.PlayerId))
                .Where(p => p.TeamId == teamId)
                .ToList();
        }

        public List<Game<string>> GetGamesInTimePeriod(DateTime first, DateTime second)
        {
            return GameRepository
                .Get()
                .Where(g => g.Date >= first)
                .Where(g => g.Date <= second)
                .ToList();
        }

        public int GetGameScoreByIdForTeam(string gameId, string teamId)
        {
            return PlayerActivityRepository
                .Get()
                .Where(a => a.GameId == gameId)
                .Where(a => GetPlayerById(a.PlayerId).TeamId == teamId)
                .Select(a => a.Points)
                .Sum();
        }
        
        public Tuple<int, int> GetGameScoreById(string gameId)
        {
            var game = GameRepository.Get(gameId);
            int firstTeamScore = GetGameScoreByIdForTeam(gameId, game.FirstTeamId);
            int secondTeamScore = GetGameScoreByIdForTeam(gameId, game.SecondTeamId);
            return new Tuple<int, int>(firstTeamScore, secondTeamScore);
        }
    }
}