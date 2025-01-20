const express = require('express');
const router = express.Router();
const atmController = require('../controllers/atm/atm');

// Reitti ATM:n sarjanumeron tarkistamiseen
router.get('/:serialNumber', atmController.checkATMSerialNumber);

module.exports = router;