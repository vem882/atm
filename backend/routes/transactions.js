const express = require('express');
const router = express.Router();
const {  depositHandler, withdrawHandler,  transferHandler, listTransactionsHandler } = require('../controllers/transactions/transactions'); // Only import handleTransaction
//const { login } = require('../controllers/authentication/atmAuth');
const authMiddleware = require('../controllers/authentication/authMiddleware');
//const { displayLastTransactions } = require('../controllers/transactions/transactions_view'); // Import display and log functions

/**
 * @swagger
 * /transactions/history/{account_id}:
 *   get:
 *     summary: Get transaction history for an account
 *     description: Retrieve the transaction history for a specific account. Requires a valid Bearer token and ATM serial number.
 *     security:
 *       - BearerAuth: []
 *     parameters:
 *       - in: path
 *         name: account_id
 *         required: true
 *         schema:
 *           type: string
 *         description: The ID of the account
 *       - in: body
 *         name: serialNumber
 *         required: true
 *         schema:
 *           type: object
 *           properties:
 *             serialNumber:
 *               type: string
 *         description: The serial number of the ATM
 *     responses:
 *       200:
 *         description: Transaction history retrieved successfully
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 message:
 *                   type: string
 *                 data:
 *                   type: array
 *                   items:
 *                     type: object
 *                     properties:
 *                       id:
 *                         type: integer
 *                       account_id:
 *                         type: string
 *                       amount:
 *                         type: number
 *                       type:
 *                         type: string
 *                       date:
 *                         type: string
 *                         format: date-time
 *       400:
 *         description: Missing required parameters (e.g., serialNumber)
 *       401:
 *         description: Unauthorized (invalid or missing token)
 *       404:
 *         description: ATM not found
 *       500:
 *         description: Server error
 */
// GET transaction history 
router.get('/history/:account_id', authMiddleware, async (req, res) => {
  try {
    const { account_id } = req.params;
    const transactions = await listTransactionsHandler({ params: { account_id } }, res);
      if (!transactions) return;  
        res.status(200).json({
        message: 'Transaction history get succesfully',
        data: transactions,
    });
  } catch (err) {
    console.error(err);
    return res.status(500).json({ success: false, message: 'Server error', error: err.message });
  }
});
/**
 * @swagger
 * /transactions/deposit:
 *   post:
 *     summary: Make a deposit
 *     description: Deposit money into an account. Requires a valid Bearer token and ATM serial number.
 *     security:
 *       - BearerAuth: []
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             type: object
 *             properties:
 *               account_id:
 *                 type: string
 *               amount:
 *                 type: number
 *               idatm:
 *                 type: string
 *               idcard:
 *                 type: string
 *               serialNumber:
 *                 type: string
 *     responses:
 *       200:
 *         description: Deposit successful
 *       400:
 *         description: Missing required parameters (e.g., serialNumber)
 *       401:
 *         description: Unauthorized (invalid or missing token)
 *       404:
 *         description: ATM not found
 *       500:
 *         description: Server error
 */
// POST route for deposit
router.post('/deposit', authMiddleware, async (req, res) => {
  const { account_id, amount, idatm, idcard } = req.body;
  if (!account_id || !amount || !idatm || !idcard) {
      return res.status(400).send({ success: false, message: 'Missing required parameters' });
  }
  try {
    await depositHandler(req, res);
  } catch (err) {
      console.log(err);
      return res.status(500).send({ success: false, message: 'Server error', error: err.message });
  }
});

/**
 * @swagger
 * /transactions/withdraw:
 *   post:
 *     summary: Make a withdrawal
 *     description: Withdraw money from an account. Requires a valid Bearer token and ATM serial number.
 *     security:
 *       - BearerAuth: []
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             type: object
 *             properties:
 *               account_id:
 *                 type: string
 *               amount:
 *                 type: number
 *               idatm:
 *                 type: string
 *               idcard:
 *                 type: string
 *               serialNumber:
 *                 type: string
 *     responses:
 *       200:
 *         description: Withdrawal successful
 *       400:
 *         description: Missing required parameters (e.g., serialNumber)
 *       401:
 *         description: Unauthorized (invalid or missing token)
 *       404:
 *         description: ATM not found
 *       500:
 *         description: Server error
 */
// POST route for withdrawal
router.post('/withdraw', authMiddleware, async (req, res) => {
    const { account_id, amount, idatm, idcard } = req.body;

    if (!account_id || !amount || !idatm || !idcard ) {
        return res.status(400).send({ success: false, message: 'Missing required parameters' });
    }
    try {
        await withdrawHandler(req, res);  
    } catch (err) {
        console.log(err);
        return res.status(500).send({ success: false, message: 'Server error', error: err.message });
    }
});

/**
 * @swagger
 * /transactions/transfer:
 *   post:
 *     summary: Make a transfer
 *     description: Transfer money from one account to another. Requires a valid Bearer token and ATM serial number.
 *     security:
 *       - BearerAuth: []
 *     requestBody:
 *       required: true
 *       content:
 *         application/json:
 *           schema:
 *             type: object
 *             properties:
 *               from_account:
 *                 type: string
 *               to_account:
 *                 type: string
 *               amount:
 *                 type: number
 *               idatm:
 *                 type: string
 *               idcard:
 *                 type: string
 *               serialNumber:
 *                 type: string
 *     responses:
 *       200:
 *         description: Transfer successful
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 message:
 *                   type: string
 *                 data:
 *                   type: object
 *       400:
 *         description: Missing required parameters (e.g., serialNumber)
 *       401:
 *         description: Unauthorized (invalid or missing token)
 *       404:
 *         description: ATM not found
 *       500:
 *         description: Server error
 */
// POST route for transfer
router.post('/transfer', authMiddleware, async (req, res) => {
  const { from_account, to_account, amount, idatm, idcard } = req.body;

  if (!from_account || !to_account || !amount || !idatm || !idcard) {
      return res.status(400).send({ success: false, message: 'Missing required parameters' });
  }

  try {
      const transfer = await transferHandler({ body: { from_account, to_account, amount, idatm, idcard } }, res);
      if (res.headersSent) return; // Prevents double response
      res.status(200).json({
        message: 'Last transfer successful',
        data: transfer,
      });
  } catch (err) {
    if (!res.headersSent) { // Prevent sending another response
      console.log(err);
      return res.status(500).send({ success: false, message: 'Server error', error: err.message });
  }
}
});

/**
 * @swagger
 * /transactions/{account_id}/display:
 *   get:
 *     summary: Display transactions for an account
 *     description: Retrieve the last transactions for a specific account. Requires a valid Bearer token and ATM serial number.
 *     security:
 *       - BearerAuth: []
 *     parameters:
 *       - in: path
 *         name: account_id
 *         required: true
 *         schema:
 *           type: string
 *         description: The ID of the account
 *       - in: body
 *         name: serialNumber
 *         required: true
 *         schema:
 *           type: object
 *           properties:
 *             serialNumber:
 *               type: string
 *         description: The serial number of the ATM
 *     responses:
 *       200:
 *         description: Transactions retrieved successfully
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 message:
 *                   type: string
 *                 data:
 *                   type: array
 *                   items:
 *                     type: object
 *                     properties:
 *                       id:
 *                         type: integer
 *                       account_id:
 *                         type: string
 *                       amount:
 *                         type: number
 *                       type:
 *                         type: string
 *                       date:
 *                         type: string
 *                         format: date-time
 *       400:
 *         description: Missing required parameters (e.g., serialNumber)
 *       401:
 *         description: Unauthorized (invalid or missing token)
 *       404:
 *         description: ATM not found
 *       500:
 *         description: Server error
 */
// Route to display transactions for an account
router.get('/:account_id/display', authMiddleware, async (req, res) => {
  const { account_id } = req.params;
  try {
    const transactions = await listTransactionsHandler(account_id);
    res.status(200).json({
      message: 'Last transactions retrieved successfully',
      data: transactions,
    });
  } catch (error) {
    res.status(500).json({ message: 'Error retrieving transactions', error: error.message });
  }
});


module.exports = router;

/*
if needed 
// POST route to get transaction history
router.post('/history', async (req, res) => {
  const { idaccount, card } = req.body;

  if (!idaccount || !card) {
      return res.status(400).send({ success: false, message: 'Missing required parameters' });
  }
  try {
      await tokenCheck.verify(req, card);
      const transactions = await listTransactionsHandler({ params: { account_id: idaccount } }, res);
  } catch (err) {
      console.log(err);
      return res.status(500).send({ success: false, message: 'Server error', error: err.message });
  }
});

*/