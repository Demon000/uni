import Vue from 'vue'
import Vuex from 'vuex'
import axios from 'axios'

Vue.use(Vuex)

export default new Vuex.Store({
    state: {
        user: null,
    },
    mutations: {
        loginStart(state) {
            state.user = null;
        },
        loginSuccess(state, user) {
            state.user = user;
        },
        loginError(state) {
            state.user = null;
        },
        logout(state) {
            state.user = null;
        },
    },
    actions: {
        newLogin: async function({ commit }, data) {
            commit('loginStart')
            let response;
            try {
                response = await axios.post('/api/auth/login', data);
            } catch (e) {
                commit('loginError');
                throw e;
            }

            const accessToken = response.data['access_token'];
            const user = response.data.user;
            localStorage.setItem('access_token', accessToken);
            axios.defaults.headers['Authorization'] = `Bearer ${accessToken}`;
            commit('loginSuccess', user);
        },
        refreshLogin: async function({ commit }) {
            commit('loginStart')
            const accessToken = localStorage.getItem('access_token');
            if (!accessToken) {
                commit('loginError');
                return;
            }

            axios.defaults.headers['Authorization'] = `Bearer ${accessToken}`;

            let response;
            try {
                response = await axios.get('/api/auth/user');
            } catch (e) {
                commit('loginError');
                return;
            }

            const user = response.data;
            commit('loginSuccess', user);
        },
    },
    getters: {
        isLoggedIn: state => !!state.user,
    },
});
