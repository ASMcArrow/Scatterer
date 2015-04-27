#include "ScattererRunAction.hh"
#include "ScattererRun.hh"
#include "ScattererDetectorHit.hh"

#include "G4RunManager.hh"
#include "ScattererDetectorConstruction.hh"
#include "G4THitsMap.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"

#include <fstream>
#define _USE_MATH_DEFINES

ScattererRunAction::ScattererRunAction(const G4String detectorName) : G4UserRunAction()
{
    DetectorName = detectorName;

    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
            Cells[i][j] = 0;
    }
}

ScattererRunAction::~ScattererRunAction()
{}

G4Run* ScattererRunAction::GenerateRun()
{
  return new ScattererRun(DetectorName, 0);
}

void ScattererRunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
}

void ScattererRunAction::EndOfRunAction(const G4Run* aRun)
{
    if(!IsMaster()) return;

    ScattererRun *scattererRun = (ScattererRun*)aRun;
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
            Cells[i][j] += scattererRun->GetCells()[i][j];
    }

    std::ofstream mapFile("ScattererUrban15.txt");

    for (G4int xBox = 0; xBox <= 200; xBox++)
    {
        mapFile << "\n";

        // bloody gnuplot!
        for (G4int yBox = 0; yBox <= 200; yBox++)
        {
            if ((yBox == 200)||(xBox == 200))
            {
                mapFile << (G4double)(xBox*6.0)/200.0 << " " << (G4double)(yBox*6.0/200.0) << " 0 \n";
            }
            else
                mapFile << (G4double)(xBox*6.0)/200.0 << " " << (G4double)(yBox*6.0/200.0) << " " << Cells[yBox][xBox] << " \n";
        }
    }  
}
