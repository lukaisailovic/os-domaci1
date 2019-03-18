#define UTIL_IMPLEMENTATION
#include "utils.h"
#include "scan.h"
#include <fcntl.h>


#define BUFFER_SIZE 128
#define DEBUG 1

int main(int argc, char *argv[])
{

	char buffer[BUFFER_SIZE];
	char scancodes_filename[BUFFER_SIZE];
	char buffer1[BUFFER_SIZE];
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
    buffer[0] = 0;
    for(i;i<BUFFER_SIZE;i++){
        len = fgets(buffer, BUFFER_SIZE, fd);
        x = atoi(buffer);
        scancodes[i] = x;
        if(x == 400){
            if(DEBUG){
                printstr("Stopped at:");
                len = itoa(i,buffer1);
                printstr(buffer1);
                newline();
            }
            scancodes_num = i;
            break;

        }
    }

    if(DEBUG){
        printstr("Scancodes:\n");
        i = 0;
        for(i;i<scancodes_num;i++){
            len = itoa(scancodes[i],buffer1);
            printstr(buffer1);
            printstr(" ");
        }
    }


	/* ponavljamo: */
		/* ucitavanje i otvaranje test fajla */
		/* parsiranje fajla, obrada scanecodova, ispis */
	_exit(0);
}

