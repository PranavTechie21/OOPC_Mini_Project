// ----------- Car Rental System Blueprint: Version 4 -----------
// New in Version 4:
//   Customer class for storing user details and loyalty
//     - Constructor: Customer(string, string, int)
//     - Methods:
//         string getName() const
//         string getContact() const
//         int getYears() const
//         void display() const

#include <string>
using namespace std;

// Base Car class (from previous versions)
class Car {
protected:
    string id;
    string model;
    string brand;
    double mileage;
    double monthlyRent;
    bool available;
    int stockDays;
public:
    Car(string, string, string, double, double, int);
    virtual ~Car();
    virtual string getCategory() const = 0;
    virtual string getFuelType() const = 0;
    void setAvailable(bool);
    bool isAvailable() const;
    virtual void display() const;
};

// EVCar and PetrolCar from Version 2
class EVCar : public Car {
public:
    EVCar(string, string, string, double, double, int);
    string getCategory() const override;
    string getFuelType() const override;
};

class PetrolCar : public Car {
public:
    PetrolCar(string, string, string, double, double, int);
    string getCategory() const override;
    string getFuelType() const override;
};

// Imported variants from Version 3
class ImportedEVCar : public EVCar {
public:
    ImportedEVCar(string, string, string, double, double, int);
    string getCategory() const override;
};

class ImportedPetrolCar : public PetrolCar {
public:
    ImportedPetrolCar(string, string, string, double, double, int);
    string getCategory() const override;
};

// ----------- Version 4: Customer Management -----------

class Customer {
private:
    string name;
    string contact;
    int yearsWithCompany;
public:
    Customer(string _name, string _contact, int _years);
    string getName() const;
    string getContact() const;
    int getYears() const;
    void display() const;  // prints customer details and loyalty
};