#define UTIL_IMPLEMENTATION
#include "utils.h"
#include "scan.h"
#include <fcntl.h>


#define BUFFER_SIZE 128
#define DEBUG 0



int main(int argc, char *argv[])
{

	char buffer[BUFFER_SIZE];
	char scancodes_filename[BUFFER_SIZE];
	char buffer1[BUFFER_SIZE];
	char sc_buffer[BUFFER_SIZE];
    int scancodes[BUFFER_SIZE];
    int scancodes_num;
    int len;

	printstr("Domaci 1\n");
	/* ucitavanje podesavanja */
	printstr("Ucitavanje podesavanja\n");
	load_config("scancodes.tbl","ctrl.map");

    /* ucitavanjje scancodes (test) fajla*/
    printstr("Unesite ime scancodes (test) fajla:\n");
    len = read(0,buffer,BUFFER_SIZE);

    if(DEBUG){
        newline();
        printstr("Ime fajla: \n");
        printstr(buffer);
        newline();
    }

    int fd = open("test1.tst", O_RDONLY);
	if(fd == -1)
	{
		printerr("Fajl neuspesno otvoren!\n");
		_exit(1);
	} else {
		printstr("Test fajl ucitan\n");
	}
    // conversion to int
    int i = 0;
    int x;

    for(i;i<BUFFER_SIZE;i++){
        buffer[0] = 0;
        len = fgets(buffer, BUFFER_SIZE, fd);
        x = atoi(buffer);
        scancodes[i] = x;
        buffer[0] = 0;
        if(x != 400){
            sc_buffer[0] = 0;
            int result = process_scancode(x,sc_buffer);
            write(1,sc_buffer,result);
        }
        if(x == 400){
            if(DEBUG){
                newline();
                printstr("Stopped at:");
                len = itoa(i,buffer1);
                printstr(buffer1);
                newline();
                scancodes_num = i;
            }

            break;
        }
    }



	/* ponavljamo: */
		/* ucitavanje i otvaranje test fajla */
		/* parsiranje fajla, obrada scanecodova, ispis */
    close(fd);
	_exit(0);
}

