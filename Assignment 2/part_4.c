#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER 256 // Maximum string length this program can handle
#define MAX_GAMES 20000 //max array length

typedef struct Game{
    char title[MAX_BUFFER], platform[MAX_BUFFER];
    int score, year;
}Game;

Game gamearray[MAX_GAMES];
int count = 0; //count for exact size of array

// The CSV parser
int next_field( FILE *f, char *buf, int max ) {
	int i=0, end=0, quoted=0;
	
	while(!feof(f)) {
		// fetch the next character from file		
		buf[i] = fgetc(f);
		// if we encounter quotes then flip our state and immediately fetch next char
		if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
		// end of field on comma if we're not inside quotes
		if(buf[i]==',' && !quoted) { break; }
		// end record on newline or end of file
		if(feof(f) || buf[i]=='\n') { end=1; break; } 
		// truncate fields that would overflow the buffer
		if( i<max-1 ) { ++i; } 
	}

	buf[i] = 0; // null terminate the string
	return end; // flag stating whether or not this is end of the line
}

void get_game(FILE *fname, Game *g){
    char buf[MAX_BUFFER];
    //gets next field and stores in a struct member
    next_field(fname, g->title, MAX_BUFFER); 
    next_field(fname, g->platform, MAX_BUFFER);
    next_field(fname, buf, MAX_BUFFER);
    g->score = atoi(buf); //convert from string into integer
    next_field(fname, buf, MAX_BUFFER);
    g->year = atoi(buf);

}

void insert(Game *g){
    if(g == NULL){ //empty do nothing
        return ;
    } else{
        gamearray[count] = *g; //adding struct into array
        count ++; 
    }
}

int load_file(char *fname){
    FILE* f;

    // boiler plate code to ensure we can open the file
    f = fopen(fname, "r");
    if (!f) {
        printf("Unable to open %s\n", fname);
        return 0 ;
    }

    get_game(f, gamearray); // discard the header

    printf("File %s loaded\n", fname);

    // Now read and print records until the end of the file
	while(!feof(f)) {
	get_game(f, gamearray); //getting parmeters for next array slot
    insert(gamearray); //putting into array slot
	}

    // Always remember to close the file
	fclose(f);
    return EXIT_SUCCESS;
}

int compare(const void * a, const void * b){
  Game *g1 = (Game *)a;
  Game *g2 = (Game *)b;
  return ( g1->score - g2->score); //returns 0, postive or negative number
}


int main ( int argc, char *argv[] ) {
    
    load_file("t4_ign.csv");
    
    qsort(gamearray, count, sizeof(Game), compare); //quick sort for array

    for(int i= count - 10; i<count; i++){ //printing out top 10 scores
        printf("Title = %s, Platfrom = %s, Score = %d, Year = %d \n",
        gamearray[i].title, gamearray[i].platform, gamearray[i].score, gamearray[i].year);
    }
    
  return 0;
}