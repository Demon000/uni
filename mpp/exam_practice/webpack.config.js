const path = require('path');

module.exports = {
    mode: 'development',
    entry: {
        index: path.resolve(__dirname, './client/ts/index.ts'),
    },
    output: {
        filename: '[name].js',
        path: path.resolve(__dirname, './client/dist/'),
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
            {
                test: /\.tsx?$/,
                use: 'ts-loader',
                exclude: /node_modules/,
            }
        ],
    },
    resolve: {
        alias: {
            vue: 'vue/dist/vue.esm.js',
        },
        extensions: [ '.tsx', '.ts', '.js', '.vue' ],
    },
    watch: true,
};
