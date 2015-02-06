#ifndef SCATTERERRUNACTION_H
#define SCATTERERRUNACTION_H

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>

class ScattererRunAction : public G4UserRunAction
{
public:

    ScattererRunAction(const G4String detectorName);
    virtual ~ScattererRunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

private:
    G4String DetectorName;
    G4double Cells[100][100];
};

#endif




