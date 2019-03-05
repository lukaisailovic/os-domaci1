#include "utils.h"
#include <unistd.h>
#include <fcntl.h>

#define MAX_SCANCODES 128
#define MAX_MNEMONICS 16

static char scancodes_lower[MAX_SCANCODES];
static char scancodes_upper[MAX_SCANCODES];
/*
	Deklaracije za nizove i tabele ovde
	tabelu za prevodjenje scancodeova i tabelu
	za cuvanje mnemonika cuvati kao staticke
	varijable unutar ovog fajla i ucitavati
	ih uz pomoc funkcije load_config

*/

void load_config(const char *scancodes_filename, const char *mnemonic_filename)
{
	int len;
	printstr("Ucitivanje scancodes iz fajla:\n");
	printstr(scancodes_filename);
	printstr("\n");
	
	// otvaranje fajla
	int fd = open(scancodes_filename, O_RDONLY);
	if(fd == -1)
	{
		printerr("Fajl neuspesno otvoren!\n");
		_exit(1);
	} else {
		printstr("Fajl otvoren!\n");
	}
	len = fgets(scancodes_lower, MAX_SCANCODES, fd);
	
	len = fgets(scancodes_upper, MAX_SCANCODES, fd);
	printstr(scancodes_lower);
	printstr(scancodes_upper);
	
	
	/*
	printstr("Ucitivanje mnemonics iz fajla:\n");
	printstr(mnemonic_filename);
	*/
}

int process_scancode(int scancode, char *buffer)
{
	int result;

	/*
		Your code goes here!
		Remember, only inline assembly.
		Good luck!
	*/

	return result;
}

void load_scancodes(char *scancodes_filename){
	
}

