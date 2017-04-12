/*Description: Assignment 2
Date: 13/3/14
Author: Jacob Gilroy
*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h> //in order to allow the Sleep() function.

#define NUMBERS 6 //the number of numbers to be input by the user.
#define MAX_NUMBER 42 //the max value that can be entered.

//declare function prototypes:
int number_validation(int []);
void display_numbers(int []);
void sort_numbers(int []);
int compare(int [], int [], int);
void number_frequency(int [], int []);
void display_freq(int [], int);
void exit_program(void);

main()
{
    int winning_numbers[NUMBERS] = {1, 3, 5, 7, 9, 11}; //set an array to the winning numbers.
    int bonus_num = 42; //set the bonus number.
    int user_attempts[NUMBERS];
    int frequencies[MAX_NUMBER]; //to remember the number of times each number has been guessed.
    int i, exit, menu_select, validation, sort, matches, game_number, retry;
    game_number = 0; //the user starts off having no previous attempts.
    validation = 0;
    sort = 0;
    exit = 0; //enable the main loop to execute at least once.
    
    for (i = 0 ; i < MAX_NUMBER ; i++) //initialise each element of the array to store the frequencies to 0.
    {
        *(frequencies + i) = 0;
    }//end for()
    
    while (exit != 1) //continue until the user opts to exit.
    {
        matches = 0;
        retry = 0; //user will have to choose to retry from the menu in order to break the inner while() loop.
        
        do
        {
            clrscr();
            printf("Enter %d numbers one by one to enter the LOTTO:\n(ALL numbers must be unique and in the range 1-42)\n", NUMBERS);
            
            for (i = 0 ; i < NUMBERS ; i++) //let the user enter numbers into the array:
            {
                scanf("%d", &*(user_attempts + i));
                flushall();
            }//end for()
            
            validation = number_validation(user_attempts); //call function number_validation() to preform error-checking on the numbers.
            //this function will return 0 if numbers are valid and 1 if not.
            
            if (validation == 1) //if there is an error in the validation of the numbers entered:
            {
                printf("\n\t\tERROR:\nThere was a problem with the numbers you entered-\nPlease try again.");
                Sleep(4500);
                
            }//end if()
            
            clrscr();
            
        }//end do-while()
        while (validation == 1); //keep prompting the user to enter numbers if the validation is unsuccessful.
        
        sort_numbers(user_attempts); //call function to sort the numbers in increasing order.
        
        printf("Your numbers have been successfully entered!");
        Sleep(2000);
        
        number_frequency(user_attempts, frequencies); //call function to calculate the number of times each number has been chosen.
        
        while (exit != 1 && retry == 0) //continue until the user opts to exit or retry.
        {
            
            printf("\n\t\tMAIN MENU:\n"
            "Enter:\tOption:\n\n"
            "1.......Check your numbers for a match\n\n"
            "2.......Display your numbers\n\n"
            "3.......Display the frequency of the numbers you've entered\n\n"
            "4.......Re-enter numbers\n\n"
            "5.......Exit\n\n");
            
            scanf("%d", &menu_select); //let the user select an option.
            flushall();
            
            if (menu_select == 1) //if the user chooses to check numbers:
            {
                matches = compare(user_attempts, winning_numbers, bonus_num); //call function to find matches.
                //function complare() will return a value depending on how many numbers were matched. This value will be stored in 'matches'.
                
                if (matches == 0) //if there are no matches:
                {
                    clrscr();
                    printf("You have no matches :(");
                    Sleep(3500);
                    clrscr();
                }//end if()
                
                if (matches == 1) // if there are 3 matches + bonus:
                {
                    clrscr();
                    printf("You have matched 3 numbers + the bonus!\nYou have won a Cinema Ticket!\n");
                    Sleep(4000);
                    
                }//end if()
                
                if (matches == 2) // if there are 4 matches:
                {
                    clrscr();
                    printf("You have matched 4 numbers!\nYou have won a Night Out!\n");
                    Sleep(4000);
                    
                }//end if()
                
                if (matches == 3) //if there are 4 matches + bonus:
                {
                    clrscr();
                    printf("You have matched 4 numbers + the bonus!\nYou have won a Weekend Away!\n");
                    Sleep(4000);
                    
                }//end if()
                
                if (matches == 4) //if there are 5 matches:
                {
                    clrscr();
                    printf("You have matched 5 numbers!\nYou have won a Holiday\n");
                    Sleep(4000);
                    
                }//end if()
                
                if (matches == 5) //if there are 5 matches + bonus:
                {
                    clrscr();
                    printf("You have matched 5 numbers + the bonus!\nYou have won a New Car\n");
                    Sleep(4000);
                    
                }//end if()
                
                if (matches == 6) //if there are 6 matches:
                {
                    clrscr();
                    printf("You have matched 6 numbers!\nYou have won the Jackpot!\n");
                    Sleep(4000);
                    
                }//end if()
                
            }//end if() for 1st option.
            
            if (menu_select == 2) //if the user chooses to display the numbers:
            {
                display_numbers(user_attempts); //call function to display the numbers entered.
                clrscr();
            }//end if() for 2nd option.
            
            if (menu_select == 3) //if user chooses to display frequencies:
            {
                display_freq(frequencies, game_number); // call function to display frequencies of the numbers entered.
            }//end if() for 3rd option.
            
            if (menu_select == 4) //if user chooses to re-enter the numbers:
            {
                retry = 1; //break from the inner while() loop.
                clrscr;
            }//end if() for 4th option
            
            if (menu_select == 5) //if user chooses to exit:
            {
                exit_program(); //call function to close the program
                exit = 1;
            }//end if() for 5th option.
            
        }//end while()
        
        game_number++; //increment the game number every time the user chooses to enter new numbers (ie. when they break the inner while() loop).
        
    }//end while()
    
    getchar();
}//end main()

//implement function number_validation() : this function checks that the numbers in the array are all unique and in the range 1-42.
//the function will return a 0 if the numbers are valid, 1 if not valid. 
int number_validation(int attempts[])
{
    int i, j, validation = 0;
    
    clrscr();
    
    for (i = 0 ; i < NUMBERS ; i++)
    {
        if (attempts[i] > 0 && attempts[i] <= MAX_NUMBER) //if number IS between 1-42: 
        {
            for (j = 0 ; j < NUMBERS ; j++) //check each number to see if its repeated:
            {
                if (i != j) //provided we're not comparing the same element:
                {
                    if (attempts[i] == attempts[j]) //if they have entered the same number:
                    {
                        validation = 1;
                        printf("Cannot enter the same number more than once!");
                        Sleep(3000);
                        return(validation);
                    }//end if()
                
                }//end if()
            
            }//end for()
        
        }//end if()
        else if (attempts[i] < 1 || attempts[i] > MAX_NUMBER) //if number ISN'T between 1-42
        {
            validation = 1;
            printf("Number must be from 1-42!");
            Sleep(3000);
            return(validation);
        }//end else if()
        
    }//end for()
    
    if (validation == 0)
    {
        return(validation);
    }//end if()
    
}//end number_validation()


//implement function display_numbers() : this function displays the numbers in the array.
void display_numbers(int attempts[])
{
    int i;
    
    clrscr();
    
    printf("The numbers you entered were:\n");
    
    for (i = 0 ; i < NUMBERS ; i++) //display numbers.
    {
        printf("- %d ", *(attempts + i));
    }//end for()
    
    Sleep(6500);
    
    printf("\n");
    
}//end display_numbers()


//implement function sort_numbers() : this function sorts the numbers in the array in increasing order using the bubble sort algorithm.
void sort_numbers(int attempts[])
{
    int i, j, temp;
    
    for (i = (NUMBERS - 1) ; i >= 0 ; i--) //sort the numbers in the array:
    {
        for (j = 0 ; j < (NUMBERS - 1) ; j++)
        {
            if ( attempts[j] > attempts[j + 1] )
            {
                temp = attempts[j + 1];
                attempts[j + 1] = attempts[j];
                attempts[j] = temp;
            }//end for()
            
        }//end for()
        
    }//end for()
    
}//end sort_numbers()


//implement function compare() : this function will check the numbers in the array with the winning numbers and will returns:
//0 for no matches ; 1 for 3 matches + bonus ; 2 for 4 matches ; 3 for 4 matches + bonus ; 4 for 5 matches ; 5 for 5 matches + bonus ; 6 for 6 matches.
int compare(int attempts[], int winning[], int bonus)
{
    int matches, i, j, num, got_bonus = 0;
    matches = 0;
    
    for (i = 0 ; i < NUMBERS ; i++) //nested for() loops will check each of the user's numbers with the winning ones and the bonus.
    {
        if ( *(attempts + i) == bonus) // check if they get the bonus:
        {
            got_bonus = 1;
        }//end if()
        
        for (j = 0 ; j < NUMBERS ; j++)
        {
            if ( *(attempts + i) == *(winning + j) ) //if a match is found:
            {
                matches++;
            } //end if()
            
        }//end for()
        
    }//end for()
    
    if (got_bonus == 0) //if bonus not found:
    {
        switch(matches)
        {
            case 0:
            case 1:
            case 2:
            case 3:
            {
                num = 0;
                return(num);
            }//end case
            case 4:
            {
                num = 2;
                return(num);
            }//end case
            case 5:
            {
                num = 4;
                return(num);
            }//end case()
            case 6:
            {
                num = 6;
                return(num);
            }//end case()
            
        }//end switch()
        
    }//end if()
    else if (got_bonus == 1) //if bonus found:
    {
        switch (matches)
        {
            case 0:
            case 1:
            case 2:
            {
                num = 0;
                return(num);
            }//end case
            case 3:
            {
                num = 1;
                return(num);
            }//end case()
            case 4:
            {
                num = 3;
                return(num);
            }//end case()
            case 5:
            {
                num = 5;
                return(num);
            }//end case()
            
        }//end switch()
        
    }//end else if()
    
}//end compare()


//implement function number frequency() : this function calculates the frequency of each number entered by incrementing the elements -
//in an array (tally) that correspond to the chosen numbers (ie. tally[0] represents 1).
void number_frequency(int attempts[], int tally[])
{
    int i;
    
    for (i = 0 ; i < NUMBERS ; i++) //increment the elements in the array that correspond to the numbers entered by the user.
    {
        tally[ (*(attempts + i)) - 1]++;
    }//end for()
    
}//end number_frequency()

//implement function display_freq(): this function displays the frequency of the numbers entered.
void display_freq(int tally[], int game_number)
{
    int i;
    
    clrscr();
    
    if (game_number >= 2)//if user has played at least 2 times:
    {
        for (i = 0 ; i < MAX_NUMBER ; i++) //display the frequencies:
        {
            if ( *(tally + i) > 0 ) //if this number has been chosen at least once:
            {
                printf("\nNumber %d has been selected %d times.", (i + 1), *(tally + i) );
            }//end if()
            
        }//end for()
        
        Sleep(6500);
        
    }//end if()
    else if(game_number < 2)//if the user has played under 2 games:
    {
        printf("You must play at least 2 times before seeing the frequency\n");
        Sleep(2500);
    }//end else if()
    
}//end display_freq()

//implement function exit_program(): this function closes the program.
//function displays goodbye message and closes.
void exit_program(void)
{
    clrscr();
    printf("Thanks for playing. Goodbye.");
    Sleep(3500);
    exit(0);
    
}//end exit_program
