#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Function to handle forest scenario
void forestScenario(string &location, bool &gameOver) {
    cout << "You are in a dark forest. There is a cave to the west and a river to the east." << endl;
    cout << "Do you go west to the cave or east to the river? (Type 'west' or 'east'): ";

    string choice;
    cin >> choice;
    transform(choice.begin(), choice.end(), choice.begin(), ::tolower);  // Convert to lowercase for validation

    if (choice == "west") {
        location = "cave";
        cout << "You enter the cave..." << endl;
    } else if (choice == "east") {
        location = "river";
        cout << "You approach the river..." << endl;
    } else {
        cout << "Invalid choice. Try again." << endl;
    }
}

// Function to handle cave scenario
void caveScenario(bool &gameOver, bool &win) {
    cout << "Inside the cave, you encounter a dangerous bear!" << endl;
    cout << "You have no weapons and the bear attacks you. You lose!" << endl;
    gameOver = true;  // The game ends with a loss
}

// Function to handle river scenario
void riverScenario(bool &gameOver, bool &win) {
    cout << "At the river, you find a boat and safely cross to the other side." << endl;
    cout << "You find a village and are saved. You win!" << endl;
    win = true;  // The player wins this scenario
    gameOver = true;
}

int main() {
    // Game variables
    string location = "forest";
    bool gameOver = false;
    bool win = false;

    cout << "Welcome to the Adventure!" << endl;

    // Main game loop
    while (!gameOver) {
        if (location == "forest") {
            forestScenario(location, gameOver);
        } else if (location == "cave") {
            caveScenario(gameOver, win);  // Player loses in the cave
        } else if (location == "river") {
            riverScenario(gameOver, win);  // Player wins at the river
        }
    }

    // Endgame message
    if (win) {
        cout << "Congratulations! You have completed the adventure successfully!" << endl;
    } else {
        cout << "Game Over. Better luck next time!" << endl;
    }

    return 0;
}
