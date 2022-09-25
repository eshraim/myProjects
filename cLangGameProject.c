#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

    int startGuessTheNumberGame(){        
/*making int variable to enter secret number and for the options.*/
int in1;
    int in2;
    int a=0;
    int count = 0;
        /*outputting question.*/
printf("enter a secret number between 1 and 10000 : ");
        /*inputing user answer.*/
scanf("%d" , &in1);
        /*declaring high and low for range of numbers to choose from.*/
   int low = 1;
        int high = 10000;
        /*while loop to loop between low and high.*/
while(low <= high){
         /*finding mid point */
   int mid = (low + high)/2;
            /*outputting answer and options*/
   printf("my guess is : %d \n" , mid);
            printf("1. my guess was correct. \n");
            printf("2. the secret number was larger than %d \n" , mid);
            printf("3. the secret number was smaller than %d \n" , mid);
            scanf("%d" , &in2);
            if(in2 == 1){
                printf("you have found the secret number!\n");
                a++;
                break;
            }
            else if (in2 == 2){
                low = mid + 1;
                a++;
            }
           
            else if (in2 == 3){
                high = mid - 1;
                a++;
            }
           
            else {
                printf("sorry that isn't an option");
            }
           
           
        }
        printf("\nyou needed %d attempts to find the secret number!\n" , a);
        for (int w = 0; w<3 ; w++){
            if(w ==2)
            printf("|");
           
            else
            printf("|\n");
        }
            for(int k = 0; k<a ; k++){
        while(count<a){
            if(count == a/2){
                printf("\n|       %d ||||", a);
                count++;
            }
            else {
                printf("\n|          ||||");
                count++;
            }
        }
        }
        printf("\n--------------------------------");
     
    }
   
   
   
    int startHangmanGame(){
        /*for random guess in array of words*/
        srand(time(NULL));
/*15 words in each category in 2d array*/
char guessFood[][15] = {"mansaf", "maqloubeh", "kabseh", "sheshbarak", "shawerma", "burger", "ouzi", "mskhan", "potato", "fish", "cake", "mloukheyeh", "pasta", "soup", "chicken"};

char guessObj[][15] = {"fridge", "laptop","table" , "yoyo", "chair", "car" , "bus", "train", "library", "map", "desk", "card", "bowl", "bottle", "bulb"};

char guessNames[][15] = {"osama", "waleed", "sanad", "sally", "maya", "dana", "mohammad", "khaled", "zidane", "hebah", "sireen", "sadeq", "ebraheem", "sameer", "jehad"};

char guessColors[][15] = {"green", "yellow", "blue", "orange", "red", "black", "white", "gray", "brown", "purple", "indigo", "violet", "pink", "silver", "gold"};

/*index for random word*/
int randomIndex = rand() % 15;
int numLives = 5;
int numCorrect = 0;
int oldCorrect = 0;
int lengthOfWord = strlen(guessFood[randomIndex]);
int in3;
/*displaying options*/
printf("choose a category:\n");
printf("1. Food\n");
printf("2. Objects\n");
printf("3. Names\n");
printf("4. Colors\n");
scanf("%d", &in3);
    //if statment to choose an option of words to match the 2d array with the words.
   
    if(in3 == 1){
    int letterGuessed[8] = { 0,0,0,0,0,0,0,0 };
int loopIndex = 0;
int reguessed = 0;
char guess[16];
char letterEntered;

    // loop for the game to keep on guessing until lives end.
while ( numCorrect < lengthOfWord ) {

printf("\n\nThe word so far is: ");
    // for loop to iterate over the word letter by letter.
for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {
//if else to see if letter was guessed and display it or not and display "-".
if(letterGuessed[loopIndex] == 1) {
printf("%c",guessFood[randomIndex][loopIndex]);
} else {
printf("-");
}

}
printf("\n");
//enter initial guess
printf("Enter a guess letter:");
fgets(guess, 16, stdin);

letterEntered = guess[0];
reguessed = 0;


oldCorrect = numCorrect;
//for loop to re iterate over the word and checking if letter entered was in the word
for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {

if(letterGuessed[loopIndex] == 1) {
if(guessFood[randomIndex][loopIndex] == letterEntered) {
reguessed = 1;
break;
}
continue;
}

if( letterEntered == guessFood[randomIndex][loopIndex] ) {
letterGuessed[loopIndex] = 1;
numCorrect++;
}

}

//if else statments for guesses to determine if they are correct to add to guesses or false to take away a life.
if( oldCorrect == numCorrect && reguessed == 0) {
numLives--;
printf("Not quite! try again!\n");
if (numLives == 0) {
break;
}
} else if( reguessed == 1) {
printf("Already Guessed!!\n");
} else {
printf("Correct! Keep going :)\n");
}

}
//while loop ends here.


//determining if you won or lost after exiting loop.
if (numLives == 0) {
printf("\nHard luck! tou were not able to find the word!\n");
} else  {
printf("\nCongrats! you found the word!)\n");
}
}
    else if(in3 == 2){
    int letterGuessed[8] = { 0,0,0,0,0,0,0,0 };
int loopIndex = 0;
int reguessed = 0;
char guess[16];
char letterEntered;

    // loop for the game to keep on guessing until lives end.
while ( numCorrect < lengthOfWord ) {

printf("\n\nThe word so far is: ");
    // for loop to iterate over the word letter by letter.
for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {
//if else to see if letter was guessed and display it or not and display "-".
if(letterGuessed[loopIndex] == 1) {
printf("%c",guessObj[randomIndex][loopIndex]);
} else {
printf("-");
}

}
printf("\n");
//enter initial guess
printf("Enter a guess letter:");
fgets(guess, 16, stdin);

letterEntered = guess[0];
reguessed = 0;

oldCorrect = numCorrect;
//for loop to re iterate over the word and checking if letter entered was in the word
for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {

if(letterGuessed[loopIndex] == 1) {
if(guessObj[randomIndex][loopIndex] == letterEntered) {
reguessed = 1;
break;
}
continue;
}

if( letterEntered == guessObj[randomIndex][loopIndex] ) {
letterGuessed[loopIndex] = 1;
numCorrect++;
}



//if else statments for guesses to determine if they are correct to add to guesses or false to take away a life.
if( oldCorrect == numCorrect && reguessed == 0) {
numLives--;
printf("Not quite! try again!\n");
if (numLives == 0) {
break;
}
} else if( reguessed == 1) {
printf("Already Guessed!!\n");
} else {
printf("Correct! Keep going :)\n");
}

}
//while loop ends here.

}
//determining if you won or lost after exiting loop.
if (numLives == 0) {
printf("\nHard luck! tou were not able to find the word!\n");
} else  {
printf("\nCongrats! you found the word!)\n");
}
    }
       
    else if(in3 == 3){
       
    int letterGuessed[8] = { 0,0,0,0,0,0,0,0 };
int loopIndex = 0;
int reguessed = 0;
char guess[16];
char letterEntered;

    // loop for the game to keep on guessing until lives end.
while ( numCorrect < lengthOfWord ) {

printf("\n\nThe word so far is: ");
    // for loop to iterate over the word letter by letter.
for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {
//if else to see if letter was guessed and display it or not and display "-".
if(letterGuessed[loopIndex] == 1) {
printf("%c",guessNames[randomIndex][loopIndex]);
} else {
printf("-");
}

}
printf("\n");
//enter initial guess
printf("Enter a guess letter:");
fgets(guess, 16, stdin);

letterEntered = guess[0];
reguessed = 0;


oldCorrect = numCorrect;
//for loop to re iterate over the word and checking if letter entered was in the word
for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {

if(letterGuessed[loopIndex] == 1) {
if(guessNames[randomIndex][loopIndex] == letterEntered) {
reguessed = 1;
break;
}
continue;
}

if( letterEntered == guessNames[randomIndex][loopIndex] ) {
letterGuessed[loopIndex] = 1;
numCorrect++;
}

}

//if else statments for guesses to determine if they are correct to add to guesses or false to take away a life.
if( oldCorrect == numCorrect && reguessed == 0) {
numLives--;
printf("Not quite! try again!\n");
if (numLives == 0) {
break;
}
} else if( reguessed == 1) {
printf("Already Guessed!!\n");
} else {
printf("Correct! Keep going :)\n");
}

}
//while loop ends here.


//determining if you won or lost after exiting loop.
if (numLives == 0) {
printf("\nHard luck! tou were not able to find the word!\n");
} else  {
printf("\nCongrats! you found the word!)\n");

    }
}
    else if (in3 == 4){
       
    int letterGuessed[10] = { 0,0,0,0,0,0,0,0,0,0 };
int loopIndex = 0;
int reguessed = 0;
char guess[16];
char letterEntered;

    // loop for the game to keep on guessing until lives end.
while ( numCorrect < lengthOfWord ) {

printf("\n\nThe word so far is: ");
    // for loop to iterate over the word letter by letter.
for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {
//if else to see if letter was guessed and display it or not and display "-".
if(letterGuessed[loopIndex] == 1) {
printf("%c",guessColors[randomIndex][loopIndex]);
} else {
printf("-");
}

}
printf("\n");
//enter initial guess
printf("Enter a guess letter:");
fgets(guess, 16, stdin);

letterEntered = guess[0];
reguessed = 0;


oldCorrect = numCorrect;
//for loop to re iterate over the word and checking if letter entered was in the word
for( loopIndex = 0; loopIndex < lengthOfWord; loopIndex++) {

if(letterGuessed[loopIndex] == 1) {
if(guessColors[randomIndex][loopIndex] == letterEntered) {
reguessed = 1;
break;
}
continue;
}

if( letterEntered == guessColors[randomIndex][loopIndex] ) {
letterGuessed[loopIndex] = 1;
numCorrect++;
}

}

//if else statments for guesses to determine if they are correct to add to guesses or false to take away a life.
if( oldCorrect == numCorrect && reguessed == 0) {
numLives--;
printf("Not quite! try again!\n");
if (numLives == 0) {
break;
}
} else if( reguessed == 1) {
printf("Already Guessed!!\n");
} else {
printf("Correct! Keep going :)\n");
}

}
//while loop ends here.


//determining if you won or lost after exiting loop.
if (numLives == 0) {
printf("\nHard luck! tou were not able to find the word!\n");
} else  {
printf("\nCongrats! you found the word!)\n");

    }  
    }
    }


    startExit(){
        return 0;
    }
   
int main() {
    char name[50];
    printf("whats your name? ");
    scanf("%s" , name);
    printf("welcome %s! \n " , name);
    printf("Please enter the number of the game you wish to play, or choose Exit.");
    printf("\n1. Guess the number game \n");
    printf("2. Hang man. \n");
    printf("3. Exit. \n");
   
    int cho = 0;
    scanf("%d" ,&cho);
    if (cho == 1){
        startGuessTheNumberGame();
    }
   
    else if (cho == 2){
        startHangmanGame();
    }
   
    else if (cho == 3 ){
        printf("exit");
        return 0;
    }
   
    else{
    printf("Invaild choice.");
    }
   
   
   
    return 0;
}
