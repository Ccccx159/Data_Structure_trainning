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

#if defined(SEQUENCESTACK_TEST)
    test_SequenceStack_demo();
#endif

#if defined(LINKEDLISTSTACK_TEST)
    test_LinkedListStack_demo();
#endif

#if defined(LINEEDITOR_TEST)
    test_LineEditor_demo();
#endif

#if defined(HANOI_TEST)
    test_Hanoi_demo();
#endif

#if defined(EXPRESSION_TEST)
    test_Expression_demo();
#endif

#if defined(MAZE_TEST)
    test_Maze_demo();
#endif

    return 0;
}
