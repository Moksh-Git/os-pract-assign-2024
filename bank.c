#include <stdio.h>

int main() {
    int n, max, allocateCount = 0;
    
 
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int required[n], allocate[n], need[n], ans[n], available, sequence = 0;

   
    printf("Enter the maximum required resource for each process: \n");
    for (int i = 0; i < n; i++) {
        printf("Requirement for Process %d: ", i + 1);
        scanf("%d", &required[i]);
    }


    printf("\nEnter the allocated resource for each process: \n");
    for (int i = 0; i < n; i++) {
        printf("Allocated for Process %d: ", i + 1);
        scanf("%d", &allocate[i]);

        
        allocateCount += allocate[i];
        

        need[i] = required[i] - allocate[i];
    }

    
    printf("\nEnter the total available resources: ");
    scanf("%d", &max);

    available = max - allocateCount;

    int count = 0, ind = 0;
    int finished[n];
   
    for (int i = 0; i < n; i++) {
        finished[i] = 0;
    }

    while (sequence < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (finished[i] == 0) {
                int j;
                for (j = 0; j < n; j++) {
                    if (need[i] > available) {
                        break;
                    }
                }


                if (j == n) {
                    available += allocate[i];
                    ans[ind++] = i + 1;
                    finished[i] = 1;
                    found = 1;
                    sequence++;
                }
            }
        }

               if (found == 0) {
            printf("\nThe system is in an unsafe state!!\n");
            return 0;
        }
    }
    printf("\nThe system is in a safe state!!\n");
    printf("Safe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", ans[i]);
    }
    printf("\n");

    return 0;
}
