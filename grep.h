/* Grep
 *
 * The grep command in Linux is a powerful text-searching utility that 
 * stands for "Global Regular Expression Print." It is used to search 
 * for specific patterns within files or input text and print lines 
 * that match those patterns.
 
 5 remaining 7 done
 
 *
 * Our implementation is limited to the following in-line options:
 * -r, --recursive	     recursively searches directories and subdirectories 
 *			     for pattern
 * -i, --ignore-case	     ignore case distinctions in patterns and data	//done
 * -v, --invert-match        select non-matching lines				//done
 * -f, --file=FILE           take PATTERNS from FILE
 * -w, --word-regexp         match only whole words				//done
 * -c, --count               print only a count of selected lines per FILE  // done
 * -m, --max-count=NUM       stop after NUM selected lines			// almost done , only extracting max count from terminal is pending
 * -b, --byte-offset         print the byte offset with output lines
 * -q, --quiet, --silent     suppress all normal output			// done
 * -H, --with-filename       print file name with output lines		// done
 * -h, --no-filename         suppress the file name prefix on output	//done
 * -e, --regexp=PATTERNS     use PATTERNS for matching					// multiple pattern passing
 *
 * Implementation: 
 * Firstly, we have to store the lines of the files that are given as 
 * arguments. To store these lines, we have used a linked list representation.
 * Then, we searched for the key in the lines and printed those lines.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>

typedef struct node {
	char *ptr;
	int linenum;
	struct node *next;
} node;

typedef struct lineList {
	node *head;
	node *tail;
} lineList;

void red(); // give red colour

void purple();

void reset();

/* Initialises the linked list */
void init(lineList *l);

/* Reads a file */
void readFile(lineList *l, char *filename);

/* Appends a node */
void append(lineList *l, char *line, int linenum, int len);

/* Searches the linked list for the given
 * key and prints the lines that contains
 * the key
 */
void search(lineList *l, char *key);

/* Prints a line */
void printLine(node *p , char* key);

/* Prints the contents of the file */
void printFile(lineList *l, char *key);

int opt_c (lineList *l, char *key);

//void opt_b(lineList *l, char *key, char *filename);

char uppercase(char ch);

void toLowerCase(char *str) ;

void opt_i(lineList *l, char *key);

void printLine_i(node *p, char *key);

void opt_v(lineList *l, char *key);

bool containsPattern (char *line,  char *key) ;

void opt_w(lineList *l, char *key);

int matchWholeWord(const char *line, const char *pattern);

int isWordBoundary(char c) ;

void opt_h(lineList *l, char *key);

void opt_m(lineList *l, char *key,int max);

void search_in_directory(const char *dirpath, const char *pattern);

void search_in_file(const char *filepath, const char *pattern);

void highlight_pattern(const char *line, const char *pattern) ;

