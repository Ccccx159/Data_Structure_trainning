#include "01_Exordium/demo_func.h"

int main(int argc, char *argv[]) {
    
#if defined(SEQUENCELIST_TEST)
    test_SequenceList_demo();
#endif

#if defined(SINGLYLINKEDLIST_TEST)
    test_SinglyLinkedList_demo();
#endif

#if defined(DUALCYCLELINKEDLIST_TEST)
    test_DualCycleLinkedList_demo();
#endif

    return 0;
}
