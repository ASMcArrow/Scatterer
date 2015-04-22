#include "ScattererEventAction.hh"
#include "ScattererDetectorHit.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4Types.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Proton.hh"
#include "G4SDManager.hh"

#include <fstream>
#include <iostream>

ScattererEventAction::ScattererEventAction():G4UserEventAction()
{}

ScattererEventAction::~ScattererEventAction()
{}

void ScattererEventAction::BeginOfEventAction(const G4Event* event)
{}

void ScattererEventAction::EndOfEventAction(const G4Event* event)
{
    if (event->GetEventID()%100000 == 0)
        G4cout << "Event #" << event->GetEventID() << G4endl;
}

