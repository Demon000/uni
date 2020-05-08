import axios from 'axios';
import Vue from "vue";

export default Vue.component('bugs-view', {
    template: '#bugs-view-template',
    props: ['user'],
    data: function () {
        return {
            isAdding: false,
            addBugTitle: '',
            addBugDescription: '',
        };
    },
    methods: {
        onAddViewToggleButtonClick: function () {
            this.isAdding = !this.isAdding;
        },
        addBug: function () {
            axios
                .post('/api/bugs', {
                    title: this.addBugTitle,
                    description: this.addBugDescription,
                })
                .then(() => {
                    this.$refs.openBugsCategory.load();
                    this.$refs.closedBugsCategory.load();
                })
                .catch(error => {
                    console.error(error);
                });
        },
    },
});
