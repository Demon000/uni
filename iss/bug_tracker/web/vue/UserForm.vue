<template>
    <div class="user-form">
        <div class="input-group">
            <label>Username</label>
            <input type="text" v-model="username">
        </div>

        <div class="input-group">
            <label>Password</label>
            <input type="password" v-model="password" v-on:keyup.enter="onFinishButtonClick">
        </div>

        <div class="buttons-wrapper">
            <button v-on:click="onFinishButtonClick">ADD USER</button>
        </div>
    </div>
</template>

<script>
    import Vue from "vue";

    export default Vue.component('user-form', {
        data() {
            return {
                username: '',
                password: '',
            };
        },
        methods: {
            onAddUserButtonClick() {
                this.$emit('-click');
            },
            getUsername() {
                return this.username;
            },
            getPassword() {
                return this.password;
            },
        }
    });
</script>

<style scoped>

</style>