//
// ********************************************************************
// * License and Disclaimer *
// * *
// * The Geant4 software is copyright of the Copyright Holders of *
// * the Geant4 Collaboration. It is provided under the terms and *
// * conditions of the Geant4 Software License, included in the file *
// * LICENSE and available at http://cern.ch/geant4/license . These *
// * include a list of copyright holders. *
// * *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work make any representation or warranty, express or implied, *
// * regarding this software system or assume any liability for its *
// * use. Please see the license in the file LICENSE and URL above *
// * for the full disclaimer and the limitation of liability. *
// * *
// * This code implementation is the result of the scientific and *
// * technical work of the GEANT4 collaboration. *
// * By using, copying, modifying or distributing the software (or *
// * any work based on the software) you agree to acknowledge its *
// * use in resulting scientific publications, and indicate your *
// * acceptance of all terms of the Geant4 Software license. *
// ********************************************************************
//
//
// $Id$
//
// PSEofSecondary
#include "PSEofSecondary.hh"
#include "BeamAnalysisManager.hh"
// (Description)
// This is a primitive scorer class for scoring number of secondaries
// in the Cell.
//
// Created: 2005-11-14 Tsukasa ASO, Akinori Kimura.
// Modify: 2011-09-09 T.Aso modify comment in PrintAll().
//
PSEofSecondary::PSEofSecondary(G4String name, G4int depth)
:G4VPrimitiveScorer(name,depth),HCID(-1),particleDef(0),
weighted(true)
{;}

PSEofSecondary::~PSEofSecondary()
{
	delete BeamAnalysisManager::Instance();
}

G4bool PSEofSecondary::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
  BeamAnalysisManager* man = BeamAnalysisManager::Instance();
//- check for newly produced particle. e.g. first step.
	if ( aStep->GetTrack()->GetCurrentStepNumber() != 1) return FALSE;
//- check for this is not a primary particle. e.g. ParentID > 0 .
	if ( aStep->GetTrack()->GetParentID() == 0 ) return FALSE;
//- check the particle if the partifle definition is given.
	if ( particleDef && particleDef != aStep->GetTrack()->GetDefinition() )
	return FALSE;
//
//- This is a newly produced secondary particle.
	G4int index = GetIndex(aStep);
	G4double energy = aStep->GetPreStepPoint()->GetKineticEnergy();
	if ( weighted ) energy *= aStep->GetPreStepPoint()->GetWeight();
	EvtMap->add(index,energy);
		man->FillH1(2,energy);
	return TRUE;
}

void PSEofSecondary::SetParticle(const G4String& particleName){
	G4ParticleDefinition* pd =
	G4ParticleTable::GetParticleTable()->FindParticle(particleName);
	if(!pd) {
		G4String msg = "Particle <";
		msg += particleName;
		msg += "> not found.";
		G4Exception("PSEofSecondary::SetParticle",
		"DetPS0101",FatalException,msg);
	}
	particleDef = pd;
}

void PSEofSecondary::Initialize(G4HCofThisEvent* HCE)
{
	EvtMap = new G4THitsMap<G4double>(detector->GetName(),GetName());
	if(HCID < 0) {HCID = GetCollectionID(0);}
	HCE->AddHitsCollection(HCID, (G4VHitsCollection*)EvtMap);
}

void PSEofSecondary::EndOfEvent(G4HCofThisEvent*)
{;}

void PSEofSecondary::clear(){
	EvtMap->clear();
}

void PSEofSecondary::DrawAll()
{;}

void PSEofSecondary::PrintAll()
{
	G4cout << " PrimitiveScorer " << GetName() << G4endl;
	G4cout << " Number of entries " << EvtMap->entries() << G4endl;
	std::map<G4int,G4double*>::iterator itr = EvtMap->GetMap()->begin();
	for(; itr != EvtMap->GetMap()->end(); itr++) {
		G4cout << " copy no.: " << itr->first
		<< " num of secondaries: " << *(itr->second)/GetUnitValue()
		<< G4endl;
	}
}

void PSEofSecondary::SetUnit(const G4String& unit)
{
	if (unit == "" ){
		unitName = unit;
		unitValue = 1.0;
	}else{
		G4String msg = "Invalid unit ["+unit+"] (Current unit is [" +GetUnit()+"] ) for " + GetName();
		G4Exception("PSEofSecondary::SetUnit","DetPS0010",JustWarning,msg);
	}
}
