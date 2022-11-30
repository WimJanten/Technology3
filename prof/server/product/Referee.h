#ifndef REFEREE_H
#define REFEREE_H

#include "IReferee.h"

class Referee : public IReferee
{
private:
    bool 
public:
    ~Referee();
    bool CheckMove(std::string move);
};

#endif
