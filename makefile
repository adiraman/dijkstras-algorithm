
CC = gcc
CXX = g++
CFLAGS = -I./include/ -O3 -std=c++11 -Wall -pedantic
LDFLAGS =

SRCDIRS = ./src
BUILDDIR = ./obj
TARGETDIR = ./exec
SRCEXT = cpp

SOURCES = $(shell find $(SRCDIRS) -type f -name *.$(SRCEXT))
#SOURCES = main.C screen.C
OBJECTS = $(patsubst $(SRCDIRS)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

EXECUTABLE = main
TARGET =$(TARGETDIR)/$(EXECUTABLE)
RM = rm -f
MKDIR_P = mkdir -p

all: directories $(TARGET)

directories: $(TARGETDIR)

$(TARGETDIR):
	$(MKDIR_P) $(TARGETDIR)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJECTS): $(SOURCES)
	$(MKDIR_P) $(BUILDDIR)
	$(CXX) $(CFLAGS) -c $^
	mv *.o $(BUILDDIR)/

clean:
	$(RM) $(OBJECTS)

realclean:
	$(RM) $(TARGET) $(OBJECTS) *.out *.o *.dot *.eps

