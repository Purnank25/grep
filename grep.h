/* Grep
 *
 * The grep command in Linux is a powerful text-searching utility that 
 * stands for "Global Regular Expression Print." It is used to search 
 * for specific patterns within files or input text and print lines 
 * that match those patterns.
 *
 * Our implementation is limited to the following in-line options:
 * -r, --recursive	     recursively searches directories and subdirectories 
 *			     for pattern
 * -i, --ignore-case	     ignore case distinctions in patterns and data
 * -v, --invert-match        select non-matching lines
 * -f, --file=FILE           take PATTERNS from FILE
 * -w, --word-regexp         match only whole words
 * -c, --count               print only a count of selected lines per FILE
 * -m, --max-count=NUM       stop after NUM selected lines
 * -b, --byte-offset         print the byte offset with output lines
 * -q, --quiet, --silent     suppress all normal output
 * -H, --with-filename       print file name with output lines
 * -h, --no-filename         suppress the file name prefix on output
 * -e, --regexp=PATTERNS     use PATTERNS for matching
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

