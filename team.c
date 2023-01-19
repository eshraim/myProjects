//
// EECS2031 team.c
//
// Program for maintaining a personal team.
//
//
// Uses a linked list to hold the team players.
//
// Author: <Eyad Mahmoud>
// Student Info: <218421230>


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>


//**********************************************************************
// Linked List Definitions 
//  Define your linked list node and pointer types
//  here for use throughout the file.
//
//
//   ADD STATEMENT(S) HERE
struct Node {
    char firstName[1023];
    char lastName[1023];
    char possition;
    int value;
    struct Node *next;
}node;

struct Node* nodeFactory( char *first, char *last, char pos, int val, struct Node *next){

    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(node)); 
    strcpy(newNode->firstName,first);
    strcpy(newNode->lastName, last);
    newNode->possition = pos;
    newNode->value = val;
    newNode->next = next;
    return newNode;
}







//**********************************************************************
// Linked List Function Declarations
//
// Functions that modify the linked list.
//   Declare your linked list functions here.
//
//   ADD STATEMENT(S) HERE
void searchByLast(char lastName[], struct Node *head);
bool checkerForLastName(struct Node *new, struct Node *head);



//**********************************************************************
// Support Function Declarations
//

void safegets (char s[], int arraySize);        // gets without buffer overflow
void familyNameDuplicate (char familyName[]);   // marker/tester friendly 
void familyNameFound (char familyName[]);       //   functions to print
void familyNameNotFound (char familyName[]);    //     messages to user
void familyNameDeleted (char familyName[]);
void printTeamEmpty (void);
void printTeamTitle(void);
void printNoPlayersWithLowerValue(int value);

//**********************************************************************
// Program-wide Constants
//

const int MAX_LENGTH = 1023;
const char NULL_CHAR = '\0';
const char NEWLINE = '\n';
const char GOALKEEPER = 'G';
const char DEFENDER = 'D';
const char MIDFIELDER = 'M';
const char STRIKER = 'S';


//**********************************************************************
// Main Program
//

int main (void)
{ 
    const char bannerString[]
        = "Personal Team Maintenance Program.\n\n";
    const char commandList[]
        = "Commands are I (insert), D (delete), S (search by name),\n"
          "  V (search by value), P (print), Q (quit).\n";

    // Declare linked list head. done
    //   ADD STATEMENT(S) HERE TO DECLARE LINKED LIST HEAD. done
    struct Node *head;
    //head = (struct Node*)malloc(sizeof(node)); 
 
    // announce start of program
    printf("%s",bannerString);
    printf("%s",commandList);
    
    char response;
    char input[MAX_LENGTH+1];
    do
    {
        printf("\nCommand?: ");
        safegets(input,MAX_LENGTH+1);
        // Response is first char entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (response == 'I'){
            // Insert a player entry into the linked list.
            // Maintain the list in correct order (G, D, M, S).
            //   ADD STATEMENT(S) HERE

            // USE THE FOLLOWING PRINTF STATEMENTS WHEN PROMPTING FOR DATA:
        
            char lastName[MAX_LENGTH];
            char firstName[MAX_LENGTH];
            char posInput;
            char pos;
            int value;

            printf("  family name: ");
            safegets(lastName, MAX_LENGTH);
            printf("  first name: ");
            safegets(firstName, MAX_LENGTH);
            printf("  position: ");
            scanf("%c", &posInput);
            printf("  value: ");
            scanf("%d", &value);
            pos = toupper(posInput);
            
            
            
             if(pos == GOALKEEPER || pos == DEFENDER|| pos == MIDFIELDER || pos == STRIKER){
                struct Node *newNode;
                struct Node *curr;
                struct Node *checker;
                checker = head;
                newNode = (struct Node*)nodeFactory(firstName, lastName, pos, value, head);
                bool lastNameExists = checkerForLastName(newNode, head);
               
            if(lastNameExists == false){
                
                if(head == NULL){
                    head = newNode;
                    newNode->next = NULL;
                }
                else if(pos == GOALKEEPER){
                    if(head->possition != GOALKEEPER){
                        newNode->next = head;
                        head = newNode;
                        
                    }
                    else if(newNode->possition == GOALKEEPER){
                        curr = head;
                        while(curr->next != NULL && curr->next->possition == GOALKEEPER){
                            curr = curr->next;  
                        }
                        newNode->next= curr->next;
                        curr->next = newNode;
                    }
    
                }

                else if(pos == DEFENDER){
                    curr = head;
                    if(curr->possition == DEFENDER){
                        while(curr->next != NULL && curr->next->possition == DEFENDER){
                            curr = curr->next;
                        }
                        newNode->next= curr->next;
                        curr->next = newNode;
                    }
                    else if(head !=NULL && head->possition != GOALKEEPER && head->possition != DEFENDER){
                        newNode->next = head;
                        head = newNode;
                    }
                    else if(head!=NULL && head->possition == GOALKEEPER &&  head->possition != DEFENDER){
                        while(curr->next != NULL && (curr->next->possition == GOALKEEPER ||curr->next->possition == DEFENDER)){
                            curr = curr->next;  
                        }
                        newNode->next= curr->next;
                        curr->next = newNode;
                    }
                    
                    else if(head!=NULL && head->possition != GOALKEEPER &&  head->possition == DEFENDER){
                        while(curr->next != NULL && curr->next->possition == DEFENDER){
                            curr = curr->next;  
                        }
                        newNode->next= curr->next;
                        curr->next = newNode;
                    }
                }

                   else if(pos == MIDFIELDER){
                    curr = head;
                    if(curr->possition == MIDFIELDER){
                        while(curr->next != NULL && curr->next->possition == MIDFIELDER){
                            curr = curr->next;
                        }
                        newNode->next= curr->next;
                        curr->next = newNode;
                    }
                    else if(head !=NULL && head->possition != GOALKEEPER && head->possition != DEFENDER && head->possition != MIDFIELDER){
                        newNode->next = head;
                        head = newNode;
                    }
                    else if(head!=NULL && head->possition == GOALKEEPER &&  head->possition != DEFENDER && head->possition != MIDFIELDER  ){
                        while(curr->next != NULL && (curr->next->possition == GOALKEEPER ||curr->next->possition == DEFENDER || curr->next->possition == MIDFIELDER )){
                            curr = curr->next;  
                        }
                        newNode->next= curr->next;
                        curr->next = newNode;
                    }
                    
                    else if(head!=NULL && head->possition != GOALKEEPER && (head->possition == DEFENDER || head->possition == MIDFIELDER)){
                        while(curr->next != NULL && curr->next->possition == MIDFIELDER){
                            curr = curr->next;  
                        }
                        newNode->next= curr->next;
                        curr->next = newNode;
                    }
                }
        
                else if(pos == STRIKER){
                curr = head;
                while(curr->next != NULL ){
                    curr = curr->next; 
                }
                curr->next = newNode;
                newNode->next = NULL;
            }  
        }
        else if(lastNameExists == true) {
            familyNameDuplicate(newNode->lastName);
        }   
        }
        
        }
    
           

        
        else if (response == 'D'){
            // Delete a player from the list.
            char lastName[MAX_LENGTH];
            printf("\nEnter family name for entry to delete: ");
            safegets(lastName, MAX_LENGTH);
            struct Node *curr;
            struct Node *prev;
            curr = prev = head;
            if (head == NULL){
                printTeamEmpty();
            }
            else if((strcmp(curr->lastName,lastName) == 0) && (curr->next != NULL)){
                curr = head;
                head = head->next;
                free(curr);
            }
            else if((strcmp(curr->lastName,lastName) == 0) && (curr->next == NULL)){
                head = NULL;
                free(curr);
            }
            else {
                bool notFound = true;
                if(notFound == true){
                    while(curr!=NULL){
                        if(strcmp(curr->lastName,lastName) == 0){
                            prev->next = curr->next;
                            free(curr);
                            break;
                        }
                        else{
                            prev = curr;
                            curr = curr->next;
                        }
                    }
                    if(curr == NULL){
                        notFound = false;
                    }
                }
                if(notFound == false){
                    familyNameNotFound(lastName);
                }
            
            }
        }
        else if (response == 'S')
        {
            // Search for a player by family name.
            char lastName[MAX_LENGTH];
            printf("\nEnter family name to search for: ");
            safegets(lastName, MAX_LENGTH);
            searchByLast(lastName, head);
        }
        else if (response == 'V')
        {
            // Search for players that are worth less than or equal a value.
            int val = 0;
            int foundCounter = 0;
            printf("\nEnter value: ");
            scanf("%d", &val);
            struct Node *curr;
            curr = head;
            while(curr != NULL){
                if(curr->value <= val){
                    printf("%s\n", curr->lastName);
                    printf("%s\n", curr->firstName);
                    printf("%c\n", curr->possition);
                    printf("%d\n", curr->value);
                    printf("\n");
                    curr = curr->next;
                    foundCounter++;
                }
                else{
                    curr = curr->next;
                }
            }
            if(foundCounter == 0){
                printNoPlayersWithLowerValue(val);
            }

            //   ADD STATEMENT(S) HERE

        }
        else if (response == 'P')
        {
            // Print the team.

            //   ADD STATEMENT(S) HERE
            struct Node *iter;
            iter = head;
            if(head == NULL){
                printTeamEmpty();
            }
            else{
                printTeamTitle();
                while(iter != NULL){
                    printf("%s\n", iter->lastName);
                    printf("%s\n", iter->firstName);
                    printf("%c\n", iter->possition);
                    printf("%d\n", iter->value);
                    printf("\n");
                    iter = iter->next;
                }     
            }

        }
        else if (response == 'Q')
        {
             // do nothing, we'll catch this case below
        }
        else 
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n%s\n",commandList);
        }
    } while(response != 'Q');
  
    // Delete the whole linked list that hold the team.
    //   ADD STATEMENT(S) HERE
        struct Node *curr;
        curr = head;
        while(curr!=NULL){
            head = head->next;
            free(curr);
            free(curr->lastName);
            free(curr->firstName);
           
        }

    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE
        struct Node *iter;
        if (head == NULL){
        }
        else{
            iter = head;
            while(iter != NULL){
                printf("%s\n", iter->lastName);
                printf("%s\n", iter->firstName);
                printf("%c\n", iter->possition);
                printf("%d\n", iter->value);
                printf("\n");
                iter = iter->next;
            }     
        }
    
    return 0;
    
}



//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets (char s[], int arraySize)
{
    int i = 0, maxIndex = arraySize-1;
    char c;
    while (i < maxIndex && (c = getchar()) != NEWLINE)
    {
        s[i] = c;
        i = i + 1;
    }
    s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name 
// that is already in the book.
void familyNameDuplicate (char familyName[])
{
    printf("\nAn entry for <%s> is already in the team!\n"
           "New entry not entered.\n",familyName);
}

// Function to call when a player with this family name was found in the team.
void familyNameFound (char familyName[])
{
    printf("\nThe player with family name <%s> was found in the team.\n",
             familyName);
}

// Function to call when a player with this family name was not found in the team.
void familyNameNotFound (char familyName[])
{
    printf("\nThe player with family name <%s> is not in the team.\n",
             familyName);
	
}

// Function to call when a family name that is to be deleted
// was found in the team.
void familyNameDeleted (char familyName[])
{
    printf("\nDeleting player with family name <%s> from the team.\n",
             familyName);
}

// Function to call when printing an empty team.
void printTeamEmpty (void)
{
    printf("\nThe team is empty.\n");
}

// Function to call to print title when whole team being printed.
void printTeamTitle (void)
{
    printf("\nMy Team: \n");
}

// Function to call when no player in the team has lower or equal value to the given value
void printNoPlayersWithLowerValue(int value)
{
	printf("\nNo player(s) in the team is worth less than or equal to <%d>.\n", value);
}

bool checkerForLastName(struct Node *new, struct Node *head){
    struct Node *curr;
    curr = head;
    
    while(curr != NULL){
        if(strcmp(new->lastName, curr->lastName) == 0){
            return true;
        }
        curr = curr->next;
    }
    return false;
}



void searchByLast(char lastName[], struct Node *head){
    struct Node *curr;
    curr = head;
    bool notFound = true;
    if (head == NULL){
        printTeamEmpty();
    }
    else if(notFound == true){
        while(curr!=NULL){
            if(strcmp(curr->lastName,lastName) == 0){
                familyNameFound(lastName);
                printf("%s\n", curr->lastName);
                printf("%s\n", curr->firstName);
                printf("%c\n", curr->possition);
                printf("%d\n", curr->value);
                break;
            }
            else{
                curr = curr->next;
            }
            if(curr == NULL){
                notFound = false;
            }
        }
        
    }
    if(notFound == false){
        familyNameNotFound(lastName);
    }
}