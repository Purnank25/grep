#include "mygrep_h.h"

int main(int argc, char *argv[]) {
	lineList l;
	init(&l);
	int found = 0;
	char *keys[16];
	for(int i = 0; i < 16; i++) {
		keys[i] = NULL;
	}
	readFile(&l, argv[2]);
	 char *pattern = NULL;
	char opt;
	int max_count = 0;
  	char arr[12];
	enum options(r = 1, i,v,f,w,c,m,b,q,H,h,e);
     
	while ((opt = getopt(argc, argv, "rivf:wcm:bqHhe:")) != -1) {
        switch (opt) {
            case 'r': // Recursive
                 search_in_directory(argv[2], argv[1]);	//done	./mygrep quick ~/Desktop -r
                break;
            case 'i': // Ignore case
                opt_i(&l, argv[1]);	//done
                break;
            case 'v': // Invert match
                opt_v(&l, argv[1]);	//done
                break;
           case 'f': //pattern r in file
           	{
            	    fOption(&l, keys, argv[2], argv[1]);	//pending
			for(int i = 0; i < 16; i++) {
    			free(keys[i]);
		}
	
                break;
                }
          case 'w': // Match whole words
                opt_w(&l, argv[1]);	//done
                break;
          case 'c':
         	 { // Count matching lines
                int c = opt_c(&l , argv[1]);
                printf("%d\n",c);		//done
                break;
                }
            case 'm': // Maximum count
                max_count = atoi(optarg);
                opt_m(&l,argv[1], max_count);	//done
                break;
	    case 'b': // Byte offset
                bOption(&l, argv[1], argv[2]);	//done
                break;
            case 'q': // Quiet
                found = qOption(&l, argv[2], argv[1]);	//done
                printf("%d\n", found);	 
                break;
            case 'H': // Print with filename
                hOption(&l, argv[1], argv[2]);	//done
                break;
            case 'h': // Suppress filename
                opt_h(&l,argv[1]);	//done
                break;
           case 'e': // Regular expression
               eOption(&l, argv, argv[5], argc);	//pending
                break;
            default: // Invalid option
                fprintf(stderr, "Usage: %s [-r] [-i] [-v] [-f FILE] [-w] [-c] [-m NUM] [-b] [-q] [-H] [-h] [-e PATTERN]\n", argv[0]);
                exit(EXIT_FAILURE);
      }
    }
	if((opt = getopt(argc, argv, "rivf:wcm:bqHhe:")) == -1) // if no option is given
		search(&l, argv[1]);
    // Handle remaining non-option arguments
     // After options, the next argument is the pattern
    if (optind < argc) {
        pattern = argv[optind++];
    } else {
        fprintf(stderr, "Error: Pattern not provided.\n");
        exit(EXIT_FAILURE);
    }

    // Remaining arguments are the file names
 /*   while (optind < argc) {
        printf("File: %s\n", argv[optind++]);
    }*/
return 0;	
}

