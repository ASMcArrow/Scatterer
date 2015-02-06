#ifndef ABCSOURCE_HH
#define ABCSOURCE_HH

#include "G4VPrimaryGenerator.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleMomentum.hh"
#include "G4SPSAngDistribution.hh"
#include "G4SPSEneDistribution.hh"

class ABCSource : private G4VPrimaryGenerator
{

public:
    ABCSource();
    ~ABCSource();

    void GeneratePrimaryVertex(G4Event *evt);

    void SetWaistCoords(G4ThreeVector coordinatesX, G4ThreeVector coordinatesY);
    void SetCentreCoords(G4ThreeVector coordinates);

    G4SPSPosDistribution* GetPosDistX() { return posGeneratorX; }
    G4SPSPosDistribution* GetPosDistY() { return posGeneratorY; }
    G4SPSAngDistribution* GetAngDistX() { return angGeneratorX; }
    G4SPSAngDistribution* GetAngDistY() { return angGeneratorY; }
    G4SPSEneDistribution* GetEneDist() { return eneGenerator; }
    G4SPSRandomGenerator* GetBiasRndm() { return biasRndm; }

private:
    G4SPSPosDistribution* posGeneratorX;
    G4SPSPosDistribution* posGeneratorY;
    G4SPSAngDistribution* angGeneratorX;
    G4SPSAngDistribution* angGeneratorY;
    G4SPSEneDistribution* eneGenerator;
    G4SPSRandomGenerator* biasRndm;

    // Other particle properties
    G4ThreeVector         particle_position_X;
    G4ThreeVector         particle_position_Y;
    G4ParticleDefinition* particle_definition;
    G4ParticleMomentum particle_momentum_direction, particle_momentum_direction_X, particle_momentum_direction_Y;
    G4double particle_energy;
    G4double particle_charge;
    G4ThreeVector particle_polarization;
    G4double particle_weight;
    G4ThreeVector Center_coordinates;
};

#endif // ABCSOURCE_HH
