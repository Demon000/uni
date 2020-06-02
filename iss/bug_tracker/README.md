# Bug Tracker

### Development setup
0. Make sure you have installed `mongod`, `nodejs` and `npm`.
1. Open a terminal and run the following commands.
2. `./mongod` to start the MongoDB database in `./data` directory.
3. Copy `config/example.json` to `config/dev.json`.
4. Open `config/dev.json` and configure the necessary fields. 
2. `npm install` to install the dependencies.
3. `npm run webpack-dev` to start watching for changes in the JavaScript files.
4. `npm run start-dev` to start the development server and start watching for changes in the
server files.
