#include <iostream>
#include <string>
using namespace std;

// Define a structure for Participants
struct Participant {
    string name;
    int id;
    string contact;
    Participant* next;
};

// Define a structure for Events
struct Event {
    int id;
    string name;
    string category;
    int maxCapacity;
    int registeredCount;
    Participant* participants;
    Participant* waitlistFront;
    Participant* waitlistRear;
    Event* next;
};

// Define a structure for Actions (used in stack for undo functionality)
struct Action {
    string actionType;
    string details;
    Action* next;
};

Event* eventList = nullptr; // Head of the linked list for events
Action* actionStack = nullptr; // Top of the stack for undo functionality

// Function to add an event
void addEvent(int id, const string& name, const string& category, int maxCapacity) {
    Event* newEvent = new Event{id, name, category, maxCapacity, 0, nullptr, nullptr, nullptr, nullptr};

    if (!eventList) {
        eventList = newEvent;
    } else {
        Event* temp = eventList;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newEvent;
    }

    // Record the action for undo
    Action* newAction = new Action{"Add Event", name, actionStack};
    actionStack = newAction;

    cout << "Event '" << name << "' added successfully.\n";
}

// Function to register a participant for an event
void registerParticipant(int eventId, const string& name, int id, const string& contact) {
    Event* event = eventList;
    while (event && event->id != eventId) {
        event = event->next;
    }

    if (!event) {
        cout << "Event with ID " << eventId << " not found.\n";
        return;
    }

    Participant* temp = event->participants;
    while (temp) {
        if (temp->id == id) {
            cout << "Participant with ID " << id << " is already registered for the event.\n";
            return;
        }
        temp = temp->next;
    }

    Participant* newParticipant = new Participant{name, id, contact, nullptr};

    if (event->registeredCount < event->maxCapacity) {
        if (!event->participants) {
            event->participants = newParticipant;
        } else {
            Participant* temp = event->participants;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newParticipant;
        }
        event->registeredCount++;
        cout << "Participant '" << name << "' registered successfully for event '" << event->name << "'.\n";
    } else {
        if (!event->waitlistFront) {
            event->waitlistFront = event->waitlistRear = newParticipant;
        } else {
            event->waitlistRear->next = newParticipant;
            event->waitlistRear = newParticipant;
        }
        cout << "Event is fully booked. Participant '" << name << "' added to the waitlist.\n";
    }

    // Record the action for undo
    Action* newAction = new Action{"Register Participant", name, actionStack};
    actionStack = newAction;
}

// Function to search for an event by ID
void searchEvent(int id) {
    Event* temp = eventList;
    while (temp && temp->id != id) {
        temp = temp->next;
    }

    if (temp) {
        cout << "Event Found: " << temp->name << " | Category: " << temp->category << " | Capacity: " << temp->maxCapacity << "\n";
    } else {
        cout << "Event with ID " << id << " not found.\n";
    }
}

// Function to undo the last action
void undoLastAction() {
    if (!actionStack) {
        cout << "No actions to undo.\n";
        return;
    }

    Action* temp = actionStack;
    actionStack = actionStack->next;

    cout << "Undid action: " << temp->actionType << " (" << temp->details << ")\n";
    delete temp;
}

// Helper function to display all events
void displayEvents() {
    Event* temp = eventList;
    while (temp) {
        cout << "Event ID: " << temp->id << " | Name: " << temp->name << " | Category: " << temp->category
             << " | Capacity: " << temp->registeredCount << "/" << temp->maxCapacity << "\n";
        temp = temp->next;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\nCampus Event Management System:\n";
        cout << "1. Add Event\n";
        cout << "2. Register Participant\n";
        cout << "3. Search Event\n";
        cout << "4. Undo Last Action\n";
        cout << "5. Display All Events\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, capacity;
                string name, category;
                cout << "Enter Event ID: ";
                cin >> id;
                cout << "Enter Event Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Event Category: ";
                getline(cin, category);
                cout << "Enter Max Capacity: ";
                cin >> capacity;
                addEvent(id, name, category, capacity);
                break;
            }
            case 2: {
                int eventId, participantId;
                string name, contact;
                cout << "Enter Event ID: ";
                cin >> eventId;
                cout << "Enter Participant Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Participant ID: ";
                cin >> participantId;
                cout << "Enter Contact Info: ";
                cin.ignore();
                getline(cin, contact);
                registerParticipant(eventId, name, participantId, contact);
                break;
            }
            case 3: {
                int eventId;
                cout << "Enter Event ID: ";
                cin >> eventId;
                searchEvent(eventId);
                break;
            }
            case 4:
                undoLastAction();
                break;
            case 5:
                displayEvents();
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
