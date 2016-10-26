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
var nativeFileSearch = require('./build/Release/nativeFileSearch');

nativeFileSearch("/search/root/path", "search regex", function (err, data) {
    console.log(data);
});

var limit = 10;
nativeFileSearch("/search/root/path", "search regex", limit, function (err, data) {
    console.log(data);
});
```



