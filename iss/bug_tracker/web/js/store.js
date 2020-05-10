import Vue from 'vue';
import Vuex from 'vuex';
import axios from 'axios';

Vue.use(Vuex);

function setAccessToken(accessToken) {
    axios.defaults.headers.authorization = `Bearer ${accessToken}`;
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
        newLogin: async function({ commit }, data) {
            commit('unsetUser');
            let response;
            try {
                response = await axios.post('/api/auth/login', data);
            } catch (e) {
                return;
            }

            const accessToken = response.data.access_token;
            const user = response.data.user;
            localStorage.setItem('access_token', accessToken);
            setAccessToken(accessToken);
            commit('setUser', user);
        },
        refreshLogin: async function({ commit }) {
            commit('unsetUser');
            const accessToken = localStorage.getItem('access_token');
            if (!accessToken) {
                return;
            }

            setAccessToken(accessToken);

            let response;
            try {
                response = await axios.get('/api/auth/user');
            } catch (e) {
                return;
            }

            const user = response.data;
            commit('setUser', user);
        },
    },
    getters: {
        isLoggedIn: state => !!state.user,
    },
});
