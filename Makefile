CXXFLAGS =	-O2 -g -Wall -fmessage-length=0 -fopenmp

OBJS =		example.o

LIBS =

TARGET =	example

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS) -fopenmp

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
