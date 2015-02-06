#include "ABCSource.hh"

#include "G4PrimaryVertex.hh"
#include "G4Proton.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"

ABCSource::ABCSource()
{
    particle_definition = G4Proton::ProtonDefinition();
    G4ThreeVector zero;
    particle_momentum_direction_X = G4ParticleMomentum(1, 0, 0);
    particle_momentum_direction_Y = G4ParticleMomentum(1, 0, 0);
    particle_energy = 1.0 * MeV;
    particle_position = zero;
    particle_time = 0.0;
    particle_polarization = zero;
    particle_charge = 0.0;
    particle_weight = 1.0;

    biasRndm = new G4SPSRandomGenerator();
    posGeneratorX = new G4SPSPosDistribution();
    posGeneratorY = new G4SPSPosDistribution();
    posGeneratorX->SetBiasRndm(biasRndm);
    posGeneratorY->SetBiasRndm(biasRndm);
    angGeneratorX = new G4SPSAngDistribution();
    angGeneratorY = new G4SPSAngDistribution();
    //angGenerator->SetPosDistribution(posGenerator);
    angGeneratorX->SetBiasRndm(biasRndm);
    angGeneratorY->SetBiasRndm(biasRndm);
    eneGenerator = new G4SPSEneDistribution();
    eneGenerator->SetBiasRndm(biasRndm);
}

ABCSource::~ABCSource()
{
    delete posGeneratorX;
    delete angGeneratorX;
    delete posGeneratorY;
    delete angGeneratorY;
    delete eneGenerator;
    delete biasRndm;
}

void ABCSource::SetCentreCoords(G4ThreeVector coordinates)
{
    Center_coordinates = coordinates;
}

void ABCSource::GeneratePrimaryVertex(G4Event *evt)
{
    particle_position_X = posGeneratorX->GenerateOne();
    particle_position_Y = posGeneratorY->GenerateOne();

    // create a new vertex
    particle_momentum_direction_X = angGeneratorX->GenerateOne();
    particle_momentum_direction_Y = angGeneratorY->GenerateOne();
    particle_energy = eneGenerator->GenerateOne(particle_definition);

    G4double tan_theta_x = particle_momentum_direction_X.getX()/particle_momentum_direction_X.getZ();
    G4double tan_theta_y = particle_momentum_direction_Y.getY()/particle_momentum_direction_Y.getZ();

    particle_position.setX(particle_position_X.getX()-(posGeneratorX->GetCentreCoords().getZ()*tan_theta_x));
    particle_position.setY(particle_position_Y.getY()-(posGeneratorY->GetCentreCoords().getZ()*tan_theta_y));
    particle_position.setZ(Center_coordinates.getZ());
    G4PrimaryVertex* vertex = new G4PrimaryVertex(particle_position, particle_time);

    particle_momentum_direction.setX(tan_theta_x/sqrt(pow(tan_theta_x,2)+pow(tan_theta_y,2)+1));
    particle_momentum_direction.setY(tan_theta_y/sqrt(pow(tan_theta_x,2)+pow(tan_theta_y,2)+1));
    particle_momentum_direction.setZ(1/sqrt(pow(tan_theta_x,2)+pow(tan_theta_y,2)+1));

    // create new primaries and set them to the vertex
    G4double mass = particle_definition->GetPDGMass();
    G4PrimaryParticle* particle = new G4PrimaryParticle(particle_definition);
    particle->SetKineticEnergy(particle_energy);
    particle->SetMass(mass);
    particle->SetMomentumDirection(particle_momentum_direction);
    particle->SetCharge(particle_charge);
    particle->SetPolarization(particle_polarization.x(),
                              particle_polarization.y(),
                              particle_polarization.z());

    // set weight equal to the multiple of all non-zero weights
    particle_weight = eneGenerator->GetWeight()*biasRndm->GetBiasWeight();
    // pass it to primary particle
    particle->SetWeight(particle_weight);
    vertex->SetPrimary(particle);

    // now pass the weight to the primary vertex. CANNOT be used here!
    // vertex->SetWeight(particle_weight)

    evt->AddPrimaryVertex(vertex);
}
