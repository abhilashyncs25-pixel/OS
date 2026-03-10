#include <stdio.h>

int main()
{
    int n,i,time=0,completed=0,idx;
    int at[20],bt[20],pr[20],ct[20],tat[20],wt[20],rt[20];
    int done[20], seq[20];   // seq[] stores execution order
    float avg_tat=0,avg_wt=0,avg_rt=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("\nProcess %d\n",i+1);

        printf("Arrival Time: ");
        scanf("%d",&at[i]);

        printf("Burst Time: ");
        scanf("%d",&bt[i]);

        printf("Priority: ");
        scanf("%d",&pr[i]);

        done[i]=0;
    }

    while(completed<n)
    {
        idx=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && done[i]==0)
            {
                if(idx==-1 || pr[i]<pr[idx])
                    idx=i;
            }
        }

        if(idx!=-1)
        {
            rt[idx]=time-at[idx];   // Response Time

            time=time+bt[idx];
            ct[idx]=time;

            tat[idx]=ct[idx]-at[idx];
            wt[idx]=tat[idx]-bt[idx];

            avg_tat+=tat[idx];
            avg_wt+=wt[idx];
            avg_rt+=rt[idx];

            done[idx]=1;
            seq[completed]=idx;   // store execution order
            completed++;
        }
        else
            time++;
    }

    // Print table
    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");
    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pr[i],ct[i],tat[i],wt[i],rt[i]);
    }

    // Print averages
    printf("\nAverage TAT = %.2f",avg_tat/n);
    printf("\nAverage WT = %.2f",avg_wt/n);
    printf("\nAverage RT = %.2f\n",avg_rt/n);

    // Print Gantt Chart
    printf("\nGantt Chart:\n");
    for(i=0;i<n;i++) printf("P%d ", seq[i]+1);
    printf("\n");
    printf("0 ");
    for(i=0;i<n;i++) printf("%d ", ct[seq[i]]);
    printf("\n");

    return 0;
}
