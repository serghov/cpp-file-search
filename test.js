'use strict';
var assert = require('assert');
const binding = require('./build/Release/node_native_search');

console.log(binding.naactotive_file_search("/home/serg/cpp", "include"));