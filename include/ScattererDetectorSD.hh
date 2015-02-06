#ifndef SCATTERERDETECTORSD_H
#define SCATTERERDETECTORSD_H

#include "G4VSensitiveDetector.hh"
#include "ScattererDetectorHit.hh"
#include "globals.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class ScattererDetectorSD : public G4VSensitiveDetector
{

public:
  ScattererDetectorSD(G4String name);
  ~ScattererDetectorSD();

  void Initialize(G4HCofThisEvent* ); 
  G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* obsolete);
  void EndOfEvent(G4HCofThisEvent* HCE);
 
private:
  ScattererDetectorHitsCollection* HitsCollection;
  G4String SensitiveDetectorName;
};
#endif


