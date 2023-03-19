const fs = require('fs');
const { getExecOperator } = require('./exe');

class Downloader {
    constructor() {
    };

    async downLoad(file) {
        console.log(file)
        const exeClass = await getExecOperator();
        const mime_type = await this.createMIME(file.type);
        const text  = fs.readFileSync('/home/i/Server/server/' + exeClass.toServerFname(file));
        console.log('text')
        console.log(text);
        return text;
    };

    createMIME(type) {
        switch(type) {
            case 'TXT':
            case 'C':
            case 'CPP':
            case 'SQL':
            case 'Java':
            case 'CSS':
                return 'text/plain';
            case 'EXE':
                return 'application/octet-stream';
            case 'HTML':
                return 'text/html';
            default:
                return null;
        }
    };
};

const dl = new Downloader();
module.exports = dl;