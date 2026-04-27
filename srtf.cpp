#include <iostream.h>
#include <conio.h>

int main() {
    int n, i;
    int current_time = 0, completed = 0;
    int min_index, min_rt;
    
    // AT = Arrival Time, BT = Burst Time, RT = Remaining Time
    int PID[50], AT[50], BT[50], RT[50], CT[50], TAT[50], WT[50]; 
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
        
        // At the start, the Remaining Time is equal to the full Burst Time
        RT[i] = BT[i]; 
    }

    // 2. SRTF Scheduling Logic
    while(completed != n) {
        min_index = -1;
        min_rt = 9999; // Start with a very large number for comparison

        // Scan all processes to find the one with the shortest remaining time
        for(i = 0; i < n; i++) {
            // Check if process has arrived AND is not finished yet (RT > 0)
            if(AT[i] <= current_time && RT[i] > 0) {
                
                if(RT[i] < min_rt) {
                    min_rt = RT[i];
                    min_index = i;
                }
                // Tie-breaker: If remaining times are equal, pick the one that arrived first
                else if(RT[i] == min_rt) {
                    if(AT[i] < AT[min_index]) {
                        min_rt = RT[i];
                        min_index = i;
                    }
                }
            }
        }

        // If a process was found
        if(min_index != -1) {
            // Run it for exactly 1 unit of time
            RT[min_index]--; 
            current_time++;  
            
            // Check if the process just finished in this exact second
            if(RT[min_index] == 0) {
                completed++;
                
                CT[min_index] = current_time;
                TAT[min_index] = CT[min_index] - AT[min_index];
                WT[min_index] = TAT[min_index] - BT[min_index];
                
                total_TAT += TAT[min_index];
                total_WT += WT[min_index];
            }
        } 
        // If no process has arrived yet, the CPU sits idle for 1 second
        else {
            current_time++;
        }
    }

    // 3. Output Results
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for(i = 0; i < n; i++) {
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
