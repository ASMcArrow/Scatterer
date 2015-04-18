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
  ~ScattererDetectorSD() {}

  virtual void Initialize(G4HCofThisEvent* );
  G4bool ProcessHits(G4Step* aStep, G4TouchableHistory* obsolete);
  virtual void EndOfEvent(G4HCofThisEvent* HCE);
  virtual void clear();
 
private:
  ScattererDetectorHitsCollection* HitsCollection;
  G4String SensitiveDetectorName;
};
#endif


