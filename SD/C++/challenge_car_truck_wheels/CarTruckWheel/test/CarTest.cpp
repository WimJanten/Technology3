#include "Car.h"

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

class CarTest : public ::testing::Test
{

protected:
    CarTest() { c = new Car("Aston Martin Vanquish", "Alloy", 20, 4); }

    virtual ~CarTest()
    {
        delete c;
        c = NULL;
    }

    void CheckWheels(int n);// example of a method within the cartest class


    Car* c;
};

void CarTest::CheckWheels(int n)
{
    // just an example which need to be completed
    for (int i = 0; i < n; i++)
    {
        const Wheel* w = c->GetWheel(i);
        ASSERT_TRUE(w != NULL);
        // not everything is tested. to be finished
    }
}

// just to show how you can call a method from a useless test.
// and how to introduce a memoryleak
TEST_F(CarTest, test_ifAllWheelsAreThere)
{
    const Wheel* w = c->GetWheel(2);
    ASSERT_TRUE(w != NULL);
    CheckWheels(4);
}

TEST_F(CarTest, test_ifLicencePlateIsSet)
{
    c->SetLicencePlate("1-ABC-123");
    ASSERT_EQ("1-ABC-123", c->GetLicencePlate());
}


