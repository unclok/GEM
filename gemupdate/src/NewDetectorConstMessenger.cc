#include "NewDetectorConstMessenger.hh"

NewDetectorConstMessenger::NewDetectorConstMessenger(NewDetectorConstruction * mpga)
:target(mpga)
{
  efieldCmd = new G4UIcmdWithABool("/mydet/setefield",this);
  efieldCmd->SetGuidance("Set field.");
  //efieldCmd->SetGuidance("Set an intencity of an uniform field.");
  efieldCmd->SetParameterName("true",false,false);
  //efieldCmd->SetParameterName("kilovolt/cm",false,true);

  efielddirectionCmd = new G4UIcmdWith3Vector("/mydet/setefielddirection",this);
  efielddirectionCmd->SetGuidance("Set a direction of an uniform field.");
  efielddirectionCmd->SetParameterName("x","y","z",false,true);
  efielddirectionCmd->SetDefaultValue(G4ThreeVector(0.,1.,0.));

  setgeometryCmd = new G4UIcmdWithABool("/mydet/setgeometry",this);
  setgeometryCmd->SetGuidance("Set detector geometry");
  setgeometryCmd->SetParameterName("true", false, false);

  setmaterialCmd = new G4UIcmdWithAString("/mydet/setmaterial",this);
  setmaterialCmd->SetCandidates("Ar Vacuum");
  setmaterialCmd->SetParameterName("material", false, false);

  getmaterialCmd = new G4UIcmdWithABool("/mydet/setgeometry",this);
  getmaterialCmd->SetGuidance("Get world material");
  getmaterialCmd->SetParameterName("true", true, true);
  getmaterialCmd->SetDefaultValue(true);

  getgeometryCmd = new G4UIcmdWithABool("/mydet/setgeometry",this);
  getgeometryCmd->SetGuidance("Get detector geometry");
  getgeometryCmd->SetParameterName("true", true, true);
  getgeometryCmd->SetDefaultValue(true);

  getefieldCmd = new G4UIcmdWithABool("/mydet/getefield",this);
  getefieldCmd->SetGuidance("Get an intencity of an uniform field.");
  getefieldCmd->SetParameterName("true", true, true);
  getefieldCmd->SetDefaultValue(true);

  getefielddirectionCmd = new G4UIcmdWithABool("/mydet/getefielddirection",this);
  getefielddirectionCmd->SetGuidance("Get a direction of an uniform field.");
  getefielddirectionCmd->SetParameterName("true", true, true);
  getefielddirectionCmd->SetDefaultValue(true);
}

NewDetectorConstMessenger::~NewDetectorConstMessenger()
{
  delete efieldCmd;
  delete efielddirectionCmd;
  delete setgeometryCmd;
  delete getgeometryCmd;
  delete getefieldCmd;
  delete getefielddirectionCmd;
}

void NewDetectorConstMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if( command==efieldCmd )
  { target->SetEField(efieldCmd->GetNewBoolValue(newValue)); }
  else if( command==efielddirectionCmd )
  { target->SetUniformFieldDirection(efielddirectionCmd->GetNew3VectorValue(newValue)); }
  else if( command==setgeometryCmd )
  { target->SetGeometryStatus(setgeometryCmd->GetNewBoolValue(newValue)); }
  else if( command==setmaterialCmd )
  { target->SetworldMaterial(newValue); }
}

G4String NewDetectorConstMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  if( command==getefieldCmd )
  { cv = getefieldCmd->ConvertToString(target->GetUniformField()); }
  else if( command==getefielddirectionCmd )
  { cv = getefielddirectionCmd->ConvertToString(target->GetUniformFieldDirection()); }
  else if( command==getgeometryCmd )
  { cv = getgeometryCmd->ConvertToString(target->GetGeometryStatus()); }
  else if( command==getmaterialCmd )
  { cv = getgeometryCmd->ConvertToString(target->GetworldMaterial()); }

  return cv;
}
