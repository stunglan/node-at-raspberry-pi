var express = require('express');
var router = express.Router();


router.get('/', function(req, res, next) {
  res.send('respond with a api');
});

router.get('/v1/timeseries',function(req,res) {
    return res.json({ message: 'hooray! welcome to our api!' }); ;
});

module.exports = router;