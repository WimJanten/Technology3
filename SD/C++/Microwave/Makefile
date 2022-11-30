PRODUCT=StateTest

CPPFLAGS=-Iproduct -Itest
CXXFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -O0 -std=c++11 $(CPPFLAGS)

SOURCES=$(wildcard product/*.cpp) \
        $(wildcard test/*.cpp)

HEADERS=$(wildcard product/*.h) \
        $(wildcard test/*.h)

LDFLAGS=-lgtest -lgmock -lgmock_main -lpthread

CXX=g++

.PHONY: all clean test klocwork klocwork_after_makefile_change

all: $(PRODUCT)

$(PRODUCT): $(SOURCES) $(HEADERS)
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o $@ $(LDFLAGS)

clean:
	@rm -rf $(PRODUCT)
	@rm -rf kwinject.out .kwlp .kwps

test: $(PRODUCT)
	@./$(PRODUCT)

klocwork:
	kwcheck run

klocwork_after_makefile_change: clean
	kwinject make
	kwcheck create -b kwinject.out
	kwcheck import /opt/klocwork/Fontys_default.pconf
	kwcheck run
