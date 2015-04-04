#include "ScattererPhysicsList.hh"

// Physic lists (contained inside the Geant4 source code, in the 'physicslists folder')
#include "G4HadronPhysicsQGSP_BIC.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4EmExtraPhysics.hh"
#include "G4StoppingPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4IonBinaryCascadePhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4NeutronTrackingCut.hh"
#include "G4LossTableManager.hh"
#include "G4UnitsTable.hh"
#include "G4ProcessManager.hh"
#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4EmProcessOptions.hh"
#include "G4ParallelWorldPhysics.hh"
#include "G4ParallelWorldScoringProcess.hh"
#include "G4EmParameters.hh"
#include "PhysListEmStandardSingleSc.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4WentzelVIModel.hh"

using namespace CLHEP;

ScattererPhysicsList::ScattererPhysicsList() : G4VModularPhysicsList()
{
  G4LossTableManager::Instance();
  defaultCutValue = 1.*mm;
  cutForGamma     = defaultCutValue;
  cutForElectron  = defaultCutValue;
  cutForPositron  = defaultCutValue;

  G4EmParameters* emParameters = G4EmParameters::Instance();
  emParameters->SetMinEnergy(0*eV);
  emParameters->SetMaxEnergy(200*MeV);
  emParameters->SetNumberOfBinsPerDecade(50);

//  emParameters->SetMuHadLateralDisplacement(true);
//  emParameters->SetLateralDisplacement(true);

//  emParameters->SetMscStepLimitType(fUseDistanceToBoundary);
//  emParameters->SetMscGeomFactor(2.5);
//  emParameters->SetMscRangeFactor(0.04);

  emParameters->SetApplyCuts(true);
  emParameters->SetVerbose(true);

  SetVerboseLevel(1);

  RegisterPhysics(new G4EmStandardPhysics_option4);
  RegisterPhysics(new PhysListEmStandardSingleSc);
  RegisterPhysics(new G4HadronPhysicsQGSP_BIC);
  RegisterPhysics(new G4EmExtraPhysics);
  RegisterPhysics(new G4HadronElasticPhysics);
  RegisterPhysics(new G4StoppingPhysics);
  RegisterPhysics(new G4IonBinaryCascadePhysics);
  RegisterPhysics(new G4NeutronTrackingCut);
}

ScattererPhysicsList::~ScattererPhysicsList()
{}

void ScattererPhysicsList::ConstructProcess()
{
    AddParallelScoring();
    G4VModularPhysicsList::ConstructProcess();
}

void ScattererPhysicsList::AddParallelScoring()
{
    G4ParallelWorldScoringProcess* theParallelWorldScoringProcess
            = new G4ParallelWorldScoringProcess("ParaWorldScoringProc");
    theParallelWorldScoringProcess->SetParallelWorld("ScattererParallelWorld");

    theParticleIterator->reset();
    while((*theParticleIterator)())
    {
        G4ProcessManager* pmanager = theParticleIterator->value()->GetProcessManager();
        pmanager->AddProcess(theParallelWorldScoringProcess);
        pmanager->SetProcessOrderingToLast(theParallelWorldScoringProcess, idxAtRest);
        pmanager->SetProcessOrdering(theParallelWorldScoringProcess, idxAlongStep, 1);
        pmanager->SetProcessOrderingToLast(theParallelWorldScoringProcess, idxPostStep);
    }
}

void ScattererPhysicsList::SetCuts()
{
 // set cut values for gamma at first and for e- second and next for e+,
 // because some processes for e+/e- need cut values for gamma
    SetCutValue(cutForGamma, "gamma");
    SetCutValue(cutForElectron, "e-");
    SetCutValue(cutForPositron, "e+");
}

