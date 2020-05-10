<template>
    <div id="bugs-view">
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
        </div>
        <div id="bugs-content">
            <button id="bug-add-view-toggle" class="fab mdi" v-bind:class="{ 'adding': isAdding }" v-on:click="onAddViewToggleButtonClick"></button>
            <div id="bug-add-view" v-bind:class="{ 'adding': isAdding }">
                <div class="input-group">
                    <label>Title</label>
                    <input type="text" v-model="addBugTitle">
                </div>

                <div class="input-group">
                    <label>Description</label>
                    <textarea v-model="addBugDescription" rows="10"></textarea>
                </div>

                <div class="buttons-wrapper">
                    <button v-on:click="addBug">ADD BUG</button>
                </div>
            </div>
            <bug-list
                    v-bind:title="'Open bugs'"
                    v-bind:status="'OPEN'"
                    v-on:after-solve="loadBugs"
                    ref="openBugsCategory"
            ></bug-list>
            <bug-list
                    v-bind:title="'Solved bugs'"
                    v-bind:status="'SOLVED'"
                    v-on:after-solve="loadBugs"
                    ref="solvedBugsCategory"
            ></bug-list>
        </div>
    </div>
</template>

<script>
    import Vue from 'vue';
    import axios from 'axios';

    export default Vue.component('bugs', {
        data: function () {
            return {
                isAdding: false,
                addBugTitle: '',
                addBugDescription: '',
            };
        },
        computed: {
            user: function() {
                return this.$store.state.user;
            },
        },
        methods: {
            onAddViewToggleButtonClick() {
                this.isAdding = !this.isAdding;
            },
            addBug() {
                axios
                    .post('/api/bugs', {
                        title: this.addBugTitle,
                        description: this.addBugDescription,
                    })
                    .then(() => {
                        this.loadBugs();
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
            loadBugs() {
                this.$refs.openBugsCategory.loadBugs();
                this.$refs.solvedBugsCategory.loadBugs();
            },
        },
    });
</script>

<style>
    #nav-bar {
        height: 64px;
        line-height: 64px;

        padding: 0 16px;

        display: flex;
        flex-direction: row;
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

    #bugs-content {
        margin: 0 auto;
        max-width: 756px;

        padding: 52px 16px 0 16px;

        position: relative;
    }

    #bug-add-view {
        max-height: 0;
        transition: max-height 500ms;
        overflow: hidden;
    }
    #bug-add-view.adding {
        max-height: 100vh;
    }
    #bug-add-view .buttons-wrapper {
        text-align: right;
    }

    #bug-add-view-toggle {
        position: absolute;
        top: 0;
        right: 16px;

        background: #bb86fc;
    }
    #bug-add-view-toggle.adding {
        background: #cf6679;
    }
    #bug-add-view-toggle::before {
        content: "\F0412";
    }
    #bug-add-view-toggle.adding::before {
        content: "\F0156";
    }
</style>