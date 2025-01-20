const connection = require('../controllers/db/database');

// Funktio, joka hakee ATM:n tiedot sarjanumeron perusteella
const getATMBySerialNumber = (serialNumber, callback) => {
  const query = 'SELECT * FROM atm WHERE serial_number = ?';
  connection.query(query, [serialNumber], (error, results) => {
    if (error) {
      return callback(error, null);
    }
    return callback(null, results);
  });
};

module.exports = {
  getATMBySerialNumber
};