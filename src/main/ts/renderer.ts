// This file is required by the index.html file and will
// be executed in the renderer process for that window.
// All of the Node.js APIs are available in this process.

let holder = document.getElementById('holder');
holder.ondragover = () => {
    return false;
};

holder.ondragleave = holder.ondragend = () => {
    return false;
};

holder.ondrop = (e) => {
    e.preventDefault();
    let file = e.dataTransfer.files[0];
    console.log('File you dragged here is', file['path']);

    const fs = require('fs');
    fs.readFile(file['path'], 'utf8', (err, data) => {
        if (err)
            return console.log(err);
        console.log(data);
    });

    return false;
};
