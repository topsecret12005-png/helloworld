#include <iostream.h>
#include <conio.h>

int main() {
    int n, m, i, j, k;
    int alloc[10][10], max[10][10], need[10][10], avail[10];
    int finish[10], safeSeq[10];
    int count = 0, flag, is_safe;

    clrscr();

    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resource types: ";
    cin >> m;

    cout << "\nEnter Allocation Matrix:\n";
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            cin >> alloc[i][j];

    cout << "Enter Max Matrix:\n";
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            cin >> max[i][j];

    cout << "Enter Available Resources:\n";
    for(j = 0; j < m; j++)
        cin >> avail[j];

    // 1. Calculate NEED Matrix (Need = Max - Alloc) & Initialize Finish to 0
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
        finish[i] = 0; // Assume no process is finished yet
    }

    // 2. The Safety Check
    for(k = 0; k < n; k++) {          // Repeat 'n' times to ensure all processes get checked
        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {      // Only check unfinished processes
                flag = 0;             // Assume process CAN run
                
                for(j = 0; j < m; j++) {
                    if(need[i][j] > avail[j]) {
                        flag = 1;     // It needs more than we have! It CANNOT run.
                        break;
                    }
                }

                // If the flag is still 0, the process CAN run safely
                if(flag == 0) {
                    safeSeq[count++] = i;         // Add to safe sequence
                    for(j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];  // Return its resources to the bank
                    }
                    finish[i] = 1;                // Mark as finished
                }
            }
        }
    }

    // 3. Final Verification
    is_safe = 1;
    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            is_safe = 0; // Found a process that couldn't finish
            break;
        }
    }

    // Output the Result
    if(is_safe == 1) {
        cout << "\n[SUCCESS] System is in SAFE state.\nSafe Sequence: ";
        for(i = 0; i < n; i++) {
            cout << "P" << safeSeq[i] << " ";
        }
    } else {
        cout << "\n[WARNING] System is in UNSAFE state! Deadlock possible.";
    }

    getch();
    return 0;
}
