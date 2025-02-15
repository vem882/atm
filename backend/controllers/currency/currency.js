//Currency moduli hakee valuuttakurssin API:sta ja palauttaa sen. Jos valuuttakurssia ei löydy, saadaan virhe。
// Jotta Free planin kutsujen määrä ei ylittysi, varmaan hyvä toteuttaa jokin cache(välimuisti), 
// jota päivitetään esim kerran päivässä

const axios = require('axios');
const dotenv = require('dotenv');
dotenv.config();
const { updateCurrencyRates } = require('../../models/currency_model'); // Assuming you have a MySQL model for Currency
const API_URL = 'https://v6.exchangerate-api.com/v6/' + process.env.exchangerate_apikey + '/latest/EUR';

// Predefined list of common currency symbols
const currencySymbols = {
    USD: '$',      // Yhdysvallat, dollari
    EUR: '€',      // Euroalue, euro
    GBP: '£',      // Yhdistynyt kuningaskunta, punta
    JPY: '¥',      // Japani, jeni
    AUD: 'A$',     // Australia, dollari
    CAD: 'C$',     // Kanada, dollari
    CHF: 'CHF',    // Sveitsi, frangi
    CNY: '¥',      // Kiina, juan
    SEK: 'kr',     // Ruotsi, kruunu
    NZD: 'NZ$',    // Uusi-Seelanti, dollari
    INR: '₹',      // Intia, rupia
    BRL: 'R$',     // Brasilia, real
    RUB: '₽',      // Venäjä, rupla
    ZAR: 'R',      // Etelä-Afrikka, rand
    SGD: 'S$',     // Singapore, dollari
    HKD: 'HK$',    // Hongkong, dollari
    NOK: 'kr',     // Norja, kruunu
    KRW: '₩',      // Etelä-Korea, won
    MXN: 'MX$',    // Meksiko, peso
    TRY: '₺',      // Turkki, liira
    IDR: 'Rp',     // Indonesia, rupia
    MYR: 'RM',     // Malesia, ringgit
    PHP: '₱',      // Filippiinit, peso
    THB: '฿',      // Thaimaa, baht
    DKK: 'kr',     // Tanska, kruunu
    PLN: 'zł',     // Puola, złoty
    HUF: 'Ft',     // Unkari, forintti
    CZK: 'Kč',     // Tšekki, koruna
    ILS: '₪',      // Israel, sekeli
    AED: 'د.إ',    // Yhdistyneet arabiemiirikunnat, dirhami
    SAR: '﷼',      // Saudi-Arabia, rial
    QAR: '﷼',      // Qatar, rial
    KWD: 'د.ك',    // Kuwait, dinaari
    BHD: '.د.ب',   // Bahrain, dinaari
    OMR: '﷼'      // Oman, rial
    // Add more symbols as needed
};

async function getCurrencyRate(forceUpdate = false) {
    try {
        const response = await axios.get(API_URL);
        const rates = response.data.conversion_rates;

        await updateCurrencyRates(rates, currencySymbols, forceUpdate);

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