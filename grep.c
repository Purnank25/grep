#include "grep.h"


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
        if (p->ptr[i] == key[j]) {
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

    printf("\n"); 
}



void printFile(lineList *l, char* key) {
    node *p = l->head;
    while (p) {
        printLine(p, key);
        p = p->next;
    }
}

