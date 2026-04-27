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

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
        finish[i] = 0; 
    }

    for(k = 0; k < n; k++) {         
        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {      
                flag = 0;            
                
                for(j = 0; j < m; j++) {
                    if(need[i][j] > avail[j]) {
                        flag = 1;     
                        break;
                    }
                }

                if(flag == 0) {
                    safeSeq[count++] = i;         
                    for(j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];  
                    }
                    finish[i] = 1;               
                }
            }
        }
    }

    
    is_safe = 1;
    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
                is_safe = 0;                                                                                                         
            break;
        }
    }

   
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
