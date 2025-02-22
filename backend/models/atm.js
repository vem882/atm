const connection = require('../controllers/db/database');

const getATMBySerialNumber = async (serialNumber) => {
  const query = 'SELECT * FROM atm WHERE serial_number = ?';
  return new Promise((resolve, reject) => {
    connection.query(query, [serialNumber], (error, results) => {
      if (error) {
        return reject(error);
      }
      resolve(results[0]); // Return the first result
    });
  });
};

module.exports = {
  getATMBySerialNumber,
};