//Mysql Tietokanta yhteyteen liittyvä moduuli
const mysql = require('mysql2');
const dotenv=require('dotenv');
dotenv.config();

//const myConnectionString = "mysql://netuser:netpass@localhost:3306/netdb";
const myConnectionString = process.env.MYSQL_SERVER;

const connection = mysql.createPool(myConnectionString);
module.exports = connection;