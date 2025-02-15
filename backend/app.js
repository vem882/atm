// Tuodaan tarvittavat moduulit
const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const dotenv = require('dotenv');
dotenv.config({ path: '../.env' });

// Tuodaan reitittimet
const indexRouter = require('./routes/index');
const atmRouter = require('./routes/atm');
const currencyRouter = require('./routes/currency');
const transactionsRouter = require('./routes/transactions'); // lisäsin
const usersRouter = require('./routes/users');

const app = express();

// Swagger-dokumentaatio
const setupSwagger = require('./swagger');
setupSwagger(app);

// Käytetään middlewarejä välikädet
app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

// Määritetään reitit
app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/atm', atmRouter); 
app.use('/currency', currencyRouter);
app.use('/transactions', transactionsRouter); // lisäsin

// 404-virheet
app.use((req, res) => {
  res.status(404).sendFile(path.join(__dirname, 'public', '404.html'));
});

// 500-virheet
app.use((err, req, res, next) => {
  res.status(500).send('500 - Internal Server Error');
});

module.exports = app;