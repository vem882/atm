const jwt = require('jsonwebtoken');
const atmModel = require('./models/atmModel'); // Olettaen, että sinulla on ATM-malli

const authMiddleware = async (req, res, next) => {
  try {
    // Hae token Authorization-headerista
    const token = req.headers.authorization?.split(' ')[1]; // Bearer <token>
    if (!token) {
      return res.status(401).json({ message: 'Token missing' });
    }

    // Tarkista token
    const decoded = jwt.verify(token, process.env.JWT_SECRET);

    // Lisää dekoodatut tiedot request-olioon
    req.user = decoded;

    // Hae ATM:n sarjanumero pyynnöstä 
    const { serialNumber } = req.body; 
    if (!serialNumber) {
      return res.status(400).json({ message: 'Serial number missing' });
    }

    // Tarkista, onko ATM olemassa
    const atm = await atmModel.getATMBySerialNumber(serialNumber);
    console.log('ATM:', atm); // Debug-tuloste
    if (!atm) {
      return res.status(404).json({ message: 'ATM not found' });
    }

    // Lisää ATM tiedot request-olioon
    req.atm = atm;

    // Jatka pyynnön käsittelyä
    next();
  } catch (error) {
    console.error('Authentication error:', error);
    return res.status(401).json({ message: 'Invalid or expired token' });
  }
};

module.exports = authMiddleware;