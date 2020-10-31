# Server


## Prerequisites
1\. [Python 3.8](https://www.python.org/downloads/)

2\. [MongoDB](https://docs.mongodb.com/manual/administration/install-community/)
    - [Add the mongod.exe executable to your PATH environment variable](https://docs.microsoft.com/en-us/azure/virtual-machines/windows/install-mongodb#configure-the-vm-and-mongodb)
    so you can use it anywhere
    
## Setup

Start a terminal in the server directory and run the following command(s).

1\. Create a python3.8 local environment
(only on first setup, no need to do when server gets updated)
```
python3.8 -m venv venv
```

2\. Use the local environment
(steps explained in running the app section)

3\. Update the packages
```
pip install -r requirements.txt
```

## Running the app
1\. Start the database

Start a terminal in the server directory and run the following command(s).

Windows:
```
mongod.exe --config=mongo.config
```

Linux:
```
mongod --config=mongo.config
```

2\. Start the app
 
Start a terminal in the server directory and run the following command(s).

a) Use the local environment

Windows (cmd):
```
.\venv\Scripts\activate.bat
```

Windows (PowerShell):
```
.\venv\Scripts\Activate.ps1
```

Linux (bash):
```
./venv/bin/activate
```

Linux (fish):
```
./venv/bin/activate.fish
```

b) Launch the app

Windows (cmd):
```
set FLASK_APP=app.py
set FLASK_ENV=development
flask run
```

Windows (PowerShell):
```
$env:FLASK_APP = "app.py"
$env:FLASK_ENV = development
flask run
```

Linux (bash / fish):
```
FLASK_APP=app.py FLASK_ENV=development flask run
```
