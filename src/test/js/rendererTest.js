it('jasmine is working', function(){ expect(true).toEqual(true); });

it('should return null', function(){
    var result = loadTroopData('');
    expect(result).toEqual(null);
});
