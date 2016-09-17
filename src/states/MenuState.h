#pragma once

#include "State.h"

class MenuState : public State {
public:
    MenuState(irr::IrrlichtDevice* dev);
    virtual ~MenuState();
    virtual void update(float dt);
};