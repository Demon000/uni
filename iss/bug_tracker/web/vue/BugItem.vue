<template>
    <div class="bug-item common-item">
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
            user() {
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
