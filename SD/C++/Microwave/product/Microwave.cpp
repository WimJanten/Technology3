#include "Microwave.h"

#include <iostream>

Microwave::Microwave(ILight& light, IMotor& motor, ISystem& system, IUserInterface& ui)
    : currentState(States::AWAITING_DOOR_CLOSED)
    , light(light)
    , motor(motor)
    , system(system)
    , ui(ui)
{
    motor.SetPower(0);
}

States Microwave::HandleIdleState(Events ev)
{
    States result = States::IDLE;

    switch (ev)
    {
    case Events::START:
        IdleExitActions();

        light.On();
        result = States::HEATING;

        HeatingEntryActions();
        break;

    case Events::DOOR_OPENED:
        IdleExitActions();

        light.On();
        result = States::AWAITING_DOOR_CLOSED;

        AwaitingDoorClosedEntryActions();
        break;

    default:
        // ignored event, nothing to do here
        break;
    }

    return result;
}

States Microwave::HandleAwaitingDoorClosedState(Events ev)
{
    States result = States::AWAITING_DOOR_OPENED;

    switch (ev)
    {
    case Events::DOOR_CLOSED:
        AwaitingDoorClosedExitActions();

        light.Off();
        result = States::IDLE;

        IdleEntryActions();
        break;
    case Events::START:
        AwaitingDoorClosedExitActions();
        
        result = States::HEATING_PAUSED;

        IdleEntryActions();
        break;

    default:
        // ignored event, nothing to do here
        break;
    }

    return result;
}

States Microwave::HandleHeatingState(Events ev)
{
    States result = States::HEATING;

    switch (ev)
    {
    case Events::DOOR_OPENED:
        HeatingExitActions();

        light.Off();
        result = States::HEATING_PAUSED;

        AwaitingDoorClosedEntryActions();
        break;

    case Events::TIME_UP:
        HeatingExitActions();

        light.Off();
        result = States::IDLE;

        IdleEntryActions();
        break;

    default:
        // ignored event, nothing to do here
        break;
    }

    return result;
}

void Microwave::HandleEvent(Events ev)
{
    switch (currentState)
    {
    case States::IDLE:
        currentState = HandleIdleState(ev);
        break;

    default:
        //std::cerr << "ERROR: illegal/unhandled state with number: " << currentState;
        break;
    };
}

void Microwave::IdleEntryActions()
{

}

void Microwave::IdleExitActions()
{

}

void Microwave::HeatingEntryActions()
{
    motor.SetPower(ui.GetRequestedPower());
    ui.StartClock();
}

void Microwave::HeatingExitActions()
{

}

void Microwave::AwaitingDoorClosedEntryActions()
{

}

void Microwave::AwaitingDoorClosedExitActions()
{

}

void Microwave::HeatingPausedEntryActions()
{

}

void Microwave::HeatingPausedExitActions()
{

}


