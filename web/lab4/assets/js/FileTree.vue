<template>
    <div class="file-tree" v-if="isLoaded">
        <span class="expand" v-on:click="onExpandClick">
            <template v-if="isDirectory && isOpen">
                -
            </template>
            <template v-else-if="isDirectory  && !isOpen">
                +
            </template>
        </span>
        <img v-bind:src="icon" alt="Icon">
        <span>{{ name }}</span>
        <div class="files" v-if="isDirectory">
            <file-tree v-for="file in files"
                       v-if="isOpen"
                       v-bind:key="file.path"
                       v-bind:path="file.path">
            </file-tree>
        </div>
    </div>
</template>

<script>
    import Request from "./Request";

    export default {
        name: 'file-tree',
        data() {
            return {
                name: '',
                type: '',
                mime: '',
                files: [],
                isOpen: false,
                isLoaded: false,
            };
        },
        props: [
            'path',
        ],
        computed: {
            icon() {
                if (!this.type) {
                    return '';
                }

                if (this.isDirectory) {
                    if (this.isOpen) {
                        return 'images/directory_open.png';
                    } else {
                        return 'images/directory_closed.png';
                    }
                } else {
                    return 'images/file.png';
                }
            },
            isHidden() {
                return this.name.startsWith('.');
            },
            isDirectory() {
                return this.type === 'directory';
            },
        },
        async mounted() {
            await this.loadFile();
        },
        methods: {
            async loadFile() {
                this.isLoaded = false;

                let response;
                try {
                    response = await Request.post(`/api/file_explorer/${this.path}`);
                } catch (e) {
                    console.error(e);
                    return;
                }

                this.name = response.name;
                this.type = response.type;
                this.mime = response.mime;
                this.files = response.files;
                this.isLoaded = true;
            },
            onExpandClick() {
                if (!this.isDirectory) {
                    return;
                }

                this.isOpen = !this.isOpen;
            },
        },
    };
</script>

<style>
    .file-tree {
        display: block;
    }
    .file-tree > .expand {
        display: inline-block;
        width: 14px;

        text-align: center;
        font-size: 18px;
        font-weight: bold;
        cursor: pointer;
    }
    .file-tree > .files {
        margin-left: 16px;
    }
</style>