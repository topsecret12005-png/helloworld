#include <iostream>
using namespace std;

// 1. Define our Semaphores and Buffer limits
int mutex = 1;         // Acts as a lock. 1 = unlocked, 0 = locked.
int full_slots = 0;    // Number of slots in the buffer that currently have items.
int empty_slots = 5;   // Number of empty slots (Maximum buffer capacity is 5).
int item_count = 0;    // The actual item being produced/consumed.

// 2. The Producer Function
void producer() {
    // Lock the buffer and decrease empty slots
    --mutex;
    --empty_slots;
    
    // Produce an item
    item_count++;
    cout << "\n[+] Producer produced item: " << item_count;
    
    // Unlock the buffer and increase full slots
    ++mutex;
    ++full_slots;
}

// 3. The Consumer Function
void consumer() {
    // Lock the buffer and decrease full slots
    --mutex;
    --full_slots;
    
    // Consume an item
    cout << "\n[-] Consumer consumed item: " << item_count;
    item_count--;
    
    // Unlock the buffer and increase empty slots
    ++mutex;
    ++empty_slots;
}

int main() {
    int choice;
    
    cout << "--- Producer-Consumer Simulation ---\n";
    cout << "Buffer Capacity: 5\n";
    
    while (true) { 
        cout << "\n\n1. Run Producer";
        cout << "\n2. Run Consumer";
        cout << "\n3. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                // Producer can only run if the buffer is unlocked AND has empty space
                if ((mutex == 1) && (empty_slots != 0)) {
                    producer();
                } else {
                    cout << "\n[!] WAIT: Buffer is FULL! Producer cannot add items.";
                }
                break;
                
            case 2:
                // Consumer can only run if the buffer is unlocked AND has items in it
                if ((mutex == 1) && (full_slots != 0)) {
                    consumer();
                } else {
                    cout << "\n[!] WAIT: Buffer is EMPTY! Consumer has nothing to consume.";
                }
                break;
                
            case 3:
                cout << "\nExiting program...\n";
                return 0;
                
            default:
                cout << "\nInvalid choice! Please enter 1, 2, or 3.";
        }
    }
    return 0;
}
