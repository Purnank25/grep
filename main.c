#include "grep.h"
int main(int argc, char *argv[]) {
	lineList l;
	init(&l);
	readFile(&l, argv[2]);
	search(&l, argv[1]);
	return 0;
}
