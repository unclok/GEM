#include "NewPrimaryGeneratorAction.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "CLHEP/Units/PhysicalConstants.h"

using namespace CLHEP;

//
NewPrimaryGeneratorAction::NewPrimaryGeneratorAction() : gunrandom(false), particleGun(0)
{
	messenger = new NewPrimaryGenMessenger(this);
	rand1 = new TRandom3;
	rand2 = new TRandom3;
	G4int n_particle = 1;
	energy = 100*eV;
	direction = G4ThreeVector(0.,0.,1.);
	particleGun = new G4ParticleGun(n_particle);

	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;
	G4ParticleDefinition* particle
				= particleTable->FindParticle(particleName="e-");
	particleGun->SetParticlePosition(G4ThreeVector(0.,0.,-29.9*um));
	particleGun->SetParticleDefinition(particle);
	particleGun->SetParticleEnergy(energy);
	particleGun->SetParticleMomentumDirection(direction);
}

NewPrimaryGeneratorAction::~NewPrimaryGeneratorAction()
{
	delete messenger;
	delete particleGun;
}

void NewPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	if(gunrandom==false)particleGun->GeneratePrimaryVertex(anEvent);
//randomly shoot a particle along conical shape
	else if(gunrandom==true){
		particleGun->SetParticleMomentumDirection(G4ThreeVector(1-2*rand1->Rndm(),1-2*rand1->Rndm(),1-2*rand1->Rndm()));
		particleGun->SetParticlePosition(G4ThreeVector((1-2*rand2->Rndm())*50*um,(1-2*rand2->Rndm())*50*um,-55*um));
		particleGun->GeneratePrimaryVertex(anEvent);
	}

	else G4cout<<"GunRandom is wrong!"<<G4endl;
}

G4double NewPrimaryGeneratorAction::GetGunEnergy()
{
	G4double energy = particleGun->GetParticleEnergy();
	return energy;
} 
