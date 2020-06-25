import Vue from 'vue';
import VueRouter from 'vue-router';

import store from './store';

Vue.use(VueRouter);

import {NavigationGuardNext, Route} from 'vue-router/types/router';
async function loginRouteGuard(toRoute: Route, fromRoute: Route, next: NavigationGuardNext) {
    if (store.getters.isLoggedIn) {
        next();
    }
    try {
        await store.dispatch('refreshLogin');
        next();
    } catch (e) {
        next({
            name: 'login',
            query: {
                redirectFrom: toRoute.fullPath
            },
        });
    }
}

import Login from '../vue/Login.vue';
import Game from '../vue/Game.vue';
export default new VueRouter({
    mode: 'history',
    routes: [
        {
            path: '/',
            name: 'game',
            component: Game,
            beforeEnter: loginRouteGuard,
        },
        {
            path: '/login',
            name: 'login',
            component: Login,
        }
    ],
});
