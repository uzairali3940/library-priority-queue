
#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct BookRequestNode {
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

class PriorityQueue {
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:
    PriorityQueue() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    // Add request according to priority
    void Add(BookRequestNode* request) {
        request->next = nullptr;

        if (front == nullptr) {
            front = rear = request;
        }
        else if (request->priority < front->priority) {
            request->next = front;
            front = request;
        }
        else {
            BookRequestNode* current = front;

            while (current->next != nullptr &&
                   current->next->priority <= request->priority) {
                current = current->next;
            }

            request->next = current->next;
            current->next = request;

            if (request->next == nullptr) {
                rear = request;
            }
        }

        count++;
    }

    // Remove highest-priority request
    BookRequestNode* Remove() {
        if (front == nullptr) {
            return nullptr;
        }

        BookRequestNode* request = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        request->next = nullptr;
        count--;

        return request;
    }

    bool IsEmpty() {
        return front == nullptr;
    }

    bool IsNotEmpty() {
        return front != nullptr;
    }

    // Display all pending requests
    void PrintQueue() {
        if (IsEmpty()) {
            cout << "No pending book requests.\n";
            return;
        }

        BookRequestNode* current = front;

        while (current != nullptr) {
            cout << "\nStudent ID: " << current->studentID;
            cout << "\nStudent Name: " << current->studentName;
            cout << "\nBook ID: " << current->bookID;
            cout << "\nBook Title: " << current->bookTitle;
            cout << "\nPriority: " << current->priority;
            cout << "\n-----------------------------\n";

            current = current->next;
        }
    }

    // Release dynamically allocated memory
    ~PriorityQueue() {
        while (front != nullptr) {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
    }
};

int main() {
    PriorityQueue requests;
    int choice;

    do {
        cout << "\n===== Library Book Request System =====\n";
        cout << "1. Add Book Request\n";
        cout << "2. Process Highest Priority Request\n";
        cout << "3. Display All Requests\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                BookRequestNode* request = new BookRequestNode;

                cout << "Enter Student ID: ";
                cin >> request->studentID;

                cout << "Enter Student Name: ";
                getline(cin >> ws, request->studentName);

                cout << "Enter Book ID: ";
                cin >> request->bookID;

                cout << "Enter Book Title: ";
                getline(cin >> ws, request->bookTitle);

                cout << "Enter Priority (1=Urgent, 2=Assignment, 3=Normal): ";
                cin >> request->priority;

                if (cin.fail() ||
                    request->priority < 1 ||
                    request->priority > 3) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input or priority. Request not added.\n";
                    delete request;
                    break;
                }

                requests.Add(request);
                cout << "Book request added successfully!\n";
                break;
            }

            case 2: {
                BookRequestNode* processed = requests.Remove();

                if (processed == nullptr) {
                    cout << "Queue is empty. No request to process.\n";
                }
                else {
                    cout << "\nRequest Processed Successfully!\n";
                    cout << "Student: " << processed->studentName << '\n';
                    cout << "Book: " << processed->bookTitle << '\n';
                    cout << "Priority: " << processed->priority << '\n';

                    delete processed;
                }
                break;
            }

            case 3:
                cout << "\n===== All Pending Requests =====\n";
                requests.PrintQueue();
                break;

            case 4:
                if (requests.IsEmpty()) {
                    cout << "Queue Status: Empty\n";
                }
                else if (requests.IsNotEmpty()) {
                    cout << "Queue Status: Not Empty\n";
                }
                break;

            case 5:
                cout << "Exiting program. Memory will be released.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}

