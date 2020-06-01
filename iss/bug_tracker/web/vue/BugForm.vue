<template>
    <div class="bug-form" ref="bugForm">
        <div class="input-group">
            <label>Title</label>
            <input type="text" v-model="detachedTitle">
        </div>

        <div class="input-group">
            <label>Description</label>
            <textarea v-model="detachedDescription" rows="10"></textarea>
        </div>

        <div class="buttons-wrapper">
            <template v-if="mode === 'add'">
                <button v-on:click="onAddButtonClick">ADD BUG</button>
            </template>
            <template v-else-if="mode === 'edit'">
                <button v-on:click="onCancelEditButtonClick">CANCEL</button>
                <button v-on:click="onSaveEditButtonClick">SAVE BUG</button>
            </template>
        </div>
    </div>
</template>

<script>
    import Vue from "vue";
    import axios from "axios";

    export default Vue.component('bug-form', {
        name: 'bug-form',
        props: {
            id: {
                type: String,
                default: '',
            },
            title: {
                type: String,
                default: '',
            },
            description: {
                type: String,
                default: '',
            },
            mode: {
                type: String,
            },
        },
        data() {
            return {
                detachedTitle: '',
                detachedDescription: '',
            };
        },
        mounted() {
            this.detachedTitle = this.title;
            this.detachedDescription = this.description;
        },
        methods: {
            clearInputs() {
                this.detachedTitle = '';
                this.detachedDescription = '';
            },
            onAddButtonClick() {
                axios
                    .post('/api/bugs', {
                        title: this.detachedTitle,
                        description: this.detachedDescription,
                    })
                    .then(() => {
                        this.clearInputs();
                        this.$emit('add-success');
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
            onSaveEditButtonClick() {
                axios
                    .post(`/api/bugs/${this.id}`, {
                        title: this.detachedTitle,
                        description: this.detachedDescription,
                    })
                    .then(() => {
                        this.$emit('edit-success');
                    })
                    .catch(error => {
                        console.error(error);
                    });
            },
            onCancelEditButtonClick() {
                this.$emit('edit-cancel');
            },
            getHeight() {
                return this.$refs.bugForm.offsetHeight;
            },
        }
    });
</script>

<style scoped>
    .bug-form {
        padding: 8px;

        border-radius: 4px;
        background: #1e1e1e;
    }
    .bug-form .buttons-wrapper {
        text-align: right;
    }
</style>