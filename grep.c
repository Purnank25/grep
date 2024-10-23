#include "grep.h"

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
				printLine(p);
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

/* Prints a line */
void printLine(node *p) {
	int i = 0;
	while(p -> ptr[i]) {
		putchar(p -> ptr[i++]);
	}
	return;
}

/* Prints the contents of the file */
void printFile(lineList *l) {
	int i = 0;
	char ch;
	node *p = l -> head;
	while(p) {
		while(1) {
			ch = p -> ptr[i++];
			if(ch == '\0') {
				i = 0;
				break;
			}
			else if(ch == EOF) {
				break;
			}
			else {
				putchar(ch);
			}
		}
		p = p -> next;
	}
	return;
}
