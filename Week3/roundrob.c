#include <stdio.h>

int main()
{
    int n, i, time = 0, completed = 0;
    int at[20], bt[20], rt[20], ct[20], tat[20], wt[20], resp[20];
    int queue[100], front = 0, rear = 0;
    int visited[20] = {0}, started[20] = {0};
    int tq;

    float avg_tat = 0, avg_wt = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("\nProcess %d\n", i+1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        rt[i] = bt[i]; // remaining time
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    // Start with first process
    queue[rear++] = 0;
    visited[0] = 1;

    while(completed < n)
    {
        int idx = queue[front++];

        // If first time execution → calculate Response Time
        if(started[idx] == 0)
        {
            resp[idx] = time - at[idx];
            avg_rt += resp[idx];
            started[idx] = 1;
        }

        if(rt[idx] > 0)
        {
            if(rt[idx] > tq)
            {
                time += tq;
                rt[idx] -= tq;
            }
            else
            {
                time += rt[idx];
                rt[idx] = 0;

                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];

                avg_tat += tat[idx];
                avg_wt += wt[idx];

                completed++;
            }

            // Add newly arrived processes
            for(i = 0; i < n; i++)
            {
                if(at[i] <= time && visited[i] == 0)
                {
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }

            // Re-add process if not finished
            if(rt[idx] > 0)
            {
                queue[rear++] = idx;
            }

            // If queue empty → pick next
            if(front == rear)
            {
                for(i = 0; i < n; i++)
                {
                    if(rt[i] > 0)
                    {
                        queue[rear++] = i;
                        visited[i] = 1;
                        break;
                    }
                }
            }
        }
    }

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1, at[i], bt[i], ct[i], tat[i], wt[i], resp[i]);
    }

    printf("\nAverage TAT = %.2f", avg_tat/n);
    printf("\nAverage WT = %.2f", avg_wt/n);
    printf("\nAverage RT = %.2f\n", avg_rt/n);

    return 0;
}
