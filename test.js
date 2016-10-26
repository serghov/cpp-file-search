'use strict';

var nativeFileSearch = require('./build/Release/nativeFileSearch');

nativeFileSearch("/home/serg/cpp", "include", function (err, data) {
    console.log(data);
});
console.log("we are very async");