#include "NewDetectorConstMessenger.hh"

NewDetectorConstMessenger::NewDetectorConstMessenger(NewDetectorConstruction * mpga)
:target(mpga)
{
  eufieldCmd = new G4UIcmdWithADouble("/mydet/setefield",this);
  eufieldCmd->SetGuidance("Set an intencity of an uniform field.");
  eufieldCmd->SetParameterName("kilovolt/cm",false,true);
  eufieldCmd->SetDefaultValue(1.);

  eufielddirectionCmd = new G4UIcmdWith3Vector("/mydet/setefielddirection",this);
  eufielddirectionCmd->SetGuidance("Set a direction of an uniform field.");
  eufielddirectionCmd->SetParameterName("x","y","z",false,true);
  eufielddirectionCmd->SetDefaultValue(G4ThreeVector(0.,1.,0.));

  geteufieldCmd = new G4UIcmdWithABool("/mydet/getefield",this);
  geteufieldCmd->SetGuidance("Get an intencity of an uniform field.");
  geteufieldCmd->SetParameterName("true", true, true);
  geteufieldCmd->SetDefaultValue(true);

  geteufielddirectionCmd = new G4UIcmdWithABool("/mydet/getefielddirection",this);
  geteufielddirectionCmd->SetGuidance("Get a direction of an uniform field.");
  geteufielddirectionCmd->SetParameterName("true", true, true);
  geteufielddirectionCmd->SetDefaultValue(true);
}

NewDetectorConstMessenger::~NewDetectorConstMessenger()
{
  delete eufieldCmd;
  delete eufielddirectionCmd;
  delete geteufieldCmd;
  delete geteufielddirectionCmd;
}

void NewDetectorConstMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if( command==eufieldCmd )
  { target->SetUniformField(eufieldCmd->GetNewDoubleValue(newValue)); }
  else if( command==eufielddirectionCmd )
  { target->SetUniformFieldDirection(eufielddirectionCmd->GetNew3VectorValue(newValue)); }
}

G4String NewDetectorConstMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  if( command==geteufieldCmd )
  { cv = geteufieldCmd->ConvertToString(target->GetUniformField()); }
  else if( command==geteufielddirectionCmd )
  { cv = geteufielddirectionCmd->ConvertToString(target->GetUniformFieldDirection()); }

  return cv;
}
