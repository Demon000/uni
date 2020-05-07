using Newtonsoft.Json;

namespace client_csharp.Domain
{
    public class Arbiter
    {
        [JsonProperty("id")]
        public int? Id { get; set; }

        [JsonProperty("name")]
        public string Name { get; set; }
        
        [JsonIgnore]
        public string Password { get; set; }
        
        public override string ToString()
        {
            return $"Arbiter{{Id={Id}, Name={Name}}}";
        }
    }
}
