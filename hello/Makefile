# 定义编译器
CXX = g++

# 定义编译选项
CXXFLAGS = -Wall -g

# 定义输出文件名
TARGET = hello

# 默认目标
all: $(TARGET)

# 编译目标规则
$(TARGET): hello.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) hello.cpp

# 清理目标
clean:
	rm -f $(TARGET)
