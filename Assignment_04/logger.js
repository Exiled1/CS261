function logger(req, res, next) {
    console.log('== New Request Recieved');
    console.log('   --req method: ', req.method);
    console.log('   --url: ', req.url);

    next();
}

module.exports = logger;