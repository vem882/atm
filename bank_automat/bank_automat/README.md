# BANK_AUTOMAT/README.md

# Bank Automat

## Project Overview
The Bank Automat project is a Qt-based application designed to simulate an ATM interface. It allows users to enter their card number and PIN, navigate through different account options, and perform transactions such as deposits and withdrawals.

## File Structure
- **src/**: Contains the source code files for the application.
  - **checker.cpp**: Implements the `Checker` class for checking resource file existence.
  - **main.cpp**: Entry point of the application, initializes the `MainWindow`.
  - **mainwindow.cpp**: Implements the `MainWindow` class for the main user interface.
  - **pinscreen.cpp**: Implements the `PinScreen` class for PIN entry dialog.
  - **checker.h**: Header file for the `Checker` class.
  - **mainwindow.h**: Header file for the `MainWindow` class.
  - **pinscreen.h**: Header file for the `PinScreen` class.
  - **mainwindow.ui**: User interface definition for the `MainWindow`.
  - **pinscreen.ui**: User interface definition for the `PinScreen`.
  - **resources.qrc**: Qt resource file for icons and translations.
  - **translations/**: Contains translation files for multiple languages.
    - **translations_en.ts**: English translations.
    - **translations_fi.ts**: Finnish translations.
    - **translations_sv.ts**: Swedish translations.

- **settings.json**: Contains the ATM serial number (SN12345) used in API calls.

- **bank_automat.pro**: Project file for the Qt application, specifying sources, headers, forms, resources, and translations.

## Features
- User-friendly interface for entering card details and PIN.
- Multi-language support with translations for English, Finnish, and Swedish.
- Resource checking for icons and other assets.
- Secure PIN entry with limited attempts.

## Usage
To run the application, ensure you have the Qt framework installed. Open the project file (`bank_automat.pro`) in Qt Creator, build the project, and run it.

## API Integration
Upon successful PIN entry, the application will make a call to the REST API to retrieve a bearer token for further transactions.

## License
This project is licensed under the MIT License.