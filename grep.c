#include "mygrep_h.h"

void reset(){
	printf("\033[0m");
	return;
}

void bold()
{
	printf("\033[1m");
}

void cyan() {
	printf("\033[0;36m");
	return;
}

/* gives purple colour */
void purple() {
	printf("\033[0;35m");
	return;
}

/* gives green colour */
void green() {
	printf("\033[0;32m");
	return;
}

void red(){
	printf("\033[0;31m");
	return;
}

/* Initialises the linked list */
void init(lineList *l) {
	l -> head = NULL;
	l -> tail = NULL;
	return;
}

/* Reads a file */
void readFile(lineList *l, char *filename) {
	char ch, line[1024];
	int linenum = 0, i = 0;
	FILE *fp;
	fp = fopen(filename, "r");
	while(1) {
		ch = getc(fp);
		line[i++] = ch;
		if(ch == '\n') {
			line[i++] = '\0';
			append(l, line, linenum, i);
			i = 0;
			linenum++;
		}
		else if(ch == EOF) {
			line[i++] = '\0';
			append(l, line, linenum, i);
			break;
		}
	}
	
	return;
}

/* Appends a node */
void append(lineList *l, char *line, int linenum, int len) {
	node *nn;
	nn = (node *)malloc(sizeof(node));
	if(nn) {
		nn -> ptr = (char *)malloc(sizeof(char) * len);
		strcpy(nn -> ptr, line);
		nn -> linenum = linenum;
		nn -> next = NULL;
	}
	else {
		return;
	}
	if(l -> head == NULL) {
		l -> head = l -> tail = nn;
		return;
	}
	else {
		l -> tail -> next = nn;;
		l -> tail = nn;
	}
	return;
}

/* Searches the linked list for the given
 * key and prints the lines that contains
 * the key
 */

void search(lineList *l, char *key) {
	node *p = l -> head;
	int i = 0, j = 0;
	while(p) {
		i = 0;
		j = 0;
		while(p -> ptr[i]) {
			if(key[j] == '\0') {
				printLine(p, key);
				break;
			}
			if((p -> ptr[i]) == key[j]) {
				
				j++;
			}
			else if(j) {
				j = 0;
			}
			i++;
		}
		p = p -> next;
	}
	return;
}

void printLine(node *p, char *key) {
    int i = 0, j = 0; 
    int key_len = strlen(key);

    while (p->ptr[i]) {
        if (p->ptr[i] == key[j] ) {
            j++;
          
            if (j == key_len) {
                printf("\033[31m"); 
                bold();
                for (int k = i - j + 1; k <= i; k++) {
                    putchar(p->ptr[k]);
                }
                printf("\033[0m"); 
                j = 0;
            }
        } else {
       
            if (j > 0) {
                for (int k = i - j; k < i; k++) {
                    putchar(p->ptr[k]);
                }
                j = 0; 
            }
            
            putchar(p->ptr[i]);
        }
        i++;
    }
    if (j > 0) {
        for (int k = i - j; k < i; k++) {
            putchar(p->ptr[k]);
        }
    }

}



void printFile(lineList *l, char* key) {
    node *p = l->head;
    while (p) {
        printLine(p, key);
        p = p->next;
    }
}

int opt_c (lineList *l, char *key)
{
	int count = 0;
	node *p = l -> head;
	int i = 0, j = 0;
	while(p) {
		i = 0;
		j = 0;
		while(p -> ptr[i]) {
			if(key[j] == '\0') {
				count++;
				break;
			}
			if((p -> ptr[i]) == key[j]) {
				
				j++;
			}
			else if(j) {
				j = 0;
			}
			i++;
		}
		p = p -> next;
	}
	
	return count;
}

char uppercase(char ch)
{
	ch = toupper(ch);
	return ch;
}
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
void opt_i(lineList *l, char *key)
{
	node *p = l -> head;
	int i = 0, j = 0;
	
	while(p) {
	char lowerline[1024];
	 strcpy(lowerline,p->ptr); // create copy of line
		toLowerCase(lowerline);// covert entire line in lower case
		i = 0;
		j = 0;
		while(p->ptr[i]) {
			if(key[j] == '\0') {
				printLine_i(p, key);
				break;
			}
			if(lowerline[i] == key[j]) {
				
				j++;
			}
			
			else if(j) {
				j = 0;
			}
			i++;
		}
		p = p -> next;
		
	}
	return;
}

void printLine_i(node *p, char *key) {
    int i = 0, j = 0; 
    int key_len = strlen(key);

    while (p->ptr[i]) {
        if (p->ptr[i] == key[j] || p->ptr[i] == uppercase(key[j])) {
            j++;
          
            if (j == key_len) {
                printf("\033[31m"); 
                bold();
                for (int k = i - j + 1; k <= i; k++) {
                    putchar(p->ptr[k]);
                }
                printf("\033[0m"); 
                j = 0;
            }
        } else {
       
            if (j > 0) {
                for (int k = i - j; k < i; k++) {
                    putchar(p->ptr[k]);
                }
                j = 0; 
            }
            
            putchar(p->ptr[i]);
        }
        i++;
    }
    if (j > 0) {
        for (int k = i - j; k < i; k++) {
            putchar(p->ptr[k]);
        }
    }

}

bool containsPattern(char *line,  char *key) {
    return strstr(line, key) != NULL;
}

void opt_v(lineList *l, char *key) {
	node *p = l -> head;
	while(p) {
		
		if (!containsPattern(p->ptr, key)) { 
         
			if (p->ptr[strlen(p->ptr) - 1] != '\n') {
				printf("%s\n", p->ptr); // Manually add newline if missing
			} 
			else {
				printf("%s", p->ptr); // Already has newline
			}
        }
        p = p->next;
    
	}
	return;
}

void opt_w(lineList *l, char *key){
	node *p = l -> head;
	
	while(p) {
		 if (matchWholeWord(p->ptr, key)) {
          		  printLine(p, key); // Print the line if it matches
        	}
		
		p = p -> next;
	}

	return;
}

int matchWholeWord(const char *line, const char *pattern) {	  // Iterate through the line to check for word boundaries
  
    for (int i = 0; line[i] != '\0'; i++) {
        if (strncmp(&line[i], pattern, strlen(pattern)) == 0) {
            if ((i == 0 || isWordBoundary(line[i - 1])) && (line[i + strlen(pattern)] == '\0' || isWordBoundary(line[i + strlen(pattern)]))) {
                return 1; // Match found , eg printf(kdkf) int print ,,if we search for int , we get only int not printf 
            }
        }
    }
    return 0; // No match found
}

int isWordBoundary(char c) {
	 return !isalnum(c) && c != '_';	// is not alpha numeric and is not _ then return 1 , basically for tab and space
	 					// isalnum = is alpha numeric 
   
}

void opt_h(lineList *l, char *key) {
	node *p = l -> head;
	int i = 0, j = 0;
	while(p) {
		i = 0;
		j = 0;
		while(p -> ptr[i]) {
			if(key[j] == '\0') {
				printLine(p, key);
				break;
			}
			if((p -> ptr[i]) == key[j]) {
				
				j++;
			}
			else if(j) {
				j = 0;
			}
			i++;
		}
		p = p -> next;
	}
	return;
}

void opt_m(lineList *l, char *key,int max){
	node *p = l -> head;
	int i = 0, j = 0, matchcount = 0;
	while(p ) {
		i = 0;
		j = 0;
		while(p -> ptr[i]) {
			if(matchcount >= max)
		{
			break;
		}
			if(key[j] == '\0') {
				printLine(p, key);
				matchcount++;
				break;
			}
			if((p -> ptr[i]) == key[j]) {
				
				j++;
			}
			else if(j) {
				j = 0;
			}
			
			i++;
		}
		
		
		p = p -> next;
		
	}
	return;
}

void search_in_file(const char *filepath, const char *pattern) {
	FILE *file = fopen(filepath, "r");
	if (!file) {
		perror("Error opening file");
		return;
	}
	
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	while ((read = getline(&line, &len, file)) != -1) {
		if (strstr(line, pattern)) {
			purple();
			printf("%s : ", filepath);
			reset();
			highlight_pattern(line, pattern);
		}
	}
	free(line);
	fclose(file);
}

void search_in_directory(const char *dirpath, const char *pattern) {
	DIR *dir = opendir(dirpath);
	if (!dir) {
		perror("Error opening directory");
		return;
	}
	struct dirent *entry;
	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		char fullpath[1024];
		snprintf(fullpath, sizeof(fullpath), "%s/%s", dirpath, entry->d_name);
		struct stat path_stat;
		if (stat(fullpath, &path_stat) == -1) {
			perror("Error retrieving file info");
			continue;
	 	}
		if (S_ISDIR(path_stat.st_mode)) {
			search_in_directory(fullpath, pattern);
		}
		else if (S_ISREG(path_stat.st_mode)) {
			search_in_file(fullpath, pattern);
		}
	}

	closedir(dir);
}



void highlight_pattern(const char *line, const char *pattern) {
	const char *pos = line;
	while ((pos = strstr(pos, pattern)) != NULL) {
		fwrite(line, 1, pos - line, stdout);
		red();
		printf( "%s" , pattern);
		reset();
		pos += strlen(pattern);
		line = pos;
	}
	printf("%s", line);
}

int checkFileOrDirectory(char *path) {
	struct stat stats;
	
	if(stat(path, &stats) == -1) {
		perror("stat failed");
		return -1;
	}
	if(S_ISREG(stats.st_mode)) {
		return 1;
	}
	else if(S_ISDIR(stats.st_mode)) {
		return 0;
	}
	return -1;
}

void readDirectory(lineList *l, char *path) {
	struct dirent *entry;
	struct stat stats;
	DIR *dir;
	dir = opendir(path);
	if(dir == NULL) {
		perror("opendir failed");
		return;
	}
	
	while((entry = readdir(dir))) {
		// Construct the full path for stat
        	char fullpath[1024];
        	snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

		// Get file attributes
		if(stat(fullpath, &stats) == -1) {
			perror("stat");
		    	continue;
		}

		// Check if it is a file or directory
		if(S_ISREG(stats.st_mode)) {
			readFile(l, fullpath);
		}
		else if(S_ISDIR(stats.st_mode)) {
			readDirectory(l, fullpath);
		}
		else {
		    	printf("Other: %s\n", entry->d_name);
		}
	}
	closedir(dir);
	return;
}

/* For -H option */
void hOption(lineList *l, char *key, char *filename) {
	
	searchForHOption(l, key, filename);
	return;
}

/*void readFileForRecursiveOption(lineList *l, char *path) {
	char ch, line[1024];
	int linenum = 0, i = 0, result;
	FILE *fp;
	fp = fopen(filename, "r");
	if(fp == NULL) {
		perror("fopen failed");
		return;
	}
	while(1) {
		ch = getc(fp);
		line[i++] = ch;
		if(ch == '\n') {
			line[i++] = '\0';
			append(l, line, linenum, i);
			i = 0;
			linenum++;
		}
		else if(ch == EOF) {
			line[i++] = '\0';
			append(l, line, linenum, i);
			break;
		}
	}
	return;
}*/

/* For -q option */
int qOption(lineList *l, char *path, char *key) {
	int found;
	readFile(l, path);
	found = searchForQOption(l, key);
	return found;
}

/* Searches the linked list for the given
 * key and returns 1 if the key is found
 * and returns 0 if the key is not found
 */
int searchForQOption(lineList *l, char *key) {
	node *p = l -> head;
	int i = 0, j = 0;
	while(p) {
		i = 0;
		j = 0;
		while(p -> ptr[i]) {
			if(key[j] == '\0') {
				return 1;
			}
			if((p -> ptr[i]) == key[j]) {
				j++;
			}
			else if(j) {
				j = 0;
			}
			i++;
		}
		p = p -> next;
	}
	return 0;
}

/* Searches the linked list for the given
 * key and prints the lines that contains
 * the key along with the filename
 */
void searchForHOption(lineList *l, char *key, char *filename) {
	node *p = l -> head;
	int i = 0, j = 0;
	while(p) {
		i = 0;
		j = 0;
		while(p -> ptr[i]) {
			if(key[j] == '\0') {
				purple();
				printf("%s", filename);
				reset();
				cyan();
				printf(":");
				reset();
				printLine(p, key);
				break;
			}
			if((p -> ptr[i]) == key[j]) {
				j++;
			}
			else if(j) {
				j = 0;
			}
			i++;
		}
		p = p -> next;
	}
	return;
}

/* For -b option */
void bOption(lineList *l, char *key, char *filename) {
	searchForbOption(l,key,filename);
	return;
}

/* Searches the linked list for the given
 * key and prints the lines that contains
 * the key along with the byte offset of
 * each line
 */
void searchForbOption(lineList *l, char *key, char *filename) {
	node *p = l -> head;
	int i = 0, j = 0, offset = 0;
	while(p) {
		i = 0;
		j = 0;
		while(p -> ptr[i]) {
			if(key[j] == '\0') {
				offset = byteOffset(filename, p -> linenum);
				green();
				printf("%d", offset);
				reset();
				cyan();
				printf(":");
				reset();
				printLine(p, key);
				break;
			}
			if((p -> ptr[i]) == key[j]) {
				j++;
			}
			else if(j) {
				j = 0;
			}
			i++;
		}
		p = p -> next;
	}
	return;
}

/* returns the byte offset of the line */
int byteOffset(char *filename, int linenum) {
	int offset = 0, i = 0;
	char ch;
	FILE *fp;
	fp = fopen(filename, "r");
	while(i < linenum) {
		ch = getc(fp);
		if(ch == '\n') {
			i++;
		}
		offset++;
	}
	fclose(fp);
	return offset;
}

/* For -e option */
void eOption(lineList *l, char *argv[], char *filename, int argc) {
	readFile(l, filename);
	searchForeOption(l, argv, argc);
	return;
}

/* Searches the linked list for the given
 * key(s) from the arguments on the command
 * line and prints the lines that contains
 * the key(s)
 */
void searchForeOption(lineList *l, char *argv[], int argc) {
	node *p = l -> head;
	int i = 0, j = 0, k = 1, len = 0, print = 0;
	char key[64];
	int indices[32];
	while(p) {
		k = 1;
		print = 0;
		while(k < argc) {	
			if((strcmp("-e", argv[k]) == 0) && (k + 1 < argc)) {
				k++;
				strcpy(key, argv[k]);
			}
			i = 0;
			j = 0;
			len = 0;
			while(p -> ptr[i]) {
				if(key[j] == '\0') {
					indices[len++] = i - j;
					indices[len++] = i;
					print = 1;
					break;
				}
				if((p -> ptr[i]) == key[j]) {
					j++;
				}
				else if(j) {
					j = 0;
				}
				i++;
			}
			k++;
		}
		if(print == 1) {
			bubbleSort(indices, len);
			printLineForeOption(p, indices);
		}
		p = p -> next;
	}
	return;
}

/* sorts an array using bubble sort */
void bubbleSort(int *arr, int len) {
	int i = 0, j = 0, temp = 0, swapped = 0;
	for(i = 0; i < len - 1; i++) {
		swapped = 0;
		for(j = 0; j < len - i - 1; j++) {
			if(arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				if(swapped == 0) {
					swapped = 1;
				}
			}
		}
		if(swapped == 0) {
			break;
		}
	}
	return;
}

/* prints a line for -e option */
void printLineForeOption(node *p, int indices[]) {
	int i = 0, j = 0;
	while(p -> ptr[i]) {
		if(i == indices[j]) {
			red();
			while(i != indices[j + 1]) {
				putchar(p -> ptr[i]);
				i++;
			}
			reset();
			j = j + 2;
		}
		else {
			putchar(p -> ptr[i]);
			i++;
		}
	}
	return;
}

/* For -f option */
void fOption(lineList *l, char *keys[], char *filename, char *patternsfile) {
	int numkeys = 0;
	readFile(l, filename);
	numkeys = readPatterns(keys, patternsfile);
	searchForfOption(l, keys, numkeys);
	return;
}

/* reads patterns from file */
int readPatterns(char *keys[], char *patternsfile) {
	char ch, key[256];
	int i = 0, j = 0;
	FILE *fp;
	fp = fopen(patternsfile, "r");
	while((ch = getc(fp)) != EOF) {
		if(ch == '\n') {
			key[i] = '\0';
			keys[j] = (char *)malloc(i + 1);
			strcpy(keys[j++], key);
			i = 0;
		}
		else {
			key[i++] = ch;		
		}
	}
	fclose(fp);
	return j;
}

/* Searches the linked list for the given
 * key(s) and prints the lines that contains
 * the key(s)
 */
void searchForfOption(lineList *l, char *keys[], int numkeys) {
	node *p = l -> head;
	int i = 0, j = 0, k = 0, len = 0, print = 0;
	char key[64];
	int indices[32];
	while(p) {
		k = 0;
		print = 0;
		while(k < numkeys) {	
			i = 0;
			j = 0;
			len = 0;
			strcpy(key, keys[k]);
			while(p -> ptr[i]) {
				if(key[j] == '\0') {
					indices[len++] = i - j;
					indices[len++] = i;
					print = 1;
					break;
				}
				if((p -> ptr[i]) == key[j]) {
					j++;
				}
				else if(j) {
					j = 0;
				}
				i++;
			}
			k++;
		}
		if(print == 1) {
			bubbleSort(indices, len);
			printLineForfOption(p, indices);
		}
		p = p -> next;
	}
	return;
}

/* prints a line for -f option */
void printLineForfOption(node *p, int indices[]) {
	int i = 0, j = 0;
	while(p -> ptr[i]) {
		if(i == indices[j]) {
			red();
			while(i != indices[j + 1]) {
				putchar(p -> ptr[i]);
				i++;
			}
			reset();
			j = j + 2;
		}
		else {
			putchar(p -> ptr[i]);
			i++;
		}
	}
	return;
}

