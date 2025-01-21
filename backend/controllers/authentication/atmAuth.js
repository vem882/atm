const cardModel = require('../../models/card_model');
const atmModel = require('../../models/atm');
const { generateToken } = require('./tokenUtils');

const login = async (req, res) => {
  const { serialNumber } = req.params;
  const { cardNumber, pin } = req.body;

  try {
    // Tarkista, onko ATM olemassa
    const atm = await atmModel.getATMBySerialNumber(serialNumber);
    if (!atm) {
      return res.status(404).json({ message: 'ATM not found' });
    }

    // Hae kortin tiedot
    const card = await cardModel.getCardByNumberAndPin(cardNumber, pin);
    if (!card) {
      return res.status(401).json({ message: 'Invalid card number or PIN' });
    }

    // Generoi token
    const token = generateToken(cardNumber);

    // Palauta token ja kortin tiedot
    res.status(200).json({
      token,
      card: {
        cardNumber: card.card_number,
        cardType: card.card_type,
        account: {
          accountNumber: card.account_number,
          balance: card.balance,
          currency: card.currency_type,
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
  login
};