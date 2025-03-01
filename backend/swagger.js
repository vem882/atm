const swaggerJsDoc = require('swagger-jsdoc');
const swaggerUi = require('swagger-ui-express');
const yaml = require('js-yaml');
const fs = require('fs');
const path = require('path');

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
        url: 'http://localhost',
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

// Generate YAML file
const swaggerYaml = yaml.dump(swaggerDocs);
const yamlFilePath = path.join(__dirname, 'swagger.yaml');
fs.writeFileSync(yamlFilePath, swaggerYaml);

module.exports = (app) => {
  // Swagger UI -reitti
  app.use('/api-docs', swaggerUi.serve, swaggerUi.setup(swaggerDocs));

  // Serve the YAML file
  app.get('/swagger.yaml', (req, res) => {
    res.sendFile(yamlFilePath);
  });

  // Add a link to download the YAML file in Swagger UI
  app.get('/api-docs', (req, res) => {
    res.send(`
      <html>
        <head>
          <title>Swagger UI</title>
          <link rel="stylesheet" type="text/css" href="https://cdnjs.cloudflare.com/ajax/libs/swagger-ui/3.52.5/swagger-ui.css">
        </head>
        <body>
          <div id="swagger-ui"></div>
          <script src="https://cdnjs.cloudflare.com/ajax/libs/swagger-ui/3.52.5/swagger-ui-bundle.js"></script>
          <script>
            window.onload = function() {
              const ui = SwaggerUIBundle({
                url: '/swagger.yaml',
                dom_id: '#swagger-ui',
                presets: [
                  SwaggerUIBundle.presets.apis,
                  SwaggerUIBundle.SwaggerUIStandalonePreset
                ],
                layout: "StandaloneLayout"
              });
              ui.initOAuth({
                clientId: "your-client-id",
                clientSecret: "your-client-secret",
                realm: "your-realms",
                appName: "your-app-name",
                scopeSeparator: " ",
                additionalQueryStringParams: {}
              });
            };
          </script>
          <a href="/swagger.yaml" download="swagger.yaml">Download YAML</a>
        </body>
      </html>
    `);
  });
};