#ifndef SCATTERERRUN_H
#define SCATTERERRUN_H

#include "G4Run.hh"
#include "G4Event.hh"

#include "ScattererDetectorHit.hh"

#include <vector>

class ScattererRun : public G4Run
{
public:

  ScattererRun(const G4String detectorName, G4bool verbose);
  virtual ~ScattererRun();

  // virtual method from G4Run.
  // The method is overriden in this class for scoring.
  virtual void RecordEvent(const G4Event*);
  virtual void Merge(const G4Run*);

  G4int GetNumberOfHits() const { return HitVector.size();}
  ScattererDetectorHit* GetHit(G4int i) {return HitVector[i];}

private:
  G4String CollName;
  G4int CollectionID;
  std::vector<ScattererDetectorHit*> HitVector;
  G4bool Verbose;
};

#endif // SCATTERERRUN_H


