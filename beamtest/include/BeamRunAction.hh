#include "G4UserRunAction.hh"
#include "G4Run.hh"

#ifndef BeamRunAction_h
#define BeamRunAction_h 1

class BeamRunAction : public G4UserRunAction
{
public:
	BeamRunAction();
	virtual ~BeamRunAction();

private:
	G4int nRun;
	G4String name;

public:
	G4Run* GenerateRun();
	void BeginOfRunAction(const G4Run*);
	void EndOfRunAction(const G4Run*);
};

#endif
