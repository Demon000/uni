import axios from 'axios';

export default class {
    constructor(api) {
        this.api = api;
    }

    getPath(sub_path) {
        let path = this.api.getPath('/races');
        if (sub_path) {
            path += sub_path;
        }
        return path;
    }

    getData(race) {
        const data = {};
        if (race.name) {
            data.name = race.name;
        }
        if (race.arbiter && race.arbiter.id) {
            data.arbiter = {};
            data.arbiter.id = race.arbiter.id;
        }
        return data;
    }

    async add(race) {
        const response = await axios.post(this.getPath('/'), this.getData(race));
        return response.data;
    }

    async find() {
        const response = await axios.get(this.getPath('/'));
        return response.data;
    }

    async update(race) {
        const response = await axios.patch(this.getPath(`/${race.id}`), this.getData(race));
        Object.assign(race, response.data);
        return response.data;
    }

    async delete(id) {
        await axios.delete(this.getPath(`/${id}`));
    }
}
