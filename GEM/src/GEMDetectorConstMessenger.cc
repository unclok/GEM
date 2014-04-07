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
// $Id: GEMDetectorConstMessenger.cc,v 1.4 2006-06-29 16:32:01 gunter Exp $
// --------------------------------------------------------------
//
#include "GEMDetectorConstMessenger.hh"
#include "GEMDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4ios.hh"

GEMDetectorConstMessenger::GEMDetectorConstMessenger(GEMDetectorConstruction* mpga)
:target(mpga)
{
  mydetDirectory = new G4UIdirectory("/mydet/");
  mydetDirectory->SetGuidance("GEM detector setup control commands.");

//  armCmd = new G4UIcmdWithADoubleAndUnit("/mydet/armAngle",this);
//  armCmd->SetGuidance("Rotation angle of the second arm.");
//  armCmd->SetParameterName("angle",true);
//  armCmd->SetRange("angle>=0. && angle<180.");
//  armCmd->SetDefaultValue(30.);
//  armCmd->SetDefaultUnit("deg");
}

GEMDetectorConstMessenger::~GEMDetectorConstMessenger()
{
//  delete armCmd;
  delete mydetDirectory;
}

void GEMDetectorConstMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
//  if( command==armCmd )
//  { target->SetArmAngle(armCmd->GetNewDoubleValue(newValue)); }
}

G4String GEMDetectorConstMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
//  if( command==armCmd )
//  { cv = armCmd->ConvertToString(target->GetArmAngle(),"deg"); }

  return cv;
}

