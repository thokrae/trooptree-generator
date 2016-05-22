export module loader {

    interface TroopData {
        name: string;
        displayName: string;
        displayNamePlural: string;
        factionId: string;
        flags: number;
        upgrade1: number;
        upgrade2: number;
        // strength: number;
        // agility: number;
        // intelligence: number;
        // charisma: number;
        // level: number;
        // prof1h: number;
        // prof2h: number;
        // profPolearms: number;
        // profArcher: number;
        // profCrossbow: number;
        // profThrowing: number;
        // profFire: number;
    }

    interface TroopDataCollection {
        [index: number]: TroopData;
    }

    export function getTroopData(input: string) {
        console.log('starting to parse troop data');

        let lines = input.split('\n');

        if (lines.length < 1)
            throw 'invalid troop file';

        let version = getVersion(lines[0]);
        console.log('detected version: ' + version);

        let troopCount = parseInt(lines[1], 10);
        console.log('expecting ' + troopCount + ' entries');

        let result: TroopDataCollection = {};
        for (let troopId = 0; troopId < troopCount; ++troopId)
            result[troopId] = getTroopDataEntry(getNext6Lines(lines, troopId));

        console.log('finished parsing troop data');

        return result;
    }

    function getVersion(input: string): number {
        if (input === 'troopsfile version 1')
            return 1;
        if (input === 'troopsfile version 2')
            return 2;
        throw 'found invalid or not supported troop file';
    }

    function getNext6Lines(lines: string[], troopId: number) {
        var result: string[] = [];
        for (let i = 0; i < 6; ++i)
            result.push(lines[troopId * 7 + i + 2]);
        return result;
    }

    export function getTroopDataEntry(input: string[]): TroopData {
        let lines: string[][] = [];
        input.forEach((line, i) => lines.push(line.split(' ')));

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

}