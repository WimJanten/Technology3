#include "Wheel.h"

#include <string>
#include <gtest/gtest.h>

class WheelTest : public ::testing::Test
{
protected:
    WheelTest() { w = new Wheel(20, "Alloy"); }

    virtual ~WheelTest()
    {
        delete w;
        w = NULL;
    }

    Wheel* w;
};

TEST_F(WheelTest, test_getMaterial)
{
    ASSERT_TRUE(w->GetMaterial() == "Alloy");
}
