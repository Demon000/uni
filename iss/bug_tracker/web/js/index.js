import VueRouter from 'vue-router';
import Vue from 'vue';

import Bugs from '../vue/Bugs.vue';
import Login from '../vue/Login.vue';

const routes = [
    {
        path: '/',
        redirect: '/login',
    },
    {
        path: '/bugs',
        name: 'bugs',
        component: Bugs,
        props: true,
    },
    {
        path: '/login',
        name: 'login',
        component: Login,
    },
];

Vue.use(VueRouter);
const router = new VueRouter({
    routes,
});

import BugsList from "../vue/BugsList.vue";
import BugItem from "../vue/BugItem.vue";
const app = new Vue({
    router,
    components: {
        'bugs-list': BugsList,
        'bug-item': BugItem,
    },
}).$mount('#app');

app.$on('login', (data) => {
    router.replace({
        name: 'bugs',
        params: {
            user: data.user,
        },
    })
        .then(() => {})
        .catch(() => {});
});

router.push('/login')
    .then(() => {})
    .catch(() => {});
