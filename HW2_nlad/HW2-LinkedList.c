/*
Name: Niyanta Lad
Gnumber: G01284622
HOMEWORK 2 - CS531
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct address_t                        //structure with type address_t with components for the four
                                        //integers of the IPv4 address along with a fifth component to
                                        //store an associated alias (key field) of up to 11 characters
{
    int octet[4];                       //integer array to store the 4 components of IPv4 address
    char alias[11];                     //character array to store the 5th component (alias) of upto 11 characters
    struct address_t *next;             //next pointer of type struct address_t that points to the next node
};

struct address_t *head = NULL;          //global variables that are pointers to the head node and the current node in the list. head node is the first node in the linked list
struct address_t *curr = NULL;


struct address_t* create_list(int val[], char name[])  //creating a singly linked list of address_t structures that contain all address/alias pairs from the “CS531_Inet.txt” file and adds data to it
{
    printf("\n-------Creating list with headnode as '[%d.%d.%d.%d]: %s'--------\n",val[0],val[1],val[2],val[3],name);
    struct address_t *ptr = (struct address_t*)malloc(sizeof(struct address_t)); // allocating memory to the structure. ptr is a pointer that now contains the base address of the newly created node
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    for(int i=0;i<4;i++)
    ptr->octet[i] = val[i];
    strcpy(ptr->alias,name);
    ptr->next = NULL;
    head = curr = ptr;
    return ptr;
}

struct address_t* add_to_list(int val[], char name[])         //function to add new node to the linked list
{
    if(NULL == head)
    {
        return (create_list(val, name));                    //function call to create_list where node is added to the front and head points to the new node
    }

    printf("\n-------Adding node 'address [%d.%d.%d.%d], alias : %s' to beginning of the list--------\n",val[0],val[1],val[2],val[3],name);
    struct address_t *ptr = (struct address_t*)malloc(sizeof(struct address_t));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    for(int i=0;i<4;i++)
    ptr->octet[i] = val[i];                             //address is added to the node where ptr is pointing to
    strcpy(ptr->alias,name);                            //alias is added to the node where ptr is pointing to
    ptr->next = head;                                   //next pointer of the newly added node will now point to head and head will be updated to ptr, so ptr becomes the new head
    head = ptr;                                         //hence new node is added to the beginning of the list
    return ptr;
}

void print_list(void)                               //function to display the linked list
{
    struct address_t *ptr = head;
    printf("\n -------Printing list Start------- \n");
    printf("\nhead:");
    int count=0;
    while(ptr != NULL)
    {
    //printf("\tnode addr:%p \t data: [%d.%d.%d.%d: %s] \tnext addr:%p\n",ptr,ptr->octet[0], ptr->octet[1], ptr->octet[2], ptr->octet[3], ptr->alias,ptr->next);
    printf("[%d.%d.%d.%d: %s] \n",ptr->octet[0], ptr->octet[1], ptr->octet[2], ptr->octet[3], ptr->alias);
    ptr = ptr->next;                            //traverses the list
    count++;
    }
    printf("Total node count: %d",count);              //count holds the number of nodes in the list
    printf("\n -------Printing list End------- \n");
    return; //returns to the main function to redisplay the main menu

}

struct address_t* search_in_list(char name[], struct address_t **prev)      //function to search a node by its alias and return its address
{
    struct address_t *ptr = head;
    struct address_t *tmp = NULL;
    bool found = false;
    while(ptr != NULL)
    {
        if(strcmp(ptr->alias,name)==0)          //checks whether the alias entered by the user matches with the aliases in our list
        {
        found = true;
        break;
        }
        else
        {
        tmp = ptr;
        ptr = ptr->next;
        }
    }
    if(true == found)
        {
        if(prev)
        *prev = tmp;
        return ptr;
        }
    else
        {
        return NULL;                        //returns NULL to the calling function if the alias is found
        }
}

void add_address()                      //function to add a new address to the list
{
    char temp[11];                      //char array to store the alias entered by the user
    printf("Enter alias: ");                        //Prompts the user for an alias
    scanf("%s", temp);
    struct address_t *ptr = head;
    printf("\n--------Searching the list for alias '%s'----------\n",temp);

    struct address_t *search = NULL;
    search = search_in_list(temp, NULL);               //checks whether the alias already exists or not. If present then the user will be warned that a duplicate address/alias exists
                                                        //and the user will be prompted to enter a unique address
    if(NULL == search)
    {
        printf("\n-------Search [alias = %s] failed, no such element found.\n-------",temp);

        printf("Enter address for alias: ");
        char buf1[500];                         //character array to store the entered address by the user
        int temp1[4];                           //temp array
        printf("Enter address for %s: ",temp);
        scanf("%s",buf1);
        sscanf(buf1,"%d.%d.%d.%d",&temp1[0],&temp1[1],&temp1[2],&temp1[3]);
        if(temp1[0]<0 || temp1[0]>255 || temp1[1]<0 || temp1[1]>255 || temp1[2]<0 || temp1[2]>255 || temp1[3]<0 || temp1[3]>255) //check if value is between 0 and 255 inclusive, if not prompt the user again
        {
            printf("\nInvalid address entered, please re-enter!\n");
        }
        else
        {
        printf("---------Adding Address: %d.%d.%d.%d, Alias: %s to the list---------", temp1[0], temp1[1], temp1[2], temp1[3], temp);
        add_to_list(temp1,temp);
        }
    }
    else
    {
    printf("\n------Search found. Alias = %s already exists--------\n",temp);
    }
    return;                     //returns to the main function to redisplay the main menu
}

void lookup_address()           //function to look up the address entered by the user
{
    char temp[11];              //temporary char array to store the alias entered by the user
    printf("Enter alias: ");
    scanf("%s", temp);
    struct address_t *ptr = head;
    printf("\n--------Searching the list for alias: '%s'----------\n",temp);
    struct address_t *search = NULL;
    search = search_in_list(temp, NULL);
    if(NULL == search)
    {
        printf("\n-------Search [alias = %s] failed, no such element found.\n",temp);

    }
    else
    {
    printf("\n------Search found. Address for %s: [%d.%d.%d.%d]--------\n",temp, search->octet[0],search->octet[1],search->octet[2],search->octet[3]);
    }
    return;
}

void update_address()           //function to update the address of the alias entered by the user
{
    char temp[11];              //temporary char array to store the alias entered by the user
    printf("Enter alias: ");
    scanf("%s", temp);
    struct address_t *ptr = head;
    printf("\n--------Searching the list for alias: '%s'----------\n",temp);
    struct address_t *search = NULL;
    search = search_in_list(temp, NULL);
    if(NULL == search)
    {
        printf("\n-------Search [alias = %s] failed, no such Alias found.\n",temp);

    }
    else
    {
        printf("\n------Search successfull. Current address for %s: [%d.%d.%d.%d]--------\n",temp, search->octet[0],search->octet[1],search->octet[2],search->octet[3]);
        printf("Enter new address for Alias: %s\n", temp);
        int buf[500];

        int i=0;
        while (i<4)
        {
        printf("Enter value#%d between 0-255: \n", i+1);
        scanf("%d",&buf[i]);
        if (buf[i]<0 || buf[i]>255) //check if value is between 0 and 255 inclusive, if not prompt the user again
		{
		    printf("ERROR: value must be between 0 and 255 inclusive, please re-enter : \n");
		  	continue;
	    }
        else
        i++;
        }

        printf("Address entered: %d.%d.%d.%d\n", buf[0], buf[1], buf[2], buf[3]);

        while(ptr!= NULL)
             {
                    if(buf[0]==ptr->octet[0] && buf[1]==ptr->octet[1]&& buf[2]==ptr->octet[2] && buf[3]==ptr->octet[3])
                    {
                        printf("Error: Duplicate address entered. Update failed\n");
                        return;
                    }
                    else
                        ptr = ptr->next;
             }
        printf("---------Updating address of %s--------\n", temp);
        for(i=0;i<4;i++)
        {
                search->octet[i]=buf[i];
        }
         printf("----------Updated list is: ---------\n");
         print_list();
    }
    return;             //returns to the main function to redisplay the main menu
}

int delete_from_list(char name[])       //function to delete a node with the entered alias from the linked list
{
    char opt[5];
    struct address_t *prev = NULL;         //pointer that points to the previous node
    struct address_t *del = NULL;           //delete pointer that points to the node to be deleted
    printf("\n Deleting value [%s] from list\n",name);
    del = search_in_list(name,&prev);          // function call to search_in_list to check whether the alias to be deleted exists in the list
    if(del == NULL)
    {
        printf("\n-------Search [alias = %s] failed, no such element found.--------\n",name);
        return -1;
    }
    else
    {
        printf("\n------Search found. Address for %s: [%d.%d.%d.%d]--------\n",name, del->octet[0],del->octet[1],del->octet[2],del->octet[3]);
        printf("Are you sure you want to delete this node from the list? Enter yes to confirm: \n");
        scanf("%s",opt);
        if(strcmp(opt, "yes")==0)
        {
            if(prev != NULL)
            prev->next = del->next;             //previous nodes next pointer will now point to the next of the node to be deleted
            if(del == curr)
            {
            curr = prev;
            }
            else if(del == head)                    //if head is to be deleted then only update the head with next of del pointer
            {
            head = del->next;
            }
        }
        else if (strcmp(opt, "no")==0)
           {
            printf("Operation Camcelled\n");
            return 1;
           }
        else
            {
                printf("Invalid input\n");
                return 1;
            }
    }
    free(del);                                  //frees the memory of the deleted node
    del = NULL;
    return 0;
}

void delete()           //function to check whether deletion has passed or failed
{
    char temp[11];
    printf("Enter the alias to be deleted: ");
    scanf("%s", temp);
    int ret=0;
    {
        ret = delete_from_list(temp); //function call to delete_from_list
        if(ret == -1)
        {
        printf("\n deletion [Alias = %s] failed\n",temp); }
        else if (ret==0)
        {
        printf("\n deletion [Alias = %s] passed \n",temp);
        }
        else
        return;                 //returns to the main function to redisplay the main menu
        }
}

void display_location()             //function to display aliases on the basis of the location entered by the user
{
        int buf[30];
        struct address_t *ptr = head;
        printf("Enter address location\n");
        printf("Enter values between 0-255: \n");
        int i=0;
        while (i<2)
        {
        printf("Enter location value %d: ", i+1);
        scanf("%d",&buf[i]);
        if (buf[i]<0 || buf[i]>255) //check if value is between 0 and 255 inclusive, if not prompt the user again
		{
		    printf("ERROR: value must be between 0 and 255 inclusive, please re-enter : \n");
		  	continue;
	    }
        else
        i++;
        }

     int flag=0;
     while(ptr!= NULL)
             {
                    if(buf[0]==ptr->octet[0] && buf[1]==ptr->octet[1])
                    {
                    printf("Address: [%d.%d.%d.%d]\t Alias: %s\n",ptr->octet[0], ptr->octet[1], ptr->octet[2], ptr->octet[3], ptr->alias);
                    flag=1;
                    }
                    ptr = ptr->next;

             }

    if(flag==0)
    printf("No aliases found at this location!\n");
    return;                     //returns to the main function to redisplay the main menu
}

void save_to_file()     //function to save the list to a file with the file name entered by the user
{
    char filename[30];
    printf("Enter file name of max 30 characters (with/without extension .txt): \n"); //you may enter the file name with or without the extension
    scanf("%s",filename);
    FILE *newfp = fopen(filename, "w");         //file pointer that points to the file opened/created in WRITE mode
    struct address_t *ptr= head;
    if (newfp==NULL)            // error handling
    {
        printf("\nError...cannot open/create file\n");
        exit(1);
    }
    while(ptr!= NULL)                   //prints the output from the list to the file
             {
                 fprintf(newfp,"%d.%d.%d.%d %s\n",ptr->octet[0],ptr->octet[1],ptr->octet[2],ptr->octet[3],ptr->alias) ;
                 ptr = ptr->next;
             }
    printf("File saved successfully! \n");
    fclose(newfp);
}

void goodbye()              //function to quit the program
{
    printf("Goodbye! \n");
}


int main()
{
    char buf[500];
    int menuoption, count=0;
    FILE *fp;               //file pointer
    fp =fopen("CS531_Inet.txt","r");        //opens the file in READ mode
    if (!fp)
    {
        perror("Input file CS531_Inet.txt not present ");
        return 1;
    }
    struct address_t *ptr = (struct address_t*)malloc(sizeof(struct address_t));
    if(NULL == ptr)
    {
        printf("\n Node creation failed \n");
    }
    printf("\n-------Reading address/alias pairs from the file-------\n\n");
        while (fgets(buf,sizeof(buf),fp) != NULL)           //adds data from the file to a buffer to further store it in a linked list
       {
           int tempoctet[4];
           char tempalias[11];
           sscanf(buf, "%d.%d.%d.%d %s", tempoctet, tempoctet + 1, tempoctet + 2, tempoctet + 3, tempalias);        // parses the data from buf into tempoctet and tempalias
           printf("Address: %d.%d.%d.%d, Alias: %s", tempoctet[0], tempoctet[1], tempoctet[2], tempoctet[3], tempalias);
           add_to_list(tempoctet,tempalias);
        }

    print_list();

    do{                                             //Display menu
        printf("\nMain Menu\n");
        printf("1) Add address\n");
        printf("2) Lookup address\n");
        printf("3) Update address\n");
        printf("4) Delete address\n");
        printf("5) Display list\n");
        printf("6) Display aliases for location\n");
        printf("7) Save to file\n");
        printf("8) Quit\n");
        printf("Enter option: ");               //prompts the user to choose a menu option
        scanf("%d",&menuoption);
        switch(menuoption)
        {
            case 1: add_address();          //function calls to perform the operations specified in the main menu
            break;

            case 2: lookup_address();
            break;

            case 3: update_address();
            break;

            case 4: delete();
            break;

            case 5: print_list();
            break;

            case 6: display_location();
            break;

            case 7: save_to_file();
            break;

            case 8: goodbye();
            break;

            default: printf("invalid input\n");     //handles invalid inputs (menu option other than 1-8 entered)
            break;
        }

    }while(menuoption !=8);

    return 0;

}