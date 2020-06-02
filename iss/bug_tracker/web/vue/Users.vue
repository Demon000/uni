<template>
    <div>
        <nav-bar></nav-bar>
        <div id="main-content">
            <user-item v-for="user in users" v-bind="user" v-bind:key="user.id"></user-item>
        </div>
    </div>
</template>

<script>
    import Vue from "vue";
    import axios from "axios";

    export default Vue.component('users',{
        data() {
            return {
                users: [],
            };
        },
        mounted() {
            this.loadUsers();
        },
        methods: {
            loadUsers() {
                axios
                    .get('/api/users')
                    .then(response => {
                        this.users = response.data;
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
        }
    });
</script>

<style scoped>
</style>
