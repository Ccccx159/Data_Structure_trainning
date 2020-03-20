#include "01_Exordium/demo_func.h"

int main(int argc, char *argv[]) {
    
#if defined(SEQUENCELIST_TEST)
    test_SequenceList_demo();
#elif defined(SINGLYLINKEDLIST_TEST)
    test_SinglyLinkedList_demo();
#endif

    return 0;
}
