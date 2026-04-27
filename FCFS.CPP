#include <iostream.h>
#include <conio.h>

int main() {
    int n, i, j, temp;
    int AT[50], BT[50], CT[50], TAT[50], WT[50], PID[50]; 

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
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (AT[j] > AT[j + 1]) {
                temp = AT[j];
                AT[j] = AT[j + 1];
                AT[j + 1] = temp;

                temp = BT[j];
                BT[j] = BT[j + 1];
                BT[j + 1] = temp;

                temp = PID[j];
                PID[j] = PID[j + 1];
                PID[j + 1] = temp;
            }
        }
    }

    CT[0] = AT[0] + BT[0];

    for (i = 1; i < n; i++) {
        if (CT[i - 1] < AT[i]) {
            CT[i] = AT[i] + BT[i];  // CPU idle
        } else {
            CT[i] = CT[i - 1] + BT[i];
        }
    }

    for (i = 0; i < n; i++) {
        TAT[i] = CT[i] - AT[i];
        WT[i] = TAT[i] - BT[i];
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

    getch(); // Pauses the screen so you can view the output
    return 0;
}
