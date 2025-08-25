# 🚗 Car Rental System
A console-based Car Rental System project demonstrating core Object-Oriented Programming (OOP) concepts with a realistic car rental workflow.


## 📖 Overview

A **console-based Car Rental System** implemented in **C++** to demonstrate core **Object-Oriented Programming Concepts (OOPC)** such as **Encapsulation, Inheritance, Polymorphism, and Abstraction**.

The system allows customers to browse available cars, book them for a given number of days, and generates a **booking summary** with costs and customer details. File handling ensures persistent storage of booking records and customer information.

---

## 📂 Project Structure

```
Car-Rental-System/
│
├── src/                         
│   ├── demo01.cpp               # Demo 1 - Initial blueprint implementation
│   ├── demo02.cpp               # Demo 2 - Added classes & encapsulation
│   ├── demo03.cpp               # Demo 3 - Added inheritance features
│   ├── demo04.cpp               # Demo 4 - Extended booking & billing
│   ├── demo05.cpp               # Demo 5 - File handling introduced
│   ├── Project_Version_1.cpp    # Version 1 - Base working version
│   ├── Project_Version_2.cpp    # Version 2 - Intermediate improvements
│   ├── Project_Version_3.cpp    # Version 3 - Pre-final version
│   └── Car_Rental_System.cpp    # Final integrated system (main project file)
│
├── data/
│   ├── booking_summary.txt      # Auto-generated booking summaries
│   └── customers.txt            # Customer records (Name | Contact | Address)
│
├── website/                     # Future Web UI (HTML, CSS, JS)
│   ├── index.html
│   ├── style.css
│   └── script.js
│
└── README.md                    # Project documentation
```

---

## ⚙️ Features

| Feature               | Description                                                                 | Status     |
| --------------------- | --------------------------------------------------------------------------- | ---------- |
| 👤 User Management    | Register/login customers; basic input validation                            | ✅ Done     |
| 🚘 Car Inventory      | Maintain cars with ID, model, brand, category, fuel, rent/day, availability | ✅ Done     |
| 📋 Availability Check | Prevent double-booking; only list available cars                            | ✅ Done     |
| 📝 Booking & Return   | Rent cars for N days; update status and return                              | ✅ Done     |
| 💰 Billing            | Calculates rent = days × rate (+ delivery, taxes)                           | ✅ Done     |
| 📄 Booking Summary    | Generates detailed text summary file                                        | ✅ Done     |
| 📂 File Handling      | Stores bookings & customer details in `.txt` files                          | ✅ Done     |
| 🛠️ Admin Tools       | Add/remove cars, review reports                                             | 🟡 Partial |
| 🗄️ Database Support  | Future: migrate to MySQL/PostgreSQL                                         | 🔜 Planned |
| 🌐 Web Frontend       | Future: HTML/CSS/JS dashboard                                               | 🔜 Planned |

---

## 🚀 How to Run

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/Car-Rental-System.git
   cd Car-Rental-System/src
   ```

2. Compile the final project:

   ```bash
   g++ Car_Rental_System.cpp -o car_rental
   ```

3. Run the program:

   ```bash
   ./car_rental
   ```

---

## 🧾 Sample Booking Summary

```
----- Booking Summary -----
Customer Name: Pranav Oswal
Contact: 9988776655
Address: London England
Car ID: I01
Car Model: Audi A8
Brand: Audi
Fuel Type: Petrol
Category: Imported
Rental Days: 45
Delivery Days: 7
Final Cost: Rs63483.8
Advance Paid: Rs50000
Booking Time: Sun Jul 20 12:39:44 2025
---------------------------
```

---

## 🏆 Acknowledgements

* C++ OOP concepts: **Encapsulation, Inheritance, Polymorphism, Abstraction**
* **File Handling** for persistent storage of bookings and customers
* Hands-on project for stronger understanding of **real-world OOP design**

---

## ✍️ Authors

Made with 💻 and ❤️ by

* **Pranav Oswal**
* **Aneesh Ojha**
* **Piyush Ahir**
* **Siddhay Bhole**

---

## 🤝 Contributing

Pull requests are welcome!
If you’d like to add features (like DB support or a web frontend), fork the repo and submit a PR 🚀.
