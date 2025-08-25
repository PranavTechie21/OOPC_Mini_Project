#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <regex>
#include <stdexcept>
#include <limits>
#include <algorithm>

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep(ms * 1000)
#endif

using namespace std;

// Utility function for cross-platform sleep
void sleep_ms(int milliseconds) {
    SLEEP(milliseconds);
}

// Utility function to clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

class Car {
protected:
    string id, model, brand;
    double mileage, monthlyRent;
    bool available;

public:
    Car(string _id, string _model, string _brand, double _mileage, double _rent)
        : id(_id), model(_model), brand(_brand), mileage(_mileage), monthlyRent(_rent), available(true) {}

    // Getter methods
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    string getId() const { return id; }
    double getMonthlyRent() const { return monthlyRent; }
    bool isAvailable() const { return available; }
    double getMileage() const { return mileage; }

    // Setter methods
    void setAvailable(bool val) { available = val; }

    // Virtual destructor
    virtual ~Car() = default;
    
    // Pure virtual functions
    virtual string getCategory() const = 0;
    virtual string getFuelType() const = 0;

    virtual void display() const {
        cout << "ID: " << id << ", Model: " << model
             << ", Brand: " << brand
             << ", Mileage: " << mileage << " km/l"
             << ", Monthly Rent: Rs" << monthlyRent
             << ", Available: " << (available ? "Yes" : "No")
             << ", Category: " << getCategory()
             << ", Fuel: " << getFuelType() << "\n";
    }
};

// EVCar class that inherits from Car
class EVCar : public Car {
public:
    EVCar(string id, string model, string brand, double mileage, double rent)
        : Car(id, model, brand, mileage, rent) {}

    string getCategory() const override { return "Normal"; }
    string getFuelType() const override { return "EV"; }
};

// PetrolCar class that inherits from Car
class PetrolCar : public Car {
public:
    PetrolCar(string id, string model, string brand, double mileage, double rent)
        : Car(id, model, brand, mileage, rent) {}

    string getCategory() const override { return "Normal"; }
    string getFuelType() const override { return "Petrol"; }
};

// Class representing an imported electric vehicle (EV) car
class ImportedEVCar : public EVCar {
public:
    ImportedEVCar(string id, string model, string brand, double mileage, double rent)
        : EVCar(id, model, brand, mileage, rent) {}

    string getCategory() const override { return "Imported"; }
};

class ImportedPetrolCar : public PetrolCar {
public:
    ImportedPetrolCar(string id, string model, string brand, double mileage, double rent)
        : PetrolCar(id, model, brand, mileage, rent) {}

    string getCategory() const override { return "Imported"; }
};

// Represents a customer with contact details
class Customer {
private:
    string name;
    string contact;
    string address;

public:
    Customer(string _name, string _contact, string _address = "") 
        : name(_name), contact(_contact), address(_address) {}

    string getName() const { return name; }
    string getContact() const { return contact; }
    string getAddress() const { return address; }
    
    void setAddress(string _address) { address = _address; }

    void display() const {
        cout << "Customer: " << name << ", Contact: " << contact;
        if (!address.empty()) {
            cout << ", Address: " << address;
        }
    }
};

// Booking class
class Booking {
    Customer customer;
    Car *car;
    double advancePayment;
    int deliveryDays;
    double finalCost;
    bool discountApplied;
    int rentDays;
    time_t bookingTime;

public:
    Booking(Customer _customer, Car *_car, int _rentDays, int _desiredDelivery)
        : customer(_customer), car(_car), advancePayment(0), discountApplied(false), 
          rentDays(_rentDays), bookingTime(time(nullptr)) {
        
        // Calculate base delivery days based on brand
        if (car->getBrand() == "Tata" || car->getBrand() == "Mahindra" || car->getBrand() == "Maruti")
            deliveryDays = 3 + rand() % 5; // 3 to 7 days
        else
            deliveryDays = 7 + rand() % 14; // 7 to 20 days

        // Adjust for user's desired delivery time
        if (_desiredDelivery < deliveryDays) {
            deliveryDays = _desiredDelivery;
        }

        // Calculate base cost
        finalCost = car->getMonthlyRent() * (rentDays / 30.0);

        // Apply discounts
        calculateDiscounts();

        // Apply urgent delivery surcharge
        if (deliveryDays < 10) {
            finalCost *= 1.10;
        }
    }

    void calculateDiscounts() {
        discountApplied = false;
        if (finalCost > 20000) {
            finalCost *= 0.95; // 5% discount
            discountApplied = true;
        }
        if (rentDays >= 30) {
            finalCost *= 0.90; // Additional 10% discount for monthly rentals
            discountApplied = true;
        }
    }

    void makeAdvancePayment(double amount) {
        if (amount < 1000) {
            throw invalid_argument("Minimum Rs1000 advance payment required!");
        }
        if (amount > finalCost) {
            throw invalid_argument("Advance payment cannot exceed final cost!");
        }
        advancePayment = amount;
    }

    void showSummary() const {
        cout << "\n=== BOOKING SUMMARY ===\n";
        customer.display();
        cout << "\nCar Details:\n";
        cout << "  Model: " << car->getModel() << " (" << car->getCategory() << ")\n";
        cout << "  Brand: " << car->getBrand() << "\n";
        cout << "  Fuel Type: " << car->getFuelType() << "\n";
        cout << "  Mileage: " << car->getMileage() << " km/l\n";
        
        cout << "\nRental Details:\n";
        cout << "  Duration: " << rentDays << " days\n";
        cout << "  Monthly Rent: Rs" << car->getMonthlyRent() << "\n";
        cout << "  Final Cost: Rs" << finalCost << "\n";
        
        if (discountApplied) {
            cout << "  ✓ Discounts Applied!\n";
        }
        
        cout << "\nPayment Details:\n";
        cout << "  Advance Payment: Rs" << advancePayment << "\n";
        cout << "  Remaining Amount: Rs" << (finalCost - advancePayment) << "\n";
        
        cout << "\nDelivery Details:\n";
        cout << "  Estimated Delivery: " << deliveryDays << " days\n";
        cout << "  " << (deliveryDays < 10 ? " Urgent delivery surcharge applied" : "Standard delivery") << "\n";
        
        cout << "\nBooking Time: " << ctime(&bookingTime);
        cout << "========================\n";
    }

    // Getter methods for file operations
    Customer getCustomer() const { return customer; }
    Car* getCar() const { return car; }
    double getFinalCost() const { return finalCost; }
    int getRentDays() const { return rentDays; }
    int getDeliveryDays() const { return deliveryDays; }
    double getAdvancePayment() const { return advancePayment; }
};

// Input validation functions
string inputName() {
    string name;
    regex nameRegex("^[A-Za-z ]{2,50}$");
    
    while (true) {
        cout << "Enter your name (2-50 characters, letters and spaces only): ";
        getline(cin, name);
        
        if (regex_match(name, nameRegex)) {
            return name;
        } else {
            cout << "Invalid name! Please use only letters and spaces (2-50 characters).\n";
        }
    }
}

string inputPhone() {
    string phone;
    regex phoneRegex("^[6-9][0-9]{9}$");
    
    while (true) {
        cout << "Enter your 10-digit phone number (starting with 6-9): ";
        getline(cin, phone);
        
        if (regex_match(phone, phoneRegex)) {
            return phone;
        } else {
            cout << "Invalid phone number! Please enter a 10-digit number starting with 6-9.\n";
        }
    }
}

string inputAddress() {
    string address;
    
    while (true) {
        cout << "Enter your address: ";
        getline(cin, address);

        if (address.length() >= 10 && address.length() <= 200) {
            // Confirm address
            string confirm;
            cout << "You entered: \"" << address << "\"\nIs this correct? (Y/N): ";
            getline(cin, confirm);
            
            if (confirm == "Y" || confirm == "y") {
                return address;
            }
        } else {
            cout << "Address must be between 10 and 200 characters!\n";
        }
    }
}

// File operations
void saveCustomer(const Customer &c) {
    try {
        ofstream file("customers.txt", ios::app);
        if (file.is_open()) {
            file << c.getName() << " | " << c.getContact() << " | " << c.getAddress() << "\n";
            file.close();
        } else {
            cout << "Warning: Could not save customer data to file.\n";
        }
    } catch (const exception &e) {
        cout << "Error saving customer data: " << e.what() << "\n";
    }
}

void saveBooking(const Booking &booking) {
    try {
        ofstream outFile("booking_summary.txt", ios::app);
        if (outFile.is_open()) {
            outFile << "----- Booking Summary -----\n";
            outFile << "Customer Name: " << booking.getCustomer().getName() << "\n";
            outFile << "Contact: " << booking.getCustomer().getContact() << "\n";
            outFile << "Address: " << booking.getCustomer().getAddress() << "\n";
            outFile << "Car ID: " << booking.getCar()->getId() << "\n";
            outFile << "Car Model: " << booking.getCar()->getModel() << "\n";
            outFile << "Brand: " << booking.getCar()->getBrand() << "\n";
            outFile << "Fuel Type: " << booking.getCar()->getFuelType() << "\n";
            outFile << "Category: " << booking.getCar()->getCategory() << "\n";
            outFile << "Rental Days: " << booking.getRentDays() << "\n";
            outFile << "Delivery Days: " << booking.getDeliveryDays() << "\n";
            outFile << "Final Cost: Rs" << booking.getFinalCost() << "\n";
            outFile << "Advance Paid: Rs" << booking.getAdvancePayment() << "\n";
            time_t now = time(nullptr);
            outFile << "Booking Time: " << ctime(&now);
            outFile << "---------------------------\n";
            outFile.close();
        } else {
            cout << "Error: Could not write booking summary to file.\n";
        }
    } catch (const exception &e) {
        cout << "Error saving booking: " << e.what() << "\n";
    }
}

class CarRentalSystem {
private:
    vector<Car *> cars;
    vector<string> upcomingModels = {"Tesla Model Y", "BMW iX", "Audi Q4 e-tron", "Mercedes EQS", "Porsche Taycan"};
    Customer currentUser{"Guest", "0000"};
    bool greeted = false;

public:
    CarRentalSystem() {
        initializeCars();
    }

    ~CarRentalSystem() {
        for (auto car : cars) {
            delete car;
        }
    }

    void initializeCars() {
        // Imported Petrol Cars
        cars.push_back(new ImportedPetrolCar("I01", "Audi A8", "Audi", 12, 45000));
        cars.push_back(new ImportedPetrolCar("I02", "BMW X5", "BMW", 10, 40000));
        cars.push_back(new ImportedPetrolCar("I03", "Mercedes-Benz GLE", "Mercedes", 8, 65000));
        cars.push_back(new ImportedPetrolCar("I04", "Audi Q7", "Audi", 6, 70000));
        cars.push_back(new ImportedPetrolCar("I05", "Porsche Macan", "Porsche", 4, 85000));

        // Normal Petrol Cars
        cars.push_back(new PetrolCar("N01", "Maruti Swift", "Maruti", 22, 8000));
        cars.push_back(new PetrolCar("N02", "Hyundai i20", "Hyundai", 18, 10000));
        cars.push_back(new PetrolCar("N03", "Tata Altroz", "Tata", 15, 9500));
        cars.push_back(new PetrolCar("N04", "Honda Amaze", "Honda", 20, 10500));

        // EV Cars
        cars.push_back(new EVCar("E01", "Tata Nexon EV", "Tata", 500, 15000));
        cars.push_back(new EVCar("E02", "Tata Tigor EV", "Tata", 200, 12000));
        cars.push_back(new EVCar("E03", "Tata Tiago EV", "Tata", 250, 11000));
        cars.push_back(new EVCar("E04", "Tata Punch EV", "Tata", 400, 13000));

        cars.push_back(new EVCar("M01", "Mahindra eKUV100", "Mahindra", 100, 14000));
        cars.push_back(new EVCar("M02", "Mahindra eXUV300", "Mahindra", 300, 20000));
        cars.push_back(new EVCar("M03", "Mahindra Treo", "Mahindra", 600, 9000));
        cars.push_back(new EVCar("M04", "Mahindra eVerito", "Mahindra", 700, 15000));

        cars.push_back(new EVCar("MG01", "MG ZS EV", "MG", 600, 29000));
        cars.push_back(new EVCar("MG02", "MG Astor EV", "MG", 500, 32000));
        cars.push_back(new EVCar("MG03", "MG Comet EV", "MG", 100, 12000));
        cars.push_back(new EVCar("MG04", "MG Hector EV", "MG", 1000, 35000));

        cars.push_back(new EVCar("H01", "Hyundai Kona Electric", "Hyundai", 250, 34000));
        cars.push_back(new EVCar("H02", "Hyundai Ioniq Electric", "Hyundai", 300, 32000));
        cars.push_back(new EVCar("H03", "Hyundai Aura EV", "Hyundai", 400, 28000));
        cars.push_back(new EVCar("H04", "Hyundai Creta EV", "Hyundai", 800, 30000));

        // Imported EV Cars
        cars.push_back(new ImportedEVCar("IE01", "Tesla Model 3", "Tesla", 800, 50000));
        cars.push_back(new ImportedEVCar("IE02", "BMW i4", "BMW", 600, 45000));
        cars.push_back(new ImportedEVCar("IE03", "Audi e-tron", "Audi", 400, 55000));
    }

    void setCurrentUser(const Customer &user) {
        currentUser = user;
    }

    void displayCurrentUser() {
        currentUser.display();
        cout << "\n";
    }

    void greet() {
        if (!greeted) {
            cout << "\nWelcome " << currentUser.getName() << " to the Car Rental System!\n";
            greeted = true;
        }
    }

    void listCars() {
        cout << "\n=== CAR FILTERING ===\n";
        cout << "1. EV Cars\n";
        cout << "2. Petrol Cars\n";
        cout << "3. All Cars\n";
        cout << "4. Back to Main Menu\n";
        cout << "Enter choice: ";
        
        int fuelChoice;
        cin >> fuelChoice;
        clearInputBuffer();
        
        if (fuelChoice == 4) return;

        string fuelFilter;
        switch (fuelChoice) {
            case 1: fuelFilter = "EV"; break;
            case 2: fuelFilter = "Petrol"; break;
            case 3: fuelFilter = "All"; break;
            default: 
                cout << "Invalid choice!\n";
                return;
        }

        // Get available brands for selected fuel type
        vector<string> brands;
        for (auto car : cars) {
            if (!car->isAvailable()) continue;
            if (fuelFilter != "All" && car->getFuelType() != fuelFilter) continue;
            
            if (find(brands.begin(), brands.end(), car->getBrand()) == brands.end()) {
                brands.push_back(car->getBrand());
            }
        }

        if (brands.empty()) {
            cout << "No cars available for this fuel type.\n";
            return;
        }

        // Sort brands alphabetically
        sort(brands.begin(), brands.end());

        cout << "\nAvailable Brands:\n";
        for (size_t i = 0; i < brands.size(); ++i) {
            cout << i + 1 << ". " << brands[i] << "\n";
        }
        cout << brands.size() + 1 << ". All Brands\n";
        cout << brands.size() + 2 << ". Back\n";
        cout << "Select brand: ";
        
        int brandChoice;
        cin >> brandChoice;
        clearInputBuffer();
        
        if (brandChoice == (int)brands.size() + 2) return;

        // Filter cars based on selection
        vector<Car *> matchingCars;
        for (auto car : cars) {
            if (!car->isAvailable()) continue;
            if (fuelFilter != "All" && car->getFuelType() != fuelFilter) continue;
            
            if (brandChoice <= (int)brands.size()) {
                if (car->getBrand() != brands[brandChoice - 1]) continue;
            }
            matchingCars.push_back(car);
        }

        if (matchingCars.empty()) {
            cout << "No cars found for the selected filters.\n";
            return;
        }

        // Display cars
        cout << "\n=== AVAILABLE CARS ===\n";
        for (size_t i = 0; i < matchingCars.size(); ++i) {
            cout << i + 1 << ". ";
            matchingCars[i]->display();
        }

        cout << "\nChoose a car number for rent or 0 to go back: ";
        int choice;
        cin >> choice;
        clearInputBuffer();
        
        if (choice <= 0 || choice > (int)matchingCars.size()) return;

        processCarRental(matchingCars[choice - 1]);
    }

    void processCarRental(Car *selectedCar) {
        cout << "\n=== RENTAL DETAILS ===\n";
        cout << "Selected Car: " << selectedCar->getModel() << " (" << selectedCar->getBrand() << ")\n";
        cout << "Monthly Rent: Rs" << selectedCar->getMonthlyRent() << "\n";

        // Get rental duration
        int rentDays;
        while (true) {
            cout << "Enter number of days for rental (1-365): ";
            cin >> rentDays;
            clearInputBuffer();
            
            if (rentDays > 0 && rentDays <= 365) break;
            cout << "Invalid input. Please enter a number between 1 and 365.\n";
        }

        // Get delivery preference
        int desiredDelivery;
        while (true) {
            cout << "Enter maximum acceptable delivery days (minimum 3 days): ";
            cin >> desiredDelivery;
            clearInputBuffer();
            
            if (desiredDelivery >= 3) break;
            cout << "Minimum delivery time is 3 days. Please enter a valid number.\n";
        }

        // Check delivery feasibility
        int baseDelivery = (selectedCar->getBrand() == "Tata" || 
                           selectedCar->getBrand() == "Mahindra" || 
                           selectedCar->getBrand() == "Maruti") ? 
                           (3 + rand() % 5) : (7 + rand() % 14);

        if (desiredDelivery < baseDelivery) {
            cout << "\nUrgent delivery requested but selected car cannot meet delivery time.\n";
            cout << "Do you want to see alternative cars for urgent delivery? (y/n): ";
            char altChoice;
            cin >> altChoice;
            clearInputBuffer();
            
            if (altChoice == 'y' || altChoice == 'Y') {
                showUrgentDeliveryAlternatives(selectedCar->getFuelType(), desiredDelivery);
                return;
            } else {
                cout << "Booking cancelled due to delivery constraints.\n";
                return;
            }
        }

        completeBooking(selectedCar, rentDays, desiredDelivery);
    }

    void showUrgentDeliveryAlternatives(string fuelType, int desiredDelivery) {
        vector<Car *> urgentCars;
        for (auto car : cars) {
            if (!car->isAvailable()) continue;
            if (car->getFuelType() != fuelType) continue;
            
            int cDelivery = (car->getBrand() == "Tata" || 
                            car->getBrand() == "Mahindra" || 
                            car->getBrand() == "Maruti") ? 
                            (3 + rand() % 5) : (7 + rand() % 14);
            
            if (cDelivery <= desiredDelivery) {
                urgentCars.push_back(car);
            }
        }

        if (urgentCars.empty()) {
            cout << "No alternative cars available for urgent delivery.\n";
            return;
        }

        cout << "\n URGENT DELIVERY ALTERNATIVES \n";
        for (size_t i = 0; i < urgentCars.size(); ++i) {
            cout << i + 1 << ". ";
            urgentCars[i]->display();
        }

        cout << "Select car number or 0 to cancel: ";
        int urgentChoice;
        cin >> urgentChoice;
        clearInputBuffer();
        
        if (urgentChoice <= 0 || urgentChoice > (int)urgentCars.size()) return;

        // Recursive call to process the new selection
        processCarRental(urgentCars[urgentChoice - 1]);
    }

    void completeBooking(Car *selectedCar, int rentDays, int desiredDelivery) {
        try {
            Booking booking(currentUser, selectedCar, rentDays, desiredDelivery);
            
            cout << "\n=== PAYMENT DETAILS ===\n";
            cout << "Final Cost: Rs" << booking.getFinalCost() << "\n";
            cout << "Minimum Advance: Rs1000\n";
            
            double amount;
            while (true) {
                cout << "Enter advance payment amount: Rs";
                cin >> amount;
                clearInputBuffer();
                
                if (amount >= 1000 && amount <= booking.getFinalCost()) break;
                cout << "Invalid amount! Must be between Rs1000 and Rs" << booking.getFinalCost() << "\n";
            }

            booking.makeAdvancePayment(amount);
            selectedCar->setAvailable(false);
            
            booking.showSummary();
            saveBooking(booking);
            
            cout << "\nBooking successful! Thank you for choosing our service.\n";
            cout << "We'll contact you at " << currentUser.getContact() << " for delivery updates.\n";
            
        } catch (const exception &e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    void showUpcomingModels() {
        cout << "\n=== UPCOMING CAR MODELS ===\n";
        for (size_t i = 0; i < upcomingModels.size(); ++i) {
            cout << i + 1 << ". " << upcomingModels[i] << "\n";
        }
        cout << "\nThese models will be available for booking next week!\n";
        cout << "Stay tuned for updates.\n";
    }

    void showMenu() {
        cout << "\n========== MAIN MENU ==========\n";
        cout << "1. Show Available Cars\n";
        cout << "2. See Upcoming Models\n";
        cout << "3. Show My Profile\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
    }

    void run() {
        while (true) {
            showMenu();
            int choice;
            cin >> choice;
            clearInputBuffer();
            
            switch (choice) {
                case 1:
                    listCars();
                    break;
                case 2:
                    showUpcomingModels();
                    break;
                case 3:
                    cout << "\n=== MY PROFILE ===\n";
                    displayCurrentUser();
                    break;
                case 4:
                    cout << "\nThank you for using our Car Rental System!\n";
                    cout << "Have a great day!\n";
                    return;
                default:
                    cout << "Invalid option! Please try again.\n";
            }
        }
    }
};

int main() {
    try {
        srand(time(nullptr));
        
        cout << "Welcome to the Car Rental System!\n";
        cout << "=====================================\n\n";
        
        // Get user information
        string name = inputName();
        string phone = inputPhone();
        string address = inputAddress();
        
        cout << "\nRegistering your details";
        for (int i = 0; i < 3; i++) {
            cout << ".";
            sleep_ms(500);
        }
        cout << "\nRegistration complete!\n";
        
        // Save customer data
        Customer user(name, phone, address);
        saveCustomer(user);
        
        // Initialize and run system
        CarRentalSystem system;
        system.setCurrentUser(user);
        system.greet();
        system.run();
        
    } catch (const exception &e) {
        cout << "Fatal error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}
