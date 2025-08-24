#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>  // for rand()
#include <ctime>    // for time()
#include <regex>

using namespace std;

// Base class for Petrol Car
class PetrolCar {
protected:
    string brand;
    string model;
    float mileage;
    int rentPerDay;
    int stockDays;
    bool available;

public:
    PetrolCar(string b, string m, float mil, int rent, int sd)
        : brand(b), model(m), mileage(mil), rentPerDay(rent), stockDays(sd), available(true) {}

    virtual string getFuelType() {
        return "Petrol";
    }
    string getBrand() {
        return brand;
    }


    virtual string getCategory() {
        return "Normal";
    }

    bool isAvailable() {
        return available;
    }

    void setUnavailable() {
        available = false;
    }

    int getRent() {
        return rentPerDay;
    }

    int getStockDays() {
        return stockDays;
    }

    void display() {
        cout << "Brand: " << brand << ", Model: " << model 
             << ", Mileage: " << mileage << " km/l, Rent/day: Rs." << rentPerDay 
             << ", Available: " << (available ? "Yes" : "No") << endl;
    }
};

// Derived class for Imported Petrol Car
class ImportedPetrolCar : public PetrolCar {
public:
    ImportedPetrolCar(string b, string m, float mil, int rent, int sd)
        : PetrolCar(b, m, mil, rent, sd) {}

    string getCategory() {
        return "Imported";
    }
};

// Base class for EV Car
class EVCar {
protected:
    string brand;
    string model;
    float mileage;
    int rentPerDay;
    int stockDays;
    bool available;

public:
    EVCar(string b, string m, float mil, int rent, int sd)
        : brand(b), model(m), mileage(mil), rentPerDay(rent), stockDays(sd), available(true) {}

    virtual string getFuelType() {
        return "Electric";
    }
    string getBrand() {
        return brand;
    }

    virtual string getCategory() {
        return "Normal";
    }

    bool isAvailable() {
        return available;
    }

    void setUnavailable() {
        available = false;
    }

    int getRent() {
        return rentPerDay;
    }

    int getStockDays() {
        return stockDays;
    }

    void display() {
        cout << "Brand: " << brand << ", Model: " << model 
             << ", Mileage: " << mileage << " km/kWh, Rent/day: Rs." << rentPerDay 
             << ", Available: " << (available ? "Yes" : "No") << endl;
    }
};

// Derived class for Imported EV Car
class ImportedEVCar : public EVCar {
public:
    ImportedEVCar(string b, string m, float mil, int rent, int sd)
        : EVCar(b, m, mil, rent, sd) {}

    string getCategory() {
        return "Imported";
    }
};

// Function to validate name using regex (alphabets + space only)
bool validateName(const string& name) {
    regex namePattern("^[A-Za-z ]+$");
    return regex_match(name, namePattern);
}

// Function to calculate delivery days randomly based on brand
int calculateDeliveryDays(const string& brand, int maxAllowedDays) {
    int days = 0;
    if (brand == "Tata" || brand == "Mahindra" || brand == "Maruti") {
        days = rand() % 5 + 1;  // 1 to 5 days
    } else {
        days = rand() % 10 + 6; // 6 to 15 days
    }
    if (days > maxAllowedDays) days = maxAllowedDays;
    return days;
}

int main() {
    srand(time(0));

    // Sample cars (version 5 style hardcoded list)
    vector<PetrolCar*> petrolCars;
    petrolCars.push_back(new PetrolCar("Tata", "Nexon", 17.5, 1500, 7));
    petrolCars.push_back(new ImportedPetrolCar("BMW", "X5", 10.0, 5000, 15));
    petrolCars.push_back(new PetrolCar("Maruti", "Swift", 20.0, 1200, 5));

    vector<EVCar*> evCars;
    evCars.push_back(new EVCar("Tata", "Tigor EV", 21.0, 2500, 10));
    evCars.push_back(new ImportedEVCar("Tesla", "Model 3", 30.0, 6000, 20));

    cout << "Welcome to Car Rental Service (Demo V5)" << endl;

    string customerName;
    do {
        cout << "Enter your full name (alphabets and spaces only): ";
        getline(cin, customerName);
        if (!validateName(customerName)) {
            cout << "Invalid name. Please try again." << endl;
        }
    } while (!validateName(customerName));

    cout << "Choose fuel type (Petrol / Electric): ";
    string fuelType;
    getline(cin, fuelType);

    // List available cars of chosen fuel type
    cout << "Available cars:" << endl;
    if (fuelType == "Petrol") {
        for (auto car : petrolCars) {
            if (car->isAvailable())
                car->display();
        }
    } else if (fuelType == "Electric") {
        for (auto car : evCars) {
            if (car->isAvailable())
                car->display();
        }
    } else {
        cout << "Invalid fuel type selected. Exiting." << endl;
        return 0;
    }

    // Simplified selection by brand input
    cout << "Enter the brand of the car you want to book: ";
    string selectedBrand;
    getline(cin, selectedBrand);

    // Find a car that matches brand and is available
    PetrolCar* selectedPetrolCar = nullptr;
    EVCar* selectedEVCar = nullptr;

    if (fuelType == "Petrol") {
for (auto car : petrolCars) {
    if (car->isAvailable() && car->getCategory() == "Imported" && car->getBrand() == selectedBrand) {
        selectedPetrolCar = car;
        break;
    }
    else if(car->isAvailable() && car->getBrand() == selectedBrand) {  // replaced brand with getBrand()
        selectedPetrolCar = car;
        break;
    }
}
        if (!selectedPetrolCar) {
            cout << "No matching petrol car available." << endl;
            return 0;
        }
    } else {
for (auto car : evCars) {
    if (car->isAvailable() && car->getBrand() == selectedBrand) {  // replaced brand with getBrand()
        selectedEVCar = car;
        break;
    }
}
        if (!selectedEVCar) {
            cout << "No matching EV available." << endl;
            return 0;
        }
    }

    int maxDeliveryDays;
    cout << "Enter maximum days you can wait for delivery: ";
    cin >> maxDeliveryDays;
    cin.ignore(); // clear input buffer

    int deliveryDays = 0;
// Delivery days calculation
if (fuelType == "Petrol") {
    deliveryDays = calculateDeliveryDays(selectedPetrolCar->getBrand(), maxDeliveryDays);  // replaced brand with getBrand()
} else {
    deliveryDays = calculateDeliveryDays(selectedEVCar->getBrand(), maxDeliveryDays);  // replaced brand with getBrand()
}

    cout << "Estimated delivery days: " << deliveryDays << endl;

    int rentDays;
    cout << "For how many days do you want to rent the car? ";
    cin >> rentDays;
    cin.ignore();

    int totalRent = 0;
    if (fuelType == "Petrol") {
        totalRent = rentDays * selectedPetrolCar->getRent();
    } else {
        totalRent = rentDays * selectedEVCar->getRent();
    }

    // Apply discount if total rent > 20000
    if (totalRent > 20000) {
        cout << "Discount of Rs. 2000 applied." << endl;
        totalRent -= 2000;
    }

    // Urgent surcharge if delivery < 10 days
    if (deliveryDays < 10) {
        cout << "Urgent delivery surcharge of Rs. 1000 applied." << endl;
        totalRent += 1000;
    }

    cout << "Total rent to pay: Rs. " << totalRent << endl;

    int advancePayment;
    do {
        cout << "Enter advance payment (minimum Rs. 1000): ";
        cin >> advancePayment;
        cin.ignore();
        if (advancePayment < 1000) {
            cout << "Advance payment too low. Please enter again." << endl;
        }
    } while (advancePayment < 1000);

    // Mark car unavailable
    if (fuelType == "Petrol") {
        selectedPetrolCar->setUnavailable();
    } else {
        selectedEVCar->setUnavailable();
    }

    // Save customer info to file
    ofstream outfile("customers.txt", ios::app);
    if (outfile.is_open()) {
        outfile << customerName << "," << selectedBrand << "," << fuelType << "," << rentDays << "," << totalRent << "\n";
        outfile.close();
        cout << "Booking confirmed and details saved." << endl;
    } else {
        cout << "Error saving booking details." << endl;
    }

    return 0;
}
