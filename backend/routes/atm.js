const express = require('express');
const router = express.Router();
const atmController = require('../controllers/atm/atm');

// Reitti ATM:n sarjanumeron tarkistamiseen
router.get('/atm/:serialNumber', atmController.checkATMSerialNumber);

module.exports = router;