#include "NewRun.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Event.hh"
#include "G4THitsMap.hh"

NewRun::NewRun() : nEvent(0)
{
	G4SDManager* SDM = G4SDManager::GetSDMpointer();
	totalSurfCurrentID1 = SDM->GetCollectionID("hodoscope1/TotalSurfCurrent1");
	electronSurfCurrentID1 = SDM->GetCollectionID("hodoscope1/ElectronSurfCurrent1");
	energyID1 = SDM->GetCollectionID("hodoscope1/Energy1");

	totalSurfCurrentID2 = SDM->GetCollectionID("hodoscope2/TotalSurfCurrent2");
	electronSurfCurrentID2 = SDM->GetCollectionID("hodoscope2/ElectronSurfCurrent2");
	energyID2 = SDM->GetCollectionID("hodoscope2/Energy2");

	currentID = SDM->GetCollectionID("hodoscope3/Current");
	secondaryCurrentID = SDM->GetCollectionID("hodoscope3/SecondaryCurrent");
}

NewRun::~NewRun()
{
}

void NewRun::RecordEvent(const G4Event* evt)
{
	nEvent++;
	G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
	eventTotalSurfCurrent1 = (G4THitsMap<G4double>*)(HCE->GetHC(totalSurfCurrentID1));
	eventelectronSurfCurrent1 = (G4THitsMap<G4double>*)(HCE->GetHC(electronSurfCurrentID1));
	eventEnergy1 = (G4THitsMap<G4double>*)(HCE->GetHC(energyID1));
	totalSurfCurrent1 += *eventTotalSurfCurrent1;
	electronSurfCurrent1 += *eventelectronSurfCurrent1;
	energy1 += *eventEnergy1;

	eventTotalSurfCurrent2 = (G4THitsMap<G4double>*)(HCE->GetHC(totalSurfCurrentID2));
	eventelectronSurfCurrent2 = (G4THitsMap<G4double>*)(HCE->GetHC(electronSurfCurrentID2));
	eventEnergy2 = (G4THitsMap<G4double>*)(HCE->GetHC(energyID2));
	totalSurfCurrent2 += *eventTotalSurfCurrent2;
	electronSurfCurrent2 += *eventelectronSurfCurrent2;
	energy2 += *eventEnergy2;

	eventCurrent = (G4THitsMap<G4double>*)(HCE->GetHC(currentID));
	current += *eventCurrent;
	eventSecondaryCurrent = (G4THitsMap<G4double>*)(HCE->GetHC(secondaryCurrentID));
	secondaryCurrent += *eventSecondaryCurrent;
}

G4double NewRun::GetTotalSurfCurrent(G4int id)
{
	if(id==1){
		G4int key;
		G4int n=0;
		G4double val=0;
		std::map<G4int,G4double*>::iterator itr = totalSurfCurrent1.GetMap()->begin();
		for(;itr!=totalSurfCurrent1.GetMap()->end();itr++)
		{
			key = (itr->first);
			G4double* pVal = (totalSurfCurrent1)[key];
			if(pVal){
				val+=*pVal;
				n++;
			}
		}

		return val;
	}

	else if(id==2){
		G4int key;
		G4int n=0;
		G4double val=0;
		std::map<G4int,G4double*>::iterator itr = totalSurfCurrent2.GetMap()->begin();
		for(;itr!=totalSurfCurrent2.GetMap()->end();itr++)
		{
			key = (itr->first);
			G4double* pVal = (totalSurfCurrent2)[key];
			if(pVal){
				val+=*pVal;
				n++;
			}
		}

		return val;
	}

	else return 1;
}	

G4double NewRun::GetElectronSurfCurrent(G4int id)
{
	if(id==1){
		G4int key;
		G4int n=0;
		G4double val=0;
		std::map<G4int,G4double*>::iterator itr = electronSurfCurrent1.GetMap()->begin();
		for(;itr!=electronSurfCurrent1.GetMap()->end();itr++)
		{
			key = (itr->first);
			G4double* pVal = (electronSurfCurrent1)[key];
			if(pVal){
				val+=*pVal;
				n++;
			}
		}

		return val;
	}

	else if(id==2){
		G4int key;
		G4int n=0;
		G4double val=0;
		std::map<G4int,G4double*>::iterator itr = electronSurfCurrent2.GetMap()->begin();
		for(;itr!=electronSurfCurrent2.GetMap()->end();itr++)
		{
			key = (itr->first);
			G4double* pVal = (electronSurfCurrent2)[key];
			if(pVal){
				val+=*pVal;
				n++;
			}
		}

		return val;
	}

	else return 1;
}	
	 
G4double NewRun::GetEnergyAverage(G4int id)
{
	if(id==1){
		G4int key;
		G4int n=0;
		G4double val=0;
		std::map<G4int,G4double*>::iterator itr = energy1.GetMap()->begin();
		for(;itr!=energy1.GetMap()->end();itr++)
		{
			key = (itr->first);
			G4double* pVal = (energy1)[key];
			if(pVal){
				val+=*pVal;
				n++;
			}
		}
		G4double result=val/(G4double)nEvent;
		return result;
	}

	else if(id==2){
		G4int key;
		G4int n=0;
		G4double val=0;
		std::map<G4int,G4double*>::iterator itr = energy2.GetMap()->begin();
		for(;itr!=energy2.GetMap()->end();itr++)
		{
			key = (itr->first);
			G4double* pVal = (energy2)[key];
			if(pVal){
				val+=*pVal;
				n++;
			}
		}

		G4double result=val/(G4double)nEvent;
		return result;
	}

	else return 1;
}	

G4double NewRun::GetCurrent()
{
	G4int key;
	G4int n=0;
	G4double val=0;
	std::map<G4int,G4double*>::iterator itr = current.GetMap()->begin();
	for(;itr!=current.GetMap()->end();itr++)
	{
		key = (itr->first);
		G4double* pVal = (current)[key];
		if(pVal){
			val+=*pVal;
			n++;
		}
	}
	return val;
}

G4double NewRun::GetSecondaryCurrent()
{
	G4int key;
	G4int n=0;
	G4double val=0;
	std::map<G4int,G4double*>::iterator itr = secondaryCurrent.GetMap()->begin();
	for(;itr!=secondaryCurrent.GetMap()->end();itr++)
	{
		key = (itr->first);
		G4double* pVal = (secondaryCurrent)[key];
		if(pVal){
			val+=*pVal;
			n++;
		}
	}
	return val;
}
