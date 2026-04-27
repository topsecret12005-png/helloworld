#include <iostream.h>
#include <conio.h>

int main() {
    int n, i;
    int current_time = 0, completed = 0;
    
    // Arrays for Process ID, Arrival, Burst, Priority, Completion, Turnaround, Waiting, and a completion flag
    int PID[50], AT[50], BT[50], PR[50], CT[50], TAT[50], WT[50], is_completed[50]; 
    float total_WT = 0.0, total_TAT = 0.0;

    clrscr();

    cout << "Enter number of processes: ";
    cin >> n;

    // 1. Take Input
    for(i = 0; i < n; i++) {
        PID[i] = i + 1;
        cout << "\nProcess " << i + 1 << "\n";
        cout << "Arrival Time: ";
        cin >> AT[i];
        cout << "Burst Time: ";
        cin >> BT[i];
        cout << "Priority (Lower number = Higher Priority): ";
        cin >> PR[i];
        
        // Initialize all processes as NOT completed (0)
        is_completed[i] = 0; 
    }

    // 2. Priority Scheduling Logic
    while(completed != n) {
        int highest_priority = 9999; // Start with a very large number (lowest possible priority)
        int selected_process = -1;

        // Scan all processes to find the one with the highest priority that has ARRIVED
        for(i = 0; i < n; i++) {
            if(AT[i] <= current_time && is_completed[i] == 0) {
                
                if(PR[i] < highest_priority) {
                    highest_priority = PR[i];
                    selected_process = i;
                }
                // Tie-breaker: If priorities are the same, pick the one that arrived first
                else if(PR[i] == highest_priority) {
                    if(AT[i] < AT[selected_process]) {
                        highest_priority = PR[i];
                        selected_process = i;
                    }
                }
            }
        }

        // If a process was found
        if(selected_process != -1) {
            // The process executes entirely
            current_time += BT[selected_process];
            
            CT[selected_process] = current_time;
            TAT[selected_process] = CT[selected_process] - AT[selected_process];
            WT[selected_process] = TAT[selected_process] - BT[selected_process];
            
            total_TAT += TAT[selected_process];
            total_WT += WT[selected_process];
            
            is_completed[selected_process] = 1; // Mark as finished
            completed++;
        } 
        // If no process has arrived yet, the CPU sits idle
        else {
            current_time++;
        }
    }

    // 3. Output Results
    cout << "\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n";
    for(i = 0; i < n; i++) {
        cout << PID[i] << "\t"
             << AT[i] << "\t"
             << BT[i] << "\t"
             << PR[i] << "\t\t"
             << CT[i] << "\t"
             << TAT[i] << "\t"
             << WT[i] << "\n";
    }

    cout << "\nAverage Waiting Time: " << (total_WT / n);
    cout << "\nAverage Turnaround Time: " << (total_TAT / n) << "\n";

    getch();
    return 0;
}
