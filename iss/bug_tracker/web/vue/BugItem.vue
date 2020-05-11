<template>
    <div class="bug-item">
        <template v-if="!isEditing">
            <div class="buttons">
                <template v-if="status === 'OPEN'">
                    <template v-if="user.role === 'PROGRAMMER'">
                        <i class="solve mdi mdi-check" v-on:click="onSolveButtonClick"></i>
                    </template>
                    <i class="edit mdi mdi-pencil" v-on:click="onEditButtonClick"></i>
                    <i class="delete mdi mdi-delete" v-on:click="onDeleteButtonClick"></i>
                </template>
            </div>
            <p class="title">{{ title }}</p>
            <p class="secondary-title">
                created by
                {{ createdBy.username }}
                at
                {{ formatDate(createdAt) }}

                <template v-if="status === 'SOLVED'">
                    <br>
                    solved by
                    {{ solvedBy.username }}
                    at
                    {{ formatDate(solvedAt) }}
                </template>
            </p>
            <p class="description">{{ description }}</p>
        </template>
        <template v-else>
            <div class="input-group">
                <label>Title</label>
                <input type="text" v-model="editedTitle">
            </div>

            <div class="input-group">
                <label>Description</label>
                <textarea v-model="editedDescription" rows="10"></textarea>
            </div>

            <div class="buttons-wrapper">
                <button v-on:click="onCancelEditButtonClick">CANCEL</button>
                <button v-on:click="onSaveEditButtonClick">SAVE BUG</button>
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
            'id',
            'title',
            'description',
            'status',
            'createdBy',
            'createdAt',
            'solvedBy',
            'solvedAt',
        ],
        computed: {
            user: function() {
                return this.$store.state.user;
            },
        },
        data: function() {
            return {
                isEditing: false,
                editedTitle: '',
                editedDescription: '',
            };
        },
        methods: {
            formatDate: function(date) {
                return moment(date).format('dddd, MMMM Do YYYY, h:mm');
            },
            onSolveButtonClick: function() {
                this.$emit('solve-click');
            },
            onEditButtonClick: function() {
                this.editedTitle = this.title;
                this.editedDescription = this.description;
                this.isEditing = true;
                this.$emit('edit-click');
            },
            onSaveEditButtonClick: function() {
                axios
                    .post(`/api/bugs/${this.id}`, {
                        title: this.editedTitle,
                        description: this.editedDescription,
                    })
                    .then(() => {
                        this.isEditing = false;
                        this.$emit('after-save');
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
            onCancelEditButtonClick: function() {
                this.isEditing = false;
            },
            onDeleteButtonClick: function() {
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
