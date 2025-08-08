# 🎟️ E-Booking Platform

A complete object-oriented **E-Booking Platform** implemented in C++, simulating an integrated system for **movie ticket booking**, **food ordering**, and **cab services**. This project uses design patterns (Factory, Singleton, Inheritance), smart pointers, STL containers, and custom exception handling to create a real-world scalable console-based booking system.

---

## 📌 Features

- 🎬 Book movie tickets by choosing from a list of theaters and movies
- 🍔 Order food items along with movie booking
- 🚕 Book cabs from source to destination with fare calculation
- 👥 Customer-specific accounts with account balance management
- 🧠 Exception handling for booking failures (e.g., no seats, out-of-stock food, insufficient balance)
- 🛠️ Design Patterns Used:
  - Factory Pattern
  - Singleton Pattern (Bank Account)
  - Inheritance & Polymorphism
- 🧹 Smart pointers used for all dynamic memory handling (no leaks)

---

## 🧾 Modules and Classes

| Module           | Key Classes Used                                  |
|------------------|---------------------------------------------------|
| Movie Booking    | `MovieTicketBookingSystem`, `Theatre`, `Movie`    |
| Cab Booking      | `CabTicketBookingSystem`, `Cab`                   |
| Food Ordering    | `FoodItem`, `FoodZone`                            |
| User Management  | `Customer`, `BankAccount`                         |
| Payment System   | `MakePayment`                                     |
| Exception Safety | `BookingException`                                |

---



