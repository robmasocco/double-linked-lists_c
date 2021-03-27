/* Roberto Masocco
 * Creation date: 31/7/2018
 * Latest version: 21/8/2019
 * ----------------------------------------------------------------------------
 * This file contains the implementation of all the methods to apply to
 * double linked lists. What each method does and how is explained in the
 * comments.
 */
/* This code is released under the MIT license.
 * See the attached LICENSE file.
 */

#include <stdlib.h>
#include "doubleLinkedList.h"

/* Creates a new record in the heap with the given data. */
Record *createRecord(void *newData) {
    Record *rec = (Record *)malloc(sizeof(Record));
    if (rec == (Record *)NULL) return NULL;  // malloc failed.
    rec->next = NULL;
    rec->prev = NULL;
    rec->recData = newData;
    return rec;
}

/* Creates a new Double Linked List. */
DLList *createDLList(void) {
    DLList *newList = (DLList *)malloc(sizeof(DLList));
    if (newList == (DLList *)NULL) return NULL;  // malloc failed.
    newList->first = NULL;
    newList->last = NULL;
    newList->recsCount = 0;
    return newList;
}

/* Releases memory for a given record. */
void eraseRecord(Record *rec) {
    free(rec);
}

/* Releases memory for a given DLList. */
void eraseList(DLList *list) {
    Record *curr = list->first;
    Record *currNext;
    while (curr != NULL) {
        currNext = curr->next;
        eraseRecord(curr);
        curr = currNext;
    }
    free(list);
}

/* As above, but also frees record data if they had been malloc'ed. */
void eraseListAndEntries(DLList *list) {
    Record *curr = list->first;
    Record *currNext;
    while (curr != NULL) {
        currNext = curr->next;
        free(curr->recData);
        eraseRecord(curr);
        curr = currNext;
    }
    free(list);
}

/* Tells if a given DLList is empty or not. */
int isListEmpty(DLList *list) {
    if (list->recsCount > 0) return 0;
    return 1;
}

/* Searches for a specific record in the list, given the data. */
Record *search(void *data, DLList *list) {
    Record *curr = list->first;
    while (curr != NULL)
        if (curr->recData == data) return curr;
        else curr = curr->next;
    return NULL;
}

/* Searches for a specific record in the list and detaches it. */
Record *searchAndPop(void *data, DLList *list) {
    return popRecord(search(data, list), list);
}

/* Detaches a given record from the list. */
Record *popRecord(Record *toPop, DLList *list) {
    if ((toPop == NULL) || (list == NULL)) return NULL;
    if (toPop == list->first) return popFirstRecord(list);
    if (toPop == list->last) return popLastRecord(list);
    toPop->prev->next = toPop->next;
    toPop->next->prev = toPop->prev;
    toPop->next = NULL;
    toPop->prev = NULL;
    list->recsCount--;
    return toPop;
}

/* Adds a new record to a list as the first. */
Record *addAsFirst(void *data, DLList *list) {
    if (list == NULL) return NULL;
    Record *newRec = createRecord(data);
    if (newRec == NULL) return NULL;  // malloc failed.
    addAsFirstRecord(newRec, list);
    return newRec;
}

/* Adds an existing record to a list as the first. */
Record *addAsFirstRecord(Record *newRec, DLList *list) {
    if ((newRec == NULL) || (list == NULL)) return NULL;
    if (!isListEmpty(list)) {
        list->first->prev = newRec;
        newRec->next = list->first;
    } else list->last = newRec;
    list->first = newRec;
    list->recsCount++;
    return newRec;
}

/* Adds a new record to the list as the last. */
Record *addAsLast(void *data, DLList *list) {
    if (list == NULL) return NULL;
    Record *newRec = createRecord(data);
    if (newRec == NULL) return NULL;  // malloc failed.
    addAsLastRecord(newRec, list);
    return newRec;
}

/* Adds an existing record to the list as the last. */
Record *addAsLastRecord(Record *newRec, DLList *list) {
    if ((newRec == NULL) || (list == NULL)) return NULL;
    if (!isListEmpty(list)) {
        list->last->next = newRec;
        newRec->prev = list->last;
    } else list->first = newRec;
    list->last = newRec;
    list->recsCount++;
    return newRec;
}

/* Returns the data in the first record of the list. */
void *getFirst(DLList *list) {
    return list->first->recData;
}

/* Returns the data in the last record of the list. */
void *getLast(DLList *list) {
    return list->last->recData;
}

/* Pops and returns the first record of the list. */
Record *popFirstRecord(DLList *list) {
    Record *rec;
    // If the list is empty...
    if (isListEmpty(list)) return NULL;
    // If the list has only one element...
    if (list->first == list->last) {
        rec = list->first;
        list->first = NULL;
        list->last = NULL;
        list->recsCount--;
        return rec;
    }
    // If the list has two or more elements...
    rec = list->first;
    list->first = rec->next;
    list->first->prev = NULL;
    rec->next = NULL;
    list->recsCount--;
    return rec;
}

/* Pops and returns the last record of the list. */
Record *popLastRecord(DLList *list) {
    Record *rec;
    // If the list is empty...
    if (isListEmpty(list)) return NULL;
    // If the list has only one element...
    if (list->first == list->last) {
        rec = list->first;
        list->first = NULL;
        list->last = NULL;
        list->recsCount--;
        return rec;
    }
    // If the list has two or more elements...
    rec = list->last;
    list->last = rec->prev;
    list->last->next = NULL;
    rec->prev = NULL;
    list->recsCount--;
    return rec;
}

/* Pops the first record of the list and returns its data. */
void *popFirst(DLList *list) {
    if (isListEmpty(list)) return NULL;
    Record *rec = popFirstRecord(list);
    void *data = rec->recData;
    eraseRecord(rec);
    return data;
}

/* Pops the last record of the list and returns its data. */
void *popLast(DLList *list) {
    if (isListEmpty(list)) return NULL;
    Record *rec = popLastRecord(list);
    void *data = rec->recData;
    eraseRecord(rec);
    return data;
}

/* Inserts an element before a specified one. Useful to keep the list sorted. */
Record *insertBefore(void *data, Record *nextOne, DLList *list) {
    // Check for erroneous call.
    if (nextOne->prev == NULL) {
        return addAsFirst(data, list);
    } else {
        // Create a new record.
        Record *newRec = createRecord(data);
        if (newRec == NULL) return NULL;  // malloc failed.
        // Add it to the list accordingly.
        nextOne->prev->next = newRec;
        newRec->prev = nextOne->prev;
        nextOne->prev = newRec;
        newRec->next = nextOne;
        list->recsCount++;
        return newRec;
    }
}
