/*NAME: NIYANTA LAD 
GNUM: G01284622*/



#include <stdio.h>
#include <string.h>
#define MAX_NO_STRINGS 10							// no. of strings to be entered by the user which will remain constant throughout the code 
#define STR_LENGTH 60								// each string can contain a maximum of 60 characters

void AscSort(char arr[MAX_NO_STRINGS][STR_LENGTH]);			//function declarations
void DescSort(char arr[MAX_NO_STRINGS][STR_LENGTH]);
int isSpecialChar(char str[], int l);
int isDuplicateString(char dup[], int sIndex);
void sortSpecification(char str[10][60]);

int s;											// s is a global variable which is an index to iterate over the 2D input array. Global variables are automatically initialized to 0 in C.
char str[MAX_NO_STRINGS][STR_LENGTH];			/* Global 2D Array of 10 rows that holds the input string from the user
													with maximum of 10 strings 
													with each string containing a maximum of 60 characters						
												*/
int main()
{
	printf("Enter 10 Strings: ");				
	while (s<10)
	{
		printf("Input String %d: ", s+1);		//ask the user to enter a string
		fgets(str[s], sizeof(str[s]), stdin);	//read the entered string by the user
												/*fgets() reads in at most one less than size of the character array and stores them into the buffer pointed to by str[s] */

		if (strlen(str[s])==1)					//check if an empty string is entered. If yes, prompt the user again
		 {
		 	printf("ERROR: Empty string entered, please re enter : \n");
		    continue;							//continue is used to prompt the user again for another input by forcing the next iteration of the loop to execute
	     }

		else if (strlen(str[s])<2 || strlen(str[s])>26) //check if strlen is between 1 and 25 inclusive, if not prompt the user again
		{	
			/* Note that the strlen of an empty string is 1 and the strlen of a string with 25 characters is 26 since a terminating null byte is stored 
			after the last character in the buffer when we use fgets*/
			 
		    printf("ERROR: String length must be between 1 and 25 inclusive, please re-enter : \n");
		  	continue;  
	    } 
 

		 else if ((isSpecialChar(str[s], strlen(str[s])))==1) 		//function call to isSpecialChar() function.
		 {
			 														//check if the entered string contains valid characters, if not prompt the user again
			printf("ERROR: Special character entered, please re-enter : \n");
			continue;
		 }

		 else if ((isDuplicateString(str[s], s))==1)				//function call to isDuplicateString() function.
		 {
			 														//check if a duplicate string is entered, if not prompt the user again
			printf("ERROR: duplicate String entered, please re-enter unique string : \n");
			continue;
		 }

		 else
		 {
			 s++;
		 }
	     
	    
	}

	sortSpecification(str);				//function call to sortSpecification function to perform sorting operation on the array
	return(0);
}

int isSpecialChar(char str[], int l)	//function definition to return whether the string includes any special characters
{
	int i=0;
	while(i<l)				// loop until the maximum number of strings are entered by the user
	{
        if (str[i]=='!' || str[i]=='@'|| str[i]=='#'|| str[i]=='$'|| str[i]=='%'|| str[i]=='^'|| str[i]=='('|| str[i]==')')
            {
				return 1;			// return 1 if string contains any of these special characters, else return 0
		    } 
		i++;
	}
	return 0;
}

int isDuplicateString(char dup[], int sIndex)	//function definition to return whether the entered string contains duplicate strings from the array
{
	if(sIndex>=1)								//to check if the array contains atleast one string to be compared to
	{
		int i=0;
		while( i<sIndex)
        {
			char buff[100];						//buffer to store the entered string and to perform string compare operation
			strcpy(buff, str[i]);				
			if((strcmp(dup,buff))==0)			//compares the entered string with all the strings already present in the array
	        {									//returns 1 if a matched string is found in the array else returns 0
		 	    return 1;
			}
			i++;
        }
	}
	return 0;
}	

void sortSpecification(char str[MAX_NO_STRINGS][STR_LENGTH])	//function definition for A and D sort specification
{
	int flag=0; 												//flag variable used to keep the loop running until the user enters a valid input
    while(flag==0)
	{	
    	char ch[10]; 											//character array to store user input
    	printf("\n\nEnter A for Ascending order or D for Descending order \n");
    	scanf("%s",ch);
		int res1= strcmp(ch,"A");								// check if user has entered 'A'
		int res2= strcmp(ch,"D");								// check if user has entered 'D'
		if(res1==0)
		{	 
        	AscSort(str);										//function call to AscSort function if 'A' is entered
        	flag=1;												//set flag to 1 and terminate the program
			break;
    	}
		else if (res2==0)										//function call to DescSort function if 'D' is entered
		{
        	DescSort(str);										//set flag to 1 and terminate the program
        	flag=1;
			break;
    	}
		else
        continue;												//prompt the user again if a character other than 'A' and 'D' is entered
    }

}

void AscSort(char arr[MAX_NO_STRINGS][STR_LENGTH])
{
    char temp[25];									//local character array declaration-temporarily holds the string to be repositioned in the array
													
													//Sorting strings in the 2d array in ascending order based on first character of input string using bubble sort
    for (int ctr1=0; ctr1<MAX_NO_STRINGS-1; ctr1++)						/* every iteration of this loop moves the string with a higher ascii value to the end of the input array
																and the smaller ascii value closer to the beginning */
    {														
        for (int ctr2=0; ctr2<MAX_NO_STRINGS-1-ctr1; ctr2++)				/*  When ctr2 resets to 0, ctr2 will run until it is less than 1 compared to its value since the last
																position now contains the string with the highest ascii value */
															
        {
            int res=strcmp(arr[ctr2],arr[ctr2+1]);			
            if(res>0)
            {												// swap arr[ctr2] with arr[ctr2+1] if the current string has greater ascii value than the next string
																
                strcpy(temp,arr[ctr2]);
                strcpy(arr[ctr2], arr[ctr2+1]);
                strcpy(arr[ctr2+1], temp);
                
            }
        }
    }
    printf("\n ****STRINGS SORTED IN ASCENDING ORDER ARE: ***** \n");
	for (int final=0; final<MAX_NO_STRINGS; final++)					//display the sorted array in ascending order. i.e. in increasing order of ascii values
	{
		printf("String %d is %s",final+1,arr[final]);
	}
	printf("\nString with lowest ascii value: %s \n", arr[0]);	//first index contains the string with lowest ascii value
	printf("String with highest ascii value: %s\n", arr[9]);		//last index contains the string with highest ascii value
	
	
}

void DescSort(char arr[MAX_NO_STRINGS][STR_LENGTH])
{
    char temp[25]; 										//local character array declaration- temporarily holds the string to be repositioned in the array
														
													//Sorting strings in the 2d array in descending order based on first character of input string using bubble sort
    for (int ctr1=0; ctr1<MAX_NO_STRINGS-1; ctr1++)							/* every iteration of this loop moves the string with a lower ascii value to the end of the input array
																and the higher ascii value closer to the beginning */
    {
        for (int ctr2=0; ctr2<MAX_NO_STRINGS-1-ctr1; ctr2++)					/*  When ctr2 resets to 0, ctr2 will run until it is less than 1 compared to its value since the last
																position now contains the string with the lowest ascii value */
        {
            int res=strcmp(arr[ctr2],arr[ctr2+1]);
            if(res<0)											// swap arr[ctr2] with arr[ctr2+1] if the current string has lower ascii value than the next string
            {
                strcpy(temp,arr[ctr2]);
                strcpy(arr[ctr2], arr[ctr2+1]);
                strcpy(arr[ctr2+1], temp);
                
            }
        }
    }
    printf("\n  ****STRINGS SORTED IN DESCENDING ORDER ARE: ***** \n");
	for (int final=0; final<MAX_NO_STRINGS; final++)					//display the sorted array in descending order. i.e. in decreasing order of ascii values
	{
		printf("String %d is %s",final+1,arr[final]);
	}
	printf("\nString with lowest ascii value: %s \n", arr[9]);		//last index contains the string with lowest ascii value
	printf("String with highest ascii value: %s\n", arr[0]);			//first index contains string with highest ascii value
}


