#ifndef SCATTERERPARALLELWORLD_H
#define SCATTERERPARALLELWORLD_H

#include "globals.hh"
#include "G4VUserParallelWorld.hh"
#include "CLHEP/Units/SystemOfUnits.h"

using namespace CLHEP;

class ScattererParallelWorld : public G4VUserParallelWorld
{
public:
    ScattererParallelWorld(G4String worldName);
    ~ScattererParallelWorld();

    void Construct();
    void ConstructSD();

private:
    G4LogicalVolume *GhostDetectorLog;
    G4LogicalVolume *GhostXBoxLog;
    G4LogicalVolume *GhostYBoxLog;
};
#endif

