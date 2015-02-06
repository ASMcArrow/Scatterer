#ifndef SCATTERERDETECTORHIT_H
#define SCATTERERDETECTORHIT_H

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class ScattererDetectorHit : public G4VHit
{

public:
    ScattererDetectorHit();
    ~ScattererDetectorHit();
 
    ScattererDetectorHit(const ScattererDetectorHit &right);
    const ScattererDetectorHit& operator = (const ScattererDetectorHit &right);
    int operator == (const ScattererDetectorHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    void Draw();
 // void Print() {} const;

    void SetEdep(G4double de)
    { EnergyDeposit = de; }

    G4double GetEdep() const
    { return EnergyDeposit; }

    void SetPos(G4ThreeVector xyz)
    { Position = xyz; }

    G4ThreeVector GetPos() const
    { return Position; }

    void SetArea(G4double area)
    { Area = area; }

    G4double GetArea() const
    { return Area; }

private:
    G4ThreeVector Position; // Position
    G4double EnergyDeposit; // Energy deposit associated with the hit
    G4double Area; // Area of the cell where this energy deposition occured
};

typedef G4THitsCollection<ScattererDetectorHit> ScattererDetectorHitsCollection;
extern G4ThreadLocal G4Allocator<ScattererDetectorHit>* ScattererDetectorHitAllocator;

inline void* ScattererDetectorHit::operator new(size_t)
{
    if(!ScattererDetectorHitAllocator)
        ScattererDetectorHitAllocator = new G4Allocator<ScattererDetectorHit>;

    return (void *)ScattererDetectorHitAllocator->MallocSingle();
}

inline void ScattererDetectorHit::operator delete(void *aHit)
{
    ScattererDetectorHitAllocator->FreeSingle((ScattererDetectorHit*) aHit);
}

#endif


