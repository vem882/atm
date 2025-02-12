var express = require('express');
var router = express.Router();

/**
 * @swagger
 * /currency:
 *   get:
 *     summary: Get a list of currencies
 *     description: Retrieve a list of all available currencies
 *     responses:
 *       200:
 *         description: A list of currencies
 *         content:
 *           application/json:
 *             schema:
 *               type: array
 *               items:
 *                 type: object
 *                 properties:
 *                   id:
 *                     type: integer
 *                     description: The currency ID
 *                   currency_type:
 *                     type: string
 *                     description: The type of currency (e.g., USD, EUR)
 *                   currency_value:
 *                     type: number
 *                     description: The value of the currency
 *                   currency_symbol:
 *                     type: string
 *                     description: The symbol of the currency (e.g., $, €)
 *       500:
 *         description: Internal server error
 */
router.get('/currency', function(req, res, next) {
  res.send('respond with a resource');
});

module.exports = router;