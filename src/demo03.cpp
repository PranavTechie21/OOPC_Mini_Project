// ----------- Car Rental System Blueprint: Version 3 -----------
// New in Version 3:
//   ImportedEVCar (subclass of EVCar)
//     - Constructor: ImportedEVCar(string, string, string, double, double, int)
//     - Overrides:
//         string getCategory() const
//   ImportedPetrolCar (subclass of PetrolCar)
//     - Constructor: ImportedPetrolCar(string, string, string, double, double, int)
//     - Overrides:
//         string getCategory() const

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

// ----------- Version 3: Imported variants -----------
class ImportedEVCar : public EVCar {
public:
    ImportedEVCar(string _id, string _model, string _brand, double _mileage, double _rent, int _stockDays);
    string getCategory() const override;  // returns "Imported"
};

class ImportedPetrolCar : public PetrolCar {
public:
    ImportedPetrolCar(string _id, string _model, string _brand, double _mileage, double _rent, int _stockDays);
    string getCategory() const override;  // returns "Imported"
};
