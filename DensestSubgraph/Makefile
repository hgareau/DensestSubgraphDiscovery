# Define the compiler and the flags
CXX = g++
CXXFLAGS = -I.

# List all the source files
SRCS = ExactTest.cpp CDSDecompose.cpp DataReader.cpp LocateCore.cpp Component.cpp \
       DensestCore.cpp FindMinCut.cpp FlowNetwork.cpp Log.cpp ComponentDecom.cpp \
       DynamicExactAlgo.cpp ExactAlgo.cpp KCore.cpp KList.cpp MDS.cpp

# List all the object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Define the target executable
TARGET = ExactTest

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile each source file into an object file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
