const getColor = require('./index');

console.time('response');

getColor((err, r, g, b) => {
	if (err) console.error(err);

	console.log('R:' + r, 'G:' + g, 'B:' + b);
	console.timeEnd('response');
});
