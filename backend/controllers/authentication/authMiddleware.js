const jwt = require('jsonwebtoken');

const authMiddleware = (req, res, next) => {
  try {
    // Hae token Authorization-headerista
    const token = req.headers.authorization?.split(' ')[1]; // Bearer <token>
    if (!token) {
      return res.status(401).json({ message: 'Token missing' });
    }

    // tarkistetaan tokenin oikeellisuus
    const decoded = jwt.verify(token, process.env.JWT_SECRET);

    // Lisää dekoodatut tiedot request-olioon
    req.user = decoded;

    // jatketaan pyynnön käsittelyä
    next();
  } catch (error) {
    console.error('Authentication error:', error);
    return res.status(401).json({ message: 'Invalid or expired token' });
  }
};

module.exports = authMiddleware;