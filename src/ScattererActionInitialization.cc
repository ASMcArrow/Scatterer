#include "ScattererActionInitialization.hh"
#include "ScattererPrimaryGeneratorAction.hh"
#include "ScattererRunAction.hh"
#include "ScattererEventAction.hh"

ScattererActionInitialization::ScattererActionInitialization()
    : G4VUserActionInitialization()
{}

ScattererActionInitialization::~ScattererActionInitialization()
{}

void ScattererActionInitialization::BuildForMaster() const
{
    SetUserAction(new ScattererRunAction("FilmDetector"));
}

void ScattererActionInitialization::Build() const
{
    SetUserAction(new ScattererPrimaryGeneratorAction);
    SetUserAction(new ScattererRunAction("FilmDetector"));
}
