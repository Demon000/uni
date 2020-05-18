import $ from 'jquery';

const useXHR = true;
const defaultOptions = {
    json: true,
};

export default class Request {
    static req_xhr(url, options) {
        return new Promise((resolve, reject) => {
            const req = new XMLHttpRequest();

            req.open(options.type, url, true);

            req.onload = () => {
                const status = req.status + '';
                if (status[0] === '2') {
                    resolve(req.response);
                } else {
                    reject({
                        error: req.statusText,
                        status: req.status,
                        response: req.response,
                    });
                }
            };

            req.onerror = () => {
                reject({
                    error: req.statusText,
                    status: req.status,
                });
            };

            if (options.json) {
                req.responseType = 'json';
            }

            if (options.data && options.json) {
                req.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
                options.data = JSON.stringify(options.data);
            }

            req.send(options.data);
        });
    }

    static req_jquery(url, options) {
        return new Promise((resolve, reject) => {
            const jqueryOptions = {
                type: options.type,
                data: options.data,
                success(response) {
                    resolve(response);
                },
                error(req) {
                    reject({
                        error: req.statusText,
                        status: req.status,
                        response: req.response,
                    });
                },
            };

            if (options.json) {
                jqueryOptions.dataType = 'json';
            }

            if (options.data && options.json) {
                jqueryOptions.contentType = 'application/json';
                jqueryOptions.data = JSON.stringify(options.data);
            }

            $.ajax(url, jqueryOptions);
        });
    }

    static req(url, options) {
        if (useXHR) {
            return this.req_xhr(url, options);
        } else {
            return this.req_jquery(url, options);
        }
    }

    static getOptions(options, overrideOptions) {
        options = options || {};
        return Object.assign({}, defaultOptions, options, overrideOptions);
    }

    static get(url, options) {
        const innerOptions = this.getOptions(options, {
            type: 'GET',
        });
        return this.req(url, innerOptions);
    }

    static patch(url, data, options={
        json: true,
    }) {
        const innerOptions = this.getOptions(options, {
            type: 'PATCH',
            data,
        });
        return this.req(url, innerOptions);
    }

    static post(url, data, options={
        json: true,
    }) {
        const innerOptions = this.getOptions(options, {
            type: 'POST',
            data,
        });
        return this.req(url, innerOptions);
    }
};
