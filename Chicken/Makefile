# 定义变量
CXX = g++
CXXFLAGS = -Wall -g
TARGET = Chicken
SRC = Chicken.cpp

# 默认目标
all: $(TARGET)

# 目标的构建规则
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# 清除编译生成的文件
clean:
	rm -f $(TARGET)

