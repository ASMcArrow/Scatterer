#ifndef SCATTERERPHYSICSLIST_H
#define SCATTERERPHYSICSLIST_H

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class ScattererPhysicsList: public G4VModularPhysicsList
{
public:

  ScattererPhysicsList();
  virtual ~ScattererPhysicsList();

  void SetCuts();
  void AddParallelScoring();
  void ConstructProcess();

private:
  G4double cutForGamma;
  G4double cutForElectron;
  G4double cutForPositron;
};

#endif
