var express = require('express');
var router = express.Router();

/* GET currency listing. */
router.get('/currency', function(req, res, next) {
  res.send('respond with a resource');
});

module.exports = router;
