const connection = require('../controllers/db/database'); // Adjust the path as needed

const updateCurrencyRates = async (rates) => {
  const querySelect = 'SELECT * FROM currency WHERE currency_type = ?';
  const queryInsert = 'INSERT INTO currency (currency_type, currency_value) VALUES (?, ?)';
  const queryUpdate = 'UPDATE currency SET currency_value = ? WHERE currency_type = ?';

  return new Promise(async (resolve, reject) => {
    try {
      for (const [currencyCode, rate] of Object.entries(rates)) {
        const [rows] = await connection.promise().query(querySelect, [currencyCode]);

        if (rows.length === 0) {
          await connection.promise().query(queryInsert, [currencyCode, rate]);
        } else {
          await connection.promise().query(queryUpdate, [rate, currencyCode]);
        }
      }
      resolve();
    } catch (error) {
      console.error('Error updating currency rates:', error);
      reject(error);
    }
  });
};

const getCurrencies = async () => {
  const query = 'SELECT * FROM currency';

  return new Promise((resolve, reject) => {
    connection.query(query, (error, results) => {
      if (error) {
        console.error('Error fetching currencies:', error);
        return reject(error);
      }
      resolve(results);
    });
  });
};

module.exports = {
  updateCurrencyRates,
  getCurrencies
};
