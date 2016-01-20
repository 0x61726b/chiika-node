var path = require('path');
var fs = require('fs');
var async = require('async')

var Chiika = require('./../');
var lib  = path.join(path.dirname(fs.realpathSync(Chiika.path)), '../');


var root = new Chiika.Root({
      userName:"arkenthera",
      pass:"123456789",
      debugMode:true,
      appMode:true,
      modulePath:lib
    });

var request = new Chiika.Request();
var database = new Chiika.Database();

console.log("Hello");
console.log(database.AnimeList);

//Verify
// request.VerifyUser(
//   function(success) {
//      console.log(success);
//     },function(err) {
//       console.log(err);
//     } );
