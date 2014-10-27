#ifndef NewPrimaryGeneratorAction_h
#define NewPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4ParticleDefinition;

class NewPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	NewPrimaryGeneratorAction();
	virtual ~NewPrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event*);

private:
	G4ParticleGun* particleGun;
	G4double energy;
	G4ThreeVector direction;
};

#endif
