// header files inclusion
#include <stdio.h>
#include <string.h>

// definition of macro
#define MAX_NUM_OF_CONTACTS 42

// definition of contact struct
typedef struct {
    char name[101];
    char number[10];
} CONTACT;

// array for mapping letters to numbers
const char *numRepArr[] = {
    "+",
    "",
    "abc",
    "def",
    "ghi",
    "jkl",
    "mno",
    "pqrs",
    "tuv",
    "wxyz"
};

// function declarations
int readContacts(CONTACT *contactArr, int *numOfContactsRead);
int readLineOfContacts(char charArr[]);
void findMaches(char inputNumbers[], int inputNumberCount,
    CONTACT *contacts, int contactsCount,
    int *numOfMatches, int *arrOfMachingIndexes);
void findInSequenceMatches(char inputNumbers[], int inputNumberCount,
    CONTACT *contacts, int contactsCount,
    int *numOfMatches, int *arrOfMachingIndexes);


int main(int argc, char *argv[]) {
    // declaration of array of contacts
    CONTACT contactArr[MAX_NUM_OF_CONTACTS];
    int numOfContactsRead;

    // stops program if data are invalid
    if (readContacts(contactArr, &numOfContactsRead) == -1) {
        fprintf(stderr,"%s","ERROR - Contact data are invalid");
        return -1;
    }


    // if program is run with no arguments, all contacts are printed
    if(argc == 1) {
        for (int i = 0; i < numOfContactsRead; ++i) {
            printf("%s, ",contactArr[i].name);
            printf("%s\n",contactArr[i].number);
        }
        return 0;
    }
    // checks if there is valid amount of arguments
    if(argc == 2 || (argc == 3 && strcmp(argv[2],"-s") == 0)) {
        int sizeOfInputArr = strlen(argv[1]);

        // if input doesnt consist of numbers throws error
        for (int i = 0; i < sizeOfInputArr; ++i) {
            if(argv[1][i] < '0' || argv[1][i] > '9') {
                fprintf(stderr,"%s","ERROR - Invalid number input");
                return -1;
            }
        }

        int numOfMatches;
        // definition of array of indexes of matching contacts
        // * since we arent alowed to use malloc.h, size is set to max number of contacts
        int arrOfMachingIndexes[MAX_NUM_OF_CONTACTS] = {0};

        if(argc == 2) {
            // searches for matches in contacts, and returns the indexes and number of contacts that mach
            findMaches(argv[1], sizeOfInputArr,
                contactArr,numOfContactsRead ,
                &numOfMatches ,arrOfMachingIndexes);
        } else {
            // shearches for contact in which input numbers are in sequence
            // returns the indexes and number of contacts that mach
            findInSequenceMatches(argv[1], sizeOfInputArr,
                contactArr,numOfContactsRead ,
                &numOfMatches ,arrOfMachingIndexes);
        }


        // if there are no matches "Not Found" is outputted
        if (numOfMatches == 0) {
            printf("Not found");
        } else {
            // prints all contacts
            for (int i = 0; i < numOfMatches; ++i) {
                printf("%s, ",contactArr[arrOfMachingIndexes[i]].name);
                printf("%s\n",contactArr[arrOfMachingIndexes[i]].number);
            }
        }
    } else {
        // throws an error message if invalid number of parameters is entered
        fprintf(stderr,"%s","ERROR - Invalid number of parameters");
        return -1;
    }

    return 0;
}

//-------------------------------------------------------------------------------------------------------------------
// function definitions

// reads contact and puts them to a contact array (parameter)
// also returns number of contacts read through numOfContacsRead
int readContacts(CONTACT *contactArr, int *numOfContactsRead) {
    *numOfContactsRead = 0;
    // reading the conntacts
    for (int i = 0; i < MAX_NUM_OF_CONTACTS; ++i) {
        CONTACT tmp;

        // if readLineOfContacts returns -1 (stands for error) returns -1 aswell
        if (readLineOfContacts(tmp.name) == -1 || readLineOfContacts(tmp.number) == -1) {
            return -1;
        }

        // stops reading contacts
        if (strlen(tmp.name) == 0 || strlen(tmp.number) == 0) {
            break;
        }

        // adds new contact to a contact array
        strcpy(contactArr[i].name, tmp.name);
        strcpy(contactArr[i].number, tmp.number);

        (*numOfContactsRead) ++;
    }
    return 0;
}

// reads one line of contacts and puts it into an array
// returns -1 if input data are invalid otherwise returns 0
int readLineOfContacts(char charArr[]) {
    char readChar;
    int i;

    for (i = 0; ((readChar = getchar()) != '\n') ; ++i) {
        charArr[i] = readChar;
        // if txt is used as an input, checks if its end of an input
        if(readChar == EOF) {
            charArr[i] = '\0';
            return 0;
        }
        // checks if inputs are invalid
        if (i >= 100) {
            fprintf(stderr,"%s","\nERROR - Contact data are invalid");
            return -1;
        }
    }
    charArr[i] = '\0';

    return 0;
}

// finds indexes of contacts that mach inputNumbers string
// number of matches and matching indexes are returned through numOfMatches, arrOfMachingIndexes
void findMaches(char inputNumbers[], int inputNumberCount,
    CONTACT *contacts, int contactsCount,
    int *numOfMatches, int *arrOfMachingIndexes) {

    *numOfMatches = 0;
    int numOfMachingNumbers;
    int wasAMach;

    // searches for mathes in contacts array
    for (int i = 0; i < contactsCount; ++i) {
        wasAMach = 0;
        // checks if in number is a mach
        for (int j = 0; j + (inputNumberCount - 1) < (int)strlen(contacts[i].number); ++j) {
            numOfMachingNumbers = 0;

            // checks if all of the numbers are behind each other in number
            for (int k = 0; k < inputNumberCount; ++k) {
                if (inputNumbers[k] != contacts[i].number[j + k]) {
                    break;
                }
                numOfMachingNumbers++;
            }

            //if all numbers mach adds their index into an array
            if(numOfMachingNumbers == inputNumberCount) {
                arrOfMachingIndexes[(*numOfMatches)] = i;
                (*numOfMatches)++;
                wasAMach = 1;
                break;
            }
        }

        // if number was a mach there is no need to check if name is mach again
        if (wasAMach) {
            continue;
        }

        // checks if in name is a mach
        for (int j = 0; j + (inputNumberCount - 1) < (int)strlen(contacts[i].name); ++j) {
            numOfMachingNumbers = 0;

            // checks if all of the numbers are behind each other in name
            for (int k = 0; k < inputNumberCount; ++k) {
                // checks if any of the characters input nuber represents is a mach in name
                for (int l = 0; l < (int)strlen(numRepArr[inputNumbers[k] - '0']); ++l) {
                    if (numRepArr[inputNumbers[k] - '0'][l] == contacts[i].name[j + k]) {
                        numOfMachingNumbers++;
                        break;
                    }
                }
                // breaks the loop if input numbers (characters) dont mach this part of the name
                if (numOfMachingNumbers != k + 1) {
                    break;
                }
            }

            //if all numbers mach adds their index into an array
            if(numOfMachingNumbers == inputNumberCount) {
                arrOfMachingIndexes[(*numOfMatches)] = i;
                (*numOfMatches)++;
                break;
            }
        }

    }
}
// (bonus task) finds contacts where numbers are in sequence
// number of matches and matching indexes are returned through numOfMatches, arrOfMachingIndexes
void findInSequenceMatches(char inputNumbers[], int inputNumberCount,
    CONTACT *contacts, int contactsCount,
    int *numOfMatches, int *arrOfMachingIndexes) {

    *numOfMatches = 0;
    int numOfMachingNumbers;
    int wasAMach;

    // searches for matches in contacts array
    for (int i = 0; i < contactsCount; ++i) {
        wasAMach = 0;
        numOfMachingNumbers = 0;

        // checks if input numbers are in sequence in phone number
        for (int j = 0; j  < (int)strlen(contacts[i].number); ++j) {
            if (inputNumbers[numOfMachingNumbers] == contacts[i].number[j]) {
                numOfMachingNumbers++;

            }

            //if all numbers mach adds their index into an array
            if(numOfMachingNumbers == inputNumberCount) {
                arrOfMachingIndexes[(*numOfMatches)] = i;
                (*numOfMatches)++;
                wasAMach = 1;
                break;
            }
        }

        // if number was a mach there is no need to check if name is mach again
        if (wasAMach) {
            continue;
        }

        numOfMachingNumbers = 0;

        // checks if input numbers (characters they represent) are in sequence in name
        for (int j = 0; j < (int)strlen(contacts[i].name); ++j) {
            // checks if any of characters is a mach for current letter
            for (int l = 0; l < (int)strlen(numRepArr[inputNumbers[numOfMachingNumbers] - '0']); ++l) {
                if (numRepArr[inputNumbers[numOfMachingNumbers] - '0'][l] == contacts[i].name[j]) {
                    numOfMachingNumbers++;
                    break;
                }
            }

            //if all numbers mach adds their index into an array
            if(numOfMachingNumbers == inputNumberCount) {
                arrOfMachingIndexes[(*numOfMatches)] = i;
                (*numOfMatches)++;
                break;
            }
        }
    }
}
//-------------------------------------------------------------------------------------------------------------------


