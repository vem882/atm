const jwt = require('jsonwebtoken');
const bcrypt = require('bcrypt');
const cardModel = require('../../models/card_model');
const atmModel = require('../../models/atm_model');

const login = async (req, res) => {
console.log('Login request received:', req.params, req.body);
  const { serialNumber } = req.params;
  const { cardNumber, pin} = req.body;

  try {
    // Tarkista, onko ATM olemassa
    const atm = await atmModel.getATMBySerialNumber(serialNumber);
    console.log('ATM:', atm); // Debug-tuloste
    if (!atm) {
      return res.status(404).json({ message: 'ATM not found' });
    }

    // Hae kortin tiedot pelkkö numero aluksi
    const card = await cardModel.getCardByNumber(cardNumber);
    console.log('Card:', card); // Debug-tuloste
    if (!card) {
      return res.status(401).json({ message: 'Invalid card number or PIN' });
    }

    // Checks if card is locked
    console.log('Card Status:', card.status); // Debug output
    if (card.status === 2) {
      return res.status(403).json({ message: 'Card is locked due to multiple failed attempts' });
    }

    // Compares entered pin with hashed stroed pin
    const isPinValid = await bcrypt.compare(pin, card.pin);
    if (!isPinValid) {
        // Increase attempts count
        await cardModel.incrementFailedAttempts(cardNumber);

        //  Checks if pin is valid and attempts 3 then lock 
        if (card.attempts >= 3) {
          await cardModel.lockCard(cardNumber);
          console.log('Card locked due to too many failed attempts'); // Debug output
          return res.status(403).json({ message: 'Card locked due to too many failed attempts' });
        } else {
          return res.status(401).json({ message: 'Invalid PIN' });
        }
        }

    // Reset attempts after successful login
    await cardModel.resetAttempts(cardNumber);

    // Generoi token
    const token = jwt.sign({ cardNumber }, process.env.JWT_SECRET, {
      expiresIn: '5m', // Token vanhenee 5 minuutin kuluttua
    });

    // Palauta token ja kortin tiedot
    res.status(200).json({
      atm,
      token,
      card: {
        cardID: card.idcard,
        cardNumber: card.card_number,
        cardType: card.card_type,
        attempts: card.attempts,
        issued: card.issued,
        valid: card.valid,
        status: card.status,
        account: {
          accountNumber: card.account_number,
          accountType: card.account_type,
          accountID: card.idaccount,
          balance: card.balance,
          credit_limit: card.credit_limit,
          currency: card.currency_id,
          },
        customer: {
          firstName: card.fname,
          lastName: card.lname,
        },
      },
    });
  } catch (error) {
    console.error('Login error:', error);
    res.status(500).json({ message: 'Internal server error' });
  }
};

module.exports = {
  login,
};

