var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
const dotenv=require('dotenv');
dotenv.config({ path: '../.env' });

var indexRouter = require('./routes/index');
var currencyRouter = require('./routes/currency');
var transactionsRouter = require('./routes/transactions');
var usersRouter = require('./routes/users');
 

var app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/atm', require('./routes/atm'));
app.use('/currency', currencyRouter);
app.use('/transactions', transactionsRouter);

module.exports = app;
