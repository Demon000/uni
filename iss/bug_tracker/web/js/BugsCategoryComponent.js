const BugsCategoryComponent = Vue.component('bugs-category-view', {
    template: '#bugs-category-view-template',
    props: ['title', 'status', 'user'],
    data: function() {
        return {
            bugs: [],
        };
    },
    mounted: function() {
        this.load();
    },
    methods: {
        load() {
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
        solveBug(bugId) {
            axios
                .post(`/api/bugs/${bugId}/solved`)
                .then(response => {
                    this.load();
                })
                .catch(error => {
                    console.error(error);
                });
        },
        deleteBug(bugId) {
            axios
                .delete(`/api/bugs/${bugId}`)
                .then(response => {
                    this.load();
                })
                .catch(error => {
                    console.error(error);
                });
        },
    },
});
