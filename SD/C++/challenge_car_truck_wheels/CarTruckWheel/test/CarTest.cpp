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
    void TestCopyConstructor();
    void TestAssignmentOperator();


    Car* c;
};

void CarTest::TestCopyConstructor(){
    Car* c2 = new Car(*c);
    ASSERT_TRUE(c2 != NULL);
    ASSERT_TRUE(c2->GetModel() == c->GetModel());
    ASSERT_TRUE(c2->GetLicencePlate() == c->GetLicencePlate());
    ASSERT_TRUE(c2->GetNrWheels() == c->GetNrWheels());
    delete c2;
    c2 = NULL;
}

void CarTest::TestAssignmentOperator(){
    Car* c2 = new Car("Audi A4", "Alloy", 20, 4);
    *c2 = *c;
    ASSERT_TRUE(c2 != NULL);
    ASSERT_TRUE(c2->GetModel() == c->GetModel());
    ASSERT_TRUE(c2->GetLicencePlate() == c->GetLicencePlate());
    ASSERT_TRUE(c2->GetNrWheels() == c->GetNrWheels());
    delete c2;
    c2 = NULL;
}

TEST_F(CarTest, test_copyConstructor)
{
    TestCopyConstructor();
}

TEST_F(CarTest, test_assignmentOperator)
{
    TestAssignmentOperator();
}
