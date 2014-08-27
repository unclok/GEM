#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "NewRunActionMessenger.hh"

#ifndef NewRunAction_h
#define NewRunAction_h 1

class NewRunActionMessenger;

class NewRunAction : public G4UserRunAction
{
public:
	NewRunAction();
	virtual ~NewRunAction();

private:
	G4int nRun;
	G4String name;
	NewRunActionMessenger* messenger;

public:
	G4Run* GenerateRun();
	void BeginOfRunAction(const G4Run*);
	void EndOfRunAction(const G4Run*);
	void SetFileName(G4String val);
	G4String GetFileName(){ return name; }
};

#endif
