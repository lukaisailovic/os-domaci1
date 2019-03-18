#include "utils.h"
#include <unistd.h>
#include <fcntl.h>

#define MAX_SCANCODES 128
#define MAX_MNEMONICS 16
#define BUFFER_SIZE 128
#define DEBUG 1



static char scancodes_lower[MAX_SCANCODES];
static char scancodes_upper[MAX_SCANCODES];
static char mnemonics[MAX_MNEMONICS][BUFFER_SIZE];

#define SHIFT 0;
int shift = SHIFT;
int ctrl = 0;
int alt = 0;

int shift_down = 200;
int SHIFT_UP = 300;
int CTRL_DOWN = 201;
int CTRL_UP = 301;
int ALT_DOWN = 202;
int ALT_UP = 302;
/*
	Deklaracije za nizove i tabele ovde
	tabelu za prevodjenje scancodeova i tabelu
	za cuvanje mnemonika cuvati kao staticke
	varijable unutar ovog fajla i ucitavati
	ih uz pomoc funkcije load_config

*/

void load_config(const char *scancodes_filename, const char *mnemonic_filename)
{

    load_scancodes(scancodes_filename);
    load_mnemonic(mnemonic_filename);

}

int process_scancode(int scancode, char *buffer)
{
    if(DEBUG){
         printstr("Processing scancode ");
         char tmp_buff[BUFFER_SIZE];
         int len = itoa(scancode,tmp_buff);
         printstr(tmp_buff)
         newline();
    }


	int result;

     __asm__ __volatile__(
            // check special codes
            "cmp $200, %%eax;"
            "je SHIFT_DOWN_HANDLE;"
            "jmp DONE;"
            //handlers
            "SHIFT_DOWN_HANDLE: ;"
            "movl (shift), %%ebx;"
            "DONE: ;"

            : "=b" (result)
            : "a" (scancode), "d" (shift)
            : "%ecx","memory"
        );

	/*
		Your code goes here!
		Remember, only inline assembly.
		Good luck!
	*/
    vardump(result);
	return result;
}

void load_scancodes(const char *scancodes_filename){
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
    // scancodes loading test
	if(DEBUG){
        newline();
        printstr("SCANCODES TEST\n");
        printstr(scancodes_lower);
        printstr(scancodes_upper);
        newline();
	}
	close(fd);
}

void load_mnemonic(const char *mnemonic_filename){
    int len;
    char buffer[BUFFER_SIZE];
	/*
	Otvaranje i ucitavanje mnemonics
	*/
    int fd = open(mnemonic_filename, O_RDONLY);
    if(fd == -1)
	{
		printerr("Fajl neuspesno otvoren!\n");
		_exit(1);
	} else {
		printstr("Mnemonic fajl ucitan\n");
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

	// mnemonics loading test
	if(DEBUG){
        newline();
        printstr("MNEMONIC TEST\n");
        i = 0;
        for(i; i < n; i++)
        {
            printstr(mnemonics[i]);
        }
        newline();
	}
	close(fd);
}

