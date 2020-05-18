import '../css/ajax_5.css';

import Vue from 'vue';
import FileTree from './FileTree.vue';

new Vue({
    el: '#app',
    delimiters: ['${', '}'],
    components: {
        'file-tree': FileTree,
    },
    data: {
        rootPath: '/',
    },
});
