#include "Truck.h"

#include <string>
#include <gtest/gtest.h>

class TruckTest : public ::testing::Test
{
protected:
    TruckTest() { t = new Truck("Volvo FH", "Alloy", 20, 8, 1000); }

    virtual ~TruckTest()
    {
        delete t;
        t = NULL;
    }

    Truck* t;
    void testCopyConstructor();
    void testAssignmentOperator();
};

void TruckTest::testCopyConstructor()
{
    Truck* t2 = new Truck(*t);
    ASSERT_TRUE(t2 != NULL);
    ASSERT_TRUE(t2->GetModel() == t->GetModel());
    ASSERT_TRUE(t2->GetLicencePlate() == t->GetLicencePlate());
    ASSERT_TRUE(t2->GetNrWheels() == t->GetNrWheels());
    ASSERT_TRUE(t2->GetPower() == t->GetPower());
    delete t2;
    t2 = NULL;
}

void TruckTest::testAssignmentOperator()
{
    Truck* t2 = new Truck("Volvo FH", "Alloy", 20, 8, 1000);
    *t2 = *t;
    ASSERT_TRUE(t2 != NULL);
    ASSERT_TRUE(t2->GetModel() == t->GetModel());
    ASSERT_TRUE(t2->GetLicencePlate() == t->GetLicencePlate());
    ASSERT_TRUE(t2->GetNrWheels() == t->GetNrWheels());
    ASSERT_TRUE(t2->GetPower() == t->GetPower());
    delete t2;
    t2 = NULL;
}

TEST_F(TruckTest, test_copyConstructor)
{
    testCopyConstructor();
}

TEST_F(TruckTest, test_assignmentOperator)
{
    testAssignmentOperator();
}

TEST_F(TruckTest, test_getPower)
{
    ASSERT_TRUE(t->GetPower() == 1000);
}
