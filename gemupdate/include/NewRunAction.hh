#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "NewRunActionMessenger.hh"
#include "NewDetectorConstruction.hh"
#include "NewPrimaryGeneratorAction.hh"

#ifndef NewRunAction_h
#define NewRunAction_h 1

class NewRunActionMessenger;

class NewRunAction : public G4UserRunAction
{
public:
	NewRunAction(NewDetectorConstruction*, NewPrimaryGeneratorAction*);
	virtual ~NewRunAction();

private:
	G4int nRun;
	G4String name;
	NewRunActionMessenger* messenger;
	NewDetectorConstruction* fDetector;
	NewPrimaryGeneratorAction* fPrimary;

public:
	G4Run* GenerateRun();
	void BeginOfRunAction(const G4Run*);
	void EndOfRunAction(const G4Run*);
	void SetFileName(G4String val);
	G4String GetFileName(){ return name; }
};

#endif
