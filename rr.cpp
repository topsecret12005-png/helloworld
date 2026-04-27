#include <iostream.h>
#include <conio.h>

int main() {
    int n, quantum, i, j, temp;
    int current_time = 0, completed = 0, flag = 0;
    
    // AT = Arrival Time, BT = Burst Time, RT = Remaining Time
    int PID[50], AT[50], BT[50], RT[50], CT[50], TAT[50], WT[50]; 
    float total_WT = 0.0, total_TAT = 0.0;

    clrscr();

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    // 1. Take Input
    for (i = 0; i < n; i++) {
        PID[i] = i + 1;
        cout << "\nProcess " << i + 1 << "\n";
        cout << "Arrival Time: ";
        cin >> AT[i];
        cout << "Burst Time: ";
        cin >> BT[i];
        
        // Initially, Remaining Time is equal to Burst Time
        RT[i] = BT[i]; 
    }

    // 2. Sort processes by Arrival Time (Bubble Sort)
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (AT[j] > AT[j + 1]) {
                temp = AT[j]; AT[j] = AT[j + 1]; AT[j + 1] = temp;
                temp = BT[j]; BT[j] = BT[j + 1]; BT[j + 1] = temp;
                temp = RT[j]; RT[j] = RT[j + 1]; RT[j + 1] = temp;
                temp = PID[j]; PID[j] = PID[j + 1]; PID[j + 1] = temp;
            }
        }
    }

    // 3. Round Robin Scheduling Logic
    while (completed != n) {
        flag = 0; // Reset flag for this cycle

        for (i = 0; i < n; i++) {
            // Check if process has arrived AND still needs CPU time
            if (AT[i] <= current_time && RT[i] > 0) {
                flag = 1; // A process was found and executed

                if (RT[i] > quantum) {
                    // Process runs for the full time quantum
                    current_time += quantum;
                    RT[i] -= quantum;
                } else {
                    // Process finishes its remaining execution
                    current_time += RT[i];
                    CT[i] = current_time; // Completion time is recorded
                    RT[i] = 0;            // Process is done
                    completed++;          // Increase completed counter

                    // Calculate TAT and WT for this finished process
                    TAT[i] = CT[i] - AT[i];
                    WT[i] = TAT[i] - BT[i];
                    
                    total_TAT += TAT[i];
                    total_WT += WT[i];
                }
            }
        }

        // If no process was ready to execute, CPU sits idle, time moves forward
        if (flag == 0) {
            current_time++;
        }
    }

    // 4. Output Results
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for (i = 0; i < n; i++) {
        cout << PID[i] << "\t"
             << AT[i] << "\t"
             << BT[i] << "\t"
             << CT[i] << "\t"
             << TAT[i] << "\t"
             << WT[i] << "\n";
    }

    cout << "\nAverage Waiting Time: " << (total_WT / n);
    cout << "\nAverage Turnaround Time: " << (total_TAT / n) << "\n";

    getch();
    return 0;
}
