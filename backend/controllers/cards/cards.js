//Cards maksukorttien liittyvät toiminnallisuudet

const { addCardHashed, verifyPin } = require('../../models/card_model');


// Handler to add a new card
const addCardHandler = async (req, res) => {
    const { card_type, idaccount, card_number, idcustomer, pincode, status } = req.body;

    if (!card_type || !idaccount || !card_number || !idcustomer || !pincode || !status) {
        return res.status(400).send({ success: false, message: 'Missing required parameters' });
    }

    try {
        const newCard = { card_type, idaccount, card_number, idcustomer, pincode, status, attempts: 0 };
        const result = await addCardHashed(newCard);
        res.status(201).json({ message: 'Card added successfully', data: result });
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
};

// Handler to verify a card's PIN
const verifyPinHandler = async (req, res) => {
    const { cardNumber, enteredPin } = req.body;

    if (!cardNumber || !enteredPin) {
        return res.status(400).send({ success: false, message: 'Missing required parameters' });
    }

    try {
        // Fetch the card details by card number
        const card = await getCardByNumber(cardNumber);
        if (!card) {
            return res.status(404).json({ success: false, message: 'Card not found' });
        }

        // Compare the entered PIN with the stored hashed PIN
        const isMatch = await verifyPin(enteredPin, card.pin);
        if (isMatch) {
            res.status(200).json({ success: true, message: 'PIN verified successfully' });
        } else {
            res.status(401).json({ success: false, message: 'Invalid PIN' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
};

module.exports = { addCardHandler, verifyPinHandler };

