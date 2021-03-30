/*
 * Write your routing code in this file.  Make sure to add your name and
 * @oregonstate.edu email address below.
 *
 * Name: Rudy Peralta
 * Email: peraltar@oregonstate.edu
 */

var path = require('path');
var express = require('express');
var expressHandleBars = require("express-handlebars");
var logger = require('./logger');
var postData = require('./postData.json');
// Required serverside libs & files/data^^ ----------------

var app = express();
var port = process.env.PORT || 3000;
// registering handlebars as a template engine.
app.engine('handlebars', expressHandleBars({
    defaultLayout: 'layout'
}));
app.set('view engine', 'handlebars'); // tells express to default HB as the view engine. 
// HB Setup & Rendering engine setup.---------------------------------------

app.use(logger);
app.use(express.static('public')); // serves the assets in the pub dir.



app.get('/', function(req, res, next) {

    console.log("Post Data: ", postData);
    res.status(200).render('bennyIndex', {
        post: postData,
        singlepost: true
    });
});

app.get('/posts/:n', function(req, res, next) {
    var postNum = req.params.n;

    console.log("Post Data: ", postData);
    if (postNum > postData.length - 1 || 0 > postNum) { // If the requested number is bigger than the json length.
        next();
    } else {
        res.status(200).render('bennyIndex', {
            post: [postData[postNum]],
            singlepost: false
        });
    }
});

app.get('*', function(req, res) { // This serves the 404 page.
    console.log("== 404 Status");
    res.status(404).render('404');
});

app.listen(port, function() {
    console.log("== Server is listening on port", port);
});