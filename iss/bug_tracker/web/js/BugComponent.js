import Vue from 'vue';
import axios from 'axios';
import moment from 'moment';

export default Vue.component('bug-view', {
    template: '#bug-view-template',
    props: ['data', 'user'],
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
                    this.$emit('finish-save');
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
