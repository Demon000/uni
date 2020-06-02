<template>
    <div class="user-item common-item">
        <div class="content">
            <p class="title">{{ username }}</p>
            <p class="secondary-title">
                {{ role }}
                <br>
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
            'role',
        ],
        methods: {
            formatDate(date) {
                return moment(date).format('dddd, MMMM Do YYYY, h:mm');
            },
        }
    });
</script>
