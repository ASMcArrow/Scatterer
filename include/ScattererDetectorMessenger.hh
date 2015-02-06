#ifndef SCATTERERMESSENGER_HH
#define SCATTERERMESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class ScattererDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

// Messenger class that implements commands:
// - /Scatterer/det/setSlabMaterialName name
// - /Scatterer/det/setSlabDimensions hx hy hz unit

class ScattererDetectorMessenger: public G4UImessenger
{

public:
    ScattererDetectorMessenger(ScattererDetectorConstruction* );
    virtual ~ScattererDetectorMessenger();

    virtual void SetNewValue(G4UIcommand* command, G4String newValue);

private:
    ScattererDetectorConstruction* DetectorConstruction;
    G4UIdirectory* TopDirectory;
    G4UIdirectory* Directory;
    G4UIcmdWithAString* SetSlabMaterialCmd;
    G4UIcmdWithADoubleAndUnit* SetSlabThicknessCmd;
};

#endif // SCATTERERMESSENGER_HH
