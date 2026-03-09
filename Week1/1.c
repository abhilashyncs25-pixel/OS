#include <stdio.h>

int main() {
    int n, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int pid[n], at[n], bt[n], ct[n], tat[n], wt[n], rt[n];

    // Input arrival time and burst time
    for(i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("\nProcess %d\n", pid[i]);
        printf("Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Burst Time: ");
        scanf("%d", &bt[i]);
    }

    // Sort processes according to Arrival Time (FCFS rule)
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {
            if(at[i] > at[j]) {
                // Swap arrival time
                int temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                // Swap burst time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap pid
                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    // Calculate Completion Time
    for(i = 0; i < n; i++) {
        if(i == 0) {
            ct[i] = at[i] + bt[i];
        } else {
            if(ct[i-1] < at[i])
                ct[i] = at[i] + bt[i];
            else
                ct[i] = ct[i-1] + bt[i];
        }
    }

    float total_wt = 0, total_tat = 0, total_rt = 0;

    // Calculate TAT, WT, RT
    for(i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        rt[i] = wt[i];  // In FCFS, Response Time = Waiting Time

        total_wt += wt[i];
        total_tat += tat[i];
        total_rt += rt[i];
    }

    // Display Output
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], at[i], bt[i], ct[i],
               tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", total_wt / n);
    printf("\nAverage Turnaround Time = %.2f", total_tat / n);
    printf("\nAverage Response Time = %.2f\n", total_rt / n);

    return 0;
}
