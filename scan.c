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


int shift = 0;
int ctrl = 0;
int alt = 0;


int MAX_SCANCODES_C = MAX_SCANCODES;
int SHIFT_DOWN = 200;
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
    if(0){
         printstr("Processing scancode ");
         char tmp_buff[BUFFER_SIZE];
         int len = itoa(scancode,tmp_buff);
         printstr(tmp_buff)
         newline();
    }


	int result;

     __asm__ __volatile__(
            // ===== special codes =====
            
            //check shift down
            "cmp (SHIFT_DOWN), %%eax;"
            "je SHIFT_DOWN_HANDLE;"
            
            //check shift up
            "cmp (SHIFT_UP), %%eax;"
            "je SHIFT_UP_HANDLE;"
            
            //check ctrl down
            "cmp (CTRL_DOWN), %%eax;"
            "je CTRL_DOWN_HANDLE;"
            
            //check ctrl up
            "cmp (CTRL_UP), %%eax;"
            "je CTRL_UP_HANDLE;"
            
            //check alt down
            "cmp (ALT_DOWN), %%eax;"
            "je ALT_DOWN_HANDLE;"
            
            //check alt up
            "cmp (ALT_UP), %%eax;"
            "je ALT_UP_HANDLE;"
            
            // ===== end special codes =====
            
            // ===== standard chars =====
            "cmp (MAX_SCANCODES_C), %%eax;"
            "jle STANDARD_CHAR_HANDLE;"
            // ===== end standard chars =====
            
            "jmp EXIT;"
            
            // ===== handlers =====
            
            // shift down
            "SHIFT_DOWN_HANDLE:;"
            "movl $1, (shift);"
            "jmp EXIT;"
            
            // shift up
            "SHIFT_UP_HANDLE:;"
            "movl $0, (shift);"
            "jmp EXIT;"
            
            // ctrl down
            "CTRL_DOWN_HANDLE:;"
            "movl $1, (ctrl);"
            "jmp EXIT;"
            
            // ctrl up
            "CTRL_UP_HANDLE:;"
            "movl $0, (ctrl);"
            "jmp EXIT;"
            
            // alt down
            "ALT_DOWN_HANDLE:;"
            "movl $1, (alt);"
            "jmp EXIT;"
            
            // alt up
            "ALT_UP_HANDLE:;"
            "movl $0, (alt);"
            "jmp EXIT;"
            
            // standard chars
            "STANDARD_CHAR_HANDLE:;"
            "movl %%eax, %%ebx;"
            "jmp EXIT;"
            
            // ===== end handlers =====
            
            //done
            "EXIT:;"          
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

