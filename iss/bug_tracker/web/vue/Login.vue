<template>
    <div id="login-view-container">
        <div id="login-view">
            <div id="login-view-logo">
                    <span class="logo-main-part">
                        Bug
                    </span>
                <span class="logo-secondary-part">
                        Tracker
                    </span>
            </div>

            <div class="input-group">
                <label>Username</label>
                <input type="text" v-model="username">
            </div>

            <div class="input-group">
                <label>Password</label>
                <input type="password" v-model="password" v-on:keyup.enter="login">
            </div>

            <p id="login-error" v-if="error">{{ error }}</p>

            <div class="buttons-wrapper">
                <button v-on:click="login">Login</button>
            </div>
        </div>
    </div>
</template>

<script>
    import axios from "axios";

    export default {
        name: 'login-view',
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
    };
</script>

<style>
    #login-view-container {
        min-width: 100%;
        min-height: 100vh;

        display: flex;
        justify-content: center;
        align-items: center;
    }

    #login-view {
        width: 100%;
        max-width: 520px;

        padding: 16px;

        border-radius: 4px;
        background: #1e1e1e;
    }

    #login-view-logo {
        font-size: 64px;
        text-align: center;
        margin-bottom: 32px;
    }

    #login-view-container .buttons-wrapper {
        text-align: center;
    }

    #login-error {
        font-size: 14px;
        color: #cf6679;
    }
</style>
