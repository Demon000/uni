<template>
    <div class="bug-list">
        <p class="title">
            {{ title }}
        </p>

        <template v-if="bugs.length">
            <bug-item
                    v-for="bug of bugs"
                    v-if="bug.status === status"
                    v-bind:key="bug.id"
                    v-bind="bug"
                    v-on:solve-success="onSolveSuccess"
                    v-on:delete-success="onDeleteSuccess"
                    v-on:edit-success="onEditSuccess"
            ></bug-item>

            <div class="buttons">
                <button class="prev" v-bind:disabled="before <= 0" v-on:click="onPrevPageClick">PREVIOUS PAGE</button>
                <span class="info">{{ before + 1 }} - {{ Math.min(before + entries, count) }} / {{ count }}</span>
                <button class="next" v-bind:disabled="after <= 0" v-on:click="onNextPageClick">NEXT PAGE</button>
            </div>
        </template>
        <template v-else>
            <p v-if="!bugs.length">
                No bugs.
            </p>
        </template>
    </div>
</template>

<script>
    import Vue from 'vue';
    import axios from 'axios';

    export default Vue.component('bug-list', {
        props: [
            'title',
            'status',
            'entries',
        ],
        data: function() {
            return {
                bugs: [],
                page: 0,
                pages: 0,
                before: 0,
                after: 0,
                count: 0,
            };
        },
        mounted: function() {
            this.loadBugs();
        },
        methods: {
            loadBugs() {
                axios
                    .get(`/api/bugs?page=${this.page}&entries=${this.entries}`, {
                        params: {
                            status: this.status,
                        },
                    })
                    .then(response => {
                        this.count = response.data.count;
                        this.before = response.data.before;
                        this.after = response.data.after;
                        this.bugs = response.data.data;
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
            onNextPageClick() {
                this.page++;
                this.loadBugs();
            },
            onPrevPageClick() {
                this.page--;
                this.loadBugs();
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

    .bug-list > .buttons {
        display: flex;
    }
    .bug-list > .buttons .prev {
        margin-right: auto;
    }
    .bug-list > .buttons .next {
        margin-left: auto;
    }
    .bug-list > .buttons .info {
        margin: 0 auto;
        color: rgba(255, 255, 255, 0.26);
        line-height: 36px;
        font-size: 14px;
    }
</style>
