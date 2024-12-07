#include "grep.h"

void purple(){
	printf("\033[0;35m");
	return;
}
void reset(){
	printf("\033[0m");
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
				
				break;
			}
			if((p -> ptr[i]) == key[j]) {
				count++;
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
		
		if (!containsPattern(p->ptr,key)) { // Line doesn't contain pattern
		    printf("%s",p->ptr); 
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
		
		if(matchcount > max)
		{
			break;
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
