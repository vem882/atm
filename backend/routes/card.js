const express = require('express');
const router = express.Router();
const { addCardHandler, verifyPinHandler } = require('../controllers/cards/cards');

// Route to add a new card
router.post('/addcard', addCardHandler);

// Route to verify a card's PIN
router.post('/verifypin', verifyPinHandler);


module.exports = router;
