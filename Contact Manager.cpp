#include <iostream>
#include <string>
using namespace std;

// Constants
const int MAX_CONTACTS = 100;

// Function prototypes
void addContact(string names[], string phoneNumbers[], int& contactCount);
void viewContacts(const string names[], const string phoneNumbers[], int contactCount);
void deleteContact(string names[], string phoneNumbers[], int& contactCount);
void displayMenu();

int main() {
    string names[MAX_CONTACTS];          
    string phoneNumbers[MAX_CONTACTS];   
    int contactCount = 0;                
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addContact(names, phoneNumbers, contactCount);
            break;
        case 2:
            viewContacts(names, phoneNumbers, contactCount);
            break;
        case 3:
            deleteContact(names, phoneNumbers, contactCount);
            break;
        case 4:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid option! Please try again." << endl;
        }

    } while (choice != 4);

    return 0;
}

// Function to display the menu
void displayMenu() {
    cout << "\n--- Contact Management System ---" << endl;
    cout << "1. Add Contact" << endl;
    cout << "2. View Contacts" << endl;
    cout << "3. Delete Contact" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

// Function to add a contact
void addContact(string names[], string phoneNumbers[], int& contactCount) {
    if (contactCount >= MAX_CONTACTS) {
        cout << "Contact list is full!" << endl;
        return;
    }

    cout << "Enter contact name: ";
    cin.ignore(); 
    getline(cin, names[contactCount]);

    cout << "Enter phone number: ";
    getline(cin, phoneNumbers[contactCount]);  

    contactCount++; 
    cout << "Contact added successfully!" << endl;
}

// Function to view all contacts
void viewContacts(const string names[], const string phoneNumbers[], int contactCount) {
    if (contactCount == 0) {
        cout << "No contacts available." << endl;
        return;
    }

    cout << "\n--- Contact List ---" << endl;
    for (int i = 0; i < contactCount; ++i) {
        cout << i + 1 << ". Name: " << names[i] << ", Phone: " << phoneNumbers[i] << endl;
    }
}

// Function to delete a contact by name
void deleteContact(string names[], string phoneNumbers[], int& contactCount) {
    if (contactCount == 0) {
        cout << "No contacts to delete." << endl;
        return;
    }

    string nameToDelete;
    cout << "Enter the name of the contact to delete: ";
    cin.ignore();
    getline(cin, nameToDelete);

    int index = -1;
    for (int i = 0; i < contactCount; ++i) {
        if (names[i] == nameToDelete) {
            index = i; 
            break;
        }
    }

    if (index == -1) {
        cout << "Contact not found!" << endl;
        return;
    }

    // Shift the remaining contacts to fill the gap
    for (int i = index; i < contactCount - 1; ++i) {
        names[i] = names[i + 1];
        phoneNumbers[i] = phoneNumbers[i + 1];
    }

    contactCount--;  // Reduce the contact count
    cout << "Contact deleted successfully!" << endl;
}
