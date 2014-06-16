#include "BeamPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

BeamPrimaryGeneratorAction::BeamPrimaryGeneratorAction()
{
	G4int n_particle = 1;
	energy = 100*MeV;
	direction = G4ThreeVector(0.,0.,1.);
	particleGun = new G4ParticleGun(n_particle);

	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;
	G4ParticleDefinition* particle
				= particleTable->FindParticle(particleName="proton");
	particleGun->SetParticlePosition(G4ThreeVector(0.,0.,-30.*cm));
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticleEnergy(energy);
	particleGun->SetParticleMomentumDirection(direction);
}

BeamPrimaryGeneratorAction::~BeamPrimaryGeneratorAction()
{
	delete particleGun;
}

void BeamPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	particleGun->GeneratePrimaryVertex(anEvent);
}
