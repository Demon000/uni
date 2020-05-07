using System.Collections.Generic;
using System.Threading.Tasks;
using client_csharp.Domain;
using Newtonsoft.Json;

namespace client_csharp.Rest
{
    public class ArbitersResource
    {
        private readonly API _api;

        public ArbitersResource(API api)
        {
            _api = api;
        }

        public async Task<List<Arbiter>> Find()
        {
            var response = await _api.Client.GetAsync("arbiters");
            if (!response.IsSuccessStatusCode) return null;
            var responseString = await response.Content.ReadAsStringAsync();
            return JsonConvert.DeserializeObject<List<Arbiter>>(responseString);
        }
    }
}
