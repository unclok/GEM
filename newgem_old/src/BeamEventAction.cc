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
// $Id$
// 
/// \file BeamEventAction.cc
/// \brief Implementation of the BeamEventAction class

#include "BeamEventAction.hh"
#include "BeamAnalysisManager.hh"

#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BeamEventAction::BeamEventAction()
 : G4UserEventAction()
{
	G4SDManager* SDM = G4SDManager::GetSDMpointer();
	driftID1 = SDM->GetCollectionID("drift1/driftChamberColl");
	driftID2 = SDM->GetCollectionID("drift2/driftChamberColl");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

BeamEventAction::~BeamEventAction()
{
	delete BeamAnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BeamEventAction::BeginOfEventAction(const G4Event* evt)
{  

  G4int eventID = evt->GetEventID();
    if(eventID%10==0)G4cout << "\n---> Begin of event: " << eventID << G4endl;
    //CLHEP::HepRandom::showEngineStatus();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void BeamEventAction::EndOfEventAction(const G4Event* evt)
{
  // Accumulate statistics
  //

  // get analysis manager
  BeamAnalysisManager* man = BeamAnalysisManager::Instance();

  // fill histograms
	G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
	eventDrift1 = (A01DriftChamberHitsCollection*)(HCE->GetHC(driftID1));
	A01DriftChamberHit* driftHit1;
	for(int i=0;i<eventDrift1->entries();i++)
	{	
		driftHit1 = (*eventDrift1)[i];
		if(evt->GetEventID()%10==0)G4cout<<"drift1"<<G4endl;
//		if(evt->GetEventID()%10==0)G4cout<<"particle ID:"<< driftHit1->GetParticleID()<<" x:"<<driftHit1->GetLocalPos().x()<<" y:"<<driftHit1->GetLocalPos().y()<<" E:"<<driftHit1->GetEnergy()<<G4endl;
			man->FillH2(0,driftHit1->GetLocalPos().x(),driftHit1->GetLocalPos().y(),driftHit1->GetEnergy());
			man->FillH2(2,driftHit1->GetLocalPos().x(),driftHit1->GetLocalPos().y());
			man->FillH1(0,driftHit1->GetParticleID());
//		man->FillNtuple(0,driftHit1->GetLocalPos().x(),driftHit1->GetLocalPos().y(),driftHit1->GetEnergy());
	}
	
	eventDrift2 = (A01DriftChamberHitsCollection*)(HCE->GetHC(driftID2));
	A01DriftChamberHit* driftHit2;
	for(int i=0;i<eventDrift2->entries();i++)
	{
		driftHit2 = (*eventDrift2)[i];
		if(evt->GetEventID()%10==0)G4cout<<"drift2"<<G4endl;
//		if(evt->GetEventID()%10==0)G4cout<<"particle name:"<< driftHit2->GetParticleID()<<" x:"<<driftHit2->GetLocalPos().x()<<" y:"<<driftHit2->GetLocalPos().x()<<" E:"<<driftHit2->GetEnergy()<<G4endl;
			man->FillH2(1,driftHit2->GetLocalPos().x(),driftHit2->GetLocalPos().y(),driftHit2->GetEnergy());
			man->FillH2(3,driftHit2->GetLocalPos().x(),driftHit2->GetLocalPos().y());
			man->FillH1(1,driftHit2->GetParticleID());
//		man->FillNtuple(1,driftHit2->GetLocalPos().x(),driftHit2->GetLocalPos().y(),driftHit2->GetEnergy());
	} 
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
