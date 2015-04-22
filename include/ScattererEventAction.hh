#ifndef SCATTEREREVENTACTION_H
#define SCATTEREREVENTACTION_H

#include "G4UserEventAction.hh"
#include "G4LogicalVolume.hh"
#include "globals.hh"

class ScattererEventAction : public G4UserEventAction
{

public:
    ScattererEventAction();
    ~ScattererEventAction();

    void BeginOfEventAction(const G4Event* event);
    void EndOfEventAction(const G4Event* event);
};

#endif

    
