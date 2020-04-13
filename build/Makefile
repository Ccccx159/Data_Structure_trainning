DIR_TRUNK := $(shell pwd)/..
DIR_SRCS := $(DIR_TRUNK)/src

GCC := gcc
CPP := g++

# head file path
CXXFLAGS := -Wno-unused-function -Wno-missing-declarations
CXXFLAGS += -I$(DIR_TRUNK)/inc
CXXFLAGS += -I$(DIR_TRUNK)/inc/01_Exordium

#common src file path
SRCS += $(DIR_SRCS)/01_Exordium/scanf_priv.cpp


ifeq ($(findstring sequence_list, $(func)), sequence_list)
CXXFLAGS += -DSEQUENCELIST_TEST
SRCS += $(DIR_SRCS)/02_LinearTable/01_SequenceList/SequenceList.cpp
SRCS += $(DIR_SRCS)/02_LinearTable/01_SequenceList/test_SequenceList_demo.cpp
endif

ifeq ($(findstring singlylinked_list, $(func)), singlylinked_list)
CXXFLAGS += -DSINGLYLINKEDLIST_TEST
SRCS += $(DIR_SRCS)/02_LinearTable/02_SinglyLinkedList/SinglyLinkedList.cpp
SRCS += $(DIR_SRCS)/02_LinearTable/02_SinglyLinkedList/test_SinglyLinkedList_demo.cpp
endif

ifeq ($(findstring dualcyclelinked_list, $(func)), dualcyclelinked_list)
CXXFLAGS += -DDUALCYCLELINKEDLIST_TEST
SRCS += $(DIR_SRCS)/02_LinearTable/03_DualCycleLinkedList/DualCycleLinkedList.cpp
SRCS += $(DIR_SRCS)/02_LinearTable/03_DualCycleLinkedList/test_DualCycleLinkedList_demo.cpp
endif

ifeq ($(findstring sequence_stack, $(func)), sequence_stack)
CXXFLAGS += -DSEQUENCESTACK_TEST
SRCS += $(DIR_SRCS)/03_StackAndQueue/01_SequenceStack/SequenceStack.cpp
SRCS += $(DIR_SRCS)/03_StackAndQueue/01_SequenceStack/test_SequenceStack_demo.cpp
endif

ifeq ($(findstring linkedlist_stack, $(func)), linkedlist_stack)
CXXFLAGS += -DLINKEDLISTSTACK_TEST
SRCS += $(DIR_SRCS)/03_StackAndQueue/02_LinkedListStack/LinkedListStack.cpp
SRCS += $(DIR_SRCS)/03_StackAndQueue/02_LinkedListStack/test_LinkedListStack_demo.cpp
endif

ifeq ($(findstring lineeditor_stack, $(func)), lineeditor_stack)
CXXFLAGS += -DLINEEDITOR_TEST
SRCS += $(DIR_SRCS)/03_StackAndQueue/01_SequenceStack/SequenceStack.cpp
SRCS += $(DIR_SRCS)/03_StackAndQueue/03_LineEditor/LineEditor.cpp
SRCS += $(DIR_SRCS)/03_StackAndQueue/03_LineEditor/test_LineEditor_demo.cpp
endif

SRCS += $(DIR_SRCS)/main.cpp

LDFLAGS += -lm -ldl -lrt -lstdc++

OBJS += $(patsubst %.cpp, %.o, $(SRCS))

TARGET = $(DIR_TRUNK)/bin/test_$(func)

SUBDIR = $(shell ls ../ -R | grep /)
SUBDIRS = $(subst :,/,$(SUBDIR))
TMPFILES = $(foreach dir,$(SUBDIRS),$(wildcard $(dir)*.o))

.PHONY:all clean
all: $(TARGET)
$(TARGET):$(OBJS)
	$(CPP) -g -fno-omit-frame-pointer -fsanitize=address -o $@ $^ $(LDFLAGS)

%.o:%.c
	$(GCC) -g $(CXXFLAGS) -o $@ -c $<

%.o:%.cpp
	$(CPP) -g $(CXXFLAGS) -o $@ -c $<

clean:
	-rm -rf $(TMPFILES)
	-rm -rf $(TARGET)
