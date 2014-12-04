#ifndef NewSteppingAction_hh
#define NewSteppingAction_hh 1

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4PropagatorInField.hh"
#include "G4ParticleGun.hh"

class G4UserSteppingAction;

class NewSteppingAction : public G4UserSteppingAction
{
public:
	NewSteppingAction();
	virtual ~NewSteppingAction();

	virtual void UserSteppingAction(const G4Step* step);

private:
	G4PropagatorInField* fFieldPropagator;
	const G4Field* Field;
};
#endif
