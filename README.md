# TVT24KMO Ryhmä 3 ATM Kesken 

## Project Overview

This project is an ATM system developed by Group 3 for the TVT24KMO/OAMK School project. The project consists of two main components:
1. **Client**: Developed using Qt with C++.
2. **Backend**: Developed using Node.js and Express.js.

## Table of Contents

- [TVT24KMO Ryhmä 3 ATM Kesken](#tvt24kmo-ryhmä-3-atm-kesken)
  - [Project Overview](#project-overview)
  - [Table of Contents](#table-of-contents)
  - [Client](#client)
    - [Setup](#setup)
    - [Structure](#structure)
    - [Frameworks and Libraries](#frameworks-and-libraries)
    - [Usage](#usage)
    - [Settings](#settings)
  - [Backend](#backend)
    - [Setup](#setup-1)
    - [Structure](#structure-1)
    - [Frameworks and Libraries](#frameworks-and-libraries-1)
    - [API Documentation](#api-documentation)
  - [Database](#database)
  - [Deployment](#deployment)
  - [Contributors](#contributors)
  - [ER Diagram](#er-diagram)

## Client

### Setup

1. **Install Qt**: Ensure you have Qt installed on your system. You can download it from [here](https://www.qt.io/download).
2. **Clone the repository**:
    ```sh
    git clone https://github.com/tvt24kmo-project/group_3.git
    cd group_3/bank_automat
    ```
3. **Open the project in Qt Creator**:
    - Open `bank_automat.pro` in Qt Creator.
4. **Build and Run**:
    - Click on the build and run button in Qt Creator.

### Structure

- **main.cpp**: Entry point of the application.
- **mainwindow.cpp/h/ui**: Main window of the application.
- **pinscreen.cpp/h/ui**: PIN screen dialog.
- **translations/**: Directory for translation files.
- **build/**: Directory for build files (ignored by git).

### Frameworks and Libraries

The client uses the following frameworks and libraries:

- **Qt**: Cross-platform application development framework.
- **QNetworkAccessManager**: Class for sending network requests.
- **QJsonDocument**: Class for handling JSON data.
- **QJsonObject**: Class for handling JSON objects.
- **QJsonArray**: Class for handling JSON arrays.
- **QFile**: Class for handling file operations.
- **QDebug**: Class for debugging output.

### Usage

- **Start the application**: Click on the "Start" button in the main window.
- **Enter PIN**: Enter the PIN on the PIN screen.
- **Navigate**: Use the buttons to navigate between different screens (Debit, Credit, Transactions).

### Settings

The `settings.json` file is used to store configuration settings for the client application, including the ATM serial number. Here is an example of the `settings.json` file:

```json
{
  "atmserialnro": "SN12345"
}
```

## Backend

### Setup

1. **Install Node.js**: Ensure you have Node.js installed on your system. You can download it from [here](https://nodejs.org/).
2. **Clone the repository**:
    ```sh
    git clone https://github.com/tvt24kmo-project/group_3.git
    cd group_3/backend
    ```
3. **Install dependencies**:
    ```sh
    npm install
    ```
4. **Create `.env` file**:
    ```sh
    touch .env
    echo "PORT=3000" >> .env
    echo "MYSQL_SERVER=mysql://username:password@localhost:3306/bank_automat" >> .env
    echo "JWT_SECRET=your_jwt_secret" >> .env
    ```
5. **Start the server**:
    ```sh
    npm start
    ```

### Structure

- **app.js**: Main application file.
- **bin/www**: Script to start the server.
- **controllers/**: Directory for controller files.
- **models/**: Directory for model files.
- **routes/**: Directory for route files.
- **public/**: Directory for public files (HTML, CSS).
- **swagger.js**: Swagger setup for API documentation.
- **.env**: Environment variables file.
- **package.json**: Project metadata and dependencies.

### Frameworks and Libraries

The backend uses the following frameworks and libraries:

- **Node.js**: JavaScript runtime environment.
- **Express.js**: Web application framework for Node.js.
- **cookie-parser**: Middleware to parse cookies.
- **debug**: Debugging utility.
- **dotenv**: Module to load environment variables from a `.env` file.
- **jsonwebtoken**: Library to work with JSON Web Tokens.
- **morgan**: HTTP request logger middleware for Node.js.
- **mysql2**: MySQL client for Node.js.
- **pm2**: Production process manager for Node.js applications.
- **swagger-jsdoc**: Library to generate Swagger definitions from JSDoc comments.
- **swagger-ui-express**: Middleware to serve auto-generated Swagger API docs.

### API Documentation

The API documentation is available at `/api-docs` when the server is running. It is generated using Swagger.

## Database

The database schema and initial data are provided in the [db_dump.sql](http://_vscodecontentref_/2) file. To set up the database:

1. **Install MySQL**: Ensure you have MySQL installed on your system.
2. **Create the database**:
    ```sh
    mysql -u username -p < db_dump.sql
    ```

## Deployment

The project uses GitHub Actions for CI/CD. The workflows are defined in the workflows directory.

- **deploy-development.yml**: Workflow for deploying to the development environment.
- **Discord.yml**: Workflow for sending notifications to Discord.

## Contributors

- Martin Negin
- Samu Lyhty
- Veikka Koskinen
- Topias Perälä

## ER Diagram

![ER Diagram](DB_diagram.png)



