#ifndef NewRunActionMessenger_h
#define NewRunActionMessenger_h 1

#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "NewRunAction.hh"
#include "G4UIcommand.hh"
#include "G4UImessenger.hh"
#include "G4ios.hh"

class NewRunAction;
class G4UIcmdWithAString;
class G4UIcmdWithABool;

class NewRunActionMessenger: public G4UImessenger
{
public:
        NewRunActionMessenger(NewRunAction* mpga);
        ~NewRunActionMessenger();

        void SetNewValue(G4UIcommand* command, G4String newValues);
        G4String GetCurrentValue(G4UIcommand* command);

private:
        NewRunAction* target;
        G4UIcmdWithAString* setnameCmd;
        G4UIcmdWithABool* getnameCmd;
};

#endif
