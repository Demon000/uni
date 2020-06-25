const path = require('path');

const VueLoaderPlugin = require('vue-loader/lib/plugin');

module.exports = {
    mode: 'development',
    devtool: 'inline-source-map',
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
                    'css-loader',
                ]
            },
            {
                test: /\.tsx?$/,
                loader: 'ts-loader',
                exclude: /node_modules/,
                options: {
                    appendTsSuffixTo: [/\.vue$/],
                    configFile: "tsconfig.client.json",
                },
            }
        ],
    },
    plugins: [
        new VueLoaderPlugin(),
    ],
    resolve: {
        alias: {
            vue: 'vue/dist/vue.esm.js',
        },
        extensions: [ '.tsx', '.ts', '.js', '.vue' ],
    },
    watch: true,
};
