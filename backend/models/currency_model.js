const dbConfig = require('../controllers/db/database'); // Adjust the path as needed

async function updateCurrencyRates(rates) {
    const connection = await mysql.createConnection(dbConfig);

    try {
        for (const [currencyCode, rate] of Object.entries(rates)) {
            const [rows] = await connection.execute(
                'SELECT * FROM currency WHERE currency_type = ?',
                [currencyCode]
            );

            if (rows.length === 0) {
                await connection.execute(
                    'INSERT INTO currency (currency_type, currency_value) VALUES (?, ?)',
                    [currencyCode, rate]
                );
            } else {
                await connection.execute(
                    'UPDATE currency SET currency_value = ? WHERE currency_type = ?',
                    [rate, currencyCode]
                );
            }
        }
    } catch (error) {
        console.error('Error updating currency rates:', error);
        throw error;
    } finally {
        await connection.end();
    }
}

async function getCurrencies() {
    const connection = await mysql.createConnection(dbConfig);

    try {
        const [rows] = await connection.execute('SELECT * FROM currency');
        return rows;
    } catch (error) {
        console.error('Error fetching currencies:', error);
        throw error;
    } finally {
        await connection.end();
    }
}

module.exports = {
    updateCurrencyRates,
    getCurrencies
};
