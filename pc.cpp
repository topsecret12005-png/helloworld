#include <iostream>
using namespace std;

  
int mutex = 1;        
int full_slots = 0;   
int empty_slots = 5;  
int item_count = 0;  

void producer() {
    
    --mutex;
    --empty_slots;
    
    
    item_count++;
    cout << "\n[+] Producer produced item: " << item_count;
    
    
    ++mutex;
    ++full_slots;
}


void consumer() {
    
    --mutex;
    --full_slots;
    
   
    cout << "\n[-] Consumer consumed item: " << item_count;
    item_count--;
    
  
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
                if ((mutex == 1) && (empty_slots != 0)) {
                    producer();
                } else {
                    cout << "\n[!] WAIT: Buffer is FULL! Producer cannot add items.";
                }
                break;
                
            case 2:
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
