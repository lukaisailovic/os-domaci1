#include "utils.h"
#include <unistd.h>
#include <fcntl.h>

#define MAX_SCANCODES 128
#define MAX_MNEMONICS 16
#define BUFFER_SIZE 128

static char scancodes_lower[MAX_SCANCODES];
static char scancodes_upper[MAX_SCANCODES];
static char mnemonics[MAX_MNEMONICS][BUFFER_SIZE];
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
	char buffer[BUFFER_SIZE];
	/*
	Otvaranje i ucitavanje scancodes fajla
	*/
	int fd = open(scancodes_filename, O_RDONLY);
	if(fd == -1)
	{
		printerr("Fajl neuspesno otvoren!\n");
		_exit(1);
	} else {
		printstr("Scancodes fajl ucitan\n");
	}
	len = fgets(scancodes_lower, MAX_SCANCODES, fd);
	len = fgets(scancodes_upper, MAX_SCANCODES, fd);

	printstr(scancodes_lower);
	printstr(scancodes_upper);

	/*
	Otvaranje i ucitavanje mnemonics
	*/
    fd = open(mnemonic_filename, O_RDONLY);
    if(fd == -1)
	{
		printerr("Fajl neuspesno otvoren!\n");
		_exit(1);
	} else {
		printstr("Mnemonics fajl ucitan\n");
	}
    len = fgets(buffer,BUFFER_SIZE,fd);
    int n = atoi(buffer);
	if(n > MAX_MNEMONICS)
	{
		printerr("Uneti broj mnemonica nije podrzan\n");
		_exit(1);
	}
	int i = 0;
	for(i; i < n; i++)
	{
		len = fgets(mnemonics[i], BUFFER_SIZE, fd);
	}

	/*
	Test

	i = 0;
	for(i; i < n; i++)
	{
		printstr(mnemonics[i]);
	}
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

