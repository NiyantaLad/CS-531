/*
Name: Niyanta Lad
Gnumber: G01284622
HOMEWORK 3 - CS531
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct address_t //structure with type address_t with components for the four
                 //integers of the IPv4 address along with a fifth component to
                 //store an associated alias (key field) of up to 11 characters
{
    int octet[4];   //integer array to store the 4 components of IPv4 address
    char alias[11]; //character array to store the 5th component (alias) of upto 11 characters
    struct address_t *leftChild, *rightChild;
};

struct address_t *root = NULL;      //global pointer

struct address_t *newNode(int val[], char name[]) //creating a BST of address_t structures that contain all address/alias pairs from the “CS531_Inet.txt” file and adds data to it
{
    struct address_t *temp = (struct address_t *)malloc(sizeof(struct address_t)); // allocating memory to the structure. temp is a pointer that now contains the base address of the newly created node
    if (NULL == temp)
    {
        printf("\n Node creation failed \n");
        return NULL;
    }
    for (int i = 0; i < 4; i++)
        temp->octet[i] = val[i];
    strcpy(temp->alias, name);
    temp->leftChild = temp->rightChild = NULL;
    return temp;
}

struct address_t *add_to_tree(struct address_t *node, int val[], char name[]) //function to add new node to the tree
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
    {
        return (newNode(val, name)); //function call to newNode where a new node is created
    }

    /* Otherwise, recur down the tree */

    if (strcmp(name, node->alias) < 0)
        node->leftChild = add_to_tree(node->leftChild, val, name);
    else
        node->rightChild = add_to_tree(node->rightChild, val, name);

    /* return the (unchanged) node pointer */
    return node;
}

void inorder(struct address_t *root) //function to display the BST using inorder traversal
{

    if (root != NULL)
    {
        inorder(root->leftChild);
        //printf("\tnode addr:%p \t data: [%d.%d.%d.%d: %s] \tleftChild addr:%p\trightChild addr:%p\n",root,root->octet[0], root->octet[1], root->octet[2], root->octet[3], root->alias,root->leftChild, root->rightChild);
        printf("\n[%d.%d.%d.%d: %s] ", root->octet[0], root->octet[1], root->octet[2], root->octet[3], root->alias);
        inorder(root->rightChild);
    }

    return; //returns to the main function to redisplay the main menu
}

struct address_t *search_in_list(struct address_t *root, char name[]) //function to search a node by its alias 
{
    // Base Case
    if (root == NULL || strcmp(root->alias, name) == 0)
        return root;
    // Recur leftChild
    if ((strcmp(name, root->alias) < 0))
        return search_in_list(root->leftChild, name);
    // Recur rightChild
    return search_in_list(root->rightChild, name);
}

void searchadd(struct address_t *root, int *flag, int arr[]) //checks whether the address already exists or not. If present then the user will be warned that a duplicate address/alias exists
                                                             //and the user will be prompted to enter a unique address
{
    if (root != NULL)
    {
        searchadd(root->leftChild, flag, arr);
        if (root->octet[0] == arr[0] && root->octet[1] == arr[1] && root->octet[2] == arr[2] && root->octet[3] == arr[3])
        {
            *flag = 1;
        }
        searchadd(root->rightChild, flag, arr);
    }
}

void add_address() //function to add a new address to the list
{
    char temp[11];           //char array to store the alias entered by the user
    printf("Enter alias: "); //Prompts the user for an alias
    scanf("%s", temp);
    printf("\n--------Searching the tree for alias '%s'----------\n", temp);

    struct address_t *search = NULL;
    struct address_t *ptr = NULL;

    search = search_in_list(root, temp); //checks whether the alias already exists or not. If present then the user will be warned that a duplicate address/alias exists
                                         //and the user will be prompted to enter a unique address
    if (NULL == search)
    {
        printf("\n-------Search [alias = %s] failed, no such element found.\n-------", temp);

        char buf1[500]; //character array to store the entered address by the user
        int temp1[4];   //temp array
        printf("Enter address for %s: ", temp);
        scanf("%s", buf1);
        sscanf(buf1, "%d.%d.%d.%d", &temp1[0], &temp1[1], &temp1[2], &temp1[3]);
        if (temp1[0] < 0 || temp1[0] > 255 || temp1[1] < 0 || temp1[1] > 255 || temp1[2] < 0 || temp1[2] > 255 || temp1[3] < 0 || temp1[3] > 255) //check if value is between 0 and 255 inclusive, if not prompt the user again
        {
            printf("\nInvalid address entered, please re-enter!\n");
        } 
        
        else
        {
            int flag = 0;
            searchadd(root, &flag, temp1); //checks whether the address entered already exists or not. If present then the user will be warned that a duplicate address is entered and main menu will be redisplayed
            if (flag == 0)
            {
                printf("---------Adding Address: %d.%d.%d.%d, Alias: %s to the list---------", temp1[0], temp1[1], temp1[2], temp1[3], temp);
                root=add_to_tree(root, temp1, temp);
            }
            else
            {
                printf("\nDuplicate address entered\n");
            }
        }
    }
    else
    {
        printf("\n------Search found. Alias = %s already exists--------\n", temp);
    }
    return; //returns to the main function to redisplay the main menu
}

void lookup_address() //function to look up the address for the alias entered by the user
{
    char temp[11]; //temporary char array to store the alias entered by the user
    printf("Enter alias: ");
    scanf("%s", temp);
    printf("\n--------Searching the BST for alias: '%s'----------\n", temp);
    struct address_t *search = NULL;
    search = search_in_list(root, temp);
    if (NULL == search)
    {
        printf("\n-------Search [alias = %s] failed, no such element found.\n", temp);
    }
    else
    {
        printf("\n------Search found. Address for %s: [%d.%d.%d.%d]--------\n", temp, search->octet[0], search->octet[1], search->octet[2], search->octet[3]);
    }
    return;
}

void update(int buf[], struct address_t *root, int *flag) //function that checks if the entered address already exists in the BST
{

    if (root != NULL)
    {

        update(buf, root->leftChild, flag);
        if (root->octet[0] == buf[0] && root->octet[1] == buf[1] && root->octet[2] == buf[2] && root->octet[3] == buf[3])
        {
            *flag = 1;
        }
        update(buf, root->rightChild, flag);
    }
}

void update_address() //function to update the address of the alias entered by the user
{
    char temp[11]; //temporary char array to store the alias entered by the user
    printf("Enter alias: ");
    scanf("%s", temp);
    printf("\n--------Searching the list for alias: '%s'----------\n", temp);
    struct address_t *search = NULL;
    search = search_in_list(root, temp);
    if (NULL == search)
    {
        printf("\n-------Search [alias = %s] failed, no such Alias found.\n", temp);
    }
    else
    {
        printf("\n------Search successfull. Current address for %s: [%d.%d.%d.%d]--------\n", temp, search->octet[0], search->octet[1], search->octet[2], search->octet[3]);
        printf("Enter new address for Alias: %s\n", temp);
        int buf[500];

        int i = 0;
        while (i < 4)
        {
            printf("Enter value#%d between 0-255: \n", i + 1);
            scanf("%d", &buf[i]);
            if (buf[i] < 0 || buf[i] > 255) //check if value is between 0 and 255 inclusive, if not prompt the user again
            {
                printf("ERROR: value must be between 0 and 255 inclusive, please re-enter : \n");
                continue;
            }
            else
                i++;
        }

        printf("Address entered: %d.%d.%d.%d\n", buf[0], buf[1], buf[2], buf[3]);

        int flag = 0;
        update(buf, root, &flag);   //call to update function that checks if the entered address already exists in the BST
        if (flag == 0)              //if flag remains zero, updates the address, else prints an error message and redisplays the main menu
        {
            printf("---------Updating address of %s--------\n", temp);
            for (i = 0; i < 4; i++)
            {
                search->octet[i] = buf[i];
            }
            printf("----------Updated BST is: ---------\n");
            inorder(root);
        }
        else
            printf("Error: Duplicate address entered. Update failed\n");
    }
    return; //returns to the main function to redisplay the main menu
}

struct address_t *minValueNode(struct address_t *node)
{
    struct address_t *current = node;
    // loop down to find the leftChildmost leaf
    while (current && current->leftChild != NULL)
        current = current->leftChild;
    return current;
}

struct address_t *deleteNode(struct address_t *root, char temp[]) //function to delete Node from the tree
{

    // base case
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key, then it lies in leftChild subtree
    // compares the ASCII values of aliases in this case
    if (strcmp(temp, root->alias) < 0)
        root->leftChild = deleteNode(root->leftChild, temp);

    // If the key to be deleted is greater than the root's key, then it lies in rightChild subtree
    else if (strcmp(temp, root->alias) > 0)
        root->rightChild = deleteNode(root->rightChild, temp);

    // if key is same as root's key, then This is the node to be deleted
    else
    {
        // node with only one child or no child
        if (root->leftChild == NULL)
        {
            struct address_t *ptr = root->rightChild;
            free(root);
            return ptr;
        }
        else if (root->rightChild == NULL)
        {
            struct address_t *ptr = root->leftChild;
            free(root);
            return ptr;
        }
        // node with two children: Get the inorder successor (smallest in the rightChild subtree)
        struct address_t *ptr = minValueNode(root->rightChild);
        // Copy the inorder successor's content to this node
        strcpy(root->alias, ptr->alias);
        root->octet[0]=ptr->octet[0];
        root->octet[1]=ptr->octet[1];
        root->octet[2]=ptr->octet[2];
        root->octet[3]=ptr->octet[3]; 
        // Delete the inorder successor
        root->rightChild = deleteNode(root->rightChild, ptr->alias);
    }

    return root;
}

int delete_from_tree(char name[]) //function to delete a node from the BST with the entered alias 
{
    char opt[5];
    struct address_t *del = NULL; 
    printf("\n Deleting value [%s] from list\n", name);
    del = search_in_list(root, name); // function call to search_in_list to check whether the alias to be deleted exists in the Tree
    if (del == NULL)
    {
        printf("\n-------Search [alias = %s] failed, no such element found.--------\n", name);
        return -1;
    }
    else
    {
        printf("\n------Search found. Address for %s: [%d.%d.%d.%d]--------\n", name, del->octet[0], del->octet[1], del->octet[2], del->octet[3]);
        printf("Are you sure you want to delete this node from the tree? Enter yes to confirm: \n");
        scanf("%s", opt);
        if (strcmp(opt, "yes") == 0)
        {
            root = deleteNode(root, name);  //if yes, function call to deleteNode to delete the node from the tree
        }
        else if (strcmp(opt, "no") == 0)
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

    return 0;
}

void delete () //function to check whether deletion has passed or failed
{
    char temp[11];
    printf("Enter the alias to be deleted: ");
    scanf("%s", temp);
    int ret = 0;
    {
        ret = delete_from_tree(temp); //function call to delete_from_tree

        if (ret == -1)
        {
            printf("\n deletion [Alias = %s] failed\n", temp);
        }
        else if (ret == 0)
        {
            printf("\n deletion [Alias = %s] passed \n", temp);
        }
        else
            return; //returns to the main function to redisplay the main menu
    }
}

void location(int buf[], struct address_t *root, int *flag)
{
    if (root != NULL)
    {
        {
            //traverse the tree through inorder traversal to check if the location entered by the user exists, if yes, flag is set to 1
            location(buf, root->leftChild, flag);
            if (buf[0] == root->octet[0] && buf[1] == root->octet[1])
            {
                *flag = 1;
                printf("Address: [%d.%d.%d.%d]\t Alias: %s\n", root->octet[0], root->octet[1], root->octet[2], root->octet[3], root->alias);
            }
            location(buf, root->rightChild, flag);
        }
        return;
    }
}

void display_location() //function to display aliases on the basis of the location entered by the user
{
    int buf[30];
    printf("Enter address location\n");
    printf("Enter values between 0-255: \n");
    int i = 0;
    while (i < 2)
    {
        printf("Enter location value %d: ", i + 1);
        scanf("%d", &buf[i]);
        if (buf[i] < 0 || buf[i] > 255) //check if value is between 0 and 255 inclusive, if not prompt the user again
        {
            printf("ERROR: value must be between 0 and 255 inclusive, please re-enter : \n");
            continue;
        }
        else
            i++;
    }
    int flag = 0;
    location(buf, root, &flag); //function call to location function that traverses the tree to check if the location entered by the user exists
    if (flag == 0)              //if flag remains unchanged, no aliases were found
        printf("No aliases found at this location!\n");

    return; //returns to the main function to redisplay the main menu
}

void save(struct address_t *root, FILE *newfp)
{
    if (root != NULL)
    {
        //traverse the tree through inorder traversal and print data of each node to the file
        save(root->leftChild, newfp);
        fprintf(newfp, "%d.%d.%d.%d %s\n", root->octet[0], root->octet[1], root->octet[2], root->octet[3], root->alias);
        save(root->rightChild, newfp);
    }
}

void save_to_file() //function to save the BST to a file with the file name entered by the user
{
    char filename[30];
    printf("Enter file name of max 30 characters (with/without extension .txt): \n"); //you may enter the file name with or without the extension
    scanf("%s", filename);
    FILE *newfp = fopen(filename, "w"); //file pointer that points to the file opened/created in WRITE mode

    if (newfp == NULL) // error handling
    {
        printf("\nError...cannot open/create file\n");
        exit(1);
    }
    save(root, newfp); //function call to print nodes of BST to file

    printf("File saved successfully! \n");
    fclose(newfp);
}

void goodbye() //function to quit the program
{
    printf("Goodbye! \n");
}

int main()
{
    char buf[500];
    int menuoption, count = 0;
    FILE *fp;                          //file pointer
    fp = fopen("CS531_Inet.txt", "r"); //opens the file in READ mode
    if (!fp)
    {
        perror("Input file CS531_Inet.txt not present ");
        return 1;
    }

    printf("\n-------Reading address/alias pairs from the file-------\n\n");
    while (fgets(buf, sizeof(buf), fp) != NULL) //adds data from the file to a buffer to further store it in a BST
    {
        int tempoctet[4];
        char tempalias[11];
        sscanf(buf, "%d.%d.%d.%d %s", tempoctet, tempoctet + 1, tempoctet + 2, tempoctet + 3, tempalias); // parses the data from buf into tempoctet and tempalias
        printf("Address: %d.%d.%d.%d, Alias: %s\n", tempoctet[0], tempoctet[1], tempoctet[2], tempoctet[3], tempalias);
        root = add_to_tree(root, tempoctet, tempalias);
    }
    printf("\n\n---------Displaying aliases for location using Inorder Traversal----------\n");
    inorder(root);

    do
    { //Display menu
        printf("\n\nMain Menu\n");
        printf("1) Add address\n");
        printf("2) Lookup address\n");
        printf("3) Update address\n");
        printf("4) Delete address\n");
        printf("5) Display list\n");
        printf("6) Display aliases for location\n");
        printf("7) Save to file\n");
        printf("8) Quit\n");
        printf("Enter option: "); //prompts the user to choose a menu option
        scanf("%d", &menuoption);
        switch (menuoption)
        {
        case 1:
            add_address(); //function calls to perform the operations specified in the main menu
            break;

        case 2:
            lookup_address();
            break;

        case 3:
            update_address();
            break;

        case 4:
            delete ();
            break;

        case 5:
            printf("\n\n---------Displaying aliases for location using Inorder Traversal----------\n");
            inorder(root);
            break;

        case 6:
            display_location();
            break;

        case 7:
            save_to_file();
            break;

        case 8:
            goodbye();
            break;

        default:
            printf("invalid input\n"); //handles invalid inputs (menu option other than 1-8 entered)
            break;
        }

    } while (menuoption != 8);

    return 0;
}