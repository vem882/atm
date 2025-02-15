//Currency moduli hakee valuuttakurssin API:sta ja palauttaa sen. Jos valuuttakurssia ei löydy, saadaan virhe。
// Jotta Free planin kutsujen määrä ei ylittysi, varmaan hyvä toteuttaa jokin cache(välimuisti), 
// jota päivitetään esim kerran päivässä

const axios = require('axios');
const dotenv = require('dotenv');
dotenv.config();
const { updateCurrencyRates } = require('../../models/currency_model'); // Assuming you have a MySQL model for Currency
const API_URL = 'https://v6.exchangerate-api.com/v6/' + process.env.exchangerate_apikey + '/latest/EUR';

async function getCurrencyRate(forceUpdate = false) {
    try {
        const response = await axios.get(API_URL);
        const rates = response.data.conversion_rates;

        await updateCurrencyRates(rates, forceUpdate);

        console.log('Currency rates updated successfully');
    } catch (error) {
        console.error('Error fetching currency rates:', error);
        throw error;
    }
}

// Schedule the fetchAndUpdateCurrencyRates function to run once a day
const schedule = require('node-schedule');
schedule.scheduleJob('0 0 * * *', () => getCurrencyRate()); // Runs every day at midnight

module.exports = {
    getCurrencyRate
};