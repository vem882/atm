const connection = require('../controllers/db/database'); // Adjust the path as needed

const updateCurrencyRates = async (rates, symbols, forceUpdate) => {
  const querySelect = 'SELECT * FROM currency WHERE currency_type = ?';
  const queryInsert = 'INSERT INTO currency (currency_type, currency_value, currency_symbol) VALUES (?, ?, ?)';
  const queryUpdate = 'UPDATE currency SET currency_value = ?, currency_symbol = ? WHERE currency_type = ?';

  return new Promise(async (resolve, reject) => {
    try {
      for (const [currencyCode, rate] of Object.entries(rates)) {
        const symbol = symbols[currencyCode] || currencyCode; // Use currency code as default symbol if not provided
        const [rows] = await connection.promise().query(querySelect, [currencyCode]);

        if (rows.length === 0) {
          await connection.promise().query(queryInsert, [currencyCode, rate, symbol]);
        } else if (forceUpdate) {
          await connection.promise().query(queryUpdate, [rate, symbol, currencyCode]);
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
