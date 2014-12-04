#include "NewRunActionMessenger.hh"

NewRunActionMessenger::NewRunActionMessenger(NewRunAction * mpga)
:target(mpga)
{
  //set a root file name
  setnameCmd = new G4UIcmdWithAString("/mydet/setfilename",this);
  setnameCmd->SetGuidance("Set a name of the file.");
  setnameCmd->SetParameterName("name",false,true);
  setnameCmd->SetDefaultValue("Beam");

  //check a root file name
  getnameCmd = new G4UIcmdWithABool("/mydet/getfilename",this);
  getnameCmd->SetGuidance("Get a name of the file.");
  getnameCmd->SetParameterName("name",false,true);
  getnameCmd->SetDefaultValue(true);
}


NewRunActionMessenger::~NewRunActionMessenger()
{
        delete setnameCmd;
        delete getnameCmd;
}

void NewRunActionMessenger::SetNewValue(G4UIcommand * command, G4String newValue)
{
        if( command==setnameCmd )
        {       target->SetFileName(newValue);  }
}

G4String NewRunActionMessenger::GetCurrentValue(G4UIcommand * command)
{
        G4String cv;
        if( command==getnameCmd )
        {       cv = getnameCmd->ConvertToString(target->GetFileName());        }

        return cv;
}
