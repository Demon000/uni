const VueLoaderPlugin = require('vue-loader/lib/plugin');

module.exports = {
    mode: 'development',
    entry: {
        index: __dirname + '/web/js/index.js',
    },
    output: {
        filename: '[name].js',
        path: __dirname + '/web/dist/'
    },
    module: {
        rules: [
            {
                test: /\.vue$/,
                loader: 'vue-loader',
            },
        ],
    },
    plugins: [
        new VueLoaderPlugin(),
    ],
    watch: true,
};
