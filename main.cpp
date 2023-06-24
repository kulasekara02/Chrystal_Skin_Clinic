#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Structure to represent a package
struct Package {
    string packageId;
    string packageName;
    double price;
};

// Function to display the available packages
void displayPackages(const vector<Package>& packages) {
    cout << "===================================" << endl;
    cout << "***Welcome To Chrystal Skin Clinic***" << endl;
    cout << "*** Billing System***" << endl;
    cout << "===================================" << endl;
    cout << "Available Packages:" << endl;
    cout << setw(10) << left << "Package ID" << setw(25) << left << "Package Name" << "Price (Rs.)" << endl;

    for (const Package& package : packages) {
        cout << setw(10) << left << package.packageId << setw(25) << left << package.packageName << fixed << setprecision(2) << package.price << endl;
    }
    cout << endl;
}

// Function to calculate the bill
double calculateBill(const vector<Package>& packages, const vector<int>& quantities) {
    double totalAmount = 0.0;
    for (size_t i = 0; i < packages.size(); i++) {
        totalAmount += packages[i].price * quantities[i];
    }
    return totalAmount;
}

int main() {
    const string username = "admin";
    const string password = "password";
    bool loggedIn = false;
    vector<Package> packages = {
        {"SKNACN01", "Acne", 3000.00},
        {"SKNBNS02", "Burns scar", 4500.00},
        {"SKNKPS03", "Keratosis Pilaris", 4500.00},
        {"SKNOPS04", "Open Pores", 3800.00},
        {"SKNXPA05", "Xanthelasma Palpebrarum", 5500.00},
        {"HRIMSTI02", "Scalp Micropigmentation Stimulation", 40000.00},
        {"HRILLT03", "Low Level Light Therapy", 28000.00},
        {"HRIPRP04", "PRP For Hair Loss Treatment", 35000.00},
        {"BDYEMS01", "EMS body toning", 15000.00},
        {"SKNWTS06", "Warts", 4800.00},
        {"SKNSDT07", "Sensitive Skin Dermal Therapy", 10000.00}
    };

    vector<int> quantities(packages.size(), 0); // Initialize quantities with 0

    while (!loggedIn) {
        string inputUsername, inputPassword;
        cout << "=== Login ===" << endl;
        cout << "Username: ";
        cin >> inputUsername;
        cout << "Password: ";
        cin >> inputPassword;

        if (inputUsername == username && inputPassword == password) {
            loggedIn = true;
            break;
        } else {
            cout << "Invalid username or password. Please try again." << endl;
        }
    }

    if (loggedIn) {
        bool exitProgram = false;
        while (!exitProgram) {
            int option;
            cout << "=== Main Menu ===" << endl;
            cout << "1. Calculate the Bill" << endl;
            cout << "2. View Products" << endl;
            cout << "3. Exit" << endl;
            cout << "Select an option: ";
            cin >> option;

            switch (option) {
                case 1: {
                    // Calculate the bill
                    double totalAmount = calculateBill(packages, quantities);
                    cout << "\nAmount Due\nRs." << fixed << setprecision(2) << totalAmount << endl;

                    // Save the receipt to a file
                    ofstream outputFile("receipt.txt");
                    if (outputFile.is_open()) {
                        outputFile << "*** Receipt ***" << endl;
                        for (size_t i = 0; i < packages.size(); i++) {
                            if (quantities[i] > 0) {
                                outputFile << "Package ID: " << packages[i].packageId << endl;
                                outputFile << "Package Name: " << packages[i].packageName << endl;
                                outputFile << "Quantity: " << quantities[i] << endl;
                                outputFile << "Subtotal: Rs." << fixed << setprecision(2) << packages[i].price * quantities[i] << endl;
                                outputFile << endl;
                            }
                        }
                        outputFile << "Total Amount Due: Rs." << fixed << setprecision(2) << totalAmount << endl;
                        outputFile.close();
                        cout << "Receipt saved to receipt.txt" << endl;
                    } else {
                        cout << "Unable to open the receipt.txt file for writing." << endl;
                    }
                    break;
                }
                case 2: {
                    // View available packages
                    displayPackages(packages);

                    // Allow the user to select package quantities
                    for (size_t i = 0; i < packages.size(); i++) {
                        int quantity;
                        cout << "Enter quantity for package " << packages[i].packageId << ": ";
                        cin >> quantity;
                        quantities[i] = quantity;
                    }
                    break;
                }
                case 3: {
                    // Exit the program
                    exitProgram = true;
                    break;
                }
                default:
                    cout << "Invalid option. Please try again." << endl;
            }
            cout << endl;
        }
    }

    cout << "Thank you for using the Chrystal Skin Clinic Billing System. Goodbye!" << endl;

    return 0;
}
