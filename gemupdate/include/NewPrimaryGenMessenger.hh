#ifndef NewPrimaryGenMessenger_h
#define NewPrimaryGenMessenger_h 1

#include "NewPrimaryGeneratorAction.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UImessenger.hh"
#include "G4ios.hh"

class NewPrimaryGeneratorAction;
class G4UIcmdWithABool;

class NewPrimaryGenMessenger: public G4UImessenger
{
public:
	NewPrimaryGenMessenger(NewPrimaryGeneratorAction* mpga);
	~NewPrimaryGenMessenger();

	void SetNewValue(G4UIcommand* command, G4String newValues);

private:
	NewPrimaryGeneratorAction* target;
	G4UIcmdWithABool* 	setgunrandomCmd;
};

#endif
