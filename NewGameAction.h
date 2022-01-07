#pragma once
#include "Action.h"

class NewGameAction :
    public Action
{
public:
    NewGameAction(ApplicationManager* pApp);
    void virtual ReadActionParameters();
    void virtual Execute();
    virtual ~NewGameAction();
};

