const express = require('express');
const router = express.Router();
const  { checkATMAvailabilityBySN } = require('../controllers/atm/ping');
/**
 * @swagger
 * /atm/{serialNumber}/ping:
 *   get:
 *     summary: Check ATM availability
 *     description: Check if the ATM with the given serial number is available
 *     parameters:
 *       - in: path
 *         name: serialNumber
 *         required: true
 *         schema:
 *           type: string
 *         description: ATM serial number
 *     responses:
 *       200:
 *         description: ATM is available
 *         content:
 *           application/json:
 *             schema:
 *               type: object
 *               properties:
 *                 available:
 *                   type: boolean
 *                   example: true
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
 *       404:
 *         description: ATM is not available
 *       500:
 *         description: Internal server error
 */

router.get('/', async function(req, res, next) {
    try {
      const checkATMAvailability = await checkATMAvailabilityBySN();
      res.status(200).json(checkATMAvailability);
    } catch (error) {
      console.error('Error fetching currencies:', error);
      res.status(500).json({ error: 'Internal server error' });
    }
  });
  

  module.exports = router;