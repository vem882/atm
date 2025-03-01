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
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (1,'1234567890','debit',8940.00,'FI3649825678345609',1000.00,1,1),(2,'9876543210','debit',13350.00,'FI8723764628198378',800.00,1,2),(4,'12345','combination',0.00,'FI12345678909',5000.00,1,2),(5,'12345','combination',0.00,'FI12345678909',5000.00,1,2);
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
  `attempts` tinyint NOT NULL DEFAULT '0',
  PRIMARY KEY (`idcard`),
  UNIQUE KEY `idcard_UNIQUE` (`idcard`),
  UNIQUE KEY `card_number_UNIQUE` (`card_number`),
  KEY `id_customer_idx` (`idcustomer`),
  CONSTRAINT `customer_id` FOREIGN KEY (`idcustomer`) REFERENCES `customer` (`idcustomer`)
) ENGINE=InnoDB AUTO_INCREMENT=19 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (3,'debit',1,'',1,'111111',1,'2025-01-01','2027-01-01',0),(4,'debit',2,'4920101020203030',2,'0101',1,'2025-02-02','2027-06-06',0),(6,'debit',3,'4920101020203333',2,'1234',1,'2025-02-02','2027-06-09',0),(10,'Debit',1,'4920404030302020',1,'$2b$10$9tscp7Llbi9KokwCYifv9OHFQLrngAeVlAHwpgIru1aRSZWnGonMK',1,'2025-02-11','2028-02-11',0),(12,'Debit',2,'4920505530302020',2,'$2b$10$4YGDSQ7x8F5Zt9WiH0VbguclC0rNst/86yp3BTaRaiJlliRKkEwym',1,'2025-02-11','2028-02-11',0),(13,'Debit',2,'4920555530302020',2,'$2b$10$yKzXtokFNR8OAJspfZN1HOoiCebs9jmE8F4OYNjKME6.wvNep1UXa',1,'2025-02-11','2028-02-11',0),(15,'Debit',2,'4920555530332020',2,'$2b$10$yn8tfrQof5dVlI5hlJOXU.wYWSYEuRbGrEk58gYaHlJZoe0jHfIj6',1,'2025-02-11','2028-02-11',0),(16,'Debit',2,'4920555530332220',2,'$2b$10$AO9ctZQgzQbTA0lvY8gNIuP2ApBD/TRDj6pjW1IN6W85Zl4xurAF6',1,'2025-02-11','2028-02-11',0),(17,'Debit',2,'4920555530332440',2,'$2b$10$YB4VpBC/czrZzJLTN8Mttuhdl07xMsVV5NxJb.Wknp2AkpBRkM62.',1,'2025-02-11','2028-02-11',0);
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
  `trans_type` varchar(15) NOT NULL,
  `trans_amount` decimal(10,2) NOT NULL,
  `targetaccount` int DEFAULT '0',
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
) ENGINE=InnoDB AUTO_INCREMENT=98 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (4,'2025-01-16 17:14:30','1',500.00,1,1,1,'debit',3),(8,'2025-01-25 16:44:11','3',200.00,2,1,1,'transfer',3),(9,'2025-01-25 16:44:13','3',200.00,2,1,1,'transfer',3),(10,'2025-01-25 16:44:24','3',200.00,2,1,1,'transfer',3),(11,'2025-01-25 16:54:47','3',200.00,2,1,1,'transfer',3),(12,'2025-01-25 16:58:41','3',200.00,2,1,1,'transfer',3),(13,'2025-01-25 17:01:50','3',200.00,2,1,1,'transfer',3),(14,'2025-01-25 17:01:50','3',200.00,0,2,1,'transfer',3),(15,'2025-01-25 17:02:18','3',200.00,2,1,1,'transfer',3),(16,'2025-01-25 17:02:18','3',200.00,0,2,1,'transfer',3),(17,'2025-01-25 17:02:59','3',200.00,2,1,1,'transfer',3),(18,'2025-01-25 17:02:59','3',200.00,0,2,1,'transfer',3),(19,'2025-01-25 17:34:54','3',200.00,2,1,1,'transfer',3),(20,'2025-01-25 17:34:54','3',200.00,0,2,1,'transfer',3),(21,'2025-01-25 21:20:07','1',100.00,NULL,1,1,'deposit',3),(22,'2025-01-25 21:20:07','2',50.00,NULL,1,1,'withdrawal',3),(23,'2025-01-25 21:20:07','3',30.00,3,1,1,'transfer',3),(24,'2025-01-25 21:40:33','3',100.00,2,1,1,'transfer',3),(25,'2025-01-25 21:40:33','3',100.00,0,2,1,'transfer',3),(26,'2025-01-25 21:41:53','3',100.00,2,1,1,'transfer',3),(27,'2025-01-25 21:41:53','3',100.00,0,2,1,'transfer',3),(30,'2025-01-25 21:46:52','1',100.00,0,1,1,'deposit',3),(31,'2025-01-25 21:46:52','2',50.00,0,1,1,'withdrawal',3),(33,'2025-01-27 14:59:34','2',50.00,0,1,1,'withdrawal',3),(34,'2025-01-27 15:00:02','2',50.00,0,1,1,'withdrawal',3),(35,'2025-01-27 15:00:15','1',50.00,0,1,1,'deposit',3),(36,'2025-01-28 21:10:01','1',100.00,0,1,1,'deposit',3),(37,'2025-01-28 21:12:16','3',100.00,2,1,1,'transfer',3),(38,'2025-01-28 21:12:16','3',100.00,0,2,1,'transfer',3),(39,'2025-01-28 21:12:20','2',100.00,0,1,1,'withdrawal',3),(40,'2025-01-28 21:14:47','1',100.00,0,1,1,'deposit',3),(41,'2025-01-28 21:15:19','2',100.00,0,1,1,'withdrawal',3),(42,'2025-01-28 21:16:18','3',1000.00,1,2,1,'transfer',3),(43,'2025-01-28 21:16:18','3',1000.00,0,1,1,'transfer',3),(44,'2025-01-28 21:16:33','3',1000.00,1,2,1,'transfer',3),(45,'2025-01-28 21:16:33','3',1000.00,0,1,1,'transfer',3),(46,'2025-01-30 21:02:46','1',500.00,0,1,1,'deposit',4),(47,'2025-01-30 21:04:03','1',500.00,0,1,1,'deposit',4),(48,'2025-01-30 21:06:10','1',500.00,0,1,1,'deposit',4),(49,'2025-01-30 21:13:40','1',500.00,0,1,1,'deposit',4),(50,'2025-01-30 21:14:36','1',500.00,0,1,1,'deposit',4),(51,'2025-01-30 21:16:30','1',500.00,0,1,1,'deposit',4),(52,'2025-01-30 21:20:17','1',500.00,0,1,1,'deposit',4),(53,'2025-01-30 21:20:45','1',500.00,0,1,1,'deposit',4),(54,'2025-01-30 21:21:09','1',500.00,0,1,1,'deposit',4),(55,'2025-01-30 21:24:13','1',500.00,0,1,1,'deposit',4),(56,'2025-01-30 21:24:59','1',500.00,0,1,1,'deposit',4),(57,'2025-01-30 21:26:02','1',500.00,0,1,1,'deposit',4),(58,'2025-01-30 21:36:04','1',500.00,0,1,1,'deposit',4),(59,'2025-01-30 21:51:03','2',500.00,0,1,1,'withdrawal',4),(60,'2025-01-30 22:00:06','2',500.00,0,1,1,'withdrawal',4),(61,'2025-01-30 22:00:53','2',500.00,0,1,1,'withdrawal',4),(62,'2025-01-30 22:03:43','2',500.00,0,1,1,'withdrawal',4),(63,'2025-01-30 22:07:04','2',500.00,0,1,1,'withdrawal',4),(64,'2025-01-30 22:08:31','2',500.00,0,1,1,'withdrawal',4),(65,'2025-01-30 22:08:56','2',500.00,0,1,1,'withdrawal',4),(66,'2025-01-30 22:15:39','2',500.00,0,1,1,'withdrawal',4),(67,'2025-01-30 22:16:47','2',500.00,0,1,1,'withdrawal',4),(68,'2025-01-30 22:18:19','2',500.00,0,1,1,'withdrawal',4),(69,'2025-01-30 22:19:12','1',500.00,0,1,1,'deposit',4),(70,'2025-02-03 15:36:14','1',500.00,0,1,1,'deposit',4),(71,'2025-02-03 15:36:32','2',500.00,0,1,1,'withdrawal',4),(72,'2025-02-03 15:38:22','2',500.00,0,1,1,'withdrawal',4),(73,'2025-02-03 15:40:25','2',50.00,0,1,1,'withdrawal',4),(74,'2025-02-03 15:42:24','2',50.00,0,1,1,'withdrawal',4),(75,'2025-02-03 15:43:03','2',50.00,0,1,1,'withdrawal',4),(76,'2025-02-03 15:43:21','2',50.00,0,1,1,'withdrawal',4),(77,'2025-02-03 15:44:00','2',50.00,0,1,1,'withdrawal',4),(78,'2025-02-03 15:51:06','3',50.00,2,1,1,'transfer',4),(79,'2025-02-03 15:51:06','3',50.00,0,2,1,'transfer',4),(80,'2025-02-03 15:53:27','2',50.00,0,1,1,'withdrawal',4),(81,'2025-02-03 15:55:11','3',50.00,2,1,1,'transfer',4),(82,'2025-02-03 15:55:11','3',50.00,0,2,1,'transfer',4),(83,'2025-02-03 15:57:31','3',50.00,2,1,1,'transfer',4),(84,'2025-02-03 15:57:31','3',50.00,0,2,1,'transfer',4),(85,'2025-02-03 15:58:18','3',500.00,1,2,1,'transfer',4),(86,'2025-02-03 15:58:18','3',500.00,0,1,1,'transfer',4),(87,'2025-02-03 15:59:45','3',500.00,1,2,1,'transfer',4),(88,'2025-02-03 15:59:45','3',500.00,0,1,1,'transfer',4),(89,'2025-02-03 16:00:05','2',50.00,0,1,1,'withdrawal',4),(90,'2025-02-03 16:00:12','1',50.00,0,1,1,'deposit',4),(91,'2025-02-03 16:02:21','1',50.00,0,1,1,'deposit',4),(92,'2025-02-03 16:02:37','3',500.00,1,2,1,'transfer',4),(93,'2025-02-03 16:02:37','3',500.00,0,1,1,'transfer',4),(94,'2025-02-03 16:05:25','3',500.00,1,2,1,'transfer',4),(95,'2025-02-03 16:05:25','3',500.00,0,1,1,'transfer',4),(96,'2025-02-11 17:33:38','1',50.00,0,1,1,'deposit',4),(97,'2025-02-11 17:33:50','2',50.00,0,1,1,'withdrawal',4);
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Dumping routines for database 'bank_automat'
--
/*!50003 DROP PROCEDURE IF EXISTS `check_credit_limit` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `check_credit_limit`(
    IN p_account_id INT,
    IN p_amount DECIMAL(10,2),
    OUT p_exceeds_limit BOOLEAN
)
BEGIN
    DECLARE current_balance DECIMAL(10,2);
    DECLARE current_credit_limit DECIMAL(10,2);

    SELECT balance, credit_limit INTO current_balance, current_credit_limit
    FROM account
    WHERE idaccount = p_account_id;

    SET p_exceeds_limit = (current_balance - p_amount) < -current_credit_limit;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `close_account` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `close_account`(
    IN p_account_id INT
)
BEGIN
    DELETE FROM account WHERE idaccount = p_account_id;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `create_account` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `create_account`(
    IN p_account_number VARCHAR(45),
    IN p_account_type VARCHAR(45),
    IN p_balance DECIMAL(10,2),
    IN p_iban VARCHAR(30),
    IN p_credit_limit DECIMAL(10,2),
    IN p_currency_id INT,
    IN p_idcustomer INT
)
BEGIN
    INSERT INTO account (account_number, account_type, balance, iban, credit_limit, currency_id, idcustomer)
    VALUES (p_account_number, p_account_type, p_balance, p_iban, p_credit_limit, p_currency_id, p_idcustomer);
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `deposit` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `deposit`(
    IN p_account_id INT,
    IN p_amount DECIMAL(10,2),
    IN p_idatm INT,
    IN p_idcard INT
)
BEGIN
    DECLARE balance_check INT DEFAULT 0;

    START TRANSACTION;

    UPDATE account 
    SET balance = balance + p_amount 
    WHERE idaccount = p_account_id;

    SET balance_check = ROW_COUNT();

    IF balance_check > 0 THEN
        INSERT INTO `transaction` (trans_date, trans_type, trans_amount, targetaccount, account_id, idatm, trans_method, idcard)
        VALUES (NOW(), 1, p_amount, 0, p_account_id, p_idatm, 'deposit', p_idcard);
        COMMIT;
    ELSE
        ROLLBACK;
    END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `list_transactions` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `list_transactions`(
    IN p_account_id INT
)
BEGIN
    SELECT 
        idtrans,
        trans_date,
        trans_amount,
        account_id,
        trans_method
    FROM `transaction`
    WHERE account_id = p_account_id
    ORDER BY trans_date DESC;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `transfer` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `transfer`(
    IN p_from_account INT,
    IN p_to_account INT,
    IN p_amount DECIMAL(10,2),
    IN p_idatm INT,
    IN p_idcard INT
)
BEGIN
    DECLARE balance_check INT DEFAULT 0;
    DECLARE transfer_check INT DEFAULT 0;

    START TRANSACTION;

    UPDATE account 
    SET balance = balance - p_amount 
    WHERE idaccount = p_from_account AND balance + credit_limit >= p_amount;

    SET balance_check = ROW_COUNT();

    IF balance_check > 0 THEN
        UPDATE account 
        SET balance = balance + p_amount 
        WHERE idaccount = p_to_account;

        SET transfer_check = ROW_COUNT();
    END IF;

    IF balance_check > 0 AND transfer_check > 0 THEN
        INSERT INTO `transaction` (trans_date, trans_type, trans_amount, targetaccount, account_id, idatm, trans_method, idcard)
        VALUES (NOW(), 3, p_amount, p_to_account, p_from_account, p_idatm, 'transfer', p_idcard);

        INSERT INTO `transaction` (trans_date, trans_type, trans_amount, targetaccount, account_id, idatm, trans_method, idcard)
        VALUES (NOW(), 3, p_amount, 0, p_to_account, p_idatm, 'transfer', p_idcard);

        COMMIT;
    ELSE
        ROLLBACK;
    END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!50003 DROP PROCEDURE IF EXISTS `withdraw` */;
/*!50003 SET @saved_cs_client      = @@character_set_client */ ;
/*!50003 SET @saved_cs_results     = @@character_set_results */ ;
/*!50003 SET @saved_col_connection = @@collation_connection */ ;
/*!50003 SET character_set_client  = utf8mb4 */ ;
/*!50003 SET character_set_results = utf8mb4 */ ;
/*!50003 SET collation_connection  = utf8mb4_0900_ai_ci */ ;
/*!50003 SET @saved_sql_mode       = @@sql_mode */ ;
/*!50003 SET sql_mode              = 'ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION' */ ;
DELIMITER ;;
CREATE DEFINER=`root`@`localhost` PROCEDURE `withdraw`(
    IN p_account_id INT,
    IN p_amount DECIMAL(10,2),
    IN p_idatm INT,
    IN p_idcard INT
)
BEGIN
    DECLARE balance_check INT DEFAULT 0;

    START TRANSACTION;

    UPDATE account 
    SET balance = balance - p_amount 
    WHERE idaccount = p_account_id AND balance + credit_limit >= p_amount;

    SET balance_check = ROW_COUNT();

    IF balance_check > 0 THEN
        INSERT INTO `transaction` (trans_date, trans_type, trans_amount, targetaccount, account_id, idatm, trans_method, idcard)
        VALUES (NOW(), 2, p_amount, 0, p_account_id, p_idatm, 'withdrawal', p_idcard);
        COMMIT;
    ELSE
        ROLLBACK;
    END IF;
END ;;
DELIMITER ;
/*!50003 SET sql_mode              = @saved_sql_mode */ ;
/*!50003 SET character_set_client  = @saved_cs_client */ ;
/*!50003 SET character_set_results = @saved_cs_results */ ;
/*!50003 SET collation_connection  = @saved_col_connection */ ;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2025-02-11 19:44:13
