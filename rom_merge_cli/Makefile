CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
STRIP = $(CROSS_COMPILE)strip

CFLAGS = -O2 -Wall
CXXFLAGS = $(CFLAGS)
LDFLAGS = -static

TARGET = ../rom_merge_cli.exe
OBJS = rom_merge_cli.o

ALL_TARGETS = $(TARGET)

all: $(ALL_TARGETS)

$(TARGET): $(OBJS)
		$(CXX) $(LDFLAGS) -o $(TARGET) $(OBJS)
		$(STRIP) $(TARGET)

clean:
		rm $(OBJS)

mrproper:
		rm $(OBJS)
		rm $(TARGET)
