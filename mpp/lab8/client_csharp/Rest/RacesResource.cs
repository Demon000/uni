using System;
using System.Collections.Generic;
using System.Net.Http;
using System.Net.Mime;
using System.Text;
using System.Threading.Tasks;
using client_csharp.Domain;
using Newtonsoft.Json;

namespace client_csharp.Rest
{
    public class RacesResource
    {
        private readonly API _api;

        public RacesResource(API api)
        {
            _api = api;
        }

        public async Task<Race> Add(string name, int? arbiterId)
        {
            var arbiter = new Arbiter {Id = arbiterId};
            var race = new Race {Name = name, Arbiter = arbiter};
            var requestString = JsonConvert.SerializeObject(race, new JsonSerializerSettings
            {
                NullValueHandling = NullValueHandling.Ignore
            });
            var content = new StringContent(requestString, Encoding.UTF8, MediaTypeNames.Application.Json);
            var response = await _api.Client.PostAsync("races", content);
            if (!response.IsSuccessStatusCode) return null;
            var responseString = await response.Content.ReadAsStringAsync();
            return JsonConvert.DeserializeObject<Race>(responseString);
        }

        public async Task<Race> FindById(int? id)
        {
            var response = await _api.Client.GetAsync($"races/{id}");
            if (!response.IsSuccessStatusCode) return null;
            var responseString = await response.Content.ReadAsStringAsync();
            return JsonConvert.DeserializeObject<Race>(responseString);
        }

        public async Task<List<Race>> Find()
        {
            var response = await _api.Client.GetAsync("races");
            if (!response.IsSuccessStatusCode) return null;
            var responseString = await response.Content.ReadAsStringAsync();
            return JsonConvert.DeserializeObject<List<Race>>(responseString);
        }
        
        public async Task<Race> Update(int? id, string name, int? arbiterId)
        {
            var arbiter = new Arbiter {Id = arbiterId};
            var race = new Race {Name = name, Arbiter = arbiter};
            var requestString = JsonConvert.SerializeObject(race, new JsonSerializerSettings
            {
                NullValueHandling = NullValueHandling.Ignore
            });
            var content = new StringContent(requestString, Encoding.UTF8, MediaTypeNames.Application.Json);
            var response = await _api.Client.PostAsync($"races/{id}", content);
            if (!response.IsSuccessStatusCode) return null;
            var responseString = await response.Content.ReadAsStringAsync();
            return JsonConvert.DeserializeObject<Race>(responseString);
        }
        
        public async Task<Race> Delete(int? id)
        {
            var response = await _api.Client.DeleteAsync($"races/{id}");
            if (!response.IsSuccessStatusCode) return null;
            var responseString = await response.Content.ReadAsStringAsync();
            return JsonConvert.DeserializeObject<Race>(responseString);
        }
    }
}
