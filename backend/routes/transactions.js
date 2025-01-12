var express = require('express');
var router = express.Router();

/* GET transactions listing. */
router.get('/transactions', function(req, res, next) {
  res.send('respond with a resource');
});

module.exports = router;
