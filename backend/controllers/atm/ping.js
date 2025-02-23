const { getATMBySerialNumber } = require('../../models/atm_model');

async function checkATMAvailabilityBySN(serialNumber) {
    try {
        const atm = await getATMBySerialNumber(serialNumber);
        if (atm) {
            return atm;
        } else {
            return null;
        }
    } catch (error) {
        console.error('Error checking ATM availability:', error);
        throw error;
    }
}

module.exports = {
    checkATMAvailabilityBySN
};