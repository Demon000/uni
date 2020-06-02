import Vue from 'vue';
import store from './store';

import Bugs from '../vue/Bugs.vue';
import Login from '../vue/Login.vue';

async function loginRouteGuard(toRoute, fromRoute, next) {
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

import VueRouter from 'vue-router';
Vue.use(VueRouter);
const router = new VueRouter({
    mode: 'history',
    routes: [
        {
            path: '/',
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

import VueSSE from 'vue-sse';
Vue.use(VueSSE);

import NavBar from '../vue/NavBar.vue';
import BugForm from '../vue/BugForm.vue';
import BugList from '../vue/BugList.vue';
import BugItem from '../vue/BugItem.vue';
new Vue({
    router,
    store,
    el: '#app',
    components: {
        'nav-bar': NavBar,
        'bug-list': BugList,
        'bug-item': BugItem,
        'bug-form': BugForm,
    },
});
