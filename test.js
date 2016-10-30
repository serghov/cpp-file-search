'use strict';

var nativeFileSearch = require('./build/Release/nativeFileSearch');

nativeFileSearch.find({
    root: "./",
    searchTerm: "include",
    isRegex: true,
    resultLimit: 100,
    caseSensitive: true
}, function (err, data) {
    console.log(err);
    console.log(data);
    console.log(data.length);
});
console.log("we are very async");