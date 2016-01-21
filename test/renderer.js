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

 function getMyAnimelist()
 {
   request.GetMyAnimelist(
     function(success) {
        console.log(success);
       },function(err) {
         console.log(err);
       } );
 }

 function getMyMangalist()
 {
   request.GetMyMangalist(
     function(success) {
        console.log(success);
       },function(err) {
         console.log(err);
       } );
 }

 function verifyUser()
 {
   request.VerifyUser(
     function(success) {
        console.log(success);
       },function(err) {
         console.log(err);
       } );
 }
 function getAnimelistLocal()
 {
   console.log(database.AnimeList);
 }
 function getMangalistLocal()
 {
   console.log(database.Mangalist);
 }
 function getUserLocal()
 {
   console.log(database.User);
 }

// Verify
// request.VerifyUser(
//   function(success) {
//      console.log(success);
//     },function(err) {
//       console.log(err);
//     } );

//Get MyAnimeList of user
