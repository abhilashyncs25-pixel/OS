#include <stdio.h>

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], rt_bt[n];
    int ct[n], tat[n], wt[n], rt[n];
    int completed = 0, time = 0;

    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess %d\n", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        rt_bt[i] = bt[i];   // remaining time
        rt[i] = -1;         // mark response time not assigned
    }

    while(completed < n) {
        int minIndex = -1;
        int minBT = 9999;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && rt_bt[i] > 0) {
                if(rt_bt[i] < minBT) {
                    minBT = rt_bt[i];
                    minIndex = i;
                }
            }
        }

        if(minIndex == -1) {
            time++;
        } else {
            if(rt[minIndex] == -1) {
                rt[minIndex] = time - at[minIndex];  // first response
            }

            rt_bt[minIndex]--;
            time++;

            if(rt_bt[minIndex] == 0) {
                ct[minIndex] = time;
                tat[minIndex] = ct[minIndex] - at[minIndex];
                wt[minIndex] = tat[minIndex] - bt[minIndex];
                completed++;
            }
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
