<template>
    <div id="login-container">
        <div id="login">
            <div id="login-logo">
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
    import Vue from 'vue';

    export default Vue.component('login', {
        data() {
            return {
                username: '',
                password: '',
                error: '',
            };
        },
        props: {
            redirectFrom: {
                type: String,
                default: null,
            }
        },
        methods: {

        },
    });
</script>

<style>
    #login-container {
        min-width: 100%;
        min-height: 100vh;

        display: flex;
        justify-content: center;
        align-items: center;
    }

    #login {
        width: 100%;
        max-width: 520px;

        padding: 16px;

        border-radius: 4px;
        background: #1e1e1e;
    }

    #login-logo {
        font-size: 64px;
        text-align: center;
        margin-bottom: 32px;
    }

    #login-container .buttons-wrapper {
        text-align: center;
    }

    #login-error {
        font-size: 14px;
        color: #cf6679;
    }
</style>
