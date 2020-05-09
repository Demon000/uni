import VueRouter from 'vue-router';
import Vue from 'vue';

import Bugs from '../vue/Bugs.vue';
import Login from '../vue/Login.vue';

function loginRouteGuard(toRoute, fromRoute, next) {
    if (store.getters.isLoggedIn) {
        next();
        return;
    }

    next('login');
}

Vue.use(VueRouter);
const router = new VueRouter({
    routes: [
        {
            path: '/bugs',
            name: 'bugs',
            component: Bugs,
            beforeEnter: loginRouteGuard,
        },
        {
            path: '/login',
            name: 'login',
            component: Login,
        }
    ],
});

import store from './store';
import BugsList from "../vue/BugsList.vue";
import BugItem from "../vue/BugItem.vue";
new Vue({
    router,
    store,
    el: '#app',
    components: {
        'bugs-list': BugsList,
        'bug-item': BugItem,
    },
});
