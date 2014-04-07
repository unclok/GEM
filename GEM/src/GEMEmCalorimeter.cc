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
// $Id: GEMEmCalorimeter.cc,v 1.6 2006-06-29 16:32:33 gunter Exp $
// --------------------------------------------------------------
//
#include "GEMEmCalorimeter.hh"
#include "GEMEmCalorimeterHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

GEMEmCalorimeter::GEMEmCalorimeter(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="EMcalorimeterColl");
  HCID = -1;
}

GEMEmCalorimeter::~GEMEmCalorimeter(){;}

void GEMEmCalorimeter::Initialize(G4HCofThisEvent*HCE)
{
  hitsCollection = new GEMEmCalorimeterHitsCollection
                   (SensitiveDetectorName,collectionName[0]);
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection); }
  HCE->AddHitsCollection(HCID,hitsCollection);

  // fill calorimeter hits with zero energy deposition
  for(int i=0;i<80;i++)
  {
    GEMEmCalorimeterHit* aHit = new GEMEmCalorimeterHit(i);
    hitsCollection->insert( aHit );
  }
}

G4bool GEMEmCalorimeter::ProcessHits(G4Step*aStep,G4TouchableHistory* /*ROhist*/)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep==0.) return true;

  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4VPhysicalVolume* thePhysical = theTouchable->GetVolume();
  G4int copyNo = thePhysical->GetCopyNo();

  GEMEmCalorimeterHit* aHit = (*hitsCollection)[copyNo];
  // check if it is first touch
  if(!(aHit->GetLogV()))
  {
    // fill volume information
    aHit->SetLogV(thePhysical->GetLogicalVolume());
    G4AffineTransform aTrans = theTouchable->GetHistory()->GetTopTransform();
    aTrans.Invert();
    aHit->SetRot(aTrans.NetRotation());
    aHit->SetPos(aTrans.NetTranslation());
  }
  // add energy deposition
  aHit->AddEdep(edep);

  return true;
}

void GEMEmCalorimeter::EndOfEvent(G4HCofThisEvent* /*HCE*/)
{;}

