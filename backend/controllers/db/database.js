//Mysql Tietokanta yhteyteen liittyvä moduuli
const mysql = require('mysql2');
const dotenv=require('dotenv');
dotenv.config();

//const myConnectionString = "mysql://netuser:netpass@localhost:3306/netdb";
const myConnectionString = process.env.MYSQL_SERVER;
if (!myConnectionString) {
    throw new Error('MYSQL_SERVER environment variable is not defined');
  }
  
  console.log('Using MySQL connection string:', myConnectionString);
  
  const connection = mysql.createPool(myConnectionString);
  module.exports = connection;