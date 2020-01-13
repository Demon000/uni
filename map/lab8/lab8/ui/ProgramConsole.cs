using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using lab8.domain;
using lab8.service;

namespace lab8.ui
{
    internal class ConsoleMenuEntry
    {
        public string Index { get; }
        public string Description { get; }
        public Action Function { get; }

        public ConsoleMenuEntry(string index, string description, Action function)
        {
            Index = index;
            Description = description;
            Function = function;
        }

        public void Call()
        {
            while (true)
            {
                try
                {
                    Function.DynamicInvoke();
                    break;
                }
                catch (Exception e)
                {
                    Console.Write(e.Message);
                }
            }
        }

        public bool IsExit()
        {
            return Index == "x";
        }

        public override string ToString()
        {
            return $"{Index}. {Description}";
        }
    }
    
    public class ProgramConsole
    {
        private CommonService Service { get; }

        private ConsoleMenuEntry[] mainEntries;
        
        public ProgramConsole(CommonService service)
        {
            Service = service;

            mainEntries = new ConsoleMenuEntry[] {
                new ConsoleMenuEntry("1", "Show players of a team", ShowPlayersForTeamId),
                new ConsoleMenuEntry("2", "Show active players for a game", ShowActivePlayersForGameId),
                new ConsoleMenuEntry("3", "Show games in a time period", ShowGamesInTimePeriod),
                new ConsoleMenuEntry("4", "Show the score of a game", ShowGameScore),
                new ConsoleMenuEntry("x", "Exit", Exit), 
            };
        }

        private string ReadString(String message, String errorMessage)
        {
            while (true)
            {
                Console.Write(message);
                string result = Console.ReadLine();
                if (string.IsNullOrEmpty(result))
                {
                    Console.WriteLine(errorMessage);
                    continue;
                }

                return result;
            }
        }

        private DateTime ReadDate(String message, String errorMessage)
        {
            while (true)
            {
                Console.Write(message);
                string raw = Console.ReadLine();
                if (!DateTime.TryParse(raw, out var result))
                {
                    Console.WriteLine(errorMessage);
                    continue;
                }

                return result;
            }
        }
        
        private void Exit()
        {
            Console.WriteLine("Goodbye!");
        }
        
        private void PrintPlayers(List<Player<string>> players)
        {
            players.ForEach(Console.WriteLine);
        }

        private void PrintGames(List<Game<string>> games)
        {
            games.ForEach(Console.WriteLine);
        }

        private void ShowPlayersForTeamId()
        {
            var teamId = ReadString("Team id: ", "Invalid team id");
            var players = Service.GetPlayersForTeamId(teamId);
            PrintPlayers(players);
        }
        
        private void ShowActivePlayersForGameId()
        {
            var gameId = ReadString("Game id: ", "Invalid game id");
            var game = Service.GetGameById(gameId);
            Console.WriteLine(game);
            
            var teamId = ReadString("Team id: ", "Invalid team id");
            var players = Service.GetActivePlayersForGameIdAtTeam(gameId, teamId);
            PrintPlayers(players);
        }

        private void ShowGamesInTimePeriod()
        {
            var firstDate = ReadDate("First date: ", "Invalid first date");
            var secondDate = ReadDate("Second date: ", "Invalid second date");

            var games = Service.GetGamesInTimePeriod(firstDate, secondDate);
            PrintGames(games);
        }

        private void ShowGameScore()
        {
            var gameId = ReadString("Game id: ", "Invalid game id");
            var (firstTeamScore, secondTeamScore) = Service.GetGameScoreById(gameId);
            Console.WriteLine($"{firstTeamScore} - {secondTeamScore}");
        }

        private void PrintEntries(ConsoleMenuEntry[] entries)
        {
            entries.ToList().ForEach(Console.WriteLine);
        }

        private ConsoleMenuEntry GetEntryByIndex(ConsoleMenuEntry[] entries, string index)
        {
            return entries.ToList().Find(e => e.Index == index);
        }
        
        private ConsoleMenuEntry ReadEntry(ConsoleMenuEntry[] entries)
        {
            String entryIndex = ReadString("Command: ", "Invalid command!");
            return GetEntryByIndex(entries, entryIndex);
        }
        
        private void RunEntries(ConsoleMenuEntry[] entries)
        {
            while (true) {
                PrintEntries(entries);
                ConsoleMenuEntry entry = ReadEntry(entries);

                if (entry == null) {
                    Console.WriteLine("Invalid command");
                    continue;
                }

                if (entry.IsExit()) {
                    break;
                }

                entry.Call();
            }
        }

        public void Run()
        {
            RunEntries(mainEntries);
        }
    }
}