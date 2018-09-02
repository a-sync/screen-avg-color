const getColor = require('./index');

console.time('scale 10%');
getColor((err, r, g, b) => {
    if (err) console.error(err);

    console.log('\nR:' + r, 'G:' + g, 'B:' + b);
    console.timeEnd('scale 10%');
});

console.time('scale 100%');
getColor((err, r, g, b) => {
    if (err) console.error(err);

    console.log('\nR:' + r, 'G:' + g, 'B:' + b);
    console.timeEnd('scale 100%');
}, {x:0, y:0, width:0, height:0, scale:100});
