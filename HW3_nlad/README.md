# HW 3

Homework # 3 builds upon Homework # 2. Recall that in HW#2, our program reads the contents of datafile “CS531_Inet.txt”.
As with HW#2, for this assignment, you will create your own test data files using the sample format. In HW#2, you were asked to construct a linked list of address_t structures, each of which contained
contains an IPv4 address and alias pair. As with HW#2, for this assignment, you will create your own test data files using the sample format. In HW#2, you were asked to construct a linked list of address_t structures, each of which contained
the four integers of an IPv4 address along with a fifth component in which to store an associated alias of up to 10 characters. In this project, you will replace the linked list with a Binary Search Tree (BST). As CS531_Inet.txt is being read in, the data will be stored in a BST composed of address_t structures containing the address/alias pairs
read in from the file.
 
Once the BST has been created, the user will receive the following menu
 options:
 1) Add address
2) Look up address
3) Update address
4) Delete address
5) Display list
6) Display aliases for location 
7) Save to file
8) Quit

# 
• Display list and Display aliases for location shall be based on Inorder Traversal
• Delete address, Look up address, and Display aliases for location will display an error message if the address (or location) entered is not listed. Following the error message, the menu will be redisplayed.
• A separate UDF will be defined for each menu option.
• No duplicate aliases or address are allowed. If attempted, display
an appropriate error message followed by the menu.
• For this exercise, all aliases will be entered in lower case.
