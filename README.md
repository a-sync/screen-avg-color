# screen-avg-color [![npm (scoped)](https://img.shields.io/npm/v/screen-avg-color.svg)](https://www.npmjs.com/package/screen-avg-color) 
Native nodejs module to return the average RGB color of your screen, or part of your screen.

# Supported OS
 - [x] Windows
 - [ ] Linux
 - [ ] OSX

## Install
```sh
npm install screen-avg-color
```

## Example
```javascript
const getColor = require('screen-avg-color');

getColor((err, r, g, b) => {
    if (err) console.error(err);

    console.log('R:' + r, 'G:' + g, 'B:' + b);
});
```

## API
```javascript
require('screen-avg-color')(callback, options);
```

### callback(err, red, green, blue)
 - err: string with error message *(null if there was no error)*
 - red: integer 0-255
 - green: integer 0-255
 - blue: integer 0-255

### options {x=0, y=0, width=0, height=0, scale=10}
#### x, y
The x and y coordinates for the top left corner of the screen.

#### width, height
The width and height of the screen in pixels. *(set to 0 to use the actual screen width or height)*

#### scale
The target size of the grabbed bitmap in percent. *(1-100)*  
(A bigger bitmap might return more precise values but it can significantly slow down the response time.)

---

## TODO
 - support for linux and osx
 - option to select which screen to use in a multi display setup
 - rewrite native bindings to n-api
