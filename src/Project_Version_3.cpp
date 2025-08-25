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

// Represents a customer with contact details and address
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

// Booking class with enhanced features
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
        cout << "  Monthly Rent: Rs" << car->getMonthlyRent() << "\n";
        cout << "\nBooking Details:\n";
        cout << "  Rental Duration: " << rentDays << " days\n";
        cout << "  Delivery Time: " << deliveryDays << " days\n";
        cout << "  Final Cost: Rs" << finalCost << "\n";
        if (discountApplied) {
            cout << "  Discount Applied: Yes\n";
        }
        cout << "  Advance Payment: Rs" << advancePayment << "\n";
        cout << "  Remaining Amount: Rs" << (finalCost - advancePayment) << "\n";
    }

    Customer getCustomer() const { return customer; }
    Car* getCar() const { return car; }
    double getFinalCost() const { return finalCost; }
    int getDeliveryDays() const { return deliveryDays; }
    int getRentDays() const { return rentDays; }
    double getAdvancePayment() const { return advancePayment; }
};

// Enhanced input validation functions
string inputName() {
    string name;
    regex namePattern("^[a-zA-Z ]{2,50}$");
    
    while (true) {
        cout << "Enter your name: ";
        getline(cin, name);
        
        if (regex_match(name, namePattern)) {
            return name;
        } else {
            cout << "Invalid name! Please enter 2-50 characters (letters and spaces only).\n";
        }
    }
}

string inputContact() {
    string contact;
    regex contactPattern("^[6-9][0-9]{9}$");
    
    while (true) {
        cout << "Enter your contact: ";
        getline(cin, contact);
        
        if (regex_match(contact, contactPattern)) {
            return contact;
        } else {
            cout << "Invalid contact! Please enter a 10-digit number starting with 6-9.\n";
        }
    }
}

string inputAddress() {
    string address;
    regex addressPattern("^[a-zA-Z0-9, .-]{10,200}$");
    
    while (true) {
        cout << "Enter your address: ";
        getline(cin, address);
        
        if (regex_match(address, addressPattern)) {
            cout << "Confirm address: " << address << " (y/n): ";
            char confirm;
            cin >> confirm;
            clearInputBuffer();
            
            if (tolower(confirm) == 'y') {
                return address;
            }
        } else {
            cout << "Invalid address! Please enter 10-200 characters.\n";
        }
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
            cout << "\n🚗 Welcome " << currentUser.getName() << " to the Car Rental System! 🚗\n";
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
        for (size_t i = 0; i < brands.size(); i++) {
            cout << (i + 1) << ". " << brands[i] << "\n";
        }

        cout << "\nEnter brand number (or 0 for all): ";
        int brandChoice;
        cin >> brandChoice;
        clearInputBuffer();

        string selectedBrand = "";
        if (brandChoice > 0 && brandChoice <= static_cast<int>(brands.size())) {
            selectedBrand = brands[brandChoice - 1];
        }

        cout << "\nAvailable Cars:\n";
        int count = 0;
        for (auto car : cars) {
            if (!car->isAvailable()) continue;
            if (fuelFilter != "All" && car->getFuelType() != fuelFilter) continue;
            if (!selectedBrand.empty() && car->getBrand() != selectedBrand) continue;
            
            cout << ++count << ". ";
            car->display();
        }
        
        if (count == 0) {
            cout << "No cars available for the selected criteria.\n";
        }
    }

    void bookCar() {
        listCars();
        
        cout << "\nEnter car number to book: ";
        int carChoice;
        cin >> carChoice;
        clearInputBuffer();

        if (carChoice < 1 || carChoice > cars.size()) {
            cout << "Invalid car choice!\n";
            return;
        }

        Car* selectedCar = nullptr;
        int count = 0;
        for (auto car : cars) {
            if (!car->isAvailable()) continue;
            count++;
            if (count == carChoice) {
                selectedCar = car;
                break;
            }
        }

        if (!selectedCar) {
            cout << "Car not available!\n";
            return;
        }

        cout << "\nEnter number of days to rent: ";
        int rentDays;
        cin >> rentDays;
        clearInputBuffer();

        if (rentDays <= 0) {
            cout << "Invalid rental duration!\n";
            return;
        }

        cout << "Enter desired delivery time (in days): ";
        int deliveryDays;
        cin >> deliveryDays;
        clearInputBuffer();

        if (deliveryDays <= 0) {
            cout << "Invalid delivery time!\n";
            return;
        }

        try {
            Booking booking(currentUser, selectedCar, rentDays, deliveryDays);
            
            cout << "\nEnter advance payment amount: ";
            double advance;
            cin >> advance;
            clearInputBuffer();

            booking.makeAdvancePayment(advance);
            selectedCar->setAvailable(false);
            
            booking.showSummary();
            
            // Save booking to file
            saveBookingToFile(booking);
            
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    void saveBookingToFile(const Booking& booking) {
        ofstream file("booking_summary.txt", ios::app);
        if (file.is_open()) {
            file << "=== NEW BOOKING ===\n";
            file << "Customer: " << booking.getCustomer().getName() << "\n";
            file << "Contact: " << booking.getCustomer().getContact() << "\n";
            if (!booking.getCustomer().getAddress().empty()) {
                file << "Address: " << booking.getCustomer().getAddress() << "\n";
            }
            file << "Car: " << booking.getCar()->getModel() << " (" << booking.getCar()->getBrand() << ")\n";
            file << "Rental Duration: " << booking.getRentDays() << " days\n";
            file << "Delivery Time: " << booking.getDeliveryDays() << " days\n";
            file << "Final Cost: Rs" << booking.getFinalCost() << "\n";
            file << "Advance Payment: Rs" << booking.getAdvancePayment() << "\n";
            file << "Remaining Amount: Rs" << (booking.getFinalCost() - booking.getAdvancePayment()) << "\n";
            file << "========================\n\n";
            file.close();
            cout << "\nBooking saved to file successfully!\n";
        } else {
            cout << "Error saving booking to file!\n";
        }
    }

    void loginUser() {
        cout << "\n=== USER LOGIN ===\n";
        string name = inputName();
        string contact = inputContact();
        string address = inputAddress();
        currentUser = Customer(name, contact, address);
        cout << "\n✅ Login successful!\n";
    }

    void showMenu() {
        cout << "\n=== CAR RENTAL SYSTEM ===";
        cout << "\n👤 Current User: " << currentUser.getName();
        cout << "\n\n1. Login/Register";
        cout << "\n2. View Profile";
        cout << "\n3. List Cars";
        cout << "\n4. Book Car";
        cout << "\n5. Exit";
        cout << "\nEnter choice: ";
    }

    void run() {
        while (true) {
            showMenu();
            int choice;
            cin >> choice;
            clearInputBuffer();

            switch (choice) {
                case 1:
                    loginUser();
                    break;
                case 2:
                    if (currentUser.getName() == "Guest") {
                        cout << "Please login first!\n";
                    } else {
                        displayCurrentUser();
                    }
                    break;
                case 3:
                    listCars();
                    break;
                case 4:
                    if (currentUser.getName() == "Guest") {
                        cout << "Please login first to book a car!\n";
                    } else {
                        bookCar();
                    }
                    break;
                case 5:
                    cout << "Thank you for using Car Rental System! 👋\n";
                    return;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
        }
    }
};

int main() {
    srand(time(nullptr));
    CarRentalSystem system;
    system.run();
    return 0;
}
