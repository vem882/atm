//Mysql Tietokanta yhteyteen liittyvä moduuli
const mysql = require('mysql2');
const dotenv=require('dotenv');
dotenv.config();

//const myConnectionString = "mysql://netuser:netpass@localhost:3306/netdb";
const connection=mysql.createPool(process.env.MYSQL_SERVER);
if (!connection) {
    throw new Error('MYSQL_SERVER environment variable is not defined');
  }
  
  console.log('Using MySQL connection string:', connection);
  
  module.exports = connection;