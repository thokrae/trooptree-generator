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

    let fs = require('fs');
    fs.readFile(file['path'], 'utf8', (err, data) => {
        if (err)
            return console.log(err);
        console.log(data);
    });

    return false;
};

interface TroopData {
    name: String;
    displayName: String;
    displayNamePlural: String;
    factionId: String;
    flags: Number;
    upgrade1: Number;
    upgrade2: Number;
    // strength: Number;
    // agility: Number;
    // intelligence: Number;
    // charisma: Number;
    // level: Number;
    // prof1h: Number;
    // prof2h: Number;
    // profPolearms: Number;
    // profArcher: Number;
    // profCrossbow: Number;
    // profThrowing: Number;
    // profFire: Number;
}

function getTroopData(input: String): TroopData {
    let lines: string[][] = [];
    input.split('\n').forEach((line, i) => lines.push(line.split(' ')));

    if (lines.length != 6)
        throw 'incomplete troop data: unexpected line count';

    return {
        name: lines[0][0],
        displayName: lines[0][1],
        displayNamePlural: lines[0][2],
        flags: parseInt(lines[0][3], 10),
        factionId: lines[0][6],
        upgrade1: parseInt(lines[0][7], 10),
        upgrade2: parseInt(lines[0][8], 10)
    };
}
