<template>
    <div class="bugs-list">
        <p class="title">
            {{ title }}
        </p>

        <p v-if="!bugs.length">No bugs.</p>
        <bug-item
                v-for="bug of bugs"
                v-if="bug.status === status"
                v-bind:key="bug.id"
                v-bind:data="bug"
                v-bind:user="user"
                v-on:solve-click="solveBug(bug.id)"
                v-on:delete-click="deleteBug(bug.id)"
                v-on:finish-save="load()"
        ></bug-item>
    </div>
</template>

<script>
    import Vue from 'vue';
    import axios from 'axios';

    export default Vue.component('bugs-list', {
        props: ['title', 'status', 'user'],
        data: function() {
            return {
                bugs: [],
            };
        },
        mounted: function() {
            this.load();
        },
        methods: {
            load() {
                axios
                    .get('/api/bugs', {
                        params: {
                            status: this.status,
                        },
                    })
                    .then(response => {
                        this.bugs = response.data;
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
            solveBug(bugId) {
                axios
                    .post(`/api/bugs/${bugId}/solved`)
                    .then(() => {
                        this.load();
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
            deleteBug(bugId) {
                axios
                    .delete(`/api/bugs/${bugId}`)
                    .then(() => {
                        this.load();
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
        },
    });
</script>

<style>
    .bugs-list {
        margin-bottom: 32px;
    }

    .bugs-list > .title {
        color: rgba(255, 255, 255, 0.6);
    }
</style>
