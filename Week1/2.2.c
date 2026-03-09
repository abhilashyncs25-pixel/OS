#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], rt[n];
    int completed[n], time = 0, count = 0;

    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess %d\n", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
        completed[i] = 0;
    }

    while(count < n) {
        int minIndex = -1;
        int minBT = 9999;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && completed[i] == 0) {
                if(bt[i] < minBT) {
                    minBT = bt[i];
                    minIndex = i;
                }
            }
        }

        if(minIndex == -1) {
            time++;
        } else {
            time += bt[minIndex];
            ct[minIndex] = time;
            tat[minIndex] = ct[minIndex] - at[minIndex];
            wt[minIndex] = tat[minIndex] - bt[minIndex];
            rt[minIndex] = wt[minIndex];  // Non-preemptive
            completed[minIndex] = 1;
            count++;
        }
    }

    float totalWT = 0, totalTAT = 0, totalRT = 0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i],
               ct[i], tat[i], wt[i], rt[i]);

        totalWT += wt[i];
        totalTAT += tat[i];
        totalRT += rt[i];
    }

    printf("\nAverage WT  = %.2f", totalWT/n);
    printf("\nAverage TAT = %.2f", totalTAT/n);
    printf("\nAverage RT  = %.2f\n", totalRT/n);

    return 0;
}
