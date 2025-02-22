const atmModel = require('../../models/atm');


const checkATMAvailability = async (req, res) => {
    const { serialNumber } = req.params;
    try {
      // Tarkista, onko ATM olemassa
      const atm = await atmModel.getATMBySerialNumber(serialNumber);
      console.log('ATM:', atm); // Debug-tuloste
      if (!atm) {
        return res.status(404).json({ message: 'ATM not found' });
      }
  
   atmModel.checkATMAvailabilityBySN = (serialNumber, callback) => {
    if (error) {
      return res.status(500).json({ error: 'Database query failed' });
    }
  
    if (results.length > 0) {
      return res.status(200).json({ message: 'ATM serial number is registered', atm: results[0] });
    } else {
      return res.status(404).json({ message: 'ATM serial number is not registered' });
    }
  };

  res.status(200).json({ message: 'Access granted', atm });
} catch (error) {
    console.error('Login error:', error);
    res.status(500).json({ message: 'Internal server error' });
  }
};
  module.exports = {
    checkATMAvailability
  };