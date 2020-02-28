using System;
using System.Linq;
using lab8.domain;
using lab8.repository;
using lab8.service;
using lab8.ui;

namespace lab8
{
    static class Program
    {
        private static readonly string[] TeamNames =
        {
            "Houston Rockets",
            "Los Angeles Lakers",
            "LA Clippers",
            "Chicago Bulls",
            "Cleveland Cavaliers",
            "Utah Jazz",
            "Brooklyn Nets",
            "New Orleans Pelicans",
            "Indiana Pacers",
            "Toronto Raptors",
            "Charlotte Hornets",
            "Phoenix Suns",
            "Portland TrailBlazers",
            "Golden State Warriors",
            "Washington Wizards",
            "San Antonio Spurs",
            "Orlando Magic",
            "Denver Nuggets",
            "Detroit Pistons",
            "Atlanta Hawks",
            "Dallas Mavericks",
            "Sacramento Kings",
            "Oklahoma City Thunder",
            "Boston Celtics",
            "New York Knicks",
            "Minnesota Timberwolves",
            "Miami Heat",
            "Milwaukee Bucks",
        };

        private static readonly string[] SchoolNames =
        {
            "Scoala Gimnaziala “Horea\"",
            "Scoala Gimnaziala \"Octavian Goga\"",
            "Liceul Teoretic \"Lucian Blaga\"",
            "Scoala Gimnaziala \"Ioan Bob\"",
            "Scoala Gimnaziala \"Ion Creanga\"",
            "Colegiul National Pedagogic \"Gheorghe Lazar\"",
            "Scoala Gimnaziala Internationala SPECTRUM",
            "Colegiul National \"Emil Racovita\"",
            "Colegiul National \"George Cosbuc\"",
            "Scoala Gimnaziala \"Ion Agarbiceanu\"",
            "Liceul Teoretic \"Avram Iancu\"",
            "Scoala Gimnaziala \"Constantin Brancusi\"",
            "Liceul Teoretic \"Onisifor Ghibu\"",
            "Liceul Teoretic \"Onisifor Ghibu\"",
            "Liceul cu Program Sportiv Cluj-Napoca",
            "Liceul Teoretic \"Nicolae Balcescu\"",
            "Liceul Teoretic \"Gheorghe Sincai\"",
            "Scoala \"Nicolae Titulescu\"",
            "Scoala Gimnaziala \"Liviu Rebreanu\"",
            "Scoala Gimnaziala \"Iuliu Hatieganu\"",
            "Liceul Teoretic \"Bathory Istvan\"",
            "Colegiul National \"George Baritiu\"",
            "Liceul Teoretic \"Apaczai Csere Janos\"",
            "Seminarul Teologic Ortodox",
            "Liceul de Informatica \"Tiberiu Popoviciu\"",
            "Scoala Gimnaziala \"Alexandru Vaida – Voevod\"",
            "Liceul Teoretic ELF",
            "Scoala Gimnaziala \"Gheorghe Sincai\" Floresti",
        };

        private static string[] FirstNames =
        {
            "Andrei",
            "Alexandru",
            "Gabriel",
            "Ionut",
            "Stefan",
            "Maria",
            "Elena",
            "Ioana",
            "Andreea",
            "Alexandra",
            "Cristian",
            "Cosmin",
            "Sebastian",
            "Mihai",
            "Adrian",
            "Teodor",
            "Razvan",
            "Silvia",
            "Nicolae",
            "Iulian",
            "Antonia",
            "Robert",
        };
        
        private static string[] LastNames =
        {
            "Popa",
            "Popescu",
            "Pop",
            "Radu",
            "Ionescu",
            "Dumitru",
            "Stoica",
            "Stan",
            "Gheorghe",
            "Rusu",
            "Munteanu",
            "Matei",
            "Constantin",
            "Serban",
            "Marin",
            "Mihai",
            "Stefan",
            "Lazar",
            "Moldovan",
            "Vasile",
            "Toma",
        };

        private static readonly int PlayersPerTeam = 15;
        private static readonly int NumberOfGames = 10;
        private static readonly int NumberOfTeams = TeamNames.Length;

        private static string GetRandomName(string[] names)
        {
            var random = new Random();
            var nameIndex = random.Next(names.Length);
            return names[nameIndex];
        }

        private static string GetTeamName(int teamIdInt)
        {
            return TeamNames[teamIdInt];
        }

        private static string GetTeamSchoolName(int teamIdInt)
        {
            return SchoolNames[teamIdInt];
        }

        private static string GetRandomTeamId(string otherTeamId)
        {
            var random = new Random();
            string teamId;

            do
            {
                teamId = random.Next(NumberOfTeams).ToString();

            } while (teamId == otherTeamId);

            return teamId;
        }

        private static PlayerActivity<string>.ActivityType GetRandomActivityType()
        {
            var random = new Random();
            var values = Enum.GetValues(typeof(PlayerActivity<string>.ActivityType));
            return (PlayerActivity<string>.ActivityType) values.GetValue(random.Next(values.Length));
        }

        private static int GetRandomPoints()
        {
            var random = new Random();
            return random.Next(5);
        }

        private static DateTime GetRandomDate()
        {
            var random = new Random();
            var start = new DateTime(2018, 1, 1);
            var range = (DateTime.Today - start).Days;
            return start.AddDays(random.Next(range));
        }
        
        private static void PopulateTeams(
            Repository<string, Team<string>> teamRepository,
            Repository<string, Player<string>> playerRepository)
        {
            teamRepository.Clear();
            playerRepository.Clear();

            for (var teamIdInt = 0; teamIdInt < NumberOfTeams; teamIdInt++)
            {
                var teamId = teamIdInt.ToString();
                var name = GetTeamName(teamIdInt);
                var schoolName = GetTeamSchoolName(teamIdInt);
                teamRepository.Add(new Team<string>(teamId, name, schoolName));
                
                for (var playerIdInt = teamIdInt * PlayersPerTeam;
                    playerIdInt < (teamIdInt + 1) * PlayersPerTeam;
                    playerIdInt++)
                {
                    var playerId = playerIdInt.ToString();
                    var playerName = $"{GetRandomName(FirstNames)} {GetRandomName(LastNames)}";
                    var player = new Player<string>(playerId, teamIdInt.ToString(), playerName);
                    playerRepository.Add(player);
                }
            }
        }

        private static void PopulateGames(
            Repository<string, Game<string>> gameRepository,
            Repository<string, Player<string>> playerRepository,
            Repository<CompositeId<string>, PlayerActivity<string>> playerActivityRepository)
        {
            gameRepository.Clear();
            playerActivityRepository.Clear();

            for (var gameId = 0; gameId < NumberOfGames; gameId++)
            {
                var firstTeamId = GetRandomTeamId(null);
                var secondTeamId = GetRandomTeamId(firstTeamId);
                var date = GetRandomDate();
                var game = new Game<string>(gameId.ToString(), firstTeamId, secondTeamId, date);
                gameRepository.Add(game);

                var firstTeamPlayers = playerRepository
                    .Get()
                    .Where(p => p.TeamId == firstTeamId)
                    .ToList();

                var secondTeamPlayers = playerRepository
                    .Get()
                    .Where(p => p.TeamId == secondTeamId)
                    .ToList();

                var players = firstTeamPlayers.Concat(secondTeamPlayers);

                foreach (var player in players)
                {
                    var points = 0;
                    var activityType = GetRandomActivityType();
                    switch (activityType)
                    {
                        case PlayerActivity<string>.ActivityType.Playing:
                            points = GetRandomPoints();
                            break;
                        case PlayerActivity<string>.ActivityType.Reserve:
                            break;
                        case PlayerActivity<string>.ActivityType.Unused:
                            continue;
                    }

                    var playerActivity = new PlayerActivity<string>(player.Id, game.Id, points, activityType);
                    playerActivityRepository.Add(playerActivity);
                }
            }
        }

        public static void Main()
        {
            var teamRepository = new XmlRepository<string, Team<string>>("teams.xml");
            var playerRepository = new XmlRepository<string, Player<string>>("players.xml");
            var gameRepository = new XmlRepository<string, Game<string>>("games.xml");
            var playerActivityRepository = new XmlRepository<CompositeId<string>, PlayerActivity<string>>("activities.xml");
            
            PopulateTeams(teamRepository,playerRepository);
            PopulateGames(gameRepository, playerRepository, playerActivityRepository);
            
            var service = new CommonService(teamRepository, playerRepository, gameRepository, playerActivityRepository);
            var console = new ProgramConsole(service);
            console.Run();
        }
    }
}
