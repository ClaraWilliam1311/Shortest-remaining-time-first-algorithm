#include<stdio.h>
struct sjf
{
       int bt,at,wt,st,pno,tt,cbt;
};

int get(struct sjf arr[],int t,int n)
{
       int imin,min=9999,i;
       for(i=0;i<n;i++)
       {
              if(arr[i].at<=t&&arr[i].st==0)
                     if(min>arr[i].bt)
                     {
                           min=arr[i].bt;
                           imin=i;
                     }
       }
       return imin;
}

void gantt_chart(struct sjf arr[],int p[],int n,int nop)
{
       int i,j,a[100],s=0;
       float avgwt=0;
       printf("\n\n\n\t\t\t\t***********\n\n");
       printf("\nBefore Arrange...\n");

        puts("+-----+------------+--------------+");
        puts("| PID | Burst Time | Arrival Time |");
        puts("+-----+------------+--------------+");

        for(i=0; i<nop; i++)
        {
            printf("| %2d  |     %2d     |      %2d      |\n", arr[i].pno, arr[i].cbt,arr[i].at);
            puts("+-----+------------+--------------+");
        }

       printf("\n\t\t\t<<GANTT CHART>>\t\t\t\n\n");
       printf("     ------      ------      ------      ------      ------       ------       ------      \n");
       printf(" [0] ");
       for(i=0;i<n-1;i++)
       {
              while(i<n-1&&p[i]==p[i+1])
              {
                  s++;
                  i++;
              }

              s++;
              printf("| p%d |",arr[p[i]].pno);
              printf(" [%d]  ",s);
              arr[p[i]].wt=s-arr[p[i]].at-arr[p[i]].tt;
       }
        printf("\n     ------      ------      ------      ------      ------       ------       ------      \n");
       for(i=0;i<nop;i++)
       {
              arr[i].tt+=arr[i].wt;
              avgwt+=arr[i].wt;
       }


       printf("\n\n\n\t\t\t\t***********\n\n");
       printf("+------------+------------------+-----------------------+------------------------+-------------------+");
       printf("\n| Process    |  Arrival Time\t|\tBurst Time\t|   Turnaround Time\t |     Waiting Time  |\n");
       printf("+------------+------------------+-----------------------+------------------------+-------------------+\n");


       for(i=0;i<nop;i++)
       {


        printf("| %2d\t     |     %2d      \t|       %2d\t\t|     %2d\t\t |     %2d  \t     |\n"
               , arr[i].pno,arr[i].at,arr[i].cbt,arr[i].tt,arr[i].wt );
        puts("+------------+------------------+-----------------------+------------------------+-------------------+");
    }

       printf("\n\n\t\t\t\t***********\n\n");
       avgwt = avgwt/nop;
       printf("Average Waiting Time : %.2f\n",avgwt);
       return;
}

int iscomplite(struct sjf arr[],int n)
{
       int i;
       for(i=0;i<n;i++)
              if(arr[i].st==0)
                     return 0;
       return 1;
}
int main()
{
       int n,i,a,t=0;
       int p[100];
       float avgwt=0,avgtt=0;
       struct sjf arr[100];
       printf("SJF (Shortest Job First) - Preemptive\n");
       printf("Note -\n1. Arrival Time of at least on process should be 0\n2. CPU should never be idle\n");
       printf("\nEnter Number of Processes:");
       scanf("%d",&n);
       for(i=0;i<n;i++)
       {
           printf("\nEnter Details of %d Process:\n",i+1);
           printf("Enter Arrival Time:");
           scanf("%d",&arr[i].at);
           printf("Enter Burst Time:");
           scanf("%d",&arr[i].bt);
           arr[i].pno = i+1;
           arr[i].cbt = arr[i].bt;
           arr[i].st=0;
           arr[i].tt=arr[i].bt;
           arr[i].wt=0;
       }
       i=0;
       while(1)
       {
              if(iscomplite(arr,n))
                     break;
              a=get(arr,t,n);
              p[i]=a;
              arr[a].bt-=1;
              if(arr[a].bt==0)
                     arr[a].st=1;
              t=t+1;
              i++;
       }
       gantt_chart(arr,p,i,n);
       return 0;
}



