<template>
    <div class="user-item">
        <div class="content" v-if="!isEditing">
            <p class="title">{{ username }}</p>
            <p class="secondary-title">
                created at
                {{ formatDate(createdAt) }}
            </p>
        </div>

    </div>
</template>

<script>
    import Vue from "vue";
    import moment from "moment";

    export default Vue.component('user-item', {
        props: [
            'id',
            'username',
            'createdAt',
        ],
        methods: {
            formatDate(date) {
                return moment(date).format('dddd, MMMM Do YYYY, h:mm');
            },
        }
    });
</script>

<style scoped>
    .user-item {
        margin-bottom: 16px;

        border-radius: 4px;
        background: #1e1e1e;
    }
    .user-item .content .title,
    .user-item .content .secondary-title {
        margin: 0;
    }
    .user-item .content {
        padding: 8px;
    }
    .user-item .content .title {
        font-size: 1.25rem;
        font-weight: 500;
        line-height: 2rem;
    }
    .user-item .content .secondary-title {
        font-size: 0.875rem;
        font-weight: 400;
        line-height: 1.25rem;

        color: rgba(255, 255, 255, 0.6);
    }
</style>