#include <iostream>
#include <string>
#include <list>
#include <queue>
using namespace std ;
// ========== Room ==========
class Room
{
    private :
        int roomNumber ;
        double price ;
        bool isBooked ;
    
    public :
        Room ( int num , double p )
        {
            roomNumber = num ;
            price = p ;
            isBooked = false ;
        }
        bool book()
        {
            if ( isBooked == false )
            {
                isBooked = true ;
                return true ;
            }
                return false ;
        }
        void cancel()
        {
            if (!isBooked)
            {
                cout << "No active booking found for this room." << endl;
                return;
            }
            isBooked = false;
            cout << "Booking cancelled successfully." << endl ;
        }
        bool isAvailable()
        {    
            return !isBooked ;       // if (isBooked == true) => not available
        }        
        double getPrice()
        {
            return price ;
        }
        int getRoomNum()
        {
            return roomNumber ;
        }
        void showRoom()
        {
            cout << "Room Number     Room Price     Room Status\n" ;
            if ( isAvailable() == true )
            {
                cout << "   " << roomNumber << "\t\t   " << getPrice() << "\t\t" << "Available" << endl ;
            }
            else
            {
                cout << "   " << roomNumber << "\t\t   " << getPrice() << "\t\t"  << "Booked" << endl ;
            }
            
    
            cout << "===========================================\n" ; 
        }
};

// ========== Person ==========
class Person
{
    protected :
        string name ;
        int id ;

    public :
        void setData( string n , int i ) 
        {
            name = n ;
            id = i ;
        }
        void showData()
        {
            cout << "======================================\n" ;
            cout << "Person Name : " << name << endl ;
            cout << "Person Id : " << id << endl ;
            cout << "======================================\n" ;
        }       
};

// ========== Declear HotelSystem ==========
class HotelSystem ;

// ========== Customer ==========
class Customer : public Person
{
    public :
        void bookRoom( Room &r , HotelSystem &h ) ;         // HotelSystem عرفت الداله الاول لان محتاج لسه داله من ال 
        
        void cancelRoom( Room &r )
        {
            r.cancel() ;
        }
};

// ========== HotelSystem ==========
class HotelSystem 
{
    private :
        list<Room> rooms ;
        queue<Customer> waitingList ;
    
    public :
        
        void addRoom( Room r )
        {   
            for (Room &room : rooms)
            {
                if ( r.getRoomNum() == room.getRoomNum() )
                {
                    cout << "Room number already exists.\n";
                    return;
                }
            }
            rooms.push_back(r) ;
        }
        void addToWaitingList( Customer c )
        {   
            waitingList.push(c) ;
            cout << ">>> Added to waiting list. <<<\n" ;
        }
        void showRooms()
        {
            if ( rooms.empty() )
            {
                cout << "No rooms in the system.\n";
                return;
            }
            for ( Room &room : rooms)
            {
                room.showRoom() ;
            } 
        }
        void showWaitingList()
        {
            if ( waitingList.empty() )
            {
                cout << ">>> Waiting List is Empty. <<<\n";
                return;
            }
            queue <Customer> temp = waitingList ;
            while ( !temp.empty() )
            {
                temp.front().showData() ;
                temp.pop();
            }    
        }
        list<Room>& getRooms()
        {
            return rooms ;
        } 
        bool isThereAvailableRoom()
        {
            for ( Room &room : rooms)
            {
                if ( room.isAvailable() )
                {
                    return true ;
                }
            } 
            return false ;
        } 
        void showAvailableRooms()
        {
            cout << "********** Available Rooms **********\n" ;
            for ( Room &room : rooms)
            {
                if ( room.isAvailable() )
                {
                    room.showRoom() ;
                }
            }
        }      
};

// ========== bookRoom Function from Customer ==========
void Customer ::  bookRoom( Room &r , HotelSystem &h ) 
        {
            if ( r.book() )
            {
                cout << "Room booked successfully!\n" ;
            }
            else
            {
                h.addToWaitingList(*this) ;
                cout << "You added to Waiting List.\n" ;
            }
        }

// ========== Manager ==========        
class Manager : public Person  
{
    public :
        void showRooms( HotelSystem &h )
        {
            h.showRooms() ;
        }
        void showWaitingList( HotelSystem &h )
        {
            h.showWaitingList() ;
        }
};

// ========== Payment Part ========== 
class Payment
{
    public:
        virtual void pay(double amount) = 0;
};

class CashPayment : public Payment
{
    public:
        void pay(double amount) 
        {
            cout << "Paid by cash : " << amount << endl ;
        }
};

class CardPayment : public Payment
{
    public:
        void pay(double amount) 
        {
            cout << "Paid by Card : " << amount << endl ;
        }
};

bool bookingCost(Room &r)
{
    int numOfDays ;
    cout << "How many days ? : " ;
    cin >> numOfDays ;
    if (numOfDays <= 0)
    {
        cout << "Invalid number of days.\n";
        return false;
    }

    Payment *p = nullptr ;
    int choice ;
    cout << "1. Cash Payment\n" ;
    cout << "2. Card Payment\n" ;

    cout << "Enter your choice : " ;
    cin >> choice ;
    switch (choice)
    {
        // معلش لسبب ضيق الوقت ملحقتش اكمل عمليه الدفع واكتفيت هكذا
        case 1 :
            p = new CashPayment();
            p -> pay (numOfDays*r.getPrice()) ;
            break;

        case 2 :
            p = new CardPayment();
            p -> pay (numOfDays*r.getPrice()) ;
            break;

        default:
            return false ;
            break;
        }
        delete p ;
        return true ;
}

int main()
{
    HotelSystem My_Frist_Hotel ;
    Manager manger ;
    My_Frist_Hotel.addRoom(Room(101, 500));
    My_Frist_Hotel.addRoom(Room(102, 300));
    My_Frist_Hotel.addRoom(Room(103, 600));
    My_Frist_Hotel.addRoom(Room(104, 250));
    My_Frist_Hotel.addRoom(Room(105, 350));
    int choice ;
    do
    {
        cout << "===== HOTEL SYSTEM MENU =====\n" ;
        cout << "1. Show Rooms\n" ;
        cout << "2. Book Room\n" ;
        cout << "3. Cancel Room\n" ;
        cout << "4. Show Waiting List\n" ;
        cout << "5. Manager View Rooms\n" ;
        cout << "6. Exit\n" ;

        cout << "Enter choice (1,...,6) : " ;
        cin >> choice ;

        switch (choice)
        {
        case 1 :
            manger.showRooms(My_Frist_Hotel) ;
            break;
        case 2:
        {
            string name;
            int id, roomnum;

            cout << "Customer name : ";
            cin >> name;

            cout << "Customer ID : ";
            cin >> id;

            Customer newcustom;
            newcustom.setData(name, id);

            if (My_Frist_Hotel.isThereAvailableRoom())
            {
                My_Frist_Hotel.showAvailableRooms();

                cout << "Enter the Number of Chosen Room : ";
                cin >> roomnum;

                bool foundRoom = false;

                for (Room &room : My_Frist_Hotel.getRooms())
                {
                    if (room.getRoomNum() == roomnum)
                    {
                        foundRoom = true;

                        if (room.isAvailable())
                        {
                            if (bookingCost(room))
                            {
                                newcustom.bookRoom(room, My_Frist_Hotel);
                            }
                            else
                            {
                                cout << "Sorry,Booking room is failed.\n" ;
                            }
                        }
                        else
                        {
                            cout << "Sorry,Room is already booked.\n";
                        }

                        break;
                    }
                }

                if (!foundRoom)
                    cout << "Room not found!\n";
            }
            else
            {
                cout << "Sorry, There isn't any Available Room.\n";

                char choice;
                cout << "Do you want to join Waiting List? (y/n): ";
                cin >> choice;

                if (choice == 'y' || choice == 'Y')
                {
                    My_Frist_Hotel.showRooms();

                    cout << "Enter Room Number: ";
                    cin >> roomnum;

                    bool foundRoom = false;

                    for (Room &room : My_Frist_Hotel.getRooms())
                    {
                        if (room.getRoomNum() == roomnum)
                        {
                            foundRoom = true;

                            newcustom.bookRoom(room, My_Frist_Hotel);
                            break;
                        }
                    }

                    if (!foundRoom)
                        cout << "Room not found!\n";
                }
            }

            break;
        }       
        case 3 :
        {
            int num;
            cout << "Room number : ";
            cin >> num;

            bool found = false;

            for (Room& r : My_Frist_Hotel.getRooms())
            {
                if (r.getRoomNum() == num)
                {
                    found = true ;
                    if ( r.isAvailable() )
                    {
                        cout << "Actually,Room is Available.\n" ;
                        break;
                    }
                    Customer customer;
                    customer.cancelRoom(r);
                    break;
                }
            }

            if (!found)
                cout << "Room not found!\n";
        }
            break;
        case 4 :
            My_Frist_Hotel.showWaitingList() ;
            break;
        case 5 :
            {
                int manageChoice ;
                do
                {
                    cout << "===== Manage Hotel System =====\n" ;
                    cout << "1. Show All Rooms" << endl ;
                    cout << "2. Add New Room" << endl ;
                    cout << "3. Show Waiting List" << endl ;
                    cout << "0. Back to Main Menu" << endl ;

                    cout << "Enter yor Choise : " ;
                    cin >> manageChoice ;

                    switch (manageChoice)
                    {
                    case 1 :
                        manger.showRooms(My_Frist_Hotel) ;
                        break;
                    case 2 :
                        {
                            int newRoomNum ;
                            double newRoomPrice ;
                            cout << "Enter the Number of New Room : ";
                            cin >> newRoomNum ;
                            cout << "Enter the Price of New Room : ";
                            cin >> newRoomPrice ;
                            My_Frist_Hotel.addRoom(Room( newRoomNum , newRoomPrice )) ;
                            cout << "Room added successfully.\n";
                        }
                        break; 
                    case 3 :
                        manger.showWaitingList(My_Frist_Hotel) ;
                        break;           
                    default:
                        break;
                    }
                } while (manageChoice != 0);
                
            }
            break;

        case 6:
            cout << "Thank you for using Hotel System.\n";
            break;

        default :
            cout << "Invalid choice. Try again.\n";
            break;
        }
    } while (choice != 6);
} 