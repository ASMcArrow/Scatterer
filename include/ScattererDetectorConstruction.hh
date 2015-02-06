#ifndef SCATTERERDETECTORCONSTRUCTION_H
#define SCATTERERDETECTORCONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"

class ScattererDetectorMessenger;
class G4LogicalVolume;
class G4VPhysicalVolume;

using namespace CLHEP;

class ScattererDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    ScattererDetectorConstruction();
    ~ScattererDetectorConstruction() {}

    static ScattererDetectorConstruction* GetInstance();
    G4VPhysicalVolume* Construct();

    void SetSlabMaterial(G4String materialName);
    void SetSlabThickness(G4double thickness);

 // void ConstructSDandField();
 // This method is used in multi-threaded applications to build
 // per-worker non-shared objects: SensitiveDetectors and Field managers

private:
    void InitializeMaterials();
    void UpdateGeometry();

    static ScattererDetectorConstruction* Instance;
    ScattererDetectorMessenger* DetectorMessenger;
    G4LogicalVolume* MaterialLogic;
    std::map <std::string, G4Material*> MaterialMap;
    G4double SlabThickness;
};

#endif

