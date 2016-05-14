it('jasmine is working', function(){ expect(true).toEqual(true); });

it('should load version 1 troop entry', function(){
    var entry = "trp_swadian_militia Swadian_Militia Swadian_Militia 67108864 0 0 6 618 618\n" //
    + "124 0 269 0 270 0 328 0 400 0 374 0 194 0 156 0 235 0 236 0 232 0 138 0 133 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 -1 0 \n" //
    + "1 2 3 4 5\n" //
    + "7 11 7 12 8 13 10\n" //
    + "274 131072 0 1 0 0\n" //
    + "17179869185 1315051091194281984 1835136 0 50465891015 7916447985573822463 2031036 0 ";  

    var result = getTroopData(entry);
    
    var expected = {
         name: 'trp_swadian_militia',
         displayName: 'Swadian_Militia',
         displayNamePlural: 'Swadian_Militia',
         flags: 67108864,
         factionId: '6',
         upgrade1: 618,
         upgrade2: 618
        };
    expect(result).toEqual(expected);
});
