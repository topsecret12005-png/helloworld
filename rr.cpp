#include <iostream.h>
#include <conio.h>

int main() {
    int n, quantum, i, j, temp;
    int current_time = 0, completed = 0, flag = 0;
    
    int PID[50], AT[50], BT[50], RT[50], CT[50], TAT[50], WT[50]; 
    float total_WT = 0.0, total_TAT = 0.0;

    clrscr();

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter Time Quantum: ";
    cin >> quantum;

    for (i = 0; i < n; i++) {
        PID[i] = i + 1;
        cout << "\nProcess " << i + 1 << "\n";
        cout << "Arrival Time: ";
        cin >> AT[i];
        cout << "Burst Time: ";
        cin >> BT[i];
        
        RT[i] = BT[i]; 
    }

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

    while (completed != n) {
        flag = 0; 

        for (i = 0; i < n; i++) {
            if (AT[i] <= current_time && RT[i] > 0) {
                flag = 1; 

                if (RT[i] > quantum) {
                    current_time += quantum;
                    RT[i] -= quantum;
                } else {
                    current_time += RT[i];
                    CT[i] = current_time; 
                    RT[i] = 0;            
                    completed++;          

                    TAT[i] = CT[i] - AT[i];
                    WT[i] = TAT[i] - BT[i];
                    
                    total_TAT += TAT[i];
                    total_WT += WT[i];
                }
            }
        }

        if (flag == 0) {
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
