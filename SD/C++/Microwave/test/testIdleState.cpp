#include "Microwave.h"

#include "MLight.h"
#include "MMotor.h"
#include "MSystem.h"
#include "MUserInterface.h"

using ::testing::Return;
using ::testing::_;

class TestIdleState : public ::testing::Test
{
protected:
    TestIdleState()
    {
        EXPECT_CALL(motor, SetPower(0));
        microwave = new Microwave(light, motor, system, ui);
    }

    virtual ~TestIdleState()
    {
        delete microwave;
        microwave = nullptr;
    }

    MLight light;
    MMotor motor;
    MSystem system;
    MUserInterface ui;
    Microwave* microwave;
};

TEST_F(TestIdleState, test_start_event)
{
    EXPECT_CALL(light, On());
    EXPECT_CALL(ui, GetRequestedPower()).WillOnce(Return(800));
    EXPECT_CALL(motor, SetPower(800));
    EXPECT_CALL(ui, StartClock());

    EXPECT_EQ(States::HEATING, microwave->HandleIdleState(Events::START));
}
















