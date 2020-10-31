from flask import Blueprint, jsonify

api = Blueprint('api_v1', __name__)


@api.route('/about')
def api_v1_about():
    return jsonify({
        'hello': 'world',
        'description': 'Version 1 API endpoint',
        'version': 1.0,
    })
