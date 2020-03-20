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
	$(CPP) -g -fno-omit-frame-pointer -o $@ $^ $(LDFLAGS)

%.o:%.c
	$(GCC) -g $(CXXFLAGS) -o $@ -c $<

%.o:%.cpp
	$(CPP) -g $(CXXFLAGS) -o $@ -c $<

clean:
	-rm -rf $(TMPFILES)
	-rm -rf $(TARGET)
