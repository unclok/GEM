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
<<<<<<< HEAD
#include "G4UIcmdWith3Vector.hh"
=======
#include "G4UIcmdWithABool.hh"
>>>>>>> 4b15fd3620995b195aef0bb7f2adaa3f4806acb8
#include "G4ios.hh"

GEMPrimaryGeneratorMessenger::GEMPrimaryGeneratorMessenger(GEMPrimaryGeneratorAction * mpga)
:target(mpga)
{
<<<<<<< HEAD
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
=======
  momentumCmd = new G4UIcmdWithADoubleAndUnit("/mydet/momentum",this);
  momentumCmd->SetGuidance("Mean momentum of primaries");
  momentumCmd->SetParameterName("p",true);
  momentumCmd->SetRange("p>=0.");
  momentumCmd->SetDefaultValue(100.);
  momentumCmd->SetDefaultUnit("eV");

  sigmaMomCmd = new G4UIcmdWithADoubleAndUnit("/mydet/sigmaMomentum",this);
  sigmaMomCmd->SetGuidance("Sigma momentum of primaries");
  sigmaMomCmd->SetParameterName("p",true);
  sigmaMomCmd->SetRange("p>=0.");
  sigmaMomCmd->SetDefaultValue(100.);
  sigmaMomCmd->SetDefaultUnit("eV");

  sigmaAngCmd = new G4UIcmdWithADoubleAndUnit("/mydet/sigmaAngle",this);
  sigmaAngCmd->SetGuidance("sigma angle divergence of primaries");
  sigmaAngCmd->SetParameterName("t",true);
  sigmaAngCmd->SetRange("t>=0.");
  sigmaAngCmd->SetDefaultValue(1.);
  sigmaAngCmd->SetDefaultUnit("deg");

  randomCmd = new G4UIcmdWithABool("/mydet/randomizePrimary",this);
  randomCmd->SetGuidance("Boolean flag for randomizing primary particle types.");
  randomCmd->SetGuidance("In case this flag is false, you can select the primary particle");
  randomCmd->SetGuidance("  with /gun/particle command.");
  randomCmd->SetParameterName("flg",true);
  randomCmd->SetDefaultValue(true);
>>>>>>> 4b15fd3620995b195aef0bb7f2adaa3f4806acb8
}

GEMPrimaryGeneratorMessenger::~GEMPrimaryGeneratorMessenger()
{
<<<<<<< HEAD
  delete energyCmd;
  delete directionCmd;
=======
  delete momentumCmd;
  delete sigmaMomCmd;
  delete sigmaAngCmd;
  delete randomCmd;
>>>>>>> 4b15fd3620995b195aef0bb7f2adaa3f4806acb8
}

void GEMPrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
<<<<<<< HEAD
  if( command==energyCmd )
  { target->SetEnergy(energyCmd->GetNewDoubleValue(newValue)); }
  if( command==directionCmd )
  { target->SetDirection(directionCmd->GetNew3VectorValue(newValue)); }
=======
  if( command==momentumCmd )
  { target->SetMomentum(momentumCmd->GetNewDoubleValue(newValue)); }
  if( command==sigmaMomCmd )
  { target->SetSigmaMomentum(sigmaMomCmd->GetNewDoubleValue(newValue)); }
  if( command==sigmaAngCmd )
  { target->SetSigmaAngle(sigmaAngCmd->GetNewDoubleValue(newValue)); }
  if( command==randomCmd )
  { target->SetRandomize(randomCmd->GetNewBoolValue(newValue)); }
>>>>>>> 4b15fd3620995b195aef0bb7f2adaa3f4806acb8
}

G4String GEMPrimaryGeneratorMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
<<<<<<< HEAD
  if( command==energyCmd )
  { cv = energyCmd->ConvertToString(target->GetEnergy(),"eV"); }
  if( command==directionCmd )
  { cv = directionCmd->ConvertToString(target->GetDirection()); }
=======
  if( command==momentumCmd )
  { cv = momentumCmd->ConvertToString(target->GetMomentum(),"GeV"); }
  if( command==sigmaMomCmd )
  { cv = sigmaMomCmd->ConvertToString(target->GetSigmaMomentum(),"GeV"); }
  if( command==sigmaAngCmd )
  { cv = sigmaAngCmd->ConvertToString(target->GetSigmaAngle(),"deg"); }
  if( command==randomCmd )
  { cv = randomCmd->ConvertToString(target->GetRandomize()); }
>>>>>>> 4b15fd3620995b195aef0bb7f2adaa3f4806acb8

  return cv;
}

