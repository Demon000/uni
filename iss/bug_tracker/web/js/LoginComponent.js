const LoginComponent = Vue.component('login-view', {
    template: '#login-view-template',
    data: function() {
        return {
            username: '',
            password: '',
            error: '',
        };
    },
    mounted: function() {
        axios
            .get('/api/auth/user')
            .then(response => {
                this.emitLogin(response.data);
            })
            .catch(error => {
                console.error(error);
            });
    },
    methods: {
        login: function() {
            this.setError(null);
            axios
                .post('/api/auth/login', {
                    username: this.username,
                    password: this.password
                })
                .then(response => {
                    this.emitLogin(response.data.user);
                })
                .catch(error => {
                    this.setError(error.response.data.message);
                });
        },
        emitLogin(user) {
            this.$router.app.$emit('login', {
                user,
            });
        },
        setError(message) {
            this.error = message;
        },
    },
});
