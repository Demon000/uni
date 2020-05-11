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
    mode: 'history',
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
import BugList from '../vue/BugList.vue';
import BugItem from '../vue/BugItem.vue';
new Vue({
    router,
    store,
    el: '#app',
    components: {
        'bug-list': BugList,
        'bug-item': BugItem,
    },
});
