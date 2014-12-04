
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
// $Id$
// 
/// \file BeamEventAction.hh
/// \brief Definition of the BeamEventAction class

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "A01DriftChamberHit.hh"
#include "G4THitsMap.hh"
#include "globals.hh"

#ifndef BeamEventAction_h
#define BeamEventAction_h 1

class BeamEventAction : public G4UserEventAction
{
  public:
    BeamEventAction();
    virtual ~BeamEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
  private:
   
	G4int driftID1;
	A01DriftChamberHitsCollection* eventDrift1; 
	G4int driftID2;
	A01DriftChamberHitsCollection* eventDrift2; 

	G4int energyID2;
	G4THitsMap<G4double>* eventEnergy2;
	
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
