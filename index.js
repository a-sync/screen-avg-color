const addon = require('./build/Release/screen_avg_color');

module.exports = (callback, {x=0, y=0, width=0, height=0, scale=10} = {}) => {
    addon(callback, x, y, width, height, scale);
};
