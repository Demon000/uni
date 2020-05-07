using System;
using System.Collections.Generic;
using System.Configuration;
using client_csharp.Domain;
using client_csharp.Rest;

namespace client_csharp
{
    class Program
    {
        private static API _api;
        private static ArbitersResource _arbitersResource;
        private static RacesResource _racesResource;

        private static string GetConfig(string key, string value)
        {
            return ConfigurationManager.AppSettings[key] ?? value;
        }

        private static int GetIntegerConfig(string key, int value)
        {
            return ConfigurationManager.AppSettings[key] != null ?
                int.Parse(ConfigurationManager.AppSettings[key]) : value;
        }

        private static void PrintArbiters(List<Arbiter> arbiters)
        {
            arbiters.ForEach(Console.WriteLine);
            Console.WriteLine();
        }
        
        private static void TryPrintAllArbiters()
        {
            try
            {
                var arbiters = _arbitersResource.Find().Result;
                if (arbiters == null)
                {
                    Console.WriteLine("Failed to find arbiters");
                    return;
                }

                PrintArbiters(arbiters);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }

        private static void PrintRaces(List<Race> races)
        {
            races.ForEach(Console.WriteLine);
            Console.WriteLine();
        }
        
        private static void TryPrintAllRaces()
        {
            try
            {
                var races = _racesResource.Find().Result;
                if (races == null)
                {
                    Console.WriteLine("Failed to find races");
                    return;
                }

                PrintRaces(races);
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
            }
        }

        public static Race TryAddRace(string name, int? arbiterId)
        {
            try
            {
                return _racesResource.Add(name, arbiterId).Result;
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return null;
            }
        }
        
        public static Race TryFindRaceById(int? id)
        {
            try
            {
                return _racesResource.FindById(id).Result;
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return null;
            }
        }
        
        public static Race TryUpdateRace(int? id, string name, int? arbiterId)
        {
            try
            {
                return _racesResource.Update(id, name, arbiterId).Result;
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return null;
            }
        }
        
        public static Race TryDeleteRace(int? id)
        {
            try
            {
                return _racesResource.Delete(id).Result;
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return null;
            }
        }
        
        private static void Main(string[] args)
        {
            _api = new API(GetConfig("serverHost", "localhost"),
                GetIntegerConfig("serverPort", 8080));
            _arbitersResource = new ArbitersResource(_api);
            _racesResource = new RacesResource(_api);
            
            Console.WriteLine("All arbiters");
            TryPrintAllArbiters();
            
            Console.WriteLine("All races");
            TryPrintAllRaces();

            Race race;

            race = TryAddRace("FANCY_CYCLING", 1);
            if (race == null)
            {
                Console.WriteLine("Failed to add race");
                Environment.Exit(-1);
            }
            Console.WriteLine("Added: " + race);
            
            Console.WriteLine("All races after add");
            TryPrintAllRaces();
            
            race = TryFindRaceById(race.Id);
            if (race == null)
            {
                Console.WriteLine("Failed to find race");
                Environment.Exit(-1);
            }
            Console.WriteLine("Found: " + race);

            race = TryUpdateRace(race.Id, "FANCY_CYCLING_CHANGED", 2);
            if (race == null)
            {
                Console.WriteLine("Failed to update race");
                Environment.Exit(-1);
            }
            Console.WriteLine("Updated: " + race);
            
            Console.WriteLine("All races after update");
            TryPrintAllRaces();
            
            race = TryDeleteRace(race.Id);
            if (race == null)
            {
                Console.WriteLine("Failed to delete race");
                Environment.Exit(-1);
            }
            Console.WriteLine("Deleted: " + race);
            
            Console.WriteLine("All races after delete");
            TryPrintAllRaces();
        }
    }
}
