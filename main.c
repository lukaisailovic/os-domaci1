#define UTIL_IMPLEMENTATION
#include "utils.h"
#include "scan.h"

#define BUFFER_SIZE 13

int main(int argc, char *argv[])
{
	
	char buffer[BUFFER_SIZE];
	char scancodes_filename[BUFFER_SIZE];
	char mnemonics_filename[BUFFER_SIZE];
	
	/* DELETE
	char *scancodes_p;
	char *scancodes_p;
	char *mnemonics_p;
	scancodes_p = scancodes_filename;
	mnemonics_p = mnemonics_filename;
	*/
	int len;
	
	printstr("Domaci 1\n");
	/* ucitavanje podesavanja */
	printstr("Ucitavanje podesavanja\n");
	
	// scancodes ucitavanje
	printstr("Naziv scancodes fajla:\n");
	
	len = read(0,scancodes_filename,BUFFER_SIZE);
	
	load_config(scancodes_filename,mnemonics_filename);
		
	/*
	//mnemonics ucitavanje
	printstr("Naziv mnemonics fajla:\n");
	len = read(0,mnemonics_filename,BUFFER_SIZE);
	*/
	
	
	
	
	/* ponavljamo: */
		/* ucitavanje i otvaranje test fajla */
		/* parsiranje fajla, obrada scanecodova, ispis */
	_exit(0);	
}

