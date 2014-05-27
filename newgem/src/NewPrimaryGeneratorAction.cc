#include "NewPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

NewPrimaryGeneratorAction::NewPrimaryGeneratorAction()
{
	G4int n_particle = 1;
	energy = 10.*eV;
	direction = G4ThreeVector(0.,0.,1.);
	particleGun = new G4ParticleGun(n_particle);

	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;
	G4ParticleDefinition* particle
				= particleTable->FindParticle(particleName="e-");
	particleGun->SetParticlePosition(G4ThreeVector(0.,0.,-31.*um));
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticleEnergy(energy);
	particleGun->SetParticleMomentumDirection(direction);
}

NewPrimaryGeneratorAction::~NewPrimaryGeneratorAction()
{
	delete particleGun;
}

void NewPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	particleGun->GeneratePrimaryVertex(anEvent);
}
