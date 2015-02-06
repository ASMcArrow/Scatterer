#include "ScattererDetectorMessenger.hh"
#include "ScattererDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

ScattererDetectorMessenger::ScattererDetectorMessenger
(ScattererDetectorConstruction* detectorConstruction)
    :G4UImessenger(), DetectorConstruction(detectorConstruction)
{
    TopDirectory = new G4UIdirectory("/Scatterer/");
    TopDirectory->SetGuidance("UI commands for Scatterer");

    Directory = new G4UIdirectory("/Scatterer/det/");
    Directory->SetGuidance("Control of material slab size and dimension");

    SetSlabMaterialCmd = new G4UIcmdWithAString("/Scatterer/det/setSlabMaterial", this);
    SetSlabMaterialCmd->SetGuidance("Select material of the slab");
    SetSlabMaterialCmd->SetParameterName("SlabMaterial", false);
    SetSlabMaterialCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    SetSlabThicknessCmd = new G4UIcmdWithADoubleAndUnit("/Scatterer/det/setSlabThickness",this);
    SetSlabThicknessCmd->SetGuidance("Set slab thickness (in half length)");
    SetSlabThicknessCmd->SetParameterName("SlabThickness", false);
    SetSlabThicknessCmd->SetUnitCategory("Length");
    SetSlabThicknessCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

ScattererDetectorMessenger::~ScattererDetectorMessenger()
{
    delete TopDirectory;
    delete Directory;
    delete SetSlabMaterialCmd;
}

void ScattererDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if(command == SetSlabMaterialCmd)
        DetectorConstruction->SetSlabMaterial(newValue);

    else if (command == SetSlabThicknessCmd)
    {
        G4double thickness = SetSlabThicknessCmd->ConvertToDimensionedDouble(newValue);
        DetectorConstruction->SetSlabThickness(thickness);
    }
}
