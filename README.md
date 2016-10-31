# cpp-file-search

on ubuntu
```sh
$ sudo apt-get install libboost-filesystem-dev
```

```sh
$ npm install
```

```sh
$ node test.js
```

from js

```js
var nativeFileSearch = require('native-search');

nativeFileSearch.find({
    root: "./",
    searchTerm: "(տեստ|1)",
    isRegex: true,
    resultLimit: 100,
    caseSensitive: true
}, function (err, data) {
    console.log(err);
    console.log(data);
    console.log(data.length);
});
```



