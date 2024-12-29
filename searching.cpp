#include <iostream>
#include <string>
using namespace std;

// Define a Node structure for the Linked List
struct EventNode {
    string eventName;     // Event name
    string eventDate;     // Event date
    EventNode* next;      // Pointer to the next node

    // Constructor to initialize an EventNode
    EventNode(string name, string date) : eventName(name), eventDate(date), next(nullptr) {}
};

// Function to search for an event in the Linked List
EventNode* searchEvent(EventNode* head, string targetName) {
    // Start from the head of the linked list
    EventNode* current = head;

    // Traverse through the linked list
    while (current != nullptr) {
        // Check if the current node's event name matches the target name
        if (current->eventName == targetName) {
            return current; // Return the pointer to the found event
        }
        current = current->next; // Move to the next node
    }

    return nullptr; // Return nullptr if the event is not found
}

int main() {
    // Create a simple Linked List of events
    EventNode* head = new EventNode("Tech Seminar", "2024-06-20");
    head->next = new EventNode("Job Fair", "2024-07-05");
    head->next->next = new EventNode("Cultural Fest", "2024-08-15");

    // Input: Event name to search
    string searchName;
    cout << "Enter the event name to search: ";
    cin >> ws;  // Clear input buffer
    getline(cin, searchName);

    // Call the search function
    EventNode* result = searchEvent(head, searchName);

    // Display the search result
    if (result != nullptr) {
        cout << "Event Found: " << result->eventName << " on " << result->eventDate << endl;
    } else {
        cout << "Event Not Found!" << endl;
    }

    // Cleanup memory
    delete head->next->next;
    delete head->next;
    delete head;

    return 0;
}
