import VueRouter from 'vue-router';
import Vue from 'vue';

import BugsComponent from './BugsComponent';
import LoginView from '../vue/Login.vue';

const routes = [
    {
        path: '/',
        redirect: '/login',
    },
    {
        path: '/bugs',
        name: 'bugs',
        component: BugsComponent,
        props: true,
    },
    {
        path: '/login',
        name: 'login',
        component: LoginView,
    },
];

Vue.use(VueRouter);
const router = new VueRouter({
    routes,
});

const app = new Vue({
    router,
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
