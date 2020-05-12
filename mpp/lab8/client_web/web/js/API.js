export default class {
    constructor(host, port) {
        this.path = `${host}:${port}/api`;
    }

    getPath(sub_path) {
        let path = this.path;
        if (sub_path) {
            path += sub_path;
        }
        return path;
    }
}
