/* C Program to implement API using Libvirt */

#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

void main()
{

    int i,val=-1,choice,num_domains;
    char choice_id[25];
    int *active_domains;
    virConnectPtr conn;
    virDomainPtr vdp;

    conn = virConnectOpen("xen:///"); 
    if (conn == NULL) {
        fprintf(stderr, "Error opening connection to XEN:/// \n");
    }
    else
    {

//For finding Active Devices
        num_domains=virConnectNumOfDomains(conn); 
        active_domains=malloc(sizeof(int) * num_domains);
        num_domains = virConnectListDomains(conn, active_domains, num_domains); 

        printf("Active domain IDs : \n");
        for (i = 0 ; i < num_domains ; i++) {
            printf(" %d\n", active_domains[i]);
        }
        free(active_domains);

        while(1)
        {
            
            printf("\n1.Start\n2.Suspend\n3.Resume\n4.stop\n ");
	    printf("Insert your choice: ");
            scanf("%d",&choice);

            printf("\n Please Insert the Domian Name: ");
            scanf("%s",choice_id);
  
            vdp=virDomainLookupByName(conn,choice_id); 
        
            switch(choice)
            {
                case 1:/* Start */
 val=virDomainCreate(vdp); 
                       if(val==0)
                           printf("Success\n");
                       else
                           printf("Failed\n");
                       break;
                case 2:/* Suspend */
val=virDomainSuspend(vdp); 
                       if(val==0)
                           printf("Success\n");
                       else
                           printf("Failed\n");
                       break;
                case 3:/* Resume */
val=virDomainResume(vdp); 
                        if(val==0)
                            printf("Success\n");
                        else
                            printf("Failed\n");
                        break;

                case 4: /* stop */
val=virDomainShutdown(vdp);
                        if(val==0)
                            printf("Success\n");
                        else
                            printf("Failed\n");
                        break;
                
            }
        }
        virConnectClose(conn);
    }
}
