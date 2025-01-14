Subscriber Management System

This project is a simple Subscriber Management System designed to handle different types of subscribers: Residential, Corporate Commercial, and Corporate Industrial. The system calculates the bill for each subscriber based on their consumption and type, and displays the information in an organized manner.
Contents

    Features
    File Descriptions
    Installation
    Usage
    Example Usage
    Contributing
    License

Features

    Subscriber Types: Supports three types of subscribers:
        Residential (Mesken): Calculates bills based on the consumption limit and unit price.
        Corporate Commercial (Kurumsal Ticarethane): For commercial institutions with a specific unit price.
        Corporate Industrial (Kurumsal Sanayi): For industrial institutions with a different unit price.

    Bill Calculation: The bill is calculated based on the consumption. For residential subscribers, a tiered pricing system applies, while corporate subscribers have fixed prices.

    File Input: Subscriber information is read from a file (aboneler.txt) and subscribers are created dynamically based on the information.

    Dynamic Memory Management: The system uses dynamic memory allocation to handle a variable number of subscribers.

    Formatted Output: The system prints formatted tables showing the details and calculated bill for each subscriber type.

File Descriptions

    subscriber_system.cpp: The main source code file containing the C++ implementation of the subscriber management system.
    aboneler.txt: The input file containing subscriber information in the format described below. This file is read by the program to dynamically create subscriber objects.

Example input format in aboneler.txt:

M 123 John Doe 100
S 456 Alice Smith 200 XYZ Corp
T 789 Bob Johnson 300 ABC Inc

Installation

To compile the program, you'll need a C++11 or higher compatible compiler such as GCC, Clang, or MSVC. Once you have a C++ compiler installed, follow these steps:

    Clone this repository to your local machine:

git clone https://github.com/yourusername/subscriber-management.git
cd subscriber-management

Compile the program:

    g++ -o subscriber_system subscriber_system.cpp

    Make sure the aboneler.txt file is present in the same directory as the compiled executable.

Usage

Once compiled, you can run the program with:

./subscriber_system

The program will:

    Read the subscriber information from aboneler.txt.
    Create the appropriate subscriber objects based on the information.
    Print the subscriber lists categorized by type: Residential, Corporate Commercial, and Corporate Industrial.
    Display the subscriber's information along with their calculated bill.

Example Usage
Residential Subscribers

Mesken Abone Listesi:
ID    Ad           Soyad        Tuketim       Fatura Tutari
-------------------------------------------------------
123   John         Doe          100           140.00
456   Alice        Smith        50            70.00

Corporate Commercial Subscribers

Kurumsal Ticarethane Abone Listesi:
ID    Ad           Soyad        Kurum Adi      Tuketim       Fatura Tutari
--------------------------------------------------------------------------------
789   Bob          Johnson      XYZ Corp        300           330.00

Corporate Industrial Subscribers

Kurumsal Sanayi Abone Listesi:
ID    Ad           Soyad        Kurum Adi      Tuketim       Fatura Tutari
--------------------------------------------------------------------------------
123   Charlie      Brown        ABC Inc         400           160.00

Contributing

We welcome contributions to the project! To contribute, follow these steps:

    Fork the repository.
    Create a new branch (git checkout -b feature-branch).
    Make your changes and commit them (git commit -am 'Add new feature').
    Push your branch (git push origin feature-branch).
    Create a new pull request.

Please ensure your changes don't break existing functionality, and add tests if possible.
License

This project is licensed under the MIT License - see the LICENSE file for details.
