//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: GEMElectricFieldMessenger.cc,v 1.4 2006-06-29 16:32:59 gunter Exp $
// --------------------------------------------------------------
//
#include "GEMElectricFieldMessenger.hh"
#include "GEMElectricField.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4ios.hh"

GEMElectricFieldMessenger::GEMElectricFieldMessenger(GEMElectricField * mpga)
:target(mpga)
{
  fieldCmd = new G4UIcmdWithAnInteger("/mydet/field",this);
  fieldCmd->SetGuidance("Field available : 10, 30, 40, 50, 70");
  fieldCmd->SetParameterName("field",true);
  fieldCmd->SetDefaultValue(40);
}

GEMElectricFieldMessenger::~GEMElectricFieldMessenger()
{
  delete fieldCmd;
}

void GEMElectricFieldMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if( command==fieldCmd )
  { target->SetField(fieldCmd->GetNewIntValue(newValue)); }
}

G4String GEMElectricFieldMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  if( command==fieldCmd )
  { cv = fieldCmd->ConvertToString(target->GetField()); }

  return cv;
}

