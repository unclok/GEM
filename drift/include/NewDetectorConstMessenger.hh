#ifndef NewDetectorConstMessenger_h
#define NewDetectorConstMessenger_h 1

#include "NewDetectorConstruction.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UImessenger.hh"
#include "G4ios.hh"

class NewDetectorConstruction;
class G4UIcmdWithADouble;
class G4UIcmdWith3Vector;
class G4UIcmdWithABool;

class NewDetectorConstMessenger: public G4UImessenger
{
public:
	NewDetectorConstMessenger(NewDetectorConstruction* mpga);
	~NewDetectorConstMessenger();

	void SetNewValue(G4UIcommand* command, G4String newValues);
	G4String GetCurrentValue(G4UIcommand* command);

private:
	NewDetectorConstruction* target;
	G4UIcmdWithADouble* 	eufieldCmd;
	G4UIcmdWith3Vector* 	eufielddirectionCmd;
	G4UIcmdWithABool* 	geteufieldCmd;
	G4UIcmdWithABool* 	geteufielddirectionCmd;
};

#endif