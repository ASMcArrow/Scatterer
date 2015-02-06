#define G4MULTITHREADED
//#undef G4MULTITHREADED

#undef G4VIS_USE
#undef G4UI_USE

#include <cstdio>
#include <ctime>

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "G4UImanager.hh"
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "ScattererPhysicsList.hh"
#include "ScattererDetectorConstruction.hh"
#include "ScattererPrimaryGeneratorAction.hh"
#include "ScattererEventAction.hh"
#include "ScattererRunAction.hh"
#include "ScattererParallelWorld.hh"
#include "ScattererActionInitialization.hh"

int main(int argc,char** argv)
{
    // Set the custom seed for the random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4long seed = time(NULL);
    G4Random::setTheSeed(seed);

#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(8);
#else
    G4RunManager* runManager = new G4RunManager;
#endif

    ScattererDetectorConstruction* massWorld = new ScattererDetectorConstruction;
    massWorld->SetSlabThickness(4.375*cm);
    massWorld->RegisterParallelWorld(new ScattererParallelWorld("ScattererParallelWorld"));

    runManager->SetUserInitialization(massWorld);

    G4VModularPhysicsList* physicsList = new ScattererPhysicsList;
    physicsList->SetVerboseLevel(0);
    runManager->SetUserInitialization(physicsList);
    runManager->SetUserInitialization(new ScattererActionInitialization);
    runManager->Initialize();

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

#ifndef G4UI_USE
#ifndef G4VIS_USE
    UImanager->ApplyCommand("/process/msc/StepLimit UseDistanceToBoundary");
    runManager->BeamOn(1000000);
#endif
#endif

#ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
#endif

#ifdef G4UI_USE

    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac");
#endif
    ui->SessionStart();
    delete ui;
#endif

    delete runManager;
    return 0;
}


