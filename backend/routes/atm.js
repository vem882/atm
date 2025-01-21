const express = require('express');
const router = express.Router();
const authMiddleware = require('../controllers/authentication/authMiddleware');
const { login } = require('../controllers/authentication/atmAuth');

// Reitti kirjautumista varten
router.post('/atm/:serialNumber/login', login);

// Suojaa reitit authMiddleware:llä
router.use('/atm/:serialNumber', authMiddleware);

// Esimerkki suojatusta reitistä
router.get('/atm/:serialNumber/account', (req, res) => {
  res.status(200).json({ message: 'Access granted', user: req.user });
});

module.exports = router;