<template>
    <div class="bug-list">
        <p class="title">
            {{ title }}
        </p>

        <p v-if="!bugs.length">No bugs.</p>
        <bug-item
                v-for="bug of bugs"
                v-if="bug.status === status"
                v-bind:key="bug.id"
                v-bind:data="bug"
                v-on:solve-click="solveBug(bug.id)"
                v-on:delete-click="deleteBug(bug.id)"
                v-on:after-save="loadBugs()"
        ></bug-item>
    </div>
</template>

<script>
    import Vue from 'vue';
    import axios from 'axios';

    export default Vue.component('bug-list', {
        props: [
            'title',
            'status'
        ],
        data: function() {
            return {
                bugs: [],
            };
        },
        mounted: function() {
            this.loadBugs();
        },
        methods: {
            loadBugs() {
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
                    .post(`/api/bugs/${bugId}/solve`)
                    .then(() => {
                        this.$emit('after-solve');
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
            deleteBug(bugId) {
                axios
                    .delete(`/api/bugs/${bugId}`)
                    .then(() => {
                        this.loadBugs();
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
        },
    });
</script>

<style>
    .bug-list {
        margin-bottom: 32px;
    }

    .bug-list > .title {
        color: rgba(255, 255, 255, 0.6);
    }
</style>
