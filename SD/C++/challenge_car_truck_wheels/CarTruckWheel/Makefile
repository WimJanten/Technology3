CFLAGS=-Wall -Werror -ggdb -O0 -Iproduct
#CFLAGS=-Wall -Werror -ggdb -O0 -Iproduct -DSHOW_CTORS

CAR_SOURCES=product/Car.cpp \
            product/Wheel.cpp \
            test/CarTest.cpp

TRUCK_SOURCES=product/Truck.cpp \
			  product/Car.cpp \
			  product/Wheel.cpp \
              test/TruckTest.cpp

WHEEL_SOURCES=product/Wheel.cpp \
              test/WheelTest.cpp

TEST_LIBS=-lgtest -lgtest_main -lpthread

GCC=g++

all: CarTest TruckTest WheelTest

CarTest: $(CAR_SOURCES) Makefile product/Car.h
	@$(GCC) $(CFLAGS) $(CAR_SOURCES) -o $@ $(TEST_LIBS)

TruckTest: $(TRUCK_SOURCES) Makefile product/Truck.h
	@$(GCC) $(CFLAGS) $(TRUCK_SOURCES)  -o $@ $(TEST_LIBS)

WheelTest: $(WHEEL_SOURCES) Makefile product/Wheel.h
	@$(GCC) $(CFLAGS) $(WHEEL_SOURCES)  -o $@ $(TEST_LIBS)

clean:
	@rm -rf CarTest TruckTest WheelTest

car: CarTest
	@valgrind ./CarTest

truck: TruckTest
	@valgrind ./TruckTest

wheel: WheelTest
	@valgrind ./WheelTest
