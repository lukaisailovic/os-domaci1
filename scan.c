#include "utils.h"
#include <unistd.h>
#include <fcntl.h>

#define MAX_SCANCODES 128
#define MAX_MNEMONICS 16
#define BUFFER_SIZE 128
#define DEBUG 0
#define ASM_DEBUG 0


static char scancodes_lower[MAX_SCANCODES];
static char scancodes_upper[MAX_SCANCODES];
static char mnemonics[MAX_MNEMONICS][BUFFER_SIZE];


int mnemonics_num = 0;
int buffer_size = BUFFER_SIZE;
int max_mnemonics = MAX_MNEMONICS;

int shift = 0;
int ctrl = 0;
int alt = 0;

int ascii_val = 0;

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
	mnemonics_num = n;
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
	int test;

     __asm__ __volatile__(

            // ===== special codes =====

            //check shift down
            "cmpl (SHIFT_DOWN), %%eax;"
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
            //"cmp (MAX_SCANCODES_C), %%eax;"
            //"jle STANDARD_CHAR_HANDLE;"
            "jmp STANDARD_CHAR_HANDLE;"
            // ===== end standard chars =====

            "jmp EXIT;"

            // ===== handlers =====

            // shift down
            "SHIFT_DOWN_HANDLE:;"
            "movl $1, (shift);"
            "xorl %%edx, %%edx;"
            "jmp EXIT;"

            // shift up
            "SHIFT_UP_HANDLE:;"
            "movl $0, (shift);"
            "xorl %%edx, %%edx;"
            "jmp EXIT;"

            // ctrl down
            "CTRL_DOWN_HANDLE:;"
            "movl $1, (ctrl);"
            "xorl %%edx, %%edx;"
            "jmp EXIT;"

            // ctrl up
            "CTRL_UP_HANDLE:;"
            "movl $0, (ctrl);"
            "xorl %%edx, %%edx;"
            "jmp EXIT;"

            // alt down
            "ALT_DOWN_HANDLE:;"
            "movl $1, (alt);"
            "xorl %%edx, %%edx;"
            "jmp EXIT;"

            // alt up
            "ALT_UP_HANDLE:;"
                //reset alt key press
            "movl $0, (alt);"
                //put ascii_val on buff
            "movl (ascii_val), %%eax;"
            "cld;"
            "stosb;"
                //reset asci_val
            "movl $0, (ascii_val);"
                //set result to 1
            "movl $1, %%edx;"
            //"xorl %%edx, %%edx;"
            "jmp EXIT;"

            // standard chars
            "STANDARD_CHAR_HANDLE:;"

            // check if shift is pressed
            "cmp $1, (shift);"
            "je UPPERCASE_CHAR_HANDLE;"
            "jne LOWERCASE_CHAR_HANDLE;"

            // ?
            "jmp EXIT;"



            // put scancodes_lower + ax value in di
            "LOWERCASE_CHAR_HANDLE:;"
                    //only return one char
            "movl $1, %%edx;"
                    // ld from scancodes_lower to si
            "cld;"
            "leal (scancodes_lower), %%esi;"
            "addl %%eax, %%esi;"
            "lodsb;"
                    // check alt
            "cmp $1, (alt);"
            "je ALT_CHAR_HANDLE;"
                    // check ctrl
            "cmp $1, (ctrl);"
            "je CTRL_CHAR_HANDLE;"
                    // cpy from ax to buff
            "cld;"
            "stosb;"


            "movl $1, %%edx;" //tst
            "jmp EXIT;"

            // put scancodes_lower + ax value in di
            "UPPERCASE_CHAR_HANDLE:;"
                    //only return one char
            "movl $1, %%edx;"
                    // ld from scancodes_lower to si
            "cld;"
            "leal (scancodes_upper), %%esi;"
            "addl %%eax, %%esi;"
            "lodsb;"
                    // check alt
            "cmp $1, (alt);"
            "je ALT_CHAR_HANDLE;"
                    // check ctrl
            "cmp $1, (ctrl);"
            "je CTRL_CHAR_HANDLE;"
                    // cpy from ax to buff
            "cld;"
            "stosb;"


            "movl $1, %%edx;" //tst
            "jmp EXIT;"


            // ALT
            "ALT_CHAR_HANDLE:;"
            "cmp $1, (alt);"
            "jne EXIT;"
            "imull $10, (ascii_val),  %%ecx;"
            "subl $48, %%eax;"
            "addl %%eax, %%ecx;"
            "movl %%ecx, (ascii_val);"
            "movl $0, %%edx;"
            "jmp EXIT;"

            // CTRL
            /*
                val -> ax
                ax == &mnemonics ?
                loop (&mnemonics + max_char) mnemonics_num times
                if true
                loop until val != '\n'
                store val in buffer
            */
            "CTRL_CHAR_HANDLE:;"
            "cmp $1, (ctrl);"
            "jne EXIT;"


                // save val in bx
            "movl %%eax, %%ebx;"
               // load mnemonics
            "leal (mnemonics), %%esi;"


            "movl $0, %%edx;"
            "movl (mnemonics_num), %%ecx;"
            "COMPARE:;"
            "movl 0(%%esi,%%edx,1), %%eax;"

                    // perform cmp
            "cmpb %%al,%%bl;"
            "je FOUND;"

            "addl $128, %%edx;"
            "loop COMPARE;"
            "movl $48, %%eax;"
            "movl $1, %%edx;"
            "jmp NEXT;"

            "FOUND:;" // found start
            "addl $2, %%edx;"
            "leal 0(%%esi,%%edx,1), %%esi;"
            // load row start address in si

            /*
            "movl (buffer_size), %%ecx;"
            "rep movsb;"    // cpy buffer size chars from si to di
            // di (buffer) now cointains whole row (si)

                //Look for and return position of new line char

            "subl (buffer_size), %%esi;"


            "movl $10, %%ebx;"
            "movl $0, %%edx;"
            "movl (buffer_size), %%ecx;"
            "COMPARE_NL:;"
            //"addl %%edx, %%esi;"
            "cld;"
            "lodsl;"
            "movl 0(%%esi,%%edx,1), %%eax;"
                    // perform cmp
            "cmpl %%eax,%%ebx;"
            "je EXIT;"
            "addl $1, %%edx;"

            "loop COMPARE_NL;"
            */
            "xorl %%eax, %%eax;"
            "movl $10, %%ebx;" // NL Char
            //"mov $0, %%edx;"
            "xorl %%edx, %%edx;"
            "COPY_DI:;"
            "cld;"
            "lodsb;" // si --> ax
            "cmpl %%eax, %%ebx;"
            "je EXIT;"
            "stosb;"
            "cmpl (buffer_size), %%edx;"
            "jge EXIT;"
            "addl $1, %%esi;"
            "addl $1, %%edx;"
            "jmp COPY_DI;"


            "NEXT:;"
            "movl $126, %%edx;"



            //"cld;"
            //"stosb;"
            //"movl $1, %%edx;"


            // ===== end handlers =====

            //done
            "EXIT:;"

            : "=d" (result),"=a" (test)
            : "a" (scancode), "D" (buffer)
            : "%ecx","%ebx","memory"
        );


	//vardump(scancode);
	//vardump(result);
	//write(1,buffer,result);

    if(ASM_DEBUG){
        vardump(scancode);
        vardump(result);
        vardump(test);
        printstr("Char: ");
        printstr(buffer);
        newline();
        newline();
    }







	return result;
}



