#!/usr/bin/env python3

from flask import Flask

from api.v1.api_v1 import api as api_v1

app = Flask(__name__)
app.register_blueprint(api_v1, url_prefix='/api/v1')
