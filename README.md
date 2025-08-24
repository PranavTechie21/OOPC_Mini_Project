# Car Rental System – OOPC Mini Project

## 📖 Overview

The **Car Rental System** is a console-based application built in **C++** to demonstrate core **Object-Oriented Programming (OOP)** principles. It simulates a realistic workflow where customers can:

* Browse available cars 🚗
* Take a car on rent for number of days 📅
* Receive a **detailed billing summary** 💰

This project applies **Encapsulation, Inheritance, Polymorphism, and Abstraction** in a practical way.

---

## ✨ Features

| Feature                | Description                                                                  | Status         |
| ---------------------- | ---------------------------------------------------------------------------- | -------------- |
| **User Management**    | Register/login customers with input validation.                              | ✅ Implemented  |
| **Car Inventory**      | Maintain cars with ID, model, brand, category, fuel, rent/day, availability. | ✅ Implemented  |
| **Availability Check** | Show only available cars and prevent double booking.                         | ✅ Implemented  |
| **Booking & Return**   | Pick cars on rent for N days, update status, handle returns.                 | ✅ Implemented  |
| **Billing**            | Compute total cost with rent/day × days (+optional delivery/taxes).          | ✅ Implemented  |
| **Booking Summary**    | Generate customer, car, dates, cost, and advance details.                    | ✅ Implemented  |
| **File Handling**      | Persist customers, cars, and bookings using files.                           | ✅ Implemented  |
| **Admin Tools**        | Add/edit/remove cars, review bookings, simple reports.                       | 🟡 In Progress |
| **Future: Database**   | Migrate storage to MySQL/PostgreSQL with schema & queries.                   | 🔜 Planned     |
| **Future: UI/UX**      | GUI/web frontend, role-based access, dashboards.                             | 🔜 Planned     |

---

## 🖥️ Sample Booking Summary

```txt
----- Booking Summary -----
Customer Name: Pranav Oswal
Contact: 9988776655
Address: Dhankawdi Pune
Car ID: I01
Car Model: Audi A8
Brand: Audi
Fuel Type: Petrol
Category: Imported
Rental Days: 45
Delivery Days: 7
Final Cost: Rs63483.8
Advance Paid: Rs50000
Booking Time: Sun Aug 24 12:39:44 2025
---------------------------
```

---

## ⚙️ How to Run

```bash
git clone https://github.com/your-username/car-rental-system.git
cd car-rental-system
g++ main.cpp -o car_rental
./car_rental
```

---

## 🔑 OOP Concepts Used

* **Encapsulation** – Private fields with getters/setters for `Car`, `Customer`.
* **Inheritance** – `User` → `Customer`, `Admin`.
* **Polymorphism** – Pricing rules per category (e.g., Imported vs Local).
* **Abstraction** – Methods like `rentCar()`, `returnCar()`, `calculateBill()`.

---

## 📂 File Structure

```
car-rental-system/
│── demo1.cpp              # Blueprint: basic Car class + simple print
│── demo2.cpp              # Add Customer class + simple booking link
│── demo3.cpp              # Add multiple cars + availability check
│── demo4.cpp              # Add billing system + rental days logic
│── demo5.cpp              # Add booking summary + file handling
│── main.cpp               # Final integrated project file
│── booking_summary.txt    # Auto-generated booking summary output
│── README.md              # Project documentation

```

---

## 🚀 Future Enhancements

* Integration with **MySQL/PostgreSQL** for scalable storage.
* Development of a **GUI / Web frontend** for better usability.
* Advanced **reporting & analytics** for admins.
* Role-based access and authentication.

---

Made with 💻 and ❤️ by

Pranav Oswal

Aneesh Ojha

Piyush Ahir

Siddhay Bhole
