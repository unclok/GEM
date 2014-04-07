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
// $Id: GEMPrimaryGeneratorMessenger.cc,v 1.4 2006-06-29 16:33:07 gunter Exp $
// --------------------------------------------------------------
//
#include "GEMPrimaryGeneratorMessenger.hh"
#include "GEMPrimaryGeneratorAction.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4ios.hh"

GEMPrimaryGeneratorMessenger::GEMPrimaryGeneratorMessenger(GEMPrimaryGeneratorAction * mpga)
:target(mpga)
{
  energyCmd = new G4UIcmdWithADoubleAndUnit("/mydet/energy",this);
  energyCmd->SetGuidance("Mean energy of primaries");
  energyCmd->SetParameterName("en",true);
  energyCmd->SetRange("en>=0.");
  energyCmd->SetDefaultValue(1.);
  energyCmd->SetDefaultUnit("eV");

  directionCmd = new G4UIcmdWith3Vector("/mydet/direction",this);
  directionCmd->SetGuidance("Direction of primaries.");
  directionCmd->SetParameterName("x","y","z",false,true);
  directionCmd->SetDefaultValue(G4ThreeVector(0.,0.,1.));
}

GEMPrimaryGeneratorMessenger::~GEMPrimaryGeneratorMessenger()
{
  delete energyCmd;
  delete directionCmd;
}

void GEMPrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if( command==energyCmd )
  { target->SetEnergy(energyCmd->GetNewDoubleValue(newValue)); }
  if( command==directionCmd )
  { target->SetDirection(directionCmd->GetNew3VectorValue(newValue)); }
}

G4String GEMPrimaryGeneratorMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  if( command==energyCmd )
  { cv = energyCmd->ConvertToString(target->GetEnergy(),"eV"); }
  if( command==directionCmd )
  { cv = directionCmd->ConvertToString(target->GetDirection()); }

  return cv;
}

