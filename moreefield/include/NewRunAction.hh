#include "G4UserRunAction.hh"
#include "G4Run.hh"

#ifndef NewRunAction_h
#define NewRunAction_h 1

class NewRunAction : public G4UserRunAction
{
public:
	NewRunAction();
	virtual ~NewRunAction();

private:
	G4int nRun;

public:
	G4Run* GenerateRun();
	void BeginOfRunAction(const G4Run*);
	void EndOfRunAction(const G4Run*);
};

#endif
