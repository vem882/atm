const swaggerJsDoc = require('swagger-jsdoc');
const swaggerUi = require('swagger-ui-express');

// Swaggerin asetukset
const swaggerOptions = {
  swaggerDefinition: {
    openapi: '3.0.0',
    info: {
      title: 'OttoHUB Atm API',
      version: '1.0.0',
      description: 'API for managing ATM operations',
      contact: {
        name: 'Martin Negin, Samu Lyhty, Veikka Koskinen, Topias Perälä',
        email: 'your.email@example.com',
      },
    },
    servers: [
      {
        url: 'https://atm.dev.zroot.it',
        description: 'Development server',
      },
    ],
    components: {
      securitySchemes: {
        BearerAuth: {
          type: 'http',
          scheme: 'bearer',
          bearerFormat: 'JWT',
        },
      },
    },
    security: [
      {
        BearerAuth: [],
      },
    ],
  },
  // Reitit, joista Swagger kerää tietoa
  apis: ['./routes/*.js'], // Tiedostopolku reitteihin
};

const swaggerDocs = swaggerJsDoc(swaggerOptions);

module.exports = (app) => {
  // Swagger UI -reitti
  app.use('/api-docs', swaggerUi.serve, swaggerUi.setup(swaggerDocs));
};