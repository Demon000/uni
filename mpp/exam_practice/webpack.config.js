module.exports = {
    mode: 'development',
    entry: {
        index: __dirname + '/client/js/index.js',
    },
    output: {
        filename: '[name].js',
        path: __dirname + '/client/dist/'
    },
    module: {
        rules: [
            {
                test: /\.vue$/,
                loader: 'vue-loader',
            },
            {
                test: /\.css$/,
                use: [
                    'vue-style-loader',
                    'css-loader'
                ]
            },
        ],
    },
    resolve: {
        alias: {
            vue: 'vue/dist/vue.esm.js',
        },
    },
    watch: true,
};
