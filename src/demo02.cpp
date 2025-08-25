/*
Version 2 extends Version 1 by adding the fuel-specific subclasses. The visible changes are:

New Subclasses

EVCar class (inherits Car)

PetrolCar class (inherits Car)

Constructors Declared

EVCar(string, string, string, double, double, int);

PetrolCar(string, string, string, double, double, int);

Override Methods

string getCategory() const override;

string getFuelType() const override;
*/

// ----------- Car Rental System Blueprint: Version 2 -----------

#include <string>
using namespace std;

// Base Car class (from Version 1)
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
    Car(string _id, string _model, string _brand, double _mileage, double _rent, int _stockDays);
    virtual ~Car();
    virtual string getCategory() const = 0;
    virtual string getFuelType() const = 0;
    void setAvailable(bool availability);
    bool isAvailable() const;
    virtual void display() const;
};

// ----------- Version 2: Fuel-specific subclasses -----------

// EV Car subclass
class EVCar : public Car {
public:
    EVCar(string _id, string _model, string _brand, double _mileage, double _rent, int _stockDays);
    string getCategory() const override;
    string getFuelType() const override;
};

// Petrol Car subclass
class PetrolCar : public Car {
public:
    PetrolCar(string _id, string _model, string _brand, double _mileage, double _rent, int _stockDays);
    string getCategory() const override;
    string getFuelType() const override;
};

