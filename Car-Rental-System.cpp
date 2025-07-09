#include <iostream>
#include <string>
using namespace std;

// Car Rental Data
const int MAX_CARS = 4;
const int MAX_RENTALS = 100;
string carNames[MAX_CARS] = {"BMW", "Ford", "Land Cruiser", "SUV"};
float carPrices[MAX_CARS] = {70, 60, 57, 80};
int carAvailable[MAX_CARS] = {10, 7, 5, 3};

// Rental Records
string rentedCars[MAX_RENTALS];
string renters[MAX_RENTALS][3]; // [0]=name, [1]=phone, [2]=city
string rentedColors[MAX_RENTALS];
int rentalDays[MAX_RENTALS];
float rentalCosts[MAX_RENTALS];
int rentalCount = 0;

// User Accounts
const int MAX_USERS = 100;
string usernames[MAX_USERS];
string passwords[MAX_USERS];
int userCount = 0;

void registerUser() {
    if (userCount >= MAX_USERS) {
        cout << "User registration limit reached." << endl;
        return;
    }

    string newUsername, newPassword;
    cout << endl << "=== Register New Account ===" << endl;
    cout << "Choose a username: ";
    cin >> newUsername;

    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == newUsername) {
            cout << "Username already exists. Try a different one." << endl;
            return;
        }
    }

    cout << "Choose a password: ";
    cin >> newPassword;

    usernames[userCount] = newUsername;
    passwords[userCount] = newPassword;
    userCount++;

    cout << "Registration successful! You can now log in." << endl;
}

bool login(string &loggedInUsername) {
    int attempts = 0;
    string username, password;

    while (attempts < 3) {
        cout << endl << "=== Login ===" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        for (int i = 0; i < userCount; i++) {
            if (usernames[i] == username && passwords[i] == password) {
                cout << "Login successful!" << endl;
                loggedInUsername = username;
                return true;
            }
        }

        cout << "Login failed." << endl;
        attempts++;
    }

    cout << "Maximum attempts reached. System locked." << endl;
    return false;
}

float calculateDiscount(int days, float cost) {
    if (days > 10) return cost * 0.10;
    else if (days > 5) return cost * 0.05;
    return 0.0;
}

void showAvailableCars() {
    cout << endl << "Available Cars:" << endl;
    for (int i = 0; i < MAX_CARS; i++) {
        cout << i + 1 << ". " << carNames[i]" << " - $" << carPrices[i] << "/day - ";
        if (carAvailable[i] > 0)
            cout << carAvailable[i] << " available" << endl;
        else
            cout << "SOLD OUT" << endl;
    }
}

void rentCar(string customerInfo[3]) {
    int choice, days, insurance;
    

    showAvailableCars();
    cout << "Select a car (1-4): ";
    cin >> choice;

    if (choice < 1 || choice > MAX_CARS) {
        cout << "Invalid choice." << endl;
        return;
    }

    int index = choice - 1;
    if (carAvailable[index] <= 0) {
        cout << "Sorry, this car is SOLD OUT."<< " in "  << endl;
        return;
    }

    cout << "Enter rental days for " << carNames[index] << ": ";
    cin >> days;
    if (days <= 0) {
        cout << "Invalid number of days." << endl;
        return;
    }

    cout << "Add insurance (5%)? (1=Yes / 0=No): ";
    cin >> insurance;

    float cost = carPrices[index] * days;
    float discount = calculateDiscount(days, cost);
    float insuranceCost = insurance ? cost * 0.05 : 0;
    float finalCost = cost - discount + insuranceCost;

    carAvailable[index]--;
    rentedCars[rentalCount] = carNames[index]; + " (" + selectedColor + ")";
    renters[rentalCount][0] = customerInfo[0];
    renters[rentalCount][1] = customerInfo[1];
    renters[rentalCount][2] = customerInfo[2];
    rentalDays[rentalCount] = days;
    rentalCosts[rentalCount] = finalCost;
    rentalCount++;

    cout << endl << "Rental Successful!" << endl;
    cout << "Car: " << carNames[index] << endl;
    cout << "Days: " << days << endl;
    cout << "Total Cost: $" << finalCost << endl;
}

void returnCar(string customerName) {
    cout << endl << "Your Rentals:" << endl;
    bool hasRentals = false;
    int customerRentals[MAX_RENTALS];
    int count = 0;

    for (int i = 0; i < rentalCount; i++) {
        if (renters[i][0] == customerName) {
            hasRentals = true;
            customerRentals[count] = i;
            cout << count + 1 << ". " << rentedCars[i] << " (" << rentalDays[i]
                 << " days) - $" << rentalCosts[i] << endl;
            count++;
        }
    }

    if (!hasRentals) {
        cout << "No rentals found under your name." << endl;
        return;
    }

    cout << "Select rental to return (1-" << count << "): ";
    int choice;
    cin >> choice;

    if (choice < 1 || choice > count) {
        cout << "Invalid selection." << endl;
        return;
    }

    int rentalIndex = customerRentals[choice - 1];
    string carName = rentedCars[rentalIndex];

    for (int i = 0; i < MAX_CARS; i++) {
        if (carNames[i] == carName) {
            carAvailable[i]++;
            break;
        }
    }

    cout << carName << " returned successfully!" << endl;
}

void viewHistory(string customerName) {
    cout << endl << "Your Rental History:" << endl;
    bool found = false;

    for (int i = 0; i < rentalCount; i++) {
        if (renters[i][0] == customerName) {
            found = true;
            cout << "Customer: " << renters[i] [0]<< endl;
            cout << "Car: " << rentedCars[i] << endl;
            cout << "Days: " << rentalDays[i] << endl;
            cout << "Cost: $" << rentalCosts[i] << endl;
            cout << "Phone: " << renters[i][1] << endl;
            cout << "City: " << renters[i][2] << endl;
            cout << "-----------------------" << endl;
        }
    }

    if (!found) {
        cout << "No rental history found." << endl;
    }
}

int main() {
    string customerInfo[3]; // [0]=name, [1]=phone, [2]=city
    string loggedInUser;

    cout << "========================================" << endl;
    cout << "       Welcome to XYZ Car Rental        " << endl;
    cout << "========================================" << endl << endl;

    int entryChoice;
    cout << "1. Register" << endl;
    cout << "2. Login" << endl;
    cout << "Choose an option: ";
    cin >> entryChoice;

    if (entryChoice == 1) {
        registerUser();
    }

    if (!login(loggedInUser)) {
        return 0;
    }

    // Name input
    cout << endl << "Enter your first name: ";
    string firstName, lastName;
    cin >> firstName;
    cout << "Enter your last name: ";
    cin >> lastName;
    customerInfo[0] = firstName + " " + lastName;
    
    // Phone input
    cout << "Enter your phone number: ";
    cin >> customerInfo[1];
    
    // City input
    cout << "Enter your city: ";
    cin >> customerInfo[2];

    while (true) {
        cout << endl << "Main Menu:" << endl;
        cout << "1. Rent a Car" << endl;
        cout << "2. Return a Car" << endl;
        cout << "3. View Rental History" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose option (1-4): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                rentCar(customerInfo);
                break;
            case 2:
                returnCar(customerInfo[0]);
                break;
            case 3:
                viewHistory(customerInfo[0]);
                break;
            case 4:
                cout << "Thank you for using XYZ Car Rental!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
}
