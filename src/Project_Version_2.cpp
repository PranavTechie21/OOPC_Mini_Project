#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <regex>
#include <stdexcept>
#include <limits>

// Cross-platform sleep implementation
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
    Car(string _id, string _model, string _brand, double _mileage, double _rent) {
        id = _id;
        model = _model;
        brand = _brand;
        mileage = _mileage;
        monthlyRent = _rent;
        available = true;
    }

    // Getter methods
    string getBrand() const { return brand; }
    string getModel() const { return model; }
    double getMonthlyRent() const { return monthlyRent; }
    bool isAvailable() const { return available; }
    double getMileage() const { return mileage; }

    // Setter methods
    void setAvailable(bool val) { available = val; }

    // Virtual destructor
    virtual ~Car() {}
    
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

public:
    Customer(string _name, string _contact) : name(_name), contact(_contact) {}

    string getName() const { return name; }
    string getContact() const { return contact; }
    
    void display() const {
        cout << "Customer: " << name << ", Contact: " << contact;
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

public:
    Booking(Customer _customer, Car *_car, int _rentDays, int _desiredDelivery)
        : customer(_customer), car(_car), advancePayment(0), discountApplied(false), rentDays(_rentDays) {
        
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

        // Apply basic discount for high-value bookings
        if (finalCost > 20000) {
            finalCost *= 0.95; // 5% discount
            discountApplied = true;
        }
    }

    void makeAdvancePayment(double amount) {
        if (amount < 1000) {
            throw invalid_argument("Minimum Rs1000 advance payment required!");
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

// Input validation functions
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

class CarRentalSystem {
public:
    vector<Car *> cars;
    vector<string> upcomingModels = {"Tesla Model Y", "BMW iX", "Audi Q4 e-tron"};
    Customer currentUser{"Guest", "0000"};
    bool greeted = false;

    void loginUser() {
        string name = inputName();
        string contact = inputContact();
        currentUser = Customer(name, contact);
    }

    void setCurrentUser(const Customer &user) {
        currentUser = user;
    }

    void displayCurrentUser() {
        currentUser.display();
    }

    CarRentalSystem() {
        // Added imported and normal EV and Petrol cars
        cars.push_back(new ImportedPetrolCar("I01", "Audi A8", "Audi", 12, 45000));
        cars.push_back(new ImportedPetrolCar("I02", "BMW X5", "BMW", 10, 40000));
        cars.push_back(new ImportedPetrolCar("I03", "Mercedes-Benz GLE", "Mercedes", 8, 65000));
        cars.push_back(new ImportedPetrolCar("I04", "Audi Q7", "Audi", 6, 70000));
        cars.push_back(new ImportedPetrolCar("I05", "Porsche Macan", "Porsche", 4, 85000));

        cars.push_back(new PetrolCar("N01", "Maruti Swift", "Maruti", 22, 8000));
        cars.push_back(new PetrolCar("N02", "Hyundai i20", "Hyundai", 18, 10000));
        cars.push_back(new PetrolCar("N03", "Tata Altroz", "Tata", 15, 9500));
        cars.push_back(new PetrolCar("N04", "Honda Amaze", "Honda", 20, 10500));

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
    }

    ~CarRentalSystem() {
        for (auto car : cars) {
            delete car;
        }
    }

    void greet() {
        if (!greeted) {
            cout << "\nWelcome " << currentUser.getName() << " to the Car Rental System!\n";
            greeted = true;
        }
    }

    void listCars() {
        cout << "\nFilter by Fuel Type:\n";
        cout << "1. EV\n2. Petrol\n3. All\n4. Exit\n";
        cout << "Enter choice: ";
        int fuelChoice;
        cin >> fuelChoice;
        clearInputBuffer();
        
        if (fuelChoice == 4) return;

        string fuelFilter;
        if (fuelChoice == 1) fuelFilter = "EV";
        else if (fuelChoice == 2) fuelFilter = "Petrol";
        else fuelFilter = "All";

        cout << "\nAvailable Cars:\n";
        int count = 0;
        for (auto car : cars) {
            if (!car->isAvailable()) continue;
            if (fuelFilter != "All" && car->getFuelType() != fuelFilter) continue;
            
            cout << ++count << ". ";
            car->display();
        }
        
        if (count == 0) {
            cout << "No cars available for this fuel type.\n";
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

    void showMenu() {
        cout << "\n=== CAR RENTAL SYSTEM ===\n";
        cout << "1. Login\n";
        cout << "2. View Profile\n";
        cout << "3. List Cars\n";
        cout << "4. Book Car\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
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
                    displayCurrentUser();
                    break;
                case 3:
                    listCars();
                    break;
                case 4:
                    bookCar();
                    break;
                case 5:
                    cout << "Thank you for using Car Rental System!\n";
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
