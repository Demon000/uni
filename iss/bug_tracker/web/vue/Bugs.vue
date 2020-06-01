<template>
    <div id="bugs-view">
        <nav-bar></nav-bar>
        <div id="bugs-content">
            <button id="bug-add-view-toggle" class="fab mdi" v-bind:class="{ 'adding': isAdding }" v-on:click="onAddViewToggleButtonClick"></button>
            <div id="bug-add-view-wrapper" v-bind:style="{ height: bugAddViewHeight }">
                <bug-form v-bind:mode="'add'"
                          v-on:add-success="onAddSuccess"
                          ref="bugAddView"></bug-form>
            </div>
            <bug-list
                    v-bind:title="'Open bugs'"
                    v-bind:status="'OPEN'"
                    v-bind:entries="10"
                    v-on:solve-success="loadBugs"
                    v-on:delete-success="loadBugs"
                    v-on:edit-success="loadBugs"
                    ref="openBugsCategory"
            ></bug-list>
            <bug-list
                    v-bind:title="'Solved bugs'"
                    v-bind:status="'SOLVED'"
                    v-bind:entries="10"
                    v-on:solve-success="loadBugs"
                    v-on:delete-success="loadBugs"
                    v-on:edit-success="loadBugs"
                    ref="solvedBugsCategory"
            ></bug-list>
        </div>
    </div>
</template>

<script>
    import Vue from 'vue';
    import { getAccessToken } from '../js/store';

    export default Vue.component('bugs', {
        data() {
            return {
                isAdding: false,
                bugAddViewHeight: '0px',
                sse: null,
            };
        },
        async mounted() {
            const accessToken = getAccessToken();
            try {
                this.sse = await this.$sse(`/api/bugs/sse?access_token=${accessToken}`, {
                    format: 'json'
                });
            } catch (e) {
                console.error(e);
                return;
            }

            this.sse.onError(e => {
                console.error(e);
            });

            const loadBugs = () => this.loadBugs();
            this.sse.subscribe('bug-add', loadBugs);
            this.sse.subscribe('bug-update', loadBugs);
            this.sse.subscribe('bug-delete', loadBugs);
        },
        methods: {
            setIsAdding(status) {
                this.isAdding = status;

                const bugAddView = this.$refs.bugAddView;
                let height = 0;
                if (this.isAdding) {
                    height = bugAddView.getHeight();
                }
                this.bugAddViewHeight = height + 'px';
            },
            onAddViewToggleButtonClick() {
                this.setIsAdding(!this.isAdding);
            },
            loadBugs() {
                this.$refs.openBugsCategory.loadBugs();
                this.$refs.solvedBugsCategory.loadBugs();
            },
            onAddSuccess() {
                this.loadBugs();
                this.setIsAdding(false);
            },
        },
    });
</script>

<style>
    #bugs-content {
        margin: 0 auto;
        max-width: 756px;

        padding: 52px 16px 0 16px;

        position: relative;
    }

    #bug-add-view-wrapper {
        transition: height 250ms;
        overflow: hidden;
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