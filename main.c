#include "grep.h"
int main(int argc, char *argv[]) {
	lineList l;
	init(&l);
	readFile(&l, argv[2]);
	search(&l, argv[1]); // normal search 
	//int count = opt_c(&l , argv[1]); // -c option
	//opt_b(&l , argv[1],argv[2]); 
	//printf("%d\n", count);
	
	//opt_i(&l, argv[1]); 
	//opt_v(&l, argv[1]); 
	//opt_w(&l,argv[1]);
	//opt_h(&l,argv[1]);
	//opt_m(&l,argv[1], 70);
	  search_in_directory(argv[2], argv[1]);
	return 0;
}
