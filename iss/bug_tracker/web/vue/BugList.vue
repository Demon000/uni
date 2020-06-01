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
                v-bind="bug"
                v-on:solve-success="onSolveSuccess"
                v-on:delete-success="onDeleteSuccess"
                v-on:edit-success="onEditSuccess"
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
            onSolveSuccess() {
                this.$emit('solve-success');
            },
            onDeleteSuccess() {
                this.$emit('delete-success');
            },
            onEditSuccess() {
                this.$emit('edit-success');
            }
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
