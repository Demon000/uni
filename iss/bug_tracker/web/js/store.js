import Vue from 'vue';
import Vuex from 'vuex';
import axios from 'axios';

Vue.use(Vuex);

function setAuthorizationHeader(accessToken) {
    axios.defaults.headers.authorization = `Bearer ${accessToken}`;
}

function unsetAuthorizationHeader() {
    delete axios.defaults.headers.authorization;
}

function setToken(accessToken) {
    localStorage.setItem('access_token', accessToken);
}

function getToken() {
    return localStorage.getItem('access_token');
}

function unsetToken() {
    localStorage.removeItem('access_token');
}

export default new Vuex.Store({
    state: {
        user: null,
    },
    mutations: {
        setUser(state, user) {
            state.user = user;
        },
        unsetUser(state) {
            state.user = null;
        },
    },
    actions: {
        async newLogin({ commit }, data) {
            commit('unsetUser');
            let response;
            try {
                response = await axios.post('/api/auth/login', data);
            } catch (e) {
                return;
            }

            const accessToken = response.data.access_token;
            const user = response.data.user;
            setToken(accessToken)
            setAuthorizationHeader(accessToken);
            commit('setUser', user);
        },
        async refreshLogin({ commit }) {
            commit('unsetUser');
            const accessToken = getToken();
            if (!accessToken) {
                return;
            }

            setAuthorizationHeader(accessToken);

            let response;
            try {
                response = await axios.get('/api/auth/user');
            } catch (e) {
                return;
            }

            const user = response.data;
            commit('setUser', user);
        },
        logout({ commit }) {
            unsetToken();
            unsetAuthorizationHeader();
            commit('unsetUser');
        }
    },
    getters: {
        isLoggedIn: state => !!state.user,
    },
});
