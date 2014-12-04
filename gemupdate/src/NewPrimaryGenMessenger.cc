#include "NewPrimaryGenMessenger.hh"

NewPrimaryGenMessenger::NewPrimaryGenMessenger(NewPrimaryGeneratorAction * mpga)
:target(mpga)
{
	//set random shot of particles
  setgunrandomCmd = new G4UIcmdWithABool("/mydet/setgunrandom",this);
  setgunrandomCmd->SetGuidance("make gun direction random.");
  setgunrandomCmd->SetParameterName("true", false, true);
  setgunrandomCmd->SetDefaultValue(false);
}

NewPrimaryGenMessenger::~NewPrimaryGenMessenger()
{
  delete setgunrandomCmd;
}

void NewPrimaryGenMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if( command==setgunrandomCmd )
  { target->SetGunRandom(setgunrandomCmd->ConvertToBool(newValue)); }
}
