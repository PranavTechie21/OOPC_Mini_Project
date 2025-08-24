#include <iostream>  // For console I/O
#include <string>    // For using std::string
#include <vector>    // For std::vector (dynamic arrays)
#include <fstream>   // For file input/output operations
#include <ctime>     // For seeding randomness and date/time utilities
#include <cstdlib>   // For rand(), srand()
#include <regex>     // For regex-based input validation
#include <stdexcept> // For exception handling (like invalid_argument)
#include <limits>    // For numeric limits like INT_MAX
#include <unistd.h>  // For sleep()
/*    or
We can use .....#include<bits/stdc++.h>
*/
using namespace std;

class Car
{
protected:
    string id, model, brand;
    double mileage, monthlyRent;
    bool available;

public:
    Car(string _id, string _model, string _brand, double _mileage, double _rent)
    {
        // Assign parameters to class members step-by-step
        id = _id;
        model = _model;
        brand = _brand;
        mileage = _mileage;
        monthlyRent = _rent;
        available = true; // Default to available when car is added
    }

    // Getter method for brand
    string getBrand() const
    {
        return brand;
    }

    // Getter method for model
    string getModel() const
    {
        return model;
    }

    // Getter method for monthly rent
    double getMonthlyRent() const
    {
        return monthlyRent;
    }

    // Checks if the car is available
    bool isAvailable() const
    {
        return available;
    }

    // Sets the availability status of the car
    void setAvailable(bool val)
    {
        available = val;
    }

    // Getter method for car mileage
    double getMileage() const
    {
        return mileage;
    }
    // Virtual destructor
    virtual ~Car()
    {
    }
    virtual string getCategory() const = 0;
    virtual string getFuelType() const = 0;

    virtual void display() const
    {
        cout << "ID: " << id << ", Model: " << model
             << ", Brand: " << brand
             << ", Mileage: " << mileage << " km/l"
             << ", Monthly Rent: Rs" << monthlyRent
             << ", Available: " << (available ? "Yes" : "No")
             << ", Category: " << getCategory()
             << ", Fuel: " << getFuelType()
             << "\n";
    }
};
// EVCar class that inherits from Car
class EVCar : public Car
{
public:
    // Constructor: initializes an EVCar with basic car properties
    EVCar(string id, string model, string brand, double mileage, double rent, int stockDays)
        : Car(id, model, brand, mileage, rent)
    {
        // we will add EV-specific setup here in the future
    }
    // Overrides the base class method to return the category
    string getCategory() const override
    {
        return "Normal";
    }
    string getFuelType() const override
    {
        return "EV";
    }
};
// PetrolCar class that inherits from Car
class PetrolCar : public Car
{
public:
    // Constructor  sets up a petrol car with given details
    PetrolCar(string id, string model, string brand, double mileage, double rent, int stockDays)
        : Car(id, model, brand, mileage, rent)
    {
    }
    string getCategory() const override
    {
        return "Normal";
    }
    string getFuelType() const override
    {
        return "Petrol";
    }
};

// Class representing an imported electric vehicle (EV) car inheriting from ev car
class ImportedEVCar : public EVCar
{
public:
    // Constructor initializes all properties by calling the base EVCar constructor
    ImportedEVCar(string id, string model, string brand, double mileage, double rent, int stockDays)
        : EVCar(id, model, brand, mileage, rent, stockDays) {}

    string getCategory() const override
    {
        return "Imported";
    }
};

class ImportedPetrolCar : public PetrolCar
{
public:
    // Constructor initializes all properties by calling the base PetrolCar constructor
    ImportedPetrolCar(string id, string model, string brand, double mileage, double rent, int stockDays)
        : PetrolCar(id, model, brand, mileage, rent, stockDays) {}

    string getCategory() const override
    {
        return "Imported";
    }
};

// Represents a customer with contact details and loyalty duration
class Customer
{
private:
    string name;
    string contact;

public:
    Customer(string _name, string _contact) : name(_name), contact(_contact) {}

    string getName() const
    {
        return name;
    }
    string getContact() const
    {
        return contact;
    }
    void display() const
    {
        cout << "Customer: " << name << ", Contact: " << contact;
    }
};

// Booking class
class Booking
{
    Customer customer;
    Car *car;
    double advancePayment;
    int deliveryDays; // estimated delivery days
    double finalCost;
    bool discountApplied;
    int rentDays; // number of days user wants to rent

public:
    Booking(Customer _customer, Car *_car, int _rentDays, int _desiredDelivery)
        : customer(_customer), car(_car), advancePayment(0), discountApplied(false), rentDays(_rentDays)
    {
        // Base deliveryDays, but if user wants earlier delivery than base, we handle later.
        if (car->getBrand() == "Tata" || car->getBrand() == "Mahindra" || car->getBrand() == "Maruti")
            deliveryDays = 3 + rand() % 5; // 3 to 7 days
        else
            deliveryDays = 7 + rand() % 14; // 7 to 20 days approx

        // Check if user requested delivery is less than available delivery
        if (_desiredDelivery < deliveryDays)
        {
            deliveryDays = _desiredDelivery; // User wants earlier delivery
        }

        // Calculate base monthly rent proportionally by days
        finalCost = car->getMonthlyRent() * (rentDays / 30.0);

        calculateDiscounts();

        // If deliveryDays < 10, add surcharge for urgent delivery (10% surcharge)
        if (deliveryDays < 10)
        {
            finalCost *= 1.10;
        }
    }

    void calculateDiscounts()
    {
        discountApplied = false;
        if (finalCost > 20000)
        {
            finalCost *= 0.95;
            discountApplied = true;
        }
    }

    void makeAdvancePayment(double amount)
    {
        if (amount < 1000)
            throw invalid_argument("Minimum Rs1000 advance payment required!");
        advancePayment = amount;
    }

    void showSummary() const
    {
        cout << "\nBooking Summary:\n";
        customer.display();
        cout << "\n Car Booked: " << car->getModel() << " (" << car->getCategory() << ")\n";
        cout << "Fuel Type: " << car->getFuelType() << "\n";
        cout << "Rent Duration: " << rentDays << " days\n";
        cout << "Monthly Rent: Rs" << car->getMonthlyRent() << "\n";
        cout << "Final Cost after Discounts and Delivery Charges: Rs" << finalCost << "\n";
        if (discountApplied)
            cout << "Discounts Applied!\n";
        cout << "Advance Payment: Rs" << advancePayment << "\n";
        cout << "Estimated Delivery: " << deliveryDays << " days\n";
    }
};

string inputAddress()
{
    string address;
    while (true)
    {
        cout << "Enter your address: ";
        getline(cin, address);

        if (address.empty())
        {
            cout << "Address cannot be empty!\n";
            continue;
        }

        // Confirm address
        string confirm;
        cout << "You entered: \"" << address << "\". Is this correct? (Y/N): ";
        getline(cin, confirm);
        if (confirm == "Y" || confirm == "y")
        {
            return address;
        }
        else
        {
            cout << "Let's try entering the address again.\n";
        }
    }
}

void saveCustomer(const Customer &c)
{
    ofstream file("customers.txt", ios::app);
    file << c.getContact() << " ";
}

// Declare inputName() before CarRentalSystem uses it
string inputName()
{
    string name;
    regex nameRegex("^[A-Za-z ]+$");
    while (true)
    {
        cout << "Enter your name: ";
        getline(cin, name);
        if (regex_match(name, nameRegex))
        {
            return name;
        }
        else
        {
            cout << "Invalid name! Only alphabets and spaces allowed.\n";
        }
    }
}

class CarRentalSystem
{
    public:
    vector<Car *> cars;
    vector<string> upcomingModels = {"Tesla Model Y", "BMW iX", "Audi Q4 e-tron"};
    Customer currentUser{"Guest", "0000"};
    bool greeted = false;

    void loginUser()
    {
        string name = inputName();

        string contact;
        cout << "Enter your contact: ";
        getline(cin, contact);

        cin.ignore(); // to clear newline left in the buffer

        currentUser = Customer(name, contact);
    }
    void setCurrentUser(const Customer &user)
    {
        currentUser = user;
    }

    void displayCurrentUser()
    {
        currentUser.display();
    }

    CarRentalSystem()
    {
        // Added imported and normal EV and Petrol cars
        //: EVCar(id, model, brand, mileage, rent, stockDays) {}
        cars.push_back(new ImportedPetrolCar("I01", "Audi A8", "Audi", 12, 45000, 200));
        cars.push_back(new ImportedPetrolCar("I02", "BMW X5", "BMW", 10, 40000, 50));
        cars.push_back(new ImportedPetrolCar("I03", "Mercedes-Benz GLE", "Mercedes", 8, 65000, 45));
        cars.push_back(new ImportedPetrolCar("I04", "Audi Q7", "Audi", 6, 70000, 55));
        cars.push_back(new ImportedPetrolCar("I05", "Porsche Macan", "Porsche", 4, 85000, 60));

        cars.push_back(new PetrolCar("N01", "Maruti Swift", "Maruti", 22, 8000, 20));
        cars.push_back(new PetrolCar("N02", "Hyundai i20", "Hyundai", 18, 10000, 300));
        cars.push_back(new PetrolCar("N03", "Tata Altroz", "Tata", 15, 9500, 37));
        cars.push_back(new PetrolCar("N04", "Honda Amaze", "Honda", 20, 10500, 35));

        cars.push_back(new EVCar("E01", "Tata Nexon EV", "Tata", 500, 15000, 60));
        cars.push_back(new EVCar("E02", "Tata Tigor EV", "Tata", 200, 12000, 26));
        cars.push_back(new EVCar("E03", "Tata Tiago EV", "Tata", 2500, 11000, 24));
        cars.push_back(new EVCar("E04", "Tata Punch EV", "Tata", 400, 13000, 35));

        cars.push_back(new EVCar("M01", "Mahindra eKUV100", "Mahindra", 100, 14000, 35));
        cars.push_back(new EVCar("M02", "Mahindra eXUV300", "Mahindra", 300, 20000, 39));
        cars.push_back(new EVCar("M03", "Mahindra Treo", "Mahindra", 600, 9000, 10));
        cars.push_back(new EVCar("M04", "Mahindra eVerito", "Mahindra", 700, 15000, 21));

        cars.push_back(new EVCar("MG01", "MG ZS EV", "MG", 600, 29000, 44));
        cars.push_back(new EVCar("MG02", "MG Astor EV", "MG", 500, 32000, 38));
        cars.push_back(new EVCar("MG03", "MG Comet EV", "MG", 100, 12000, 24));   // small hatch
        cars.push_back(new EVCar("MG04", "MG Hector EV", "MG", 1000, 35000, 50)); // concept/expected

        cars.push_back(new EVCar("H01", "Hyundai Kona Electric", "Hyundai", 250, 34000, 39));
        cars.push_back(new EVCar("H02", "Hyundai Ioniq Electric", "Hyundai", 300, 32000, 38));
        cars.push_back(new EVCar("H03", "Hyundai Aura EV", "Hyundai", 400, 28000, 36));  // hypothetical EV variant
        cars.push_back(new EVCar("H04", "Hyundai Creta EV", "Hyundai", 800, 30000, 40)); // upcoming EV SUV
    }

    ~CarRentalSystem()
    {
        for (auto c : cars)
            delete c;
    }

    void greet()
    {
        if (!greeted)
        {
            cout << "\nWelcome " << currentUser.getName() << " to the Car Rental System!\n";
            greeted = true;
        }
    }

    void listCars()
    {
        cout << "\nFilter by Fuel Type:\n";
        cout << "1. EV\n2. Petrol\n3. All\n4. Exit\n";
        cout << "Enter choice: ";
        int fuelChoice;
        cin >> fuelChoice;
        if (fuelChoice == 4)
            return;

        string fuelFilter;
        if (fuelChoice == 1)
            fuelFilter = "EV";
        else if (fuelChoice == 2)
            fuelFilter = "Petrol";
        else
            fuelFilter = "All";

        // Show list of brands for selected fuel type
        vector<string> brands;
        for (auto c : cars)
        {
            if (!c->isAvailable())
                continue;
            if (fuelFilter != "All" && c->getFuelType() != fuelFilter)
                continue;
            if (find(brands.begin(), brands.end(), c->getBrand()) == brands.end())
                brands.push_back(c->getBrand());
        }
        if (brands.empty())
        {
            cout << "No cars available for this fuel type.\n";
            return;
        }

        cout << "\nAvailable Brands:\n";
        for (size_t i = 0; i < brands.size(); ++i)
            cout << i + 1 << ". " << brands[i] << "\n";
        cout << brands.size() + 1 << ". All\n";
        cout << brands.size() + 2 << ". Exit\n";
        cout << "Select brand: ";
        int brandChoice;
        cin >> brandChoice;
        if (brandChoice == brands.size() + 2)
            return;

        vector<Car *> matchingCars;
        for (auto c : cars)
        {
            if (!c->isAvailable())
                continue;
            if (fuelFilter != "All" && c->getFuelType() != fuelFilter)
                continue;
            if (brandChoice <= brands.size())
            {
                if (c->getBrand() != brands[brandChoice - 1])
                    continue;
            }
            matchingCars.push_back(c);
        }

        if (matchingCars.empty())
        {
            cout << "No cars found for the selected filters.\n";
            return;
        }

        cout << "\nAvailable Cars:\n";
        for (size_t i = 0; i < matchingCars.size(); ++i)
        {
            cout << i + 1 << ". ";
            matchingCars[i]->display();
        }

        cout << "\nChoose a car number for rent or 0 to go back: ";
        int choice;
        cin >> choice;
        if (choice <= 0 || choice > (int)matchingCars.size())
            return;

        // Ask user rental days and delivery preference
        int rentDays;
        while (true)
        {
            cout << "Enter number of days you want the car for rent: ";
            cin >> rentDays;
            if (rentDays > 0)
                break;
            cout << "Invalid input. Please enter a positive number.\n";
        }

        int desiredDelivery;
        while (true)
        {
            cout << "Enter maximum acceptable delivery days (min 3days): ";
            cin >> desiredDelivery;
            if (desiredDelivery >= 3)
            {
                break;
            }
            else if ((desiredDelivery < 3) && (desiredDelivery > 0))
            {
                cout << "Sorry not possible to deliver in less than 3 days!";
                break;
            }
            else
            {
                cout << "Invlid input" << endl;
            }
        }

        Car *selectedCar = matchingCars[choice - 1];

        // Check if delivery days of selected car can meet desired delivery
        int baseDelivery = (selectedCar->getBrand() == "Tata" || selectedCar->getBrand() == "Mahindra" || selectedCar->getBrand() == "Maruti") ? (3 + rand() % 5) : (7 + rand() % 14);
        if (desiredDelivery < baseDelivery)
        {
            cout << "\nUrgent delivery requested but selected car cannot meet delivery time.\n";
            // Offer options for urgent delivery alternative cars
            cout << "Do you want to see alternative cars available for urgent delivery? (y/n): ";
            char altChoice;
            cin >> altChoice;
            if (altChoice == 'y' || altChoice == 'Y')
            {
                vector<Car *> urgentCars;
                for (auto c : cars)
                {
                    if (!c->isAvailable())
                        continue;
                    // Fuel type match
                    if (fuelFilter != "All" && c->getFuelType() != fuelFilter)
                        continue;
                    // Delivery time check
                    int cDelivery = (c->getBrand() == "Tata" || c->getBrand() == "Mahindra" || c->getBrand() == "Maruti") ? (3 + rand() % 5) : (7 + rand() % 14);
                    if (cDelivery <= desiredDelivery)
                    {
                        urgentCars.push_back(c);
                    }
                }
                if (urgentCars.empty())
                {
                    cout << "No alternative cars available for urgent delivery.\n";
                    return;
                }
                cout << "\nUrgent Delivery Available Cars:\n";
                for (size_t i = 0; i < urgentCars.size(); ++i)
                {
                    cout << i + 1 << ". ";
                    urgentCars[i]->display();
                }
                cout << "Select car number or 0 to cancel: ";
                int urgentChoice;
                cin >> urgentChoice;
                if (urgentChoice <= 0 || urgentChoice > urgentCars.size())
                    return;
                selectedCar = urgentCars[urgentChoice - 1];
            }
            else
            {
                cout << "Booking cancelled due to delivery constraints.\n";
                return;
            }
        }
        rentCar(selectedCar, rentDays, desiredDelivery);
    }
    void showMenu()
    {
        cout << "\n---------  MAIN MENU  ---------\n";
        cout << "1. Show Available Cars\n";
        // cout << "2. Rent a Car\n";
        cout << "2. See Upcoming Car Models\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
    }
    void rentCar(Car *selectedCar, int rentDays, int desiredDelivery)
    {
        Booking booking(currentUser, selectedCar, rentDays, desiredDelivery);
        cout << "Enter advance payment amount(Minimum Rs 1000): ";
        double amount;
        cin >> amount;
        try
        {
            booking.makeAdvancePayment(amount);
            selectedCar->setAvailable(false);
            booking.showSummary();
            ofstream outFile("booking_summary.txt", ios::app);
            if (outFile)
            {
                outFile << "----- Booking Summary -----\n";
                outFile << "Customer Name: " << currentUser.getName() << "\n";
                outFile << "Contact: " << currentUser.getContact() << "\n";
                outFile << "Car Model: " << selectedCar->getModel() << "\n";
                outFile << "Brand: " << selectedCar->getBrand() << "\n";
                outFile << "Fuel Type: " << selectedCar->getFuelType() << "\n";
                outFile << "Rental Days: " << rentDays << "\n";
                outFile << "Delivery Days: " << desiredDelivery << "\n";
                outFile << "Advance Paid: " << amount << "\n";
                outFile << "---------------------------\n";
                outFile.close();
                cout << "\nThank-you for booking!.\nVisit again\n";
                exit(1);
            }
            else
            {
                cout << "Error: Could not write booking summary to file.\n";
            }
        }
        catch (const exception &e)
        {
            cout << "Error: " << e.what() << "\n";
        }
    }
    void showUpcomingModels()
    {
        cout << "\nUpcoming Car Models:\n";
        for (const auto &model : upcomingModels)
        {
            cout << "- " << model << "\n";
        }
        cout << "If u want upcoming models please visit next week\nThank you Sir or Madam\n";
    }
    void run()
    {
        while (true)
        {
            showMenu();
            int ch;
            cin >> ch;
            switch (ch)
            {
            case 1:
                listCars();
                break;
            case 2:
                showUpcomingModels();
                break;
            case 3:
                cout << "Goodbye!\n";
                return;
            default:
                cout << "Invalid option!\n";
            }
        }
    }
};
string inputPhone()
{
    string phone;
    regex phoneRegex("^[6-9][0-9]{9}$");
    while (true)
    {
        cout << "Enter your 10-digit phone number starting with 6-9: ";
        getline(cin, phone);
        if (regex_match(phone, phoneRegex))
        {
            return phone;
        }
        else
        {
            cout << "Invalid phone number! Try again.\n";
        }
    }
}
int main()
{
    srand(time(NULL));
    cout << "Welcome to the Car Rental System!\n";
    string name = inputName();
    string phone = inputPhone();
    string address = inputAddress();
    cout << " Registering Your Details...\n";
    sleep(2);
    cout << "Sir/Madam Till That time What would you like Vadapav...Samosa\n";
    sleep(4);
    saveCustomer(Customer(name, phone));
    Customer user(name, phone);
    CarRentalSystem system;
    system.setCurrentUser(user);
    system.greet();              // Greets with actual user info
    system.displayCurrentUser(); // Optional: show user info
    system.run();
    return 0;
}
