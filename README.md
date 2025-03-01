# TVT24KMO Ryhmä 3 ATM 

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
    - [Client Structure](#client-structure)
    - [Frameworks and Libraries](#frameworks-and-libraries)
    - [Usage](#usage)
    - [Settings](#settings)
  - [Backend](#backend)
    - [Setup](#setup-1)
    - [Structure](#structure)
    - [Frameworks and Libraries](#frameworks-and-libraries-1)
    - [API Documentation](#api-documentation)
  - [API Endpoint: Login to ATM](#api-endpoint-login-to-atm)
    - [POST /atm/{serialNumber}/login](#post-atmserialnumberlogin)
      - [Description](#description)
      - [Authentication](#authentication)
      - [Parameters](#parameters)
      - [Responses](#responses)
  - [API Endpoint: Get Account Details](#api-endpoint-get-account-details)
    - [GET /atm/{serialNumber}/account](#get-atmserialnumberaccount)
      - [Description](#description-1)
      - [Authentication](#authentication-1)
      - [Parameters](#parameters-1)
      - [Responses](#responses-1)
  - [API Endpoint: Get a List of Currencies](#api-endpoint-get-a-list-of-currencies)
    - [GET /currency](#get-currency)
      - [Description](#description-2)
      - [Authentication](#authentication-2)
      - [Responses](#responses-2)
  - [API Endpoint: Get Transaction History](#api-endpoint-get-transaction-history)
    - [GET /transactions/history/{account\_id}](#get-transactionshistoryaccount_id)
      - [Description](#description-3)
      - [Authentication](#authentication-3)
      - [Parameters](#parameters-2)
      - [Responses](#responses-3)
  - [API Endpoint: Make a Deposit](#api-endpoint-make-a-deposit)
    - [POST /transactions/deposit](#post-transactionsdeposit)
      - [Description](#description-4)
      - [Authentication](#authentication-4)
      - [Request Body](#request-body)
      - [Responses](#responses-4)
  - [API Endpoint: Make a Withdrawal](#api-endpoint-make-a-withdrawal)
    - [POST /transactions/withdraw](#post-transactionswithdraw)
      - [Description](#description-5)
      - [Authentication](#authentication-5)
      - [Request Body](#request-body-1)
      - [Responses](#responses-5)
    - [Swagger YAML](#swagger-yaml)
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

### Client Structure
![Client File Stucture](Client_Structure.PNG)
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

```sh
backend/
├── bin/
│   └── www
├── controllers/
│   ├── accounts/
│   │   └── accounts.js
│   ├── atm/
│   │   └── atm.js
│   ├── authentication/
│   │   ├── atmAuth.js
│   │   ├── authMiddleware.js
│   │   └── tokenUtils.js
│   ├── cards/
│   │   └── cards.js
│   ├── currency/
│   │   └── currency.js
│   ├── db/
│   │   └── database.js
│   ├── transactions/
│   │   ├── transactions.js
│   │   └── transactions_view.js
│   └── users/
│       ├── holders.js
│       └── owners.js
├── models/
│   ├── account_model.js
│   ├── atm.js
│   ├── card_model.js
│   ├── currency_model.js
│   ├── holder_model.js
│   ├── owner_model.js
│   ├── procedures_model.js
│   └── transaction_model.js
├── public/
│   ├── 404.html
│   ├── index.html
│   └── stylesheets/
│       ├── 404.png
│       ├── bg.gif
│       └── style.css
├── routes/
│   ├── atm.js
│   ├── currency.js
│   ├── index.js
│   ├── transactions.js
│   └── users.js
├── .env
├── .gitignore
├── app.js
├── package.json
└── swagger.js
```
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

## API Endpoint: Login to ATM

### POST /atm/{serialNumber}/login

#### Description
Login to an ATM using a card number and PIN.

#### Authentication
No authentication required for this endpoint.

#### Parameters
- **serialNumber** (string, required): The ATM's serial number.
- **credentials** (object, required, in body):
  - **cardNumber** (string, required): The card number.
  - **pin** (string, required): The PIN code.

#### Responses
- **200 OK**: Login successful.
  ```json
  {
    "token": "jwt_token_here",
    "atm": {
      "idatm": 1,
      "serial_number": "ATM12345",
      "ip_address": "192.168.1.1",
      "location": "Oulu"
    },
    "card": {
      "cardNumber": "1234567890123456",
      "cardType": "Debit",
      "attempts": 0,
      "issued": "2023-01-01T00:00:00Z",
      "valid": "2027-01-01T00:00:00Z",
      "status": 1,
      "account": {
        "accountNumber": "FI1234567890",
        "accountID": 101,
        "balance": "1000.50",
        "currency": "EUR"
      },
      "customer": {
        "firstName": "John",
        "lastName": "Doe"
      }
    }
  }
  ```
- **401 Unauthorized**: Invalid card number or PIN.
- **404 Not Found**: ATM not found.
- **500 Internal Server Error**: Unexpected error.

---

## API Endpoint: Get Account Details

### GET /atm/{serialNumber}/account

#### Description
Retrieve account details for the logged-in user.

#### Authentication
Requires a valid API token in the header.

#### Parameters
- **serialNumber** (string, required): The ATM's serial number.

#### Responses
- **200 OK**: Account details retrieved successfully.
  ```json
  {
    "message": "Success",
    "user": {
      "cardNumber": "1234567890123456"
    }
  }
  ```
- **401 Unauthorized**: Invalid or missing token.
- **404 Not Found**: ATM not found.

---

## API Endpoint: Get a List of Currencies

### GET /currency

#### Description
Retrieve a list of available currencies.

#### Authentication
No authentication required.

#### Responses
- **200 OK**: List of currencies retrieved successfully.
  ```json
  [
    {
      "id": 1,
      "currency_type": "USD",
      "currency_value": 1.0,
      "currency_symbol": "$"
    },
    {
      "id": 2,
      "currency_type": "EUR",
      "currency_value": 0.85,
      "currency_symbol": "€"
    }
  ]
  ```
- **500 Internal Server Error**: Unexpected error.

---

## API Endpoint: Get Transaction History

### GET /transactions/history/{account_id}

#### Description
Retrieve the transaction history for a specific account.

#### Authentication
Requires a valid API token in the header.

#### Parameters
- **account_id** (string, required): The ID of the account.
- **serialNumber** (string, required, in body): The serial number of the ATM.

#### Responses
- **200 OK**: Transaction history retrieved successfully.
  ```json
  {
    "message": "Success",
    "data": [
      {
        "idtrans": 1,
        "account_id": 101,
        "trans_amount": "50.00",
        "trans_date": "2025-02-01T12:00:00Z",
        "trans_method": "Withdrawal"
      }
    ]
  }
  ```
- **400 Bad Request**: Missing required parameters.
- **401 Unauthorized**: Invalid or missing token.
- **404 Not Found**: ATM not found.
- **500 Internal Server Error**: Unexpected error.

---

## API Endpoint: Make a Deposit

### POST /transactions/deposit

#### Description
Deposit money into an account.

#### Authentication
Requires a valid API token in the header.

#### Request Body
- **account_id** (string, required): The ID of the account.
- **amount** (number, required): The deposit amount.
- **idatm** (string, required): The ATM ID.
- **idcard** (string, required): The card ID.
- **serialNumber** (string, required): The ATM serial number.

#### Responses
- **200 OK**: Deposit successful.
- **400 Bad Request**: Missing required parameters.
- **401 Unauthorized**: Invalid or missing token.
- **404 Not Found**: ATM not found.
- **500 Internal Server Error**: Unexpected error.

---

## API Endpoint: Make a Withdrawal

### POST /transactions/withdraw

#### Description
Withdraw money from an account.

#### Authentication
Requires a valid API token in the header.

#### Request Body
- **account_id** (string, required): The ID of the account.
- **amount** (number, required): The withdrawal amount.
- **idatm** (string, required): The ATM ID.
- **idcard** (string, required): The card ID.
- **serialNumber** (string, required): The ATM serial number.

#### Responses
- **200 OK**: Withdrawal successful.
- **400 Bad Request**: Missing required parameters.
- **401 Unauthorized**: Invalid or missing token.
- **404 Not Found**: ATM not found.
- **500 Internal Server Error**: Unexpected error.

### Swagger YAML

The Swagger YAML file is located at `swagger.yaml` in the root directory of the backend project. It defines the API endpoints, request/response schemas, and other details for the API documentation.

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
## ER Diagram
![Esittelyvideo](https://www.youtube.com/embed/pzEEPkySRms)




