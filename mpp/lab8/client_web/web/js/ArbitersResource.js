import axios from 'axios';

export default class {
    constructor(api) {
        this.api = api;
    }

    async find() {
        const response = await axios.get(this.api.getPath('/arbiters'));
        return response.data;
    }
}
