# Car-Rental-System

A C++ car rental system with incremental versions and a simple website front-end scaffold.

## Project Structure
```
Car-Rental-System/
│
├── src/                          
│   ├── demo01.cpp               # Demo 1 - Initial blueprint implementation
│   ├── demo02.cpp               # Demo 2 - Added classes & encapsulation
│   ├── demo03.cpp               # Demo 3 - Added inheritance features
│   ├── demo04.cpp               # Demo 4 - Extended booking & billing
│   ├── demo05.cpp               # Demo 5 - Near final with file handling
│   ├── Project_Version_1.cpp    # Version 1 - Base working version
│   ├── Project_Version_2.cpp    # Version 2 - Intermediate improved version
│   ├── Project_Version_3.cpp    # Version 3 - Pre-final version
│   └── Car_Rental_System.cpp    # Final integrated system (main project file)
│
├── data/
│   ├── booking_summary.txt      # Auto-generated booking summary (latest booking)
│   └── customers.txt            # Stores all customer records
│
├── website/                     # Web front-end (future)
│   ├── index.html               # Landing page
│   ├── style.css                # Styling
│   └── script.js                # Functionality / logic
│
└── README.md                    # Main project documentation
```

## Build & Run (Windows)
```
# Example: build final system
cd src
g++ -std=c++17 -O2 -o Car_Rental_System.exe Car_Rental_System.cpp
./Car_Rental_System.exe
```

## Build & Run (Linux/Mac)
```
cd src
g++ -std=c++17 -O2 -o Car_Rental_System Car_Rental_System.cpp
./Car_Rental_System
```

## Website
Static landing page under `website/`. Open `website/index.html` in a browser.

## Notes
- Data files in `data/` are written by the C++ apps (append mode).
- Demos show incremental concepts; versions show progression to the final system.
