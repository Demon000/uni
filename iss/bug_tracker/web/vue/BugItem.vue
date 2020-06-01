<template>
    <div class="bug-item">
        <div class="content" v-if="!isEditing">
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
        </div>
        <bug-form v-else
                  v-bind:id="id"
                  v-bind:title="title"
                  v-bind:description="description"
                  v-bind:mode="'edit'"
                  v-on:edit-success="onEditSuccess"
                  v-on:edit-cancel="onCancelEditButtonClick"></bug-form>
    </div>
</template>

<script>
    import Vue from 'vue';
    import axios from 'axios';
    import moment from 'moment';

    export default Vue.component('bug-item', {
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
        data() {
            return {
                isEditing: false,
            };
        },
        methods: {
            formatDate(date) {
                return moment(date).format('dddd, MMMM Do YYYY, h:mm');
            },
            setIsEditing(status) {
                this.isEditing = status;
            },
            onSolveButtonClick() {
                axios
                    .post(`/api/bugs/${this.id}/solve`)
                    .then(() => {
                        this.$emit('solve-success');
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
            onDeleteButtonClick() {
                axios
                    .delete(`/api/bugs/${this.id}`)
                    .then(() => {
                        this.$emit('delete-success');
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
            onEditButtonClick() {
                this.setIsEditing(true);
            },
            onCancelEditButtonClick() {
                this.setIsEditing(false);
            },
            onEditSuccess() {
                this.$emit('edit-success');
                this.setIsEditing(false);
            },
        }
    });
</script>

<style scoped>
    .bug-item {
        margin-bottom: 16px;

        border-radius: 4px;
        background: #1e1e1e;

        position: relative;
    }
    .bug-item .content {
        padding: 8px;
    }
    .bug-item .content .title,
    .bug-item .content .secondary-title,
    .bug-item .content .description {
        margin: 0;
    }
    .bug-item .content .secondary-title {
        font-size: 0.875rem;
        font-weight: 400;
        line-height: 1.25rem;

        color: rgba(255, 255, 255, 0.6);
    }
    .bug-item .content .title {
        font-size: 1.25rem;
        font-weight: 500;
        line-height: 2rem;
    }
    .bug-item .content .description {
        margin: 16px 0 8px 0;
    }
    .bug-item .content .buttons {
        position: absolute;
        top: 0;
        right: 0;

        font-size: 18px;
        padding: 8px;
    }
    .bug-item .content .buttons .mdi {
        display: inline-block;
        width: 32px;
        height: 32px;
        line-height: 24px;
        text-align: center;
        padding: 4px;

        border-radius: 50%;
    }
    .bug-item .content .buttons .solve {
        color: #03dac6;
    }
    .bug-item .content .buttons .solve:hover {
        background: rgba(3, 218, 198, 0.06);
    }
    .bug-item .content .buttons .delete {
        color: #cf6679;
    }
    .bug-item .content .buttons .delete:hover {
        background: rgba(207, 102, 121, 0.06);
    }
    .bug-item .content .buttons .edit {
        color: #ffee58;
    }
    .bug-item .content .buttons .edit:hover {
        background: rgba(255, 238, 88, 0.06);
    }
</style>
