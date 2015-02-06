#ifndef SCATTERERACTIONINITIASLIZATION_HH
#define SCATTERERACTIONINITIASLIZATION_HH

#include "G4VUserActionInitialization.hh"

class ScattererActionInitialization : public G4VUserActionInitialization
{
  public:

    ScattererActionInitialization();
    virtual ~ScattererActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif // SCATTERERACTIONINITIASLIZATION_HH
