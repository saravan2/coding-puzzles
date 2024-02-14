# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic -g

# Source files
TARGET1_SRCS = RegulateTemperature.cpp 
TARGET2_SRCS = IpcWriter.cpp

# Object files
TARGET1_OBJS = $(TARGET1_SRCS:.cpp=.o)
TARGET2_OBJS = $(TARGET2_SRCS:.cpp=.o)

# Header files directory
INCDIR = include

# Executable name
TARGET1 = RegulateTemperature
TARGET2 = IpcWriter

# Default rule
all: $(TARGET1) $(TARGET2)

# Rule to compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@

# Rule to link object files into executable
$(TARGET1): $(TARGET1_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TARGET2): $(TARGET2_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean rule
clean:
	rm -f $(TARGET1_OBJS) $(TARGET2_OBJS) $(TARGET1) $(TARGET2)
	rm -f log*.txt
