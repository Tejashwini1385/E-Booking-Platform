#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <map>
#include <unordered_map>
#include <string>
#include <ctime>
#include <cstdlib>
#define RED_TEXT "\x1b[31m"
#define GREEN_TEXT "\x1b[32m"
#define RESET_TEXT "\x1b[0m"
#define BLUE_TEXT "\x1b[34m"
#define YELLOW_TEXT "\x1b[33m"

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printLargeTextLine(const char *text)
{
    std::cout << "\033[1;33;5m";
    std::cout << text << std::endl;
    std::cout << "\033[0m";
}


void welcomePage()
{
    clearScreen();

    for (int i = 0; i < 5; i++)
    {
        std::cout << std::endl;
    }

    // Print "W E L C O M E  to JOB Search" with increased font size
    printLargeTextLine("");
    printLargeTextLine("                                                                                                                          ");
    printLargeTextLine("                                                 E B O O K I N G                                                ");
    printLargeTextLine("                                                        *");
    printLargeTextLine("");

    std::cout << std::endl;
    std::cout << "                                EXPLORE BOOKING OPTIONS AND BOOK MOVIE ENJOY IT WITH FOOD                    " << std::endl;
     std::cout << "                                           ENJOY YOUR JOURNEY BY BOOKING CAB                                " << std::endl;
    std::cout << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl
              << std::endl;
    std::cout << "Press Enter to continue...";
    // Wait for the user to press Enter
    std::cin.ignore();
    //std::cin.get();

    // Clear the screen again before displaying the menu
    clearScreen();
}
// Forward declarations
class BookingSystem;
class MovieTicketBookingSystem;
class CabTicketBookingSystem;
class Customer;
template <typename T1, typename T2>
class BankAccount;
class MakePayment;
class Theatre;
class FoodZone;
class FoodItem;
class BookingException;
class Cab;
class Movie;

// BookingException class for handling exceptions
class BookingException : public exception {
private:
    string errorMessage; // Error message

public:
    // Constructor
    BookingException(const string& msg) : errorMessage(msg) {}

    // Overridden method to get error message
    const char* what() const noexcept override {
        cout<<RED_TEXT<<errorMessage.c_str()<<RESET_TEXT<<endl;
        return errorMessage.c_str();
    }
};
template <typename T1, typename T2>
class BankAccount {
private:
    T1 accNo;
    T2 balance;
    static shared_ptr<BankAccount<T1, T2>> instance;

    BankAccount() : accNo(0), balance(0.0) {}

public:
    static shared_ptr<BankAccount<T1, T2>> getInstance() {
        if (instance == nullptr) {
            instance = shared_ptr<BankAccount<T1, T2>>(new BankAccount<T1, T2>());
        }
        return instance;
    }

    void setAccountDetails(T1 accNo, T2 balance) {
        this->accNo = accNo;
        this->balance = balance;
    }

    bool debitAmount(T2 amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << GREEN_TEXT << "Debited: " << amount << ". New Balance: " << balance << RESET_TEXT << endl;
            return true;
        } else {
            throw BookingException("Insufficient Balance!");
            return false;
        }
    }

    double getBalance() {
        return balance;
    }
};

template <typename T1, typename T2>
shared_ptr<BankAccount<T1, T2>> BankAccount<T1, T2>::instance = nullptr;

// Abstract Factory for BookingSystem
class BookingSystemFactory {
public:
    // Pure virtual method to create a booking system
    virtual shared_ptr<BookingSystem> createBookingSystem() = 0;
};

// Factory for MovieTicketBookingSystem
class MovieTicketBookingSystemFactory : public BookingSystemFactory {
public:
    shared_ptr<BookingSystem> createBookingSystem();
};

// Factory for CabTicketBookingSystem
class CabTicketBookingSystemFactory : public BookingSystemFactory {
public:
    shared_ptr<BookingSystem> createBookingSystem();
};

// BookingSystem base class
class BookingSystem {
protected:
    string eBookType; // Type of e-booking

public:
    // Constructor
    BookingSystem(string type) : eBookType(type) {}

    // Virtual destructor
    virtual ~BookingSystem() {}

    // Pure virtual methods for making booking and printing details
    virtual void makeBooking(Customer& customer) = 0;
    virtual void printDetails() = 0;
};

// MovieTicketBookingSystem derived class
class MovieTicketBookingSystem : public BookingSystem {
private:
    shared_ptr<Theatre> theatre; // Associated theatre

public:
    // Constructor
    MovieTicketBookingSystem(string type) : BookingSystem(type), theatre(nullptr) {}

    // Method to make a booking
    void makeBooking(Customer& customer);

    // Method to print booking details
    void printDetails();

    // Method to set theatre
    void setTheatre(shared_ptr<Theatre> th) {
        theatre = th;
    }

    // Method to get theatre
    shared_ptr<Theatre> getTheatre() {
        return theatre;
    }
};

// CabTicketBookingSystem derived class
class CabTicketBookingSystem : public BookingSystem {
private:
    shared_ptr<Cab> cab; // Associated cab

public:
    // Constructor
    CabTicketBookingSystem(string type) : BookingSystem(type), cab(nullptr) {}

    // Method to make a booking
    void makeBooking(Customer& customer);

    // Method to print booking details
    void printDetails();

    // Method to set cab
    void setCab(shared_ptr<Cab> c) {
        cab = c;
    }

    // Method to get cab
    shared_ptr<Cab> getCab() {
        return cab;
    }
};

// Customer class
class Customer {
private:
    string custName;
    string location;
    int custId;
    string phoneNo;
shared_ptr<BankAccount<int, double>> bankAccount; // Associated bank account

public:
    // Constructor
    Customer(string name, string loc, int id, string phone, shared_ptr<BankAccount<int, double>> ba)
        : custName(name), location(loc), custId(id), phoneNo(phone), bankAccount(ba) {}

    // Method to get customer name
    string getName() {
        return custName;
    }

    // Method to get bank account
   shared_ptr<BankAccount<int, double>>  getBankAccount() {
        return bankAccount;
    }

    // Method to make a booking
    void makeBooking(shared_ptr<BookingSystem> bookingSystem) {
        bookingSystem->makeBooking(*this);
    }

    // Method to cancel a booking
    void cancelBooking() {
        cout << "Booking cancelled for " << custName << endl;
    }
};

// Factory Method Implementations
shared_ptr<BookingSystem> MovieTicketBookingSystemFactory::createBookingSystem() {
    return make_shared<MovieTicketBookingSystem>("MovieTicket");
}

shared_ptr<BookingSystem> CabTicketBookingSystemFactory::createBookingSystem() {
    return make_shared<CabTicketBookingSystem>("CabTicket");
}

// MakePayment class
class MakePayment {
private:
    double amount; // Payment amount
    string transactionStatus; // Status of transaction
   shared_ptr<BankAccount<int, double>> bankAccount; // Associated bank account
    shared_ptr<Customer> customer; // Associated customer

public:
    // Constructor
    MakePayment(double amt, shared_ptr<BankAccount<int, double>> ba, shared_ptr<Customer> cust)
        : amount(amt), bankAccount(ba), customer(cust), transactionStatus("Pending") {}

    // Method to display bill
    void displayBill() const {
        cout << "Amount: " << amount << ", Status: " << transactionStatus << endl;
    }

    // Method to show transaction details
    void transactionDetails() {
        cout << "Processing payment of " << amount << " for customer " << customer->getName() << endl;
        if (bankAccount->debitAmount(amount)) {
            transactionStatus = "Completed";
        } else {
            transactionStatus = "Failed";
        }
    }
};

// FoodItem class
class FoodItem {
private:
    string foodName;
    double price;
    int foodItemId;
    int availableQuantity; // Available quantity

public:
    // Constructor
    FoodItem(string name, double p, int id, int qty) : foodName(name), price(p), foodItemId(id), availableQuantity(qty) {}

    // Method to print item details
    void printDetails() const {
        cout << "Food Item: " << foodName << ", Price: " << price << ", Available Quantity: " << availableQuantity << endl;
    }

    // Method to check and order item
    bool orderItem(int qty) {
        if (availableQuantity >= qty) {
            availableQuantity -= qty;
            return true;
        } else {
            return false;
        }
    }

    // Method to get food item ID
    int getFoodItemId() const {
        return foodItemId;
    }

    // Method to get food item name
    string getFoodName() const {
        return foodName;
    }

    // Method to get price
    double getPrice() const {
        return price;
    }
};

// Theatre class
class Theatre {
private:
    string theatreName; // Theatre name
    string date; // Date of show
    string time; // Time of show
    string location; // Location of theatre
    int noOfSeats; // Number of seats
    shared_ptr<Movie> movie; // Associated movie
    shared_ptr<FoodZone> foodZone; // Associated food zone

public:
    // Constructor
    Theatre(string name, string dt, string tm, string loc, int seats, shared_ptr<Movie> mv, shared_ptr<FoodZone> fz)
        : theatreName(name), date(dt), time(tm), location(loc), noOfSeats(seats), movie(mv), foodZone(fz) {}

    // Method to select a cinema
    void selectCinema() {
        cout << "Cinema selected: " << theatreName << endl;
    }

    // Method to display theatre details
    void displayDetails() const {
        cout <<GREEN_TEXT<<"Theatre: " << theatreName << ", Date: " << date << ", Time: " << time << ", Location: " << location <<RESET_TEXT<< endl;
    }

    // Method to check seats availability
    void seatsAvailable() const {
        cout << "Seats available: " << noOfSeats << endl;
        if(noOfSeats==0)
        {
            throw BookingException("The seats are fully occupied!");
        }
    }

    // Method to get associated movie
    shared_ptr<Movie> getMovie() const {
        return movie;
    }

    // Method to get associated food zone
    shared_ptr<FoodZone> getFoodZone() const {
        return foodZone;
    }
};


// Movie class
class Movie {
private:
    string movieName; // Movie name
    double ticketPrice; // Ticket price

public:
    // Constructor
    Movie(string name, double price) : movieName(name), ticketPrice(price) {}

    // Method to display movie details
    void movieDetails() const {
        cout << GREEN_TEXT<<"Movie: " << movieName << ", Ticket Price: " << ticketPrice << RESET_TEXT<<endl;
    }

    // Method to get ticket price
    double getTicketPrice() const {
        return ticketPrice;
    }
};

// FoodZone class
class FoodZone {
private:
    string foodZoneName; // Food zone name
    vector<shared_ptr<FoodItem>> foodItems; // Vector of food items

public:
    // Constructor
    FoodZone(string name, const vector<shared_ptr<FoodItem>>& items) : foodZoneName(name), foodItems(items) {}

    // Method to display food zone details
    void displayDetails() const {
        cout << "Food Zone: " << foodZoneName << endl;
        for (const auto& item : foodItems) {
            item->printDetails();
        }
    }

    // Method to get food items
    vector<shared_ptr<FoodItem>> getFoodItems() const {
        return foodItems;
    }
};

// Cab class
class Cab {
private:
    string cabType; // Cab type
    string source; // Source location
    string destination; // Destination location
    double distance; // Distance to destination
    double fare; // Fare

public:
    // Constructor
    Cab(string type, string src, string dest, double dist, double fr)
        : cabType(type), source(src), destination(dest), distance(dist), fare(fr) {}

    // Method to select a cab
    void selectCab() {
        cout << "Cab selected: " << cabType << endl;
    }

    // Method to display cab details
    void displayDetails() const {
        cout <<GREEN_TEXT<< "Cab: " << cabType << ", Source: " << source << ", Destination: " << destination << ", Distance: " << distance << ", Fare: " << fare <<RESET_TEXT<< endl;
    }

    // Method to calculate fare
    double calculateFare() const {
        return distance * fare;
    }
};

// MovieTicketBookingSystem method implementations
void MovieTicketBookingSystem::makeBooking(Customer& customer) {
    if (theatre == nullptr) {
        cout << "Theatre is not set for movie booking." << endl;
        return;
    }

    theatre->selectCinema();
    theatre->displayDetails();
    theatre->seatsAvailable();
    double amount = theatre->getMovie()->getTicketPrice();

    cout << "Booking ticket for " << customer.getName() << endl;
    cout << "Ticket Price: " << amount << endl;

    shared_ptr<MakePayment> payment = make_shared<MakePayment>(amount, customer.getBankAccount(), make_shared<Customer>(customer));
    payment->transactionDetails();
    payment->displayBill();
}

void MovieTicketBookingSystem::printDetails() {
    cout << "MovieTicketBookingSystem Details" << endl;
    if (theatre) {
        theatre->displayDetails();
    }
}

// CabTicketBookingSystem method implementations
void CabTicketBookingSystem::makeBooking(Customer& customer) {
    if (cab == nullptr) {
        cout << "Cab is not set for booking." << endl;
        return;
    }

    cab->selectCab();
    cab->displayDetails();
    double amount = cab->calculateFare();

    cout << GREEN_TEXT<<"Booking cab for " << customer.getName()<< RESET_TEXT << endl;
    cout <<GREEN_TEXT<< "Fare: " << amount << RESET_TEXT<<endl;

    shared_ptr<MakePayment> payment = make_shared<MakePayment>(amount, customer.getBankAccount(), make_shared<Customer>(customer));
    payment->transactionDetails();
    payment->displayBill();
}

void CabTicketBookingSystem::printDetails() {
    cout << "CabTicketBookingSystem Details" << endl;
    if (cab) {
        cab->displayDetails();
    }
}


// Modify the main function to include choices for theaters, movies, and food items

int main() {
        welcomePage();
    cout <<YELLOW_TEXT<<" WELCOME TO THE BOOKING SYSTEM \n\n"<<RESET_TEXT;
    vector<shared_ptr<Customer>> customers;
    vector<shared_ptr<BookingSystem>> bookings;
    string continueBooking;

    // Mapping method for theaters
    unordered_map<int, string> theaterMap = {
        {10, "PVR"}, {9, "INOX"}, {8, "Cinepolis"}, {7, "AMC"}, {6, "Regal"},
        {5, "Vue"}, {4, "Odeon"}, {3, "Gaumont"}, {2, "CGR"}, {1, "Kinoplex"}
    };

    // Mapping method for movies
    unordered_map<int, string> movieMap = {
        {10, "Inception"}, {9, "The Dark Knight"}, {8, "Interstellar"}, {7, "Dunkirk"}, {6, "The Prestige"},
        {5, "Tenet"}, {4, "Memento"}, {3, "Batman Begins"}, {2, "Insomnia"}, {1, "Following"}
    };

    // Mapping method for food items
    unordered_map<int, string> foodItemMap = {
        {10, "Popcorn"}, {9, "Soda"}, {8, "Nachos"}, {7, "Hot Dog"}, {6, "Pizza"},
        {5, "Burger"}, {4, "Fries"}, {3, "Ice Cream"}, {2, "Candy"}, {1, "Pretzel"}
    };

    do {
        cout << "Enter customer details: " << endl;
        string name, location, phone;
        int id, accNo;
        double balance;

        cout << "Name: ";
        cin >> name;
        cout << "Location: ";
        cin >> location;
        cout << "ID: ";
        cin >> id;
        cout << "Phone: ";
        cin >> phone;
        cout << "Account No: ";
        cin >> accNo;
        cout << "Balance: ";
        cin >> balance;

        // Create bank account and customer
        shared_ptr<BankAccount<int, double>> bankAccount = BankAccount<int, double>::getInstance();
    bankAccount->setAccountDetails(accNo, balance);
        shared_ptr<Customer> customer = make_shared<Customer>(name, location, id, phone, bankAccount);
        customers.push_back(customer);

        cout << BLUE_TEXT<<"MENU\n1: Movie\n2: Cab\n3: Both cab and movie\n"<<RESET_TEXT;
        int choice;
        cin >> choice;
try{
        if (choice == 1 || choice == 3) {
            // Movie booking
            MovieTicketBookingSystemFactory movieFactory;
            shared_ptr<BookingSystem> movieBooking = movieFactory.createBookingSystem();

            // Select a theatre
            cout << "Select a theatre:" << endl;
            for (const auto& entry : theaterMap) {
                cout << entry.first<< ": " << entry.second << endl;
            }
            int theaterChoice;
            cin >> theaterChoice;
            string selectedTheater = theaterMap[theaterChoice];

            // Select a movie
            cout << "Select a movie:" << endl;
            for (const auto& entry : movieMap) {
                cout << entry.first << ": " << entry.second << endl;
            }
            int movieChoice;
            cin >> movieChoice;
            string selectedMovie = movieMap[movieChoice];

            // Select food items
            shared_ptr<FoodZone> foodZone = make_shared<FoodZone>("Main Food Zone", vector<shared_ptr<FoodItem>>{});
            cout << "Select food items (enter item numbers, 0 to finish):" << endl;
            vector<int> selectedItems;
            int itemChoice;

            do {
                for (const auto& entry : foodItemMap) {
                    cout << entry.first <<": " << entry.second << endl;
                }
                cin >> itemChoice;
                if (itemChoice > 0 && itemChoice <= foodItemMap.size()) {
                    selectedItems.push_back(itemChoice);
                }
            } while (itemChoice != 0);

            // Calculate total food price
            double totalFoodPrice = 0.0;
            for (int itemIndex : selectedItems) {
                auto foodItem = make_shared<FoodItem>(foodItemMap[itemIndex], 5.0, itemIndex, 10);
                foodItem->printDetails();
                cout << "Enter quantity: ";
                int quantity;
                cin >> quantity;
                if (foodItem->orderItem(quantity)) {
                    totalFoodPrice += foodItem->getPrice() * quantity;
                } else {
                   throw BookingException("Out of Stock!");
                }
            }

            cout << "Total Food Price: " << totalFoodPrice << endl;

            // Create theater and book movie
            shared_ptr<Theatre> theatre = make_shared<Theatre>(selectedTheater, "2023-06-20", "18:00", "City Center", 100, make_shared<Movie>(selectedMovie, 150.0), foodZone);
            dynamic_pointer_cast<MovieTicketBookingSystem>(movieBooking)->setTheatre(theatre);
            customer->makeBooking(movieBooking);
            bookings.push_back(movieBooking);
        }

        if (choice == 2 || choice == 3) {
            // Cab booking
            CabTicketBookingSystemFactory cabFactory;
            shared_ptr<BookingSystem> cabBooking = cabFactory.createBookingSystem();

            // Cab details
            cout << "Enter cab type:" << endl;
            string cabType;
            cin.ignore(); // Ignore previous newline character
            getline(cin, cabType);

            cout << "Enter source location: ";
            string source;
            getline(cin, source);

            cout << "Enter destination location: ";
            string destination;
            getline(cin, destination);

            cout << "Enter distance in km: ";
            double distance;
            cin>> distance;

            // Create cab and book cab
            shared_ptr<Cab> cab = make_shared<Cab>(cabType, source, destination, distance, 2.5);
            dynamic_pointer_cast<CabTicketBookingSystem>(cabBooking)->setCab(cab);

            customer->makeBooking(cabBooking);
            bookings.push_back(cabBooking);
        }

        cout << "Do you want to make another booking? (yes/no): ";
        cin >> continueBooking;


    } catch(const BookingException& be)
       {
          be.what();
       }


    }while (continueBooking == "yes");
    cout << "Summary of bookings:" << endl;
    for (const auto& booking : bookings) {
        booking->printDetails();
    }

    return 0;
}
