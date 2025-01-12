var express = require('express');
var router = express.Router();

/* GET ATM page. */
router.get('/atm', function(req, res, next) {
  res.render('atm', { title: 'Express' });
});

module.exports = router;
