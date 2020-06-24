<template>
    <div class="login-container">
        <div class="login">
            <h1>Login</h1>

            <div>
                <label>Username</label>
                <input type="text" v-model="username">
            </div>

            <div>
                <label>Password</label>
                <input type="password" v-model="password" v-on:keyup.enter="login">
            </div>

            <button v-on:click="login">Login</button>
        </div>
    </div>
</template>

<script lang="ts">
    import 'reflect-metadata';
    import {Component, Prop, Vue} from 'vue-property-decorator';
    import store from '../ts/store';
    import router from '../ts/router';

    @Component
    export default class Login extends Vue {
        username: string = '';
        password: string = '';
        error: string = '';

        @Prop({
            default: undefined,
        })
        readonly redirectFrom: string | undefined;

        async login() {
            try {
                await store.dispatch('newLogin', {
                    username: this.username,
                    password: this.password,
                });
            } catch (e) {
                this.error = e.response.data.message;
                return;
            }

            try {
                if (this.redirectFrom == null) {
                    await router.replace({
                        name: 'game',
                    });
                } else {
                    await router.replace(this.redirectFrom);
                }
            } catch (e) {
                console.error(e);
            }
        }
    }
</script>

<style scoped>

</style>
