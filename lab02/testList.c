#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "DLList.h"
/** Testing insert before and after 
 * assert length and expected current value**/
void test1 (DLList myList);

/** Testing delete **/
void test2 (DLList myList);

/** Prints entire List in a certain format**/
void printList (DLList myList);

/** Tests from lab parther Farhan z5199861 **/
void test_Farhan (DLList myList);

int main (void)
{
    DLList myList = getDLList (stdin);
    test1(myList);
    test_Farhan(myList);
    test2(myList);
    DLListDelete(myList);
    printList(myList);
    assert(validDLList(myList));
    freeDLList (myList);
    return EXIT_SUCCESS;
}
/** Testing insert before and after 
 * assert length and expected current value**/
void test1 (DLList myList){
    
    size_t initialLength = DLListLength(myList);
    assert(validDLList (myList));
    char *a = "AAA";    // 1sr string
    char *b = "BBB";    // 2nd string
    char *c = "CCC";    // 3rd string

    printf("Showing the list before operations\n");
    printf("Current-> %s\n",DLListCurrent(myList));
    printf("nItem is %d\n",(int)DLListLength(myList));
    printList(myList);
    
    printf("Moving Current halfway (%d)\n",(int)(initialLength/2));
    DLListMove(myList, (int)(initialLength/2)); // Moves curr mid-list
    printf("Current-> %s\n",DLListCurrent(myList));
    printf("Insert a string %s after curr\n",a);
    DLListAfter(myList, a); // Inserts first string
    assert(DLListLength(myList) == initialLength + 1); // Check for correct length
    assert(validDLList(myList));
    printList(myList);

    printf("Current after 1st insertion-> %s\n",DLListCurrent(myList));    
    printf("Moving current forward 1 node\n");
    DLListMove(myList,1); // Move 1 node
    printf("Doing 3 insertions\n");
    DLListAfter(myList, a);
    printf("Current-> %s\n",DLListCurrent(myList));
    assert(DLListLength(myList)==initialLength+2);
    DLListAfter(myList, b);
    printf("Current-> %s\n",DLListCurrent(myList));
    assert(DLListLength(myList)==initialLength+3);
    DLListAfter(myList, c);
    printf("Current-> %s\n",DLListCurrent(myList));
    assert(DLListLength(myList)==initialLength+4);
    printList(myList);
    assert(strcmp(DLListCurrent(myList),c)==0);

    printf("Move back to first and insert %s at the beginning\n",b);
    DLListMoveTo(myList,1);
    DLListBefore(myList,b);
    assert(DLListLength(myList)==initialLength+5);
    assert(strcmp(DLListCurrent(myList),b)==0);
    printf("Current-> %s\n",DLListCurrent(myList));
    assert(validDLList(myList));
    printList(myList);
    printf("Moving Current halfway (%d)\n",(int)(DLListLength(myList)/2));
    DLListMove(myList,(int)(DLListLength(myList)/2));
    printf("Adding 'a line of text' before and after current\n");
    DLListBefore(myList, "a line of text");
    DLListMove(myList,1);
    DLListAfter(myList, "a line of text");
    DLListMove(myList,-2);
    assert(strcmp(DLListCurrent(myList),"a line of text")==0);
    printList(myList);
    printf("nItem is %d\n",(int)DLListLength(myList));
    assert(validDLList(myList));
    printf("\nTest 1 Completed\n");
}

/** Testing delete **/
void test2 (DLList myList) {
    
    printf("Starting test 2\n");
    printList(myList);
    assert(validDLList(myList));
    printf("Current is '%s' and size is %d\n", DLListCurrent(myList), (int)DLListLength(myList));

    //Delete last and then first until the list is empty;
    //And print the list at the end of every loop
    while((int)DLListLength(myList)!=0) {
        assert(!DLListIsEmpty(myList));
        DLListMoveTo(myList,(int)DLListLength(myList));
        DLListDelete(myList);
        assert(validDLList(myList));
        DLListMoveTo(myList,1);
        DLListDelete(myList);
        assert(validDLList(myList));
        printList(myList);
    }
    assert(validDLList(myList));
    assert(DLListIsEmpty(myList));
    printf("\nTest 2 Completed\n");
}

/** Prints entire List in a certain format**/
void printList (DLList myList) {
    printf("\n------\n");
    putDLList (stdout, myList);
    printf("------\n\n");
}

/** Tests from lab parther Farhan z5199861 **/
void test_Farhan (DLList myList) {

    size_t initial_size = DLListLength(myList);
    
    printf("----------\n");
    printf("TEST 1 - DLListBefore - Insert before head of list\n");
    
    printf("----------\n");    
    DLListBefore(myList , "NEW LINE BEFORE CURRENT HEAD");
    assert(validDLList (myList));
    putDLList(stdout , myList);
    printf("----------\n");
    
    printf("TEST 2 - Remove head of list\n");
    
    printf("----------\n");
    DLListDelete(myList);
    assert(validDLList (myList));
    putDLList(stdout , myList);
    size_t new_size = DLListLength(myList);
    assert(initial_size == new_size);
    printf("----------\n");
    
    printf("TEST 3 - Remove node between head and tail of list\n");
    
    printf("----------\n");
    DLListMove(myList , 3);
    DLListDelete(myList);
    new_size = DLListLength(myList);
    assert(initial_size == new_size + 1);
    assert(validDLList (myList));
    putDLList(stdout , myList);
    printf("----------\n");
    
    printf("TEST 4 - DLListAfter - Insert in front of new current after pervious delete\n");
    
    printf("----------\n");
    DLListAfter(myList , "NEW LINE AFTER DELETE");
    assert(validDLList (myList));
    putDLList(stdout , myList);
    printf("----------\n");
    
    printf("TEST 5 - DLListAfter - Insert in front of tail of list\n");
    
    printf("----------\n");
    new_size = DLListLength(myList);
    DLListMove(myList , (int) new_size);
    DLListAfter(myList , "NEW LINE AT END");
    assert(validDLList (myList));
    putDLList(stdout , myList);
    printf("----------\n");
    
    printf("TEST 6 - Remove tail of list\n");
    
    printf("----------\n");
    DLListMove(myList , (int)new_size);
    DLListDelete(myList);
    assert(validDLList (myList));
    putDLList(stdout , myList);
    new_size = DLListLength(myList);
    assert(initial_size == new_size);
    printf("----------\n");
}
