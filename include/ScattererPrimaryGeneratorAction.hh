#ifndef SCATTERERPRIMARYGENERATORACTION_H
#define SCATTERERPRIMARYGENERATORACTION_H

#include "ABCSource.hh"

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4SPSPosDistribution.hh"
#include "G4Types.hh"
#include "G4SingleParticleSource.hh"

class G4Event;

class ScattererPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{

public:
    ScattererPrimaryGeneratorAction();
    ~ScattererPrimaryGeneratorAction();

    // Method for setting the A, B, C coefficients. 0 in forth  argument stands for x, 1 - for y;
    //    void SetABC(G4double A, G4double B, G4double C, G4int axis);
    void GeneratePrimaries(G4Event* event);

private:
    G4SingleParticleSource* CircleSource;
    //    ABCSource* ABCParticleSource;
    //    G4double A_x, B_x, C_x, D_x, A_y, B_y, C_y, D_y;
};

#endif


