#define UTIL_IMPLEMENTATION
#include "utils.h"
#include "scan.h"

#define BUFFER_SIZE 13

int main(int argc, char *argv[])
{

	char buffer[BUFFER_SIZE];

	printstr("Domaci 1\n");
	/* ucitavanje podesavanja */
	printstr("Ucitavanje podesavanja\n");
	load_config("scancodes.tbl","ctrl.map");

	/* ponavljamo: */
		/* ucitavanje i otvaranje test fajla */
		/* parsiranje fajla, obrada scanecodova, ispis */
	_exit(0);
}

