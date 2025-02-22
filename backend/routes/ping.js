const express = require('express');
const router = express.Router();
const { checkATMAvailability  } = require('../controllers/atm/atm');
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
router.get('/ping', (req, res) => {
    const serialNumber = req.headers['serialnumber']; // Headerista 'serialnumber'
    if (!serialNumber) {
      return res.status(400).json({ message: 'Serial number missing' });
    }
  
    checkATMAvailability(serialNumber, (error, result) => {
      if (error) {
        return res.status(500).json({ error: 'Database query failed' });
      }
      if (result.available) {
        return res.status(200).json(result);
      } else {
        return res.status(404).json({ message: 'ATM serial number is not registered' });
      }
    });
  });