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
        component: LoginComponent,
    },
];

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
    });
});

router.push('/login')
    .then(() => {})
    .catch(() => {});
