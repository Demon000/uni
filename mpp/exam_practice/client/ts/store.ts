import Vue from 'vue';
import Vuex from 'vuex';
import axios from 'axios';

Vue.use(Vuex);

enum LocalStorageItems {
    ACCESS_TOKEN_PAYLOAD = 'access_token_payload',
}

function setAuthorizationHeader(accessToken: string) {
    axios.defaults.headers.authorization = `Bearer ${accessToken}`;
}

function unsetAuthorizationHeader() {
    delete axios.defaults.headers.authorization;
}

function setAccessTokenPayload(accessToken: string) {
    localStorage.setItem(LocalStorageItems.ACCESS_TOKEN_PAYLOAD, accessToken);
}

export function getAccessTokenPayload() {
    return localStorage.getItem(LocalStorageItems.ACCESS_TOKEN_PAYLOAD);
}

function unsetAccessTokenPayload() {
    localStorage.removeItem(LocalStorageItems.ACCESS_TOKEN_PAYLOAD);
}

export default new Vuex.Store({
    state: {
        user: undefined,
    },
    mutations: {
        setUser(state, user) {
            state.user = user;
        },
        unsetUser(state) {
            state.user = undefined;
        },
    },
    actions: {
        async newLogin({ commit }, data) {
            commit('unsetUser');
            const response = await axios.post('/api/auth/login', data);
            const accessToken = response.data.access_token;
            const user = response.data.user;
            setAccessTokenPayload(accessToken)
            setAuthorizationHeader(accessToken);
            commit('setUser', user);
        },
        async refreshLogin({ commit }) {
            commit('unsetUser');
            const accessToken = getAccessTokenPayload();
            if (!accessToken) {
                throw new Error('Missing access token');
            }

            setAuthorizationHeader(accessToken);

            const response = await axios.get('/api/auth/user');
            const user = response.data;
            commit('setUser', user);
        },
        logout({ commit }) {
            unsetAccessTokenPayload();
            unsetAuthorizationHeader();
            commit('unsetUser');
        }
    },
});
