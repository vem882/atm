const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');
const dotenv = require('dotenv');
const io = require('@pm2/io')
dotenv.config({ path: '../.env' });

const indexRouter = require('./routes/index');
const atmRouter = require('./routes/atm');
const currencyRouter = require('./routes/currency');
const transactionsRouter = require('./routes/transactions');
const usersRouter = require('./routes/users');

const app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/atm', atmRouter); // ATM-reitit
app.use('/currency', currencyRouter);
app.use('/transactions', transactionsRouter);

io.init({
    transactions: true, // will enable the transaction tracing
    http: true // will enable metrics about the http server (optional)
  })
module.exports = app;