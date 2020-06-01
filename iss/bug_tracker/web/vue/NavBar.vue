<template>
    <div id="nav-bar">
        <div id="nav-bar-logo">
                <span class="logo-main-part">
                    Bug
                </span>
            <span class="logo-secondary-part">
                    Tracker
                </span>
        </div>
        <div id="nav-bar-user">
            <span id="nav-bar-user-username" v-if="user">{{ user.username }}</span>
            <i id="nav-bar-user-icon" class="mdi mdi-account-circle"></i>
        </div>
        <span id="nav-bar-logout" v-on:click="onLogoutButtonClick">LOGOUT</span>
    </div>
</template>

<script>
    import Vue from "vue";

    export default Vue.component('nav-bar',{
        computed: {
            user() {
                return this.$store.state.user;
            },
        },
        methods: {
            async onLogoutButtonClick() {
                await this.$store.dispatch('logout');
                await this.$router.replace({
                    name: 'login',
                });
            },
        }
    });
</script>

<style scoped>
    #nav-bar {
        height: 64px;
        line-height: 64px;
        font-size: 14px;

        padding: 0 16px;

        display: flex;
        flex-direction: row;
    }

    #nav-bar > * {
        margin: 0 8px;
    }

    #nav-bar-logo {
        font-size: 32px;
    }

    #nav-bar-user {
        margin-left: auto;
    }

    #nav-bar-user-username {
        padding: 0 8px;
    }

    #nav-bar-user-icon {
        font-size: 32px;
        vertical-align: middle;

        color: #bb86fc;
    }

    #nav-bar-logout {
        cursor: pointer;
    }
</style>