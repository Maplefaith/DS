# 定义变量
CXX = g++
CXXFLAGS = -Wall -g
TARGET = BST
SRC = main.cpp

# 默认目标
all: $(TARGET)

# 目标的构建规则
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

run:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)
	./$(TARGET)

report:
	xelatex report.tex
# 清除编译生成的文件
clean:
	rm -f $(TARGET)

