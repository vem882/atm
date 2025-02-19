const connection = require('../controllers/db/database');
const bcrypt = require('bcrypt');

const saltRounds = 10;


// Increment failed attempts
const incrementFailedAttempts = async (cardNumber) => {
  const query = `UPDATE card SET attempts = attempts + 1 WHERE card_number = ?`;
  return new Promise((resolve, reject) => {
      connection.execute(query, [cardNumber], (error, results) => {
          if (error) return reject(error);
          console.log(`Attempts incremented for card ${cardNumber}`);
          resolve(results);
      });
  });
};

// Lock the card when attempts reach 3 (status = 2)
const lockCard = async (cardNumber) => {
  const query = `UPDATE card SET status = 2 WHERE card_number = ?`;
  return new Promise((resolve, reject) => {
      connection.execute(query, [cardNumber], (error, results) => {
          if (error) return reject(error);
          resolve(results);
      });
  });
};

// Reset attempts after successful login
const resetAttempts = async (cardNumber) => {
  const query = `UPDATE card SET attempts = 0 WHERE card_number = ?`;
  return new Promise((resolve, reject) => {
      connection.execute(query, [cardNumber], (error, results) => {
          if (error) return reject(error);
          resolve(results);
      });
  });
};

const getCardByNumber = async (cardNumber, pin) => {
  const query = `
    SELECT c.*, a.*, cu.fname, cu.lname
    FROM card c
    JOIN account a ON c.idaccount = a.idaccount
    JOIN customer cu ON a.idcustomer = cu.idcustomer
    WHERE c.card_number = ? AND c.pin = ?
  `;
  return new Promise((resolve, reject) => {
    connection.query(query, [cardNumber, pin], (error, results) => {
      if (error) {
        return reject(error);
      }
      resolve(results[0]); // Palauta ensimmäinen tulos, muutetaan tämä myöhemmin.
    });
  });
};

// Function to hash a PIN
const hashPin = async (pin) => {
  try {
      const hashedPin = await bcrypt.hash(pin, saltRounds);
      return hashedPin;
  } catch (error) {
      console.error('Error hashing PIN:', error);
      throw error;
  }
};

const addCardHashed = async (newCard) => {
  try {
    const hashedPincode = await bcrypt.hash(newCard.pincode, 10);

    const query = `
      INSERT INTO card (card_type, idaccount, card_number, idcustomer, pin, status, issued, valid) 
      VALUES (?, ?, ?, ?, ?, ?, NOW(), DATE_ADD(NOW(), INTERVAL 3 YEAR))`;

    return new Promise((resolve, reject) => {
      connection.execute(query, [
        newCard.card_type, newCard.idaccount, newCard.card_number, newCard.idcustomer, hashedPincode, newCard.status
      ], (error, results) => {
        if (error) {
          console.error("Error adding card:", error);
          return reject(error);
        }
        resolve(results);
      });
    });
  } catch (error) {
    console.error("Error adding card:", error);
    throw error;
  }
};


// Function to verify a card's PIN
const verifyPin = async (enteredPin, storedHashedPin) => {
  try {
      const match = await bcrypt.compare(enteredPin, storedHashedPin);
      return match;
  } catch (error) {
      console.error('Error verifying PIN:', error);
      throw error;
  }
};


module.exports = {
  getCardByNumber,
  addCardHashed,
  hashPin,
  verifyPin,
  incrementFailedAttempts,
  lockCard,
  resetAttempts,
};

