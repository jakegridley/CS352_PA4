/* Jake Gridley
** CSC352
** PA4: sgrep
** sgrep.c: This program is a simple grep command that is used to search files for certain key words or patterns.
**          This program will read lines from stdin and check each line for the key word.  It can take certain flags
**          -i, -o, -e.  -i allows for case insensitve search.  -o make it where only the word is printed and not the
**          whole line. -e allows to search for patterns rather than specific key words.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
** This function checks the input for key word/pattern. If the input is not valid, a message will be printed to stderr
** and will return an exit code of 2.
*/
int checkInputs(char input[]) {
    
    if (strlen(input) == 0) {
        fprintf(stderr, "%s", "Invalid search term.\n");
        return 2;
    }

    for (int i = 0; i<strlen(input); i++) {
        //printf("%d\n", input[i]);
        if ((input[i] >= 65) && (input[i] <= 90)) {
            ;
        } else if ((input[i] >= 97) && (input[i] <= 122)) {
            ;
        } else if ((input[i] >= 48) && (input[i] <= 57)) {
            ;
        } else if (input[i] == 46) {
            ;
        } else if (input[i] == 35) {
            if (i == 0) {
                fprintf(stderr, "%s", "Invalid search term.\n");
                return 2;
            }
            if (((input[i+1] < 65) || (input[i+1] > 122)) || ((input[i+1] < 97) && (input[i+1] > 90))) {
                fprintf(stderr, "%s", "Invalid search term.\n");
                return 2; 
            }
            if (((input[i-1] < 65) || (input[i-1] > 122)) || ((input[i-1] < 97) && (input[i-1] > 90))) {
                fprintf(stderr, "%s", "Invalid search term.\n");
                return 2;
            }
        } else {
            fprintf(stderr, "%s", "Invalid search term.\n");
            return 2;
        }
    }
    return 0;
}

/*
** This function will check for certain patterns of words in a case insensitive manner (-e and -i are flagged). It takes four inputs, an empty char[]
** for the word to be found (wordFound), term which is a char[] for the pattern to be searched for, line which is the current
** line being searched as a char[].  boolO is a boolean for whether the flag -o is activated.
*/
int customFindIns(char wordFound[], char term[], char line[], int boolO) { 
    char first = term[0];
    char firstUp = term[0]+32;
    char firstLow = term[0]-32;
    int contains = 1;

    for (int i = 0; i<strlen(line); i++) {
        if ((first == '.') || (first == line[i]) || (firstUp == line[i]) || 
        (firstLow == line[i])) {
            int j = 0;
            int k = i;
            int foundIdx = 0;
            contains = 0;
            while ((k<strlen(line)) && (j<strlen(term))) {
                if ((term[j] == '.') || (term[j] == line[k]) || 
                ((term[j]-32) == line[k]) || ((term[j]+32) == line[k])) {
                    wordFound[foundIdx] = line[k];
                    k++;
                    foundIdx++;
                    j++;
                } else if (term[j] == '#') {
                    while (((line[k] != term[j+1]) && (line[k] != (term[j+1]+32)) && 
                    (line[k] != (term[j+1]-32))) && (k<strlen(line))) {
                        wordFound[foundIdx] = line[k];
                        foundIdx++;
                        k++;
                    }
                    if (k>=strlen(line)){
                        contains = 1;
                        return contains;
                    }
                    j++;
                } else {
                    contains = 1;
                    break;
                }
            }
            if (contains == 0) {
                wordFound[foundIdx] = '\0';
                if (boolO == 1) {
                    printf("%s\n", wordFound);
                }
                strcpy(wordFound, "");
            }
        }                
    }
    if ((boolO == 0) && (contains == 0)) {
        printf("%s", line);
    }
    return contains;
}


/*
** This function will check for certain patterns of words in a case sensitive manner (-e is flagged). It takes four inputs, an empty char[]
** for the word to be found (wordFound), term which is a char[] for the pattern to be searched for, line which is the current
** line being searched as a char[].  boolO is a boolean for whether the flag -o is activated.
*/
int customFind(char wordFound[], char term[], char line[], int boolO) { 
    char first = term[0];
    int contains = 1;

    for (int i = 0; i<strlen(line); i++) {
        if ((first == '.') || (first == line[i])) {
            int j = 0;
            int k = i;
            int foundIdx = 0;
            contains = 0;
            while ((k<strlen(line)) && (j<strlen(term))) {
                if ((term[j] == '.') || (term[j] == line[k])) {
                    wordFound[foundIdx] = line[k];
                    k++;
                    foundIdx++;
                    j++;
                } else if (term[j] == '#') {
                    while ((line[k] != term[j+1]) && (k<strlen(line))) {
                        wordFound[foundIdx] = line[k];
                        foundIdx++;
                        k++;
                    }
                    if (k>=strlen(line)){
                        contains = 1;
                        return contains;
                    }
                    j++;
                } else {
                    contains = 1;
                    break;
                }
            }
            if (contains == 0) {
                wordFound[foundIdx] = '\0';
                if (boolO == 1) {
                    printf("%s\n", wordFound);
                }
                strcpy(wordFound, "");
            }
        }                
    }
    if ((boolO == 0) && (contains == 0)) {
        printf("%s", line);
    }
    return contains;
}


/*
** This function will check for certain specific words in a case insensitive manner (-e is not flagged, -o is). It takes four inputs, an empty char[]
** for the word to be found (wordFound), term which is a char[] for the pattern to be searched for, line which is the current
** line being searched as a char[].  boolO is a boolean for whether the flag -o is activated.
*/
int containsCaseIns(char wordFound[], char term[], char line[], int boolO) {
    char first = term[0];
    char firstUp = term[0] + 32;
    char firstLow = term[0] - 32;
    int contains = 1;
    for (int i = 0; i<strlen(line); i++) {
        if ((first == line[i]) || (firstUp == line[i]) || 
        (firstLow == line[i])) {
            for (int j = 0; j<strlen(term); j++) {
                if ((line[j+i] == term[j]) || 
                (line[j+i] == (term[j]-32)) || (line[j+i] == (term[j]+32))) {
                    wordFound[j] = line[j+i];
                } else {
                    break;
                }
                if (j+1==strlen(term)) {
                    if (boolO == 1) {
                        printf("%s\n", wordFound);
                    }
                    strcpy(wordFound, "");
                    contains = 0;
                }
            }
        }
    }
    if ((boolO == 0) && (contains == 0)) {
        printf("%s", line);
    }
    return contains;
}



/*
** This function will check for certain specific words in a case sensitive manner (-e and -i are not flagged). It takes four inputs, an empty char[]
** for the word to be found (wordFound), term which is a char[] for the pattern to be searched for, line which is the current
** line being searched as a char[].  boolO is a boolean for whether the flag -o is activated.
*/
int contains(char wordFound[], char term[], char line[], int boolO) {
    char first = term[0];
    int contains = 1;
    for (int i = 0; i<strlen(line); i++) {
        if (first == line[i]) {
            for (int j = 0; j<strlen(term); j++) {
                if (term[j] == line[i+j]) {
                    wordFound[j] = line[j+i];
                } else {
                    break;
                }
                if (j+1==strlen(term)) {
                    if (boolO == 1) {
                        printf("%s\n", wordFound);
                    }
                    strcpy(wordFound, "");
                    contains = 0;
                }
            }
        }
    }
    if ((boolO == 0) && (contains == 0)) {
        printf("%s", line);
    }
    return contains;
}

/*
** THis is the main function that runs the program, it calls all other functions doing things such as checking input for validation, marking all flags
** and running the loop getting each line from stdin.
*/
int main(int argc, char * argv[]) {
    
    if (argc < 1) {
        fprintf(stderr, "%s", "Requires more command-line arguments.\n");
        return 1;
    }
    
    int boolO = 0;
    int boolI = 0;
    int boolE = 0;
    char term[201];    

    for (int i = 1; i<argc; i++) {
        //printf("%s\n", argv[i]);
        if (strcmp(argv[i], "-o") == 0) {
            boolO = 1;
        } else if (strcmp(argv[i], "-i") == 0) {
            boolI = 1;
        } else if (strcmp(argv[i], "-e") == 0) {
            boolE = 1;
        } else {
            strcpy(term, argv[i]);
        }
    }

    int check;
    check = checkInputs(term);
    if (check != 0) {return check;}    
    
    char line[201];
    while (fgets(line, 200, stdin) != NULL) {
        //printf("LINE: %s\n", line);   
        char wordFound[201];     
        if ((boolI == 0) && (boolE == 0)) {
            contains(wordFound, term, line, boolO);
        } else if ((boolI == 1) && (boolE == 0)){
            containsCaseIns(wordFound, term, line, boolO);
            //printf("BOOLEAN: %d\n", boolean);
        } else if ((boolI == 0) && (boolE == 1)) {
            customFind(wordFound, term, line, boolO);
        } else if ((boolI == 1) && (boolE == 1)) {
            customFindIns(wordFound, term, line, boolO);
        }
    }
    return 0;
}
