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
// $Id: GEMapp.cc,v 1.9 2009-11-14 14:41:13 allison Exp $
// --------------------------------------------------------------
//
// --------------------------------------------------------------
//      GEANT 4 - GEMapp
// --------------------------------------------------------------
// Comments
//   Tutorial for Geant4 lectures
// --------------------------------------------------------------


#include "G4RunManager.hh"
#include "G4UImanager.hh"
<<<<<<< HEAD
//#include "G4ScoringManager.hh"
=======
>>>>>>> 4b15fd3620995b195aef0bb7f2adaa3f4806acb8

#include "GEMDetectorConstruction.hh"
#include "GEMPhysicsList.hh"
#include "GEMPrimaryGeneratorAction.hh"
<<<<<<< HEAD
#include "GEMRunAction.hh"

#include "GEMEventAction.hh"

#include "G4PhysListFactory.hh"

=======

#include "GEMEventAction.hh"

>>>>>>> 4b15fd3620995b195aef0bb7f2adaa3f4806acb8
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

int main(int argc,char** argv)
{
  // RunManager construction
  G4RunManager* runManager = new G4RunManager;

<<<<<<< HEAD
//  G4ScoringManager* scManager = G4ScoringManager::GetScoringManager();
//  scManager->SetVerboseLevel(1);

=======
>>>>>>> 4b15fd3620995b195aef0bb7f2adaa3f4806acb8
#ifdef G4VIS_USE
  // Visualization manager construction
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  // mandatory user initialization classes
  runManager->SetUserInitialization(new GEMDetectorConstruction);
<<<<<<< HEAD
//  runManager->SetUserInitialization(new GEMPhysicsList);
  G4PhysListFactory factory;
  G4VModularPhysicsList* physlist = factory.GetReferencePhysList("FTFP_BERT_PEN");
  runManager->SetUserInitialization(physlist);
=======
  runManager->SetUserInitialization(new GEMPhysicsList);
>>>>>>> 4b15fd3620995b195aef0bb7f2adaa3f4806acb8

  // initialize Geant4 kernel
  runManager->Initialize();

  // mandatory user action class
  runManager->SetUserAction(new GEMPrimaryGeneratorAction);

  // optional user action classes
<<<<<<< HEAD
  //runManager->SetUserAction(new GEMEventAction);
  runManager->SetUserAction(new GEMRunAction);
=======
  runManager->SetUserAction(new GEMEventAction);
>>>>>>> 4b15fd3620995b195aef0bb7f2adaa3f4806acb8

  if(argc>1)
  // execute an argument macro file if exist
  {
    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else
  // start interactive session
  {
#ifdef G4UI_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    ui->SessionStart();
    delete ui;
#endif
  }

#ifdef G4VIS_USE
  delete visManager;
#endif

  delete runManager;

  return 0;
}

