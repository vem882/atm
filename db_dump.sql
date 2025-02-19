CREATE DATABASE  IF NOT EXISTS `bank_automat` /*!40100 DEFAULT CHARACTER SET utf8mb3 */ /*!80016 DEFAULT ENCRYPTION='N' */;
USE `bank_automat`;
-- MySQL dump 10.13  Distrib 8.0.38, for Win64 (x86_64)
--
-- Host: 127.0.0.1    Database: bank_automat
-- ------------------------------------------------------
-- Server version	8.2.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `idaccount` int NOT NULL AUTO_INCREMENT,
  `account_number` varchar(45) NOT NULL,
  `account_type` varchar(45) NOT NULL,
  `balance` decimal(10,2) NOT NULL,
  `iban` varchar(30) NOT NULL,
  `credit_limit` decimal(10,2) NOT NULL DEFAULT '1000.00',
  `currency_id` int NOT NULL,
  `idcustomer` int NOT NULL,
  PRIMARY KEY (`idaccount`),
  UNIQUE KEY `idaccount_UNIQUE` (`idaccount`),
  KEY `id_currency_idx` (`currency_id`),
  KEY `id_customer_idx` (`idcustomer`),
  CONSTRAINT `id_currency` FOREIGN KEY (`currency_id`) REFERENCES `currency` (`idcurrency`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `id_customer` FOREIGN KEY (`idcustomer`) REFERENCES `customer` (`idcustomer`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,'1234567890','debit',6540.00,'FI3649825678345609',1000.00,1,1),(2,'9876543210','debit',14500.00,'FI8723764628198378',800.00,1,2);
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `account_ownership`
--

DROP TABLE IF EXISTS `account_ownership`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account_ownership` (
  `idaccount_ownership` int NOT NULL AUTO_INCREMENT,
  `idcard` int NOT NULL,
  `idaccount` int NOT NULL,
  PRIMARY KEY (`idaccount_ownership`),
  KEY `id_account_idx` (`idaccount`),
  KEY `id_card_idx` (`idcard`),
  CONSTRAINT `id_account` FOREIGN KEY (`idaccount`) REFERENCES `account` (`idaccount`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `id_card` FOREIGN KEY (`idcard`) REFERENCES `card` (`idcard`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account_ownership`
--

LOCK TABLES `account_ownership` WRITE;
/*!40000 ALTER TABLE `account_ownership` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_ownership` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `atm`
--

DROP TABLE IF EXISTS `atm`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `atm` (
  `idatm` int NOT NULL AUTO_INCREMENT,
  `serial_number` varchar(45) NOT NULL,
  `ip_address` varchar(45) NOT NULL,
  `location` varchar(45) NOT NULL,
  PRIMARY KEY (`idatm`),
  UNIQUE KEY `serial_number_UNIQUE` (`serial_number`),
  UNIQUE KEY `idatm_UNIQUE` (`idatm`),
  UNIQUE KEY `ip_address_UNIQUE` (`ip_address`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `atm`
--

LOCK TABLES `atm` WRITE;
/*!40000 ALTER TABLE `atm` DISABLE KEYS */;
INSERT INTO `atm` VALUES (1,'SN12345','192.168.0.1','lahti'),(2,'SN54321','192.168.0.2','turku');
/*!40000 ALTER TABLE `atm` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `idcard` int NOT NULL AUTO_INCREMENT,
  `card_type` varchar(20) NOT NULL,
  `idaccount` int NOT NULL,
  `card_number` varchar(45) NOT NULL,
  `idcustomer` int NOT NULL,
  `pin` varchar(255) NOT NULL,
  `status` int NOT NULL,
  `issued` date NOT NULL,
  `valid` date NOT NULL,
  PRIMARY KEY (`idcard`),
  UNIQUE KEY `idcard_UNIQUE` (`idcard`),
  UNIQUE KEY `card_number_UNIQUE` (`card_number`),
  KEY `id_customer_idx` (`idcustomer`),
  CONSTRAINT `customer_id` FOREIGN KEY (`idcustomer`) REFERENCES `customer` (`idcustomer`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (3,'debit',1,'',1,'111111',1,'2025-01-01','2027-01-01');
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `currency`
--

DROP TABLE IF EXISTS `currency`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `currency` (
  `idcurrency` int NOT NULL AUTO_INCREMENT,
  `currency_type` varchar(45) NOT NULL,
  `currency_value` decimal(10,2) NOT NULL,
  `currency_symbol` varchar(45) NOT NULL,
  PRIMARY KEY (`idcurrency`),
  UNIQUE KEY `idcurrency_UNIQUE` (`idcurrency`)
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `currency`
--

LOCK TABLES `currency` WRITE;
/*!40000 ALTER TABLE `currency` DISABLE KEYS */;
INSERT INTO `currency` VALUES (1,'USD',1.00,'$'),(2,'EUR',1.10,'€');
/*!40000 ALTER TABLE `currency` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customer` (
  `idcustomer` int NOT NULL AUTO_INCREMENT,
  `fname` varchar(45) NOT NULL,
  `lname` varchar(45) NOT NULL,
  `address` varchar(45) NOT NULL,
  `customer_type` int NOT NULL,
  PRIMARY KEY (`idcustomer`),
  KEY `id_customer` (`idcustomer`) /*!80000 INVISIBLE */
) ENGINE=InnoDB AUTO_INCREMENT=3 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (1,'Jari','Aalto','Karikuja 3',1),(2,'Jane','Smith','Latulaakso 2b',1);
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transaction`
--

DROP TABLE IF EXISTS `transaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transaction` (
  `idtrans` int NOT NULL AUTO_INCREMENT,
  `trans_date` timestamp NOT NULL,
  `trans_type` int NOT NULL,
  `trans_amount` decimal(10,2) NOT NULL,
  `targetaccount` varchar(45) NOT NULL,
  `account_id` int DEFAULT NULL,
  `idatm` int NOT NULL,
  `trans_method` varchar(45) NOT NULL,
  `idcard` int NOT NULL,
  PRIMARY KEY (`idtrans`),
  UNIQUE KEY `idtrans_UNIQUE` (`idtrans`),
  KEY `id_account_idx` (`account_id`),
  KEY `id_atm_idx` (`idatm`),
  KEY `id_card_idx` (`idcard`),
  CONSTRAINT `account_id` FOREIGN KEY (`account_id`) REFERENCES `account` (`idaccount`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `card_id` FOREIGN KEY (`idcard`) REFERENCES `card` (`idcard`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `id_atm` FOREIGN KEY (`idatm`) REFERENCES `atm` (`idatm`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (4,'2025-01-16 17:14:30',1,500.00,'1',1,1,'debit',3);
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'bank_automat'
--
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-01-16 22:04:29
