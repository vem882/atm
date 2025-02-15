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
    "EUR": "€",      // Euro
    "AED": "د.إ",    // Arabiemiirikuntien dirhami
    "AFN": "؋",      // Afganistanin afgaani
    "ALL": "L",      // Albanian lek
    "AMD": "֏",      // Armenian dram
    "ANG": "ƒ",      // Alankomaiden Antillien guldeni
    "AOA": "Kz",     // Angolan kwanza
    "ARS": "$",      // Argentiinan peso
    "AUD": "A$",     // Australian dollari
    "AWG": "ƒ",      // Aruban floriini
    "AZN": "₼",      // Azerbaidžanin manat
    "BAM": "KM",     // Bosnia-Hertsegovinan vaihdettava markka
    "BBD": "$",      // Barbadoksen dollari
    "BDT": "৳",      // Bangladeshin taka
    "BGN": "лв",     // Bulgarian leva
    "BHD": ".د.ب",   // Bahrainin dinaari
    "BIF": "FBu",    // Burundin frangi
    "BMD": "$",      // Bermudan dollari
    "BND": "$",      // Brunein dollari
    "BOB": "Bs",     // Bolivian boliviano
    "BRL": "R$",     // Brasilian real
    "BSD": "$",      // Bahaman dollari
    "BTN": "Nu",     // Bhutanin ngultrum
    "BWP": "P",      // Botswanan pula
    "BYN": "Br",     // Valko-Venäjän rupla
    "BZD": "$",      // Belizen dollari
    "CAD": "C$",     // Kanadan dollari
    "CDF": "FC",     // Kongon frangi
    "CHF": "CHF",    // Sveitsin frangi
    "CLP": "$",      // Chilen peso
    "CNY": "¥",      // Kiinan juan
    "COP": "$",      // Kolumbian peso
    "CRC": "₡",      // Costa Rican colón
    "CUP": "$",      // Kuuban peso
    "CVE": "$",      // Kap Verden escudo
    "CZK": "Kč",     // Tšekin koruna
    "DJF": "Fdj",    // Djiboutin frangi
    "DKK": "kr",     // Tanskan kruunu
    "DOP": "$",      // Dominikaanisen tasavallan peso
    "DZD": "د.ج",    // Algerian dinaari
    "EGP": "£",      // Egyptin punta
    "ERN": "Nfk",    // Eritrean nakfa
    "ETB": "Br",     // Etiopian birr
    "FJD": "$",      // Fidžin dollari
    "FKP": "£",      // Falklandinsaarten punta
    "FOK": "kr",     // Färsaarten kruunu
    "GBP": "£",      // Brittiläinen punta
    "GEL": "₾",      // Georgian lari
    "GGP": "£",      // Guernseyn punta
    "GHS": "₵",      // Ghanan cedi
    "GIP": "£",      // Gibraltarin punta
    "GMD": "D",      // Gambian dalasi
    "GNF": "FG",     // Guinean frangi
    "GTQ": "Q",      // Guatemalan quetzal
    "GYD": "$",      // Guyanan dollari
    "HKD": "HK$",    // Hongkongin dollari
    "HNL": "L",      // Hondurasin lempira
    "HRK": "kn",     // Kroatian kuna
    "HTG": "G",      // Haitin gourde
    "HUF": "Ft",     // Unkarin forintti
    "IDR": "Rp",     // Indonesian rupia
    "ILS": "₪",      // Israelin sekeli
    "IMP": "£",      // Mansaaren punta
    "INR": "₹",      // Intian rupia
    "IQD": "ع.د",    // Irakin dinaari
    "IRR": "﷼",      // Iranin rial
    "ISK": "kr",     // Islannin kruunu
    "JEP": "£",      // Jerseyn punta
    "JMD": "$",      // Jamaikan dollari
    "JOD": "د.ا",    // Jordanian dinaari
    "JPY": "¥",      // Japanin jeni
    "KES": "KSh",    // Kenian šillinki
    "KGS": "с",      // Kirgisian som
    "KHR": "៛",      // Kambodžan riel
    "KID": "$",      // Kiribatin dollari
    "KMF": "CF",     // Komorien frangi
    "KRW": "₩",      // Etelä-Korean won
    "KWD": "د.ك",    // Kuwaitin dinaari
    "KYD": "$",      // Caymansaarten dollari
    "KZT": "₸",      // Kazakstanin tenge
    "LAK": "₭",      // Laosin kip
    "LBP": "ل.ل",    // Libanonin punta
    "LKR": "Rs",     // Sri Lankan rupia
    "LRD": "$",      // Liberian dollari
    "LSL": "L",      // Lesothon loti
    "LYD": "ل.د",    // Libyan dinaari
    "MAD": "د.م.",   // Marokon dirhami
    "MDL": "L",      // Moldovan leu
    "MGA": "Ar",     // Madagaskarin ariary
    "MKD": "ден",    // Makedonian denaari
    "MMK": "K",      // Myanmarin kyat
    "MNT": "₮",      // Mongolian tugrik
    "MOP": "MOP$",   // Macaon pataca
    "MRU": "UM",     // Mauritanian ouguiya
    "MUR": "₨",      // Mauritiuksen rupia
    "MVR": "ރ.",     // Malediivien rufiyaa
    "MWK": "MK",     // Malawin kwacha
    "MXN": "$",      // Meksikon peso
    "MYR": "RM",     // Malesian ringgit
    "MZN": "MT",     // Mosambikin metical
    "NAD": "$",      // Namibian dollari
    "NGN": "₦",      // Nigerian naira
    "NIO": "C$",     // Nicaraguan córdoba
    "NOK": "kr",     // Norjan kruunu
    "NPR": "₨",      // Nepalin rupia
    "NZD": "NZ$",    // Uuden-Seelannin dollari
    "OMR": "﷼",      // Omanin rial
    "PAB": "B/.",    // Panaman balboa
    "PEN": "S/.",    // Perun sol
    "PGK": "K",      // Papua-Uuden-Guinean kina
    "PHP": "₱",      // Filippiinien peso
    "PKR": "₨",      // Pakistanin rupia
    "PLN": "zł",     // Puolan złoty
    "PYG": "₲",      // Paraguayn guarani
    "QAR": "﷼",      // Qatarin rial
    "RON": "lei",    // Romanian leu
    "RSD": "дин",    // Serbian dinaari
    "RUB": "₽",      // Venäjän rupla
    "RWF": "FRw",    // Ruandan frangi
    "SAR": "﷼",      // Saudi-Arabian rial
    "SBD": "$",      // Salomonsaarten dollari
    "SCR": "₨",      // Seychellien rupia
    "SDG": "£",      // Sudanin punta
    "SEK": "kr",     // Ruotsin kruunu
    "SGD": "S$",     // Singaporen dollari
    "SHP": "£",      // Saint Helenan punta
    "SLE": "Le",     // Sierra Leonen leone
    "SLL": "Le",     // Sierra Leonen leone (vanha)
    "SOS": "S",      // Somalian šillinki
    "SRD": "$",      // Surinamen dollari
    "SSP": "£",      // Etelä-Sudanin punta
    "STN": "Db",     // São Tomén ja Príncipen dobra
    "SYP": "£",      // Syyrian punta
    "SZL": "L",      // Swazimaan lilangeni
    "THB": "฿",      // Thaimaan baht
    "TJS": "ЅМ",     // Tadžikistanin somoni
    "TMT": "T",      // Turkmenistanin manat
    "TND": "د.ت",    // Tunisian dinaari
    "TOP": "T$",     // Tongan paʻanga
    "TRY": "₺",      // Turkin liira
    "TTD": "$",      // Trinidadin ja Tobagon dollari
    "TVD": "$",      // Tuvalun dollari
    "TWD": "NT$",    // Taiwanin dollari
    "TZS": "TSh",    // Tansanian šillinki
    "UAH": "₴",      // Ukrainan hryvnia
    "UGX": "USh",    // Ugandan šillinki
    "USD": "$",      // Yhdysvaltain dollari
    "UYU": "$",      // Uruguayn peso
    "UZS": "so'm",   // Uzbekistanin som
    "VES": "Bs",     // Venezuelan bolívar
    "VND": "₫",      // Vietnamin dong
    "VUV": "Vt",     // Vanuatun vatu
    "WST": "T",      // Samoan tala
    "XAF": "FCFA",   // Keski-Afrikan CFA-frangi
    "XCD": "$",      // Itä-Karibian dollari
    "XDR": "SDR",    // IMF:n erityisnosto-oikeus
    "XOF": "CFA",    // Länsi-Afrikan CFA-frangi
    "XPF": "₣",      // Ranskan Tyynenmeren frangi
    "YER": "﷼",      // Jemenin rial
    "ZAR": "R",      // Etelä-Afrikan rand
    "ZMW": "ZK",     // Sambian kwacha
    "ZWL": "$"      // Zimbabwen dollari (2009)
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