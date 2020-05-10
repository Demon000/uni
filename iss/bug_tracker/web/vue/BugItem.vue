<template>
    <div class="bug-item">
        <template v-if="!isEditing">
            <div class="buttons">
                <template v-if="data.status === 'OPEN'">
                    <template v-if="user.role === 'PROGRAMMER'">
                        <i class="solve mdi mdi-check" v-on:click="solveButtonClick"></i>
                    </template>
                    <i class="edit mdi mdi-pencil" v-on:click="editButtonClick"></i>
                    <i class="delete mdi mdi-delete" v-on:click="deleteButtonClick"></i>
                </template>
            </div>
            <p class="title">{{ data.title }}</p>
            <p class="secondary-title">
                <template v-if="data.status === 'OPEN'">
                    created by
                    {{ data.createdBy.username }}
                    at
                    {{ formatDate(data.createdAt) }}
                </template>
                <template v-else-if="data.status === 'SOLVED'">
                    solved by
                    {{ data.solvedBy.username }}
                    at
                    {{ formatDate(data.solvedAt) }}
                </template>
            </p>
            <p class="description">{{ data.description }}</p>
        </template>
        <template v-else>
            <div class="input-group">
                <label>Title</label>
                <input type="text" v-model="data.title">
            </div>

            <div class="input-group">
                <label>Description</label>
                <textarea v-model="data.description" rows="10"></textarea>
            </div>

            <div class="buttons-wrapper">
                <button v-on:click="saveButtonClick">SAVE BUG</button>
            </div>
        </template>
    </div>
</template>

<script>
    import Vue from 'vue';
    import axios from 'axios';
    import moment from 'moment';

    export default Vue.component('bug-item', {
        name: 'bug-item',
        props: [
            'data',
        ],
        computed: {
            user: function() {
                return this.$store.state.user;
            },
        },
        data: function() {
            return {
                isEditing: false,
            };
        },
        methods: {
            formatDate: function(date) {
                return moment(date).format('dddd, MMMM Do YYYY, h:mm');
            },
            solveButtonClick: function() {
                this.$emit('solve-click');
            },
            editButtonClick: function() {
                this.isEditing = true;
                this.$emit('edit-click');
            },
            saveButtonClick: function() {
                axios
                    .post(`/api/bugs/${this.data.id}`, this.data)
                    .then(() => {
                        this.$emit('after-save');
                        this.isEditing = false;
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
            deleteButtonClick: function() {
                this.$emit('delete-click');
            }
        }
    });
</script>

<style>
    .bug-item {
        margin-bottom: 16px;

        padding: 8px;

        border-radius: 4px;
        background: #1e1e1e;

        position: relative;
    }
    .bug-item > .title,
    .bug-item > .secondary-title,
    .bug-item > .description {
        margin: 0;
    }
    .bug-item > .secondary-title {
        font-size: 0.875rem;
        font-weight: 400;
        line-height: 1.25rem;

        color: rgba(255, 255, 255, 0.6);
    }
    .bug-item > .title {
        font-size: 1.25rem;
        font-weight: 500;
        line-height: 2rem;
    }
    .bug-item > .description {
        margin: 16px 0 8px 0;
    }
    .bug-item > .buttons {
        position: absolute;
        top: 0;
        right: 0;

        font-size: 18px;
        padding: 8px;
    }
    .bug-item .buttons-wrapper {
        text-align: right;
    }
    .bug-item > .buttons > .mdi {
        display: inline-block;
        width: 32px;
        height: 32px;
        line-height: 24px;
        text-align: center;
        padding: 4px;

        border-radius: 50%;
    }
    .bug-item > .buttons > .solve {
        color: #03dac6;
    }
    .bug-item > .buttons > .solve:hover {
        background: rgba(3, 218, 198, 0.06);
    }
    .bug-item > .buttons > .delete {
        color: #cf6679;
    }
    .bug-item > .buttons > .delete:hover {
        background: rgba(207, 102, 121, 0.06);
    }
    .bug-item > .buttons > .edit {
        color: #ffee58;
    }
    .bug-item > .buttons > .edit:hover {
        background: rgba(255, 238, 88, 0.06);
    }
</style>
