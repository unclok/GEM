#ifndef NewPrimaryGeneratorAction_h
#define NewPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "NewPrimaryGenMessenger.hh"
#include "G4ThreeVector.hh"
#include "TRandom3.h"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4ParticleDefinition;
class NewPrimaryGenMessenger;

class NewPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	NewPrimaryGeneratorAction();
	virtual ~NewPrimaryGeneratorAction();

	virtual void GeneratePrimaries(G4Event*);
	void SetGunRandom(bool b){	gunrandom=b;	}
	G4double GetGunEnergy();
	G4ParticleGun* GetParticleGun(){ return particleGun; };

private:
	G4ParticleGun* particleGun;
	G4double energy;
	G4ThreeVector direction;
	NewPrimaryGenMessenger* messenger;
	G4bool gunrandom;
	TRandom3 *rand1;
	TRandom3 *rand2;
};

#endif
