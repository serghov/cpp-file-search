# cpp-file-search

on ubuntu
```sh
$ sudo apt-get install libboost-filesystem-dev
```

```sh
$ node-gyp configure
$ node-gyp build
```

```sh
$ node test.js
```

```js
const file_search = require('./build/Release/node_native_search');
console.log(file_search.native_file_search("/your/directory", "search term"));
```



