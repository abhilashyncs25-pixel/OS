#include <stdio.h>
#include <limits.h>

int main()
{
    int n,i,time=0,completed=0,idx;
    int at[20],bt[20],pr[20],rt[20],ct[20],tat[20],wt[20],resp[20];
    int started[20]={0};
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

        rt[i]=bt[i];
    }

    while(completed<n)
    {
        idx=-1;
        int highest=INT_MAX;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]>0)
            {
                if(pr[i]<highest)
                {
                    highest=pr[i];
                    idx=i;
                }
            }
        }

        if(idx!=-1)
        {
            if(started[idx]==0)
            {
                resp[idx]=time-at[idx]; // Response time
                started[idx]=1;
            }

            rt[idx]--;
            time++;

            if(rt[idx]==0)
            {
                completed++;

                ct[idx]=time;
                tat[idx]=ct[idx]-at[idx];
                wt[idx]=tat[idx]-bt[idx];

                avg_tat+=tat[idx];
                avg_wt+=wt[idx];
                avg_rt+=resp[idx];
            }
        }
        else
            time++;
    }

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\tRT\n");

    for(i=0;i<n;i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        i+1,at[i],bt[i],pr[i],ct[i],tat[i],wt[i],resp[i]);
    }

    printf("\nAverage TAT = %.2f",avg_tat/n);
    printf("\nAverage WT = %.2f",avg_wt/n);
    printf("\nAverage RT = %.2f\n",avg_rt/n);

    return 0;
}
