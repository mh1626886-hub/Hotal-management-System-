#include<iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;
// 1. Define the structure for a Linked List node representing a hotel room
struct Room {
    int roomNumber;
    string guestName;
    bool isOccupied;
    string roomType;
    Room*next; // Pointer to the next room in the linked list
};
class Hotel {
private:
    Room*head; // 2. Head pointer for the Singly Linked List of rooms
    queue<string> checkInQueue; // 3. STL Queue to manage guests in a First-In-First-Out (FIFO) manner
    stack<string> checkOutStack; // 4. STL Stack to track checkout history in Last-In-First-Out (LIFO) order
public:
    Hotel() {head=NULL; }
    // 5. Insert a new room at the beginning of the linked list (O(1) complexity)
    void addRoom(int rNo, string type) {
        Room*newRoom = new Room();
        newRoom->roomNumber=rNo;
        newRoom->roomType =type;
        newRoom->isOccupied =false;
        newRoom->guestName="N/A";
        newRoom->next=head;
        head=newRoom;
    }
    // 6. Push a guest name onto the waiting queue
    void addToCheckInQueue(string name) {
        checkInQueue.push(name);
        cout << name << " added to check-in queue.\n";
    }
    // 7. Logic to assign the person at the front of the queue to a specific room
    void checkIn(int rNo) {
        if (checkInQueue.empty()) {
            cout << "No guests in queue.\n";
            return;
        }
        Room* temp = head;
        // 8. Traverse the linked list to find the matching room number
        while (temp) {
            if (temp->roomNumber == rNo && !temp->isOccupied) {
                temp->guestName = checkInQueue.front(); // Assign the first person in queue
                temp->isOccupied = true;
                cout << "Check-in successful: " << temp->guestName << endl;
                checkInQueue.pop(); // Remove the guest from the queue after successful check-in
                return;
            }
            temp = temp->next;
        }
        cout << "Room not available.\n";
    }
    // 9. Logic to free up a room and record the checkout in the stack
    void checkOut(int rNo) {
        Room* temp = head;
        while (temp) {
            if (temp->roomNumber == rNo && temp->isOccupied) {
                // 10. Push the guest's name to the stack before clearing the room data
                checkOutStack.push(temp->guestName);
                temp->guestName = "N/A";
                temp->isOccupied = false;
                cout << "Room " << rNo << " checked out.\n";
                return;
            }
            temp = temp->next;
        }
        cout<<"Room not found or already vacant.\n";
    }
    // 11. Traverse and display all nodes in the linked list
    void displayStatus() {
        Room*temp = head;
        cout<<"\n--- Hotel Status ---\n";
        while(temp) {
            cout<<"Room "<<temp->roomNumber<< " | "
                 <<temp->roomType << " | "
                 <<(temp->isOccupied ? "Occupied" : "Vacant")
                 <<" | Guest: "<<temp->guestName<<endl;
            temp=temp->next;
        }
    }

    // 12. Peek at the top of the stack to see the most recent guest who left
    void showLastCheckout() {
        if (!checkOutStack.empty())
            cout << "Last checked-out guest: " << checkOutStack.top() << endl;
        else
            cout << "No check-out history.\n";
    }
};

int main() {
    Hotel myHotel;
    // 13. Pre-populate the hotel with a few rooms
    myHotel.addRoom(101, "Deluxe");
    myHotel.addRoom(102, "AC");
    myHotel.addRoom(103, "Non-AC");

    int choice, room;
    string name;
    
    // 14. Menu-driven interface for user interaction
    do {
        cout<<"\n1.Add Guest to Queue\n2.Check-In\n3.Status\n4.Check-Out\n5.Last Check-Out\n6.Exit\nChoice: ";
        cin>>choice;
        switch(choice) {
        case 1:
            cout<<"Guest Name: ";
            cin.ignore(); // 15. Clear the input buffer to ensure getline works correctly
            getline(cin, name);
            myHotel.addToCheckInQueue(name);
            break;
        case 2:
            cout<<"Room No: ";
            cin>>room;
            myHotel.checkIn(room);
            break;
        case 3:
            myHotel.displayStatus();
            break;
        case 4:
            cout<<"Room No: ";
            cin>>room;
            myHotel.checkOut(room);
            break;
        case 5:
            myHotel.showLastCheckout();
            break;
        }
    } while(choice!=6);
    return 0;
