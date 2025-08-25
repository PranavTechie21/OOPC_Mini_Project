// ----------- Car Rental System Blueprint: Version 1 -----------
// Classes:
//   Car
//     - Constructors: Car(string, string, string, double, double, int)
//     - Destructor: virtual ~Car()
//     - Pure virtual methods:
//         string getCategory() const
//         string getFuelType() const
//     - Methods:
//         void setAvailable(bool)
//         bool isAvailable() const
//         virtual void display() const

#include <string>
using namespace std;

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
