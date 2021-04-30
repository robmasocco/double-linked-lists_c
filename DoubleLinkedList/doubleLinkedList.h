/* Roberto Masocco
 * Creation date: 31/7/2018
 * Latest version: 12/10/2020
 * ----------------------------------------------------------------------------
 * This file contains type definition and declaration for the "Double Linked
 * List" data structure. Methods are in the associated library.
 * Lists and data are dynamically allocated in the heap using the malloc
 * library, so remember to free everything (wrappers for this are included).
 * These lists are made to store whatever you want, as long as such contents
 * are at most 64-bits wide.
 * This implementation requires the C standard library (stdlib.h).
 */
/* This code is released under the MIT license.
 * See the attached LICENSE file.
 */

#ifndef DLLIST_H
#define DLLIST_H

/* Record (entry) for a DLList. */
typedef struct _record {
    struct _record *prev;    // Pointer to previous record.
    struct _record *next;    // Pointer to next record.
    void *recData;           // Actual data stored in the record.
} Record;

/* Double Linked List. Stores key pointers and information. */
typedef struct _dlList {
    Record *first;           // Pointer to first record.
    Record *last;            // Pointer to last record.
    unsigned long int recsCount;  // Number of records in the list (length).
} DLList;

/* Functions in the library (see other file). */
Record *createRecord(void *newData);
DLList *createDLList(void);
void eraseRecord(Record *rec);
void eraseList(DLList *list);
void eraseListAndEntries(DLList *list);
Record *search(void *data, DLList *list);
Record *searchAndPop(void *data, DLList *list);
Record *popRecord(Record *toPop, DLList *list);
int isListEmpty(DLList *list);
Record *addAsFirst(void *data, DLList *list);
Record *addAsLast(void *data, DLList *list);
Record *addAsFirstRecord(Record *newRec, DLList *list);
Record *addAsLastRecord(Record *newRec, DLList *list);
Record *insertBefore(void *data, Record *nextOne, DLList *list);
void *getFirst(DLList *list);
void *getLast(DLList *list);
Record *popFirstRecord(DLList *list);
Record *popLastRecord(DLList *list);
void *popFirst(DLList *list);
void *popLast(DLList *list);

#endif
