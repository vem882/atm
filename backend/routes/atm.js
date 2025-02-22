const express = require('express');
const router = express.Router();
const { login } = require('../controllers/authentication/atmAuth');
const authMiddleware = require('../controllers/authentication/authMiddleware');
/**
 * @swagger
 * /atm/{serialNumber}/login:
 *   post:
 *     summary: Login to ATM
 *     description: Login using card number and PIN
 *     parameters:
 *       - in: path
 *         name: serialNumber
 *         required: true
 *         schema:
 *           type: string
 *         description: ATM serial number
 *       - in: body
 *         name: credentials
 *         required: true
 *         schema:
 *           type: object
 *           properties:
 *             cardNumber:
 *               type: string
 *             pin:
 *               type: string
 *     responses:
 *       200:
 *         description: Login successful
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 token:
 *                   type: string
 *                 atm:
 *                   type: object
 *                   properties:
 *                     idatm:
 *                       type: integer
 *                     serial_number:
 *                       type: string
 *                     ip_address:
 *                       type: string
 *                     location:
 *                       type: string
 *                 card:
 *                   type: object
 *                   properties:
 *                     cardNumber:
 *                       type: string
 *                     cardType:
 *                       type: string
 *                     attempts:
 *                       type: integer
 *                     issued:
 *                       type: string
 *                       format: date-time
 *                     valid:
 *                       type: string
 *                       format: date-time
 *                     status:
 *                       type: integer
 *                     account:
 *                       type: object
 *                       properties:
 *                         accountNumber:
 *                           type: string
 *                         accountID:
 *                           type: integer
 *                         balance:
 *                           type: string
 *                         currency:
 *                           type: integer
 *                     customer:
 *                       type: object
 *                       properties:
 *                         firstName:
 *                           type: string
 *                         lastName:
 *                           type: string
 *       401:
 *         description: Invalid card number or PIN
 *       404:
 *         description: ATM not found
 *       500:
 *         description: Internal server error
 */
// Reitti kirjautumista varten
router.post('/:serialNumber/login', login);
/**
 * @swagger
 * /atm/{serialNumber}/account:
 *   get:
 *     summary: Get account details
 *     description: Get account details for the logged-in user
 *     security:
 *       - BearerAuth: []
 *     parameters:
 *       - in: path
 *         name: serialNumber
 *         required: true
 *         schema:
 *           type: string
 *         description: ATM serial number
 *     responses:
 *       200:
 *         description: Account details retrieved successfully
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 message:
 *                   type: string
 *                 user:
 *                   type: object
 *                   properties:
 *                     cardNumber:
 *                       type: string
 *       401:
 *         description: Unauthorized
 *       404:
 *         description: ATM not found
 */
// Suojattu reitti (vaatii tokenin)
router.get('/:serialNumber/account', authMiddleware, (req, res) => {
  res.status(200).json({ message: 'Access granted', user: req.user });
});

module.exports = router;