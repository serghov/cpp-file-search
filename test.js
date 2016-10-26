'use strict';

var nativeFileSearch = require('./build/Release/nativeFileSearch');

nativeFileSearch("/home/serg/cpp", "include", 10, function (err, data) {
    console.log(err);
    console.log(data);
});
console.log("we are very async");