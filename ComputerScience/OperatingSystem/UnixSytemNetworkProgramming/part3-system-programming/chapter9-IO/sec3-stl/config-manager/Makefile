# 컴파일러 및 옵션 지정
CXX = c++
CCFLG = -g -I. -c

# 실행 파일 이름 지정
TARGET = CheckTrace

# 소스 파일 및 오브젝트 파일 지정
SRCS = Config.cxx Trace.cxx
OBJS = Config.o Trace.o

.SUFFIXES: .cxx

.cxx.o:
	$(CXX) $(CCFLG) $<

# Target
all : $(OBJS)
		$(CXX) -o $(TARGET) $(OBJS)

clean:
		rm $(OBJS)
		rm $(TARGET)