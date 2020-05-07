using Newtonsoft.Json;

namespace client_csharp.Domain
{
    public class Race
    {
        [JsonProperty("id")]
        public int? Id { get; set; }
        
        [JsonProperty("name")]
        public string Name { get; set; }
        
        [JsonProperty("arbiter")]
        public Arbiter Arbiter { get; set; }

        public override string ToString()
        {
            return $"Race{{Id={Id}, Name={Name}, Arbiter={Arbiter}}}";
        }
    }
}
