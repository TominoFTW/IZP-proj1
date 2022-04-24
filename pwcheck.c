#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define PW_LEN 100
#define ASCII 128 //ASCII has 2^7 characters


/**************************
Tomas Behal, 1BIT, xbehal02
       31. 10. 2021
**************************/



// checks validity of third argument "--stats"
// false if not valid or entered, true otherwise
bool is_argstats_valid(char *argstats) 
{
    //not entered
    if (argstats == NULL)
        return false;
    //not valid
    else
    {   
        char argstring[8] = "--stats";
        for (int i = 0; argstring[i] != '\0' || argstats[i] != '\0'; i++)
        {
            if (argstring[i] != argstats[i])
                return false;
        }
    }
    //otherwise
    return true;
}

// checks validity of other arguments
// false if args contains non-numeric characters or not entered right, true otherwise
bool is_arg_valid(int count, char **argv)
{
    // valid number of arguments
    if (count < 3 || count > 4)
    {
        fprintf(stderr,"Neplatny pocet argumentu\n");
        return false;
    }
    // if "--stats" entered
    else if (count == 4) 
    {
        if(!is_argstats_valid(argv[3]))
        {
            fprintf(stderr,"Spatne zadany argument \"--stats\"\n");
            return false;
        }
    }
    // if contains numbers and in range 
    for (int i = 1; i <= 2; i++) 
    {   
        char *ptr;
        long int ret = strtol(argv[i], &ptr, 10);
        
        if (*ptr != '\0' || (i == 1 && !(ret >= 1 && ret <= 4)) 
                || (i == 2 && (ret < 1 || ret > LONG_MAX))) 
            {
                fprintf(stderr,"Chybne zadani argumentu\n");
                return false;
            }
    }
    return true;
}

// returns length of given string
int length(char *string)
{
    int i;
    for (i = 0; string[i] != '\0';i++){}
    return i;
}

// false if password on stdin is longer than 100 characters, true otherwise
char is_input_valid(char *password)
{   
    for (int i = 0; password[i] != '\0'; i++)
    {
        // valid password has '\n' on any position from 0 to 100
        // since we need to print number of unique characters it has to be replaced so it's not counted 
        if (password[i] == '\n')
        {
            password[i] = '\0';
            return true;
        }
    }
    return false;
}

// ******************* security rules *******************
// every rule has its own criteria for passing
// for password that passes function returns true, otherwise false

// password needs to contain at least one upper and lower case character
bool rule_1(char *password)
{
    bool upper_case = false;
    bool lower_case = false;

    for (int i = 0; password[i] != '\0'; i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            upper_case = true;
        }
        else if (password[i] >= 'a' && password[i] <= 'z')
        {
            lower_case = true;
        }
    }

    if (lower_case && upper_case)
        return true;
    else
        return false;
}

// password needs to contain at least one character from each group
// true if password has passed equal or more groups that user requested 
bool rule_2(char *password, long long int ngroups)
{
    int upper_case = 0;
    int lower_case = 0;
    int number = 0;
    int miscellaneous = 0;

    // every password request for more than 4 groups has to pass each one of them
    if(ngroups > 4)
        ngroups = 4;
    
    for (int i = 0; password[i] != '\0'; i++)
    {
        if(password[i] >= 'A' && password[i] <= 'Z')
            upper_case = 1;
        else if(password[i] >= 'a' && password[i] <= 'z')
            lower_case = 1;
        else if(password[i] >= '0' && password[i] <= '9')
            number = 1;
        else // non-alfanumeric characters  
            miscellaneous = 1;
    }

    if (upper_case + lower_case + number + miscellaneous >= ngroups)
        return true;
    else
        return false;
}

// false if password contains sequence of same character for given length of sequeniton
bool rule_3(char *password, long long int length_seq)
{
    // counter for characters in sequence
    int seq_counter = 1;

    for (int i = 0; password[i] != '\0'; i++)
    {
        // checks for meeting criteria
        if (seq_counter == length_seq)
            return false;

        // resets counter
        if (password[i] != password[i+1])
            seq_counter = 1; 

        // increments counter by 1
        else
            seq_counter++;
    }

    return true;
}


// false if password contains two equal substrings of given length
bool rule_4(char *password, int substr_len)
{
    // if given length is higher or equal to length of password it cannot contain two substrings of that length
    if (substr_len >= length(password))
        return true;

    char substr[substr_len];
    substr[substr_len] = '\0';
    int substr_count = 0;
    int i_mm;
    
    for (int i = 0; password[i] != '\0'; i++)
    {
        int j;
        for (j = 0; j < substr_len; j++)
        {
            substr[j] = password[j+i];
        }
        
        // memorization of password index counter
        i_mm = i; 
        // reset of substring index counter
        j = 0;

        while (password[i] != '\0')
        {
            if (substr[j] == password[i+1])
            {
                // increments counter by 1 and checks for substring length
                substr_count++;
                if (substr_count == substr_len)
                    return false;
                j++;
            }
            else
            {
                // resets counter and substring index counter to start from beginning
                substr_count = 0;
                j = 0;
            }
            i++;
        }
        // getting back memorized index
        i = i_mm;
    }
    return true;
}

// ******************* stats *******************
// returns number of unique characters in given passwords
int number_of_unique_characters(char *password, char *uchars)
{
    int nuchars = 0;

    for (int i = 0; password[i] != '\0'; i++)
    {
        for (int j = 0; uchars[j] != '\0'; j++)
        {
            if (password[i] == uchars[j])
                    break;

            else if(uchars[j] == ' ' && (password[i] != uchars[j]))
            {
                uchars[j] = password[i];
                nuchars++;
                break;
            }
        }
    }
    return nuchars;
}

// returns minimal length of password
int minimal_length_of_password(char *password, int min_len)
{   
    if (min_len > length(password))
        min_len = length(password);
    return min_len;
}


int main(int argc,char **argv)
{
    int LEVEL;
    int PARAM;

    if (is_arg_valid(argc, argv))
    {  
        LEVEL = atoi(argv[1]);
        PARAM = atoi(argv[2]);
    }
    else
        return 1;

    char password[PW_LEN + 2];


    // variables for stats
    char uchars[ASCII]; 
    for (int i = 0; i < ASCII; i++)
            uchars[i] = ' ';
    uchars[ASCII] = '\0';

    int MIN = 100;
    int NCHARS = 0;
    int count = 0;
    float len = 0;
    
    // taking passwords from stdin 
    // if valid it is checks for rules and when every password is evaluated prints stats if requested
    // if invalid prints error message and ends program
    while (fgets(password, PW_LEN + 2, stdin) != NULL)
    {
        if (is_input_valid(password))
        {
            if (LEVEL == 1 && rule_1(password))
                printf("%s\n", password);

            else if (LEVEL == 2 && rule_1(password) 
                    && rule_2(password,PARAM))
                printf("%s\n", password);

            else if (LEVEL == 3 && rule_1(password) 
                    && rule_2(password,PARAM) 
                    && rule_3(password,PARAM))
                printf("%s\n", password);

            else if (LEVEL == 4 && rule_1(password) 
                    && rule_2(password,PARAM) 
                    && rule_3(password,PARAM) 
                    && rule_4(password,PARAM))
                printf("%s\n", password);

            // stats counters
            len += length(password);
            count++;

            MIN = minimal_length_of_password(password,MIN);

            NCHARS += number_of_unique_characters(password, uchars);
        }
        else
        {
            fprintf(stderr,"Neplatny vstup\n");
            return EXIT_FAILURE;
        }
    }
    if (is_argstats_valid(argv[3]) && (argc = 4))
        printf("Statistika:\nRuznych znaku: %d\nMinimalni delka: %d\nPrumerna delka: %.1f\n", NCHARS, MIN, len/count);

    return EXIT_SUCCESS;
}