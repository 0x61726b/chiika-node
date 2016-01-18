var path = require('path');
var fs = require('fs');
var async = require('async')

var chiika = require('./../');
var lib  = path.join(path.dirname(fs.realpathSync(chiika.path)), '../');


var r2 = new chiika.Root({
      userName:"arkenthera",
      pass:"123asd456",
      debugMode:true,
      appMode:true
    });
