#include "ScattererPrimaryGeneratorAction.hh"
#include "ABCSource.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SingleParticleSource.hh"
#include "G4SPSAngDistribution.hh"
#include "G4SPSPosDistribution.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4Proton.hh"
#include "globals.hh"
#include "Randomize.hh"

using namespace CLHEP;

ScattererPrimaryGeneratorAction::ScattererPrimaryGeneratorAction()
{
    CircleSource = new G4SingleParticleSource();
    CircleSource->SetParticleDefinition(G4Proton::Definition());

    G4SPSEneDistribution* energy = CircleSource->GetEneDist();
    energy->SetEnergyDisType("Gauss");
    energy->SetBeamSigmaInE(1 *MeV);
    energy->SetMonoEnergy(219 *MeV);

    G4SPSPosDistribution* position = CircleSource->GetPosDist();
    position->SetPosDisType("Beam");
    position->SetBeamSigmaInX(0.3*mm);
    position->SetBeamSigmaInY(0.3*mm);
 //   position->SetPosDisShape("Circle");
 //   position->SetRadius(3*mm);
    position->SetCentreCoords(G4ThreeVector(0*m, 0*m, -80.2*cm - 10.5*cm - 50*cm));

    G4SPSAngDistribution* angular = CircleSource->GetAngDist();
    angular->SetAngDistType("beam2d");
    angular->SetParticleMomentumDirection(G4ThreeVector(0.0,0.0,1.0));
    angular->DefineAngRefAxes("angref1", G4ThreeVector(-1.0,0.0,0.0));
    angular->SetBeamSigmaInAngX(0.000*rad);
    angular->SetBeamSigmaInAngY(0.000*rad);

    CircleSource->SetNumberOfParticles(1);

    //    this->SetABC(2.503367, -4.799269E-04, 2.427160E-06, 0);
    //    this->SetABC(5.657701E-01, 1.132192E-03, 3.184419E-06, 1);

    //    this->SetABC(7.056491E-01, 7.761171E-04, 4.980770E-06, 0);
    //    this->SetABC(3.937532, -8.238743E-03, 5.958428E-05, 1);

    //    G4double beam_waist_x = -B_x/C_x;
    //    G4double beam_waist_y = -B_y/C_y;
    //    G4double sigma_pos_x_waist = sqrt(0.5*(D_x/C_x));
    //    G4double sigma_pos_y_waist = sqrt(0.5*(D_y/C_y));
    //    G4double sigma_theta_x_waist = sqrt(0.5*C_x);
    //    G4double sigma_theta_y_waist = sqrt(0.5*C_y);

    //    ABCParticleSource = new ABCSource();
    //    ABCParticleSource->SetCentreCoords(G4ThreeVector(0*m, 0*m, -80.2*cm - 10.1*cm - 0*cm));

    //    G4SPSEneDistribution* energy = ABCParticleSource->GetEneDist();
    //    energy->SetEnergyDisType("Gauss");
    //    energy->SetBeamSigmaInE(1.58 *MeV);
    //    energy->SetMonoEnergy(217 *MeV);

    //    // For X waist
    //    G4SPSPosDistribution* positionX = ABCParticleSource->GetPosDistX();
    //    positionX->SetCentreCoords(G4ThreeVector(0, 0, beam_waist_x));
    //    positionX->SetPosDisType("Beam");
    //    positionX->SetBeamSigmaInX(sigma_pos_x_waist*cm);
    //    positionX->SetBeamSigmaInY(sigma_pos_x_waist*cm);

    //    G4SPSAngDistribution* angularX = ABCParticleSource->GetAngDistX();
    //    angularX->SetVerbosity(0);
    //    angularX->DefineAngRefAxes("angref1",G4ThreeVector(-1, 0, 0.));
    //    angularX->SetAngDistType("beam2d");
    //    angularX->SetBeamSigmaInAngX(sigma_theta_x_waist);
    //    angularX->SetBeamSigmaInAngY(sigma_theta_x_waist);

    //    // For Y waist
    //    G4SPSPosDistribution* positionY = ABCParticleSource->GetPosDistY();
    //    positionY->SetCentreCoords(G4ThreeVector(0, 0, beam_waist_y));
    //    positionY->SetPosDisType("Beam");
    //    positionY->SetBeamSigmaInX(sigma_pos_y_waist*cm);
    //    positionY->SetBeamSigmaInY(sigma_pos_y_waist*cm);

    //    G4SPSAngDistribution* angularY = ABCParticleSource->GetAngDistY();
    //    angularY->SetVerbosity(0);
    //    angularY->DefineAngRefAxes("angref1",G4ThreeVector(-1, 0, 0.));
    //    angularY->SetAngDistType("beam2d");
    //    angularY->SetBeamSigmaInAngX(sigma_theta_y_waist);
    //    angularY->SetBeamSigmaInAngY(sigma_theta_y_waist);
}

//void ScattererPrimaryGeneratorAction::SetABC(G4double A, G4double B, G4double C, G4int axis)
//{
//    if (axis == 0)
//    {
//        A_x = A;
//        B_x = B;
//        C_x = C;
//        D_x = A_x*C_x - pow(B_x,2);
//    }
//    else if (axis == 1)
//    {
//        A_y = A;
//        B_y = B;
//        C_y = C;
//        D_y = A_y*C_y - pow(B_y,2);
//    }
//}

ScattererPrimaryGeneratorAction::~ScattererPrimaryGeneratorAction()
{
    //delete ABCParticleSource;
    delete CircleSource;
}

void ScattererPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    //ABCParticleSource->GeneratePrimaryVertex(event);
    CircleSource->GeneratePrimaryVertex(event);
}
