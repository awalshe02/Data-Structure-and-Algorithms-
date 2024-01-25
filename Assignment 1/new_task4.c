#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_SIZE 501
#define ARRAY_SIZE 59
#define TASK4_PROMPT ">>> Person ID Deposition ID Surname Forename Age Person Type Gender Nationality Religion Occupation"
#define NAME_PROMPT "Enter term to get frequency or type \"quit\" to escape\n>>> " 
//you can use this string as your invitation to the user
#define NEW_LINE_PROMPT ">>> "
//you can use this string as your invitation to the user where the user should input the name

typedef struct person person;
struct person {
    //bits of info for each person
    char person_id[ARRAY_SIZE], deposition_id[ARRAY_SIZE], surname[ARRAY_SIZE], forename[ARRAY_SIZE], age[ARRAY_SIZE], person_type[ARRAY_SIZE], gender[ARRAY_SIZE], nationality[ARRAY_SIZE], religion[ARRAY_SIZE], occupation[ARRAY_SIZE];
    struct person *next; //used to point at next node
};

person* hashtable[ARRAY_SIZE];
int collisions = 0;
int num_terms = 0;


unsigned long hash1(char* s) { //get hash number 1
    int hash = 0;
        while(*s){
        hash = (hash + *s-'A') % ARRAY_SIZE;
        s++;
}
    return hash;
}

unsigned long hash3(char* s){ //get hash number 3
    int hash = 0;
    while(*s){
        hash = 1+ (hash + *s-'A') % (ARRAY_SIZE-1);
        s++;
    }
    return hash;
}

int insert(person *p) {
    
    if(p == NULL){ // if no person
        return 0;
    }
    unsigned long index1 = hash1(p->surname);
    unsigned long index3 = hash3(p->surname);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        unsigned long  d_hash = (index1 + (i * index3)) % ARRAY_SIZE; // double hashing
    
        if (hashtable[d_hash] == NULL) { //slot is empty
            hashtable[d_hash] = p;
            return 1;
        }
        else if (strcmp(hashtable[d_hash]->surname, p->surname)==0){ // slot is full and names are the same
            p->next = hashtable[d_hash]; // making next of node the head
            hashtable[d_hash] = p;  //head of list pointing to this node
            return 1;           
            }
        else collisions++; // slot full and names are not the same
    }
    return 0;
}

person *search(char *name){

    unsigned long index1 = hash1(name);
    unsigned long index3 = hash3(name);

    for (int i = 0; i < ARRAY_SIZE; i++) {
        unsigned long  d_hash = (index1 + (i * index3)) % ARRAY_SIZE; // double hashing

        person *p = hashtable[d_hash];

        if (hashtable[d_hash] != NULL &&
            strcmp(hashtable[d_hash]->surname, name) == 0) { //full and same name
            return p;
        }
        
    }
    return NULL; //if not found
}

void occurance(char* name) {
    person* p = search(name);
    if (p == NULL) { //not found
        printf("%s%s not in table",NEW_LINE_PROMPT, name);
    }
    else { //found
        printf("%s\n", TASK4_PROMPT);
        printf("      %s   %s     %s     %s     %s  %s %2s %6s %4s %3s\n", p->person_id, p->deposition_id, p->surname, p->forename, p->age, p->person_type, p->gender, p->nationality, p->religion, p->occupation);
    }
}

// From assignment 0
// Reads strings of alpha numeric characters from input file. Truncates strings which are too long to string_max-1
int next_token ( char *buf, FILE *f, int string_max ) {
	// start by skipping any characters we're not interested in
	buf[0] = fgetc(f);
	while ( !isalnum(buf[0]) && !feof(f) ) { buf[0] = fgetc(f); }
	// read string of alphanumeric characters
	int i=1;
	for (;;) {
		buf[i] = fgetc(f);                // get next character from file
		if( !isalnum(buf[i]) ) { 
            if(buf[i]!=' '){ // we still want to keep spaces
                break; // only load letters and numbers
            }
        } 
		if( feof(f) ) { break; }          // file ended?
		if( i < (string_max-1) ) { ++i; } // truncate strings that are too long
	}
	buf[i] = '\0'; // NULL terminate the string
}

person* create_new_person( FILE *f){
    person *p = (person*)malloc(sizeof(person));

    next_token(p->person_id, f, MAX_STRING_SIZE);
    next_token(p->deposition_id, f, MAX_STRING_SIZE);
    next_token(p->surname, f, MAX_STRING_SIZE);
    next_token(p->forename, f, MAX_STRING_SIZE);
    next_token(p->age, f, MAX_STRING_SIZE);
    next_token(p->person_type, f, MAX_STRING_SIZE);
    next_token(p->gender, f, MAX_STRING_SIZE);
    next_token(p->nationality, f, MAX_STRING_SIZE);
    next_token(p->religion, f, MAX_STRING_SIZE);
    next_token(p->occupation, f, MAX_STRING_SIZE);

    p->next = NULL;
}

//  Reads the contents of a file and adds them to the hash table - returns 1 if file was successfully read and 0 if not.
int load_file(char* fname) {
    FILE* f;
    char buf[MAX_STRING_SIZE];
    person *p; 

    // boiler plate code to ensure we can open the file
    f = fopen(fname, "r");
    if (!f) {
        printf("Unable to open %s\n", fname);
        return 0;
    }

    // read until the end of the file
    while (!feof(f)) {
        p = create_new_person(f);
        insert(p);
        num_terms++;
    }

    printf("File %s loaded\n", fname);
    float load = (float)num_terms/ARRAY_SIZE; //TODO7
    printf(" Capacity: %i\n Num Terms: %i\n Collisions: %i\n Load: %f\n", ARRAY_SIZE, num_terms, collisions, load);
    // always remember to close your file stream
    fclose(f);

    return 1;
}



int main(int argc, char *argv[]) {

    load_file("truncated.csv");
    char input[MAX_STRING_SIZE];

    printf("%s", NAME_PROMPT);
    scanf("%s", input);

    while (strcmp(input, "quit") != 0) {
        occurance(input);

        printf("\n%s",NEW_LINE_PROMPT);
        scanf("%s", input); 
    }


    return 0;
}