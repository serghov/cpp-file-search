'use strict';

var nativeFileSearch = require('./build/Release/native-search');

nativeFileSearch.find({
    root: "./",
    searchTerm: "(տեստ|inClude)",
    isRegex: true,
    resultLimit: 10000,
    caseSensitive: true
}, function (err, data) {
    console.log(err);
    console.log(data);
    console.log(data.length);
});
console.log("we are very async");