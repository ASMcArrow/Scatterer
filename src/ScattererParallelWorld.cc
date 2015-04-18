#include "ScattererParallelWorld.hh"
#include "ScattererDetectorSD.hh"

#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"
#include "G4SDManager.hh"

ScattererParallelWorld::ScattererParallelWorld(G4String worldName)
    :G4VUserParallelWorld(worldName)
{}

ScattererParallelWorld::~ScattererParallelWorld()
{}

void ScattererParallelWorld::Construct()
{
    G4VPhysicalVolume *ghostWorld = GetWorld();
    G4LogicalVolume *worldLog = ghostWorld->GetLogicalVolume();

 // Place volumes in the parallel world here
    G4double detHalfDimension = 3.0*cm;
    G4double nDivisions = 200.0;
    G4double halfBoxWidth = (detHalfDimension/nDivisions);

 // The cylinder with concentric circles
    G4Box *ghostDetector = new G4Box("GhostDetectorBox", detHalfDimension, detHalfDimension, 0.25*cm);
    GhostDetectorLog = new G4LogicalVolume(ghostDetector, 0, "GhostDetectorLog");
    new G4PVPlacement(0, G4ThreeVector(0, 0, 0.25*cm), GhostDetectorLog, "GhostDetectorPhys", worldLog, 0, 0);

    G4VisAttributes* visAttributes = new G4VisAttributes;
    visAttributes->SetColor(0,0,1);
    GhostDetectorLog->SetVisAttributes(visAttributes);

 // Divide along X coordinate
    G4Box* ghostXBox = new G4Box("ghostXBox", halfBoxWidth, detHalfDimension, 0.25*cm);
    GhostXBoxLog = new G4LogicalVolume(ghostXBox, 0, "GhostXBoxLog");
    new G4PVReplica("GhostXBoxPhys", GhostXBoxLog, GhostDetectorLog, kXAxis, nDivisions, halfBoxWidth*2, 0);

 // Divide along Y coordinate
    G4Box* ghostYBox = new G4Box("ghostYBox", halfBoxWidth, halfBoxWidth, 0.25*cm);
    GhostYBoxLog = new G4LogicalVolume(ghostYBox, 0, "GhostYBoxLog");
    new G4PVReplica("GhostYBoxPhys", GhostYBoxLog, GhostXBoxLog, kYAxis, nDivisions, halfBoxWidth*2, 0);
}

void ScattererParallelWorld::ConstructSD()
{
    G4SDManager* sDman = G4SDManager::GetSDMpointer();
    G4VSensitiveDetector* sDetector = new ScattererDetectorSD("FilmDetector");
    sDman->AddNewDetector(sDetector);
    GhostYBoxLog->SetSensitiveDetector(sDetector);
}
