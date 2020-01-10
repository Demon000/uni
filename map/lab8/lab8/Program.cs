using System;
using lab8.domain;
using lab8.repository;

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

        static void PopulateTeams(Repository<string, Team<string>> teamRepository)
        {
            teamRepository.Clear();
            for (var teamId = 0; teamId < TeamNames.Length; teamId++)
            {
                teamRepository.Add(new Team<string>(teamId.ToString(), TeamNames[teamId], SchoolNames[teamId]));
            }
        }

        private static void PopulatePlayers(XmlRepository<string, Player<string>> playerRepository)
        {
            var rnd = new Random();
            var playerId = 0;

            playerRepository.Clear();

            for (var teamId = 0; teamId < TeamNames.Length; teamId++)
            {
                for (var i = 0; i < 15; i++)
                {
                    var firstNameIndex = rnd.Next(FirstNames.Length);
                    var firstName = FirstNames[firstNameIndex];
                    var lastNameIndex = rnd.Next(LastNames.Length);
                    var lastName = LastNames[lastNameIndex];
                    var player = new Player<string>(playerId.ToString(), teamId.ToString(), $"{firstName} {lastName}");
                    playerRepository.Add(player);
                    playerId++;
                }
            }
        }
        
        public static void Main(string[] args)
        {
            var teamRepository = new XmlRepository<string, Team<string>>("teams.xml");
            var playerRepository = new XmlRepository<string, Player<string>>("players.xml");

            /*PopulateTeams(teamRepository);
            PopulatePlayers(playerRepository);*/
        }
    }
}
