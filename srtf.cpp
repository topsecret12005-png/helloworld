#include <iostream.h>
#include <conio.h>

int main() {
    int n, i;
    int current_time = 0, completed = 0;
    int min_index, min_rt;
    
    int PID[50], AT[50], BT[50], RT[50], CT[50], TAT[50], WT[50]; 
    float total_WT = 0.0, total_TAT = 0.0;

    clrscr();

    cout << "Enter number of processes: ";
    cin >> n;

    for(i = 0; i < n; i++) {
        PID[i] = i + 1;
        cout << "\nProcess " << i + 1 << "\n";
        cout << "Arrival Time: ";
        cin >> AT[i];
        cout << "Burst Time: ";
        cin >> BT[i];
        
        RT[i] = BT[i]; 
    }

    while(completed != n) {
        min_index = -1;
        min_rt = 9999; 

        for(i = 0; i < n; i++) {
            if(AT[i] <= current_time && RT[i] > 0) {
                
                if(RT[i] < min_rt) {
                    min_rt = RT[i];
                    min_index = i;
                }
                else if(RT[i] == min_rt) {
                    if(AT[i] < AT[min_index]) {
                        min_rt = RT[i];
                        min_index = i;
                    }
                }
            }
        }

        if(min_index != -1) {
            RT[min_index]--; 
            current_time++;  
            
            if(RT[min_index] == 0) {
                completed++;
                
                CT[min_index] = current_time;
                TAT[min_index] = CT[min_index] - AT[min_index];
                WT[min_index] = TAT[min_index] - BT[min_index];
                
                total_TAT += TAT[min_index];
                total_WT += WT[min_index];
            }
        } 
        else {
            current_time++;
        }
    }

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
