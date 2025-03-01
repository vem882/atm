const express = require('express');
const router = express.Router();
const { checkATMAvailabilityBySN } = require('../controllers/atm/ping');

/**
 * @swagger
 * /ping:
 *   get:
 *     summary: Check ATM availability
 *     description: Check if the ATM with the given serial number is available
 *     parameters:
 *       - in: header
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
 *                 sn:
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
 *       401:
 *         description: ATM is not registered
 *       500:
 *         description: Internal server error
 */
router.get('/', async (req, res) => {
    try {
        const serialNumber = req.headers.serialnumber;
        if (!serialNumber) {
            return res.status(400).json({ message: 'serialNumber header is required' });
        }

        const atmAvailability = await checkATMAvailabilityBySN(serialNumber);
        if (atmAvailability) {
            res.status(200).json({
                sn: true,
                //atm: atmAvailability
            });
        } else {
            res.status(401).json({
                sn: false,
                message: 'ATM is not registered'
            });
        }
    } catch (error) {
        console.error('Error checking ATM availability:', error);
        res.status(500).json({
            message: 'Internal server error'
        });
    }
});

module.exports = router;