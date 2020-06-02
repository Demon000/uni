# Bug Tracker

### Development setup
0. Make sure you have installed `mongod`, `nodejs` and `npm`.
1. Copy `config/example.json` to `config/dev.json`.
2. Open `config/dev.json` and configure the necessary fields.
3. Open a terminal and run the following commands.
4. `./mongod` to start the MongoDB database in `./data` directory.
5. `npm install` to install the dependencies.
6. `npm run webpack-dev` to start watching for changes in the JavaScript files.
7. `npm run start-dev` to start the development server and start watching for changes in the
server files.
