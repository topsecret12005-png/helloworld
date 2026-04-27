#include <iostream.h>
#include <conio.h>

int main() {
    int n, i;
    int current_time = 0, completed = 0;
    
    int PID[50], AT[50], BT[50], CT[50], TAT[50], WT[50], is_completed[50]; 
    float total_WT = 0.0, total_TAT = 0.0;

    clrscr();

    cout << "Enter number of processes: ";
    cin >> n;

    for (i = 0; i < n; i++) {
        PID[i] = i + 1;
        cout << "\nProcess " << i + 1 << "\n";
        cout << "Arrival Time: ";
        cin >> AT[i];
        cout << "Burst Time: ";
        cin >> BT[i];
        
        is_completed[i] = 0; 
    }

    while (completed != n) {
        int min_index = -1;
        int min_bt = 9999; 

        for (i = 0; i < n; i++) {
            if (AT[i] <= current_time && is_completed[i] == 0) {
                if (BT[i] < min_bt) {
                    min_bt = BT[i];
                    min_index = i;
                }
                if (BT[i] == min_bt) {
                    if (AT[i] < AT[min_index]) {
                        min_bt = BT[i];
                        min_index = i;
                    }
                }
            }
        }

        if (min_index != -1) {
            current_time += BT[min_index];
            
            CT[min_index] = current_time;
            TAT[min_index] = CT[min_index] - AT[min_index];
            WT[min_index] = TAT[min_index] - BT[min_index];
            
            total_TAT += TAT[min_index];
            total_WT += WT[min_index];
            
            is_completed[min_index] = 1; // Mark this process as finished
            completed++;
        } 
        else {
            current_time++;
        }
    }

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
