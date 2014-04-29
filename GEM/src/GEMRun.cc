#include "GEMRun.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Event.hh"
#include "G4THitsMap.hh"

GEMRun::GEMRun() : nEvent(0)
{
  G4SDManager* SDM = G4SDManager::GetSDMpointer();
  totalSurfFluxID1 = SDM->GetCollectionID("hodoscope1/TotalSurfFlux1");
  electronSurfFluxID1 = SDM->GetCollectionID("hodoscope1/ElectronSurfFlux1");
  totalDoseID1 = SDM->GetCollectionID("hodoscope1/TotalDose1");
  secondaryCurrentID1 = SDM->GetCollectionID("hodoscope1/SecondaryCurrent1");
  energyID1 = SDM->GetCollectionID("hodoscope1/Energy1");

  currentID = SDM->GetCollectionID("hodoscope3/Current");

  totalSurfFluxID2 = SDM->GetCollectionID("hodoscope2/TotalSurfFlux2");
  electronSurfFluxID2 = SDM->GetCollectionID("hodoscope2/ElectronSurfFlux2");
  totalDoseID2 = SDM->GetCollectionID("hodoscope2/TotalDose2");
  secondaryCurrentID2 = SDM->GetCollectionID("hodoscope2/SecondaryCurrent2");
  energyID2 = SDM->GetCollectionID("hodoscope2/Energy2");

}

GEMRun::~GEMRun()
{
}

void GEMRun::RecordEvent(const G4Event* evt)
{
  nEvent++;
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  eventTotalSurfFlux1 = (G4THitsMap<G4double>*)(HCE->GetHC(totalSurfFluxID1));
  eventelectronSurfFlux1 = (G4THitsMap<G4double>*)(HCE->GetHC(electronSurfFluxID1));
  eventTotalDose1 = (G4THitsMap<G4double>*)(HCE->GetHC(totalDoseID1));
  eventSecondaryCurrent1 = (G4THitsMap<G4double>*)(HCE->GetHC(secondaryCurrentID1));
  eventEnergy1 = (G4THitsMap<G4double>*)(HCE->GetHC(energyID1));
  totalSurfFlux1 += *eventTotalSurfFlux1;
  electronSurfFlux1 += *eventelectronSurfFlux1;
  totalDose1 += *eventTotalDose1;
  secondaryCurrent1 += *eventSecondaryCurrent1;
  energy1 += *eventEnergy1;

  eventCurrent = (G4THitsMap<G4double>*)(HCE->GetHC(currentID));
  current += *eventCurrent;

  eventTotalSurfFlux2 = (G4THitsMap<G4double>*)(HCE->GetHC(totalSurfFluxID2));
  eventelectronSurfFlux2 = (G4THitsMap<G4double>*)(HCE->GetHC(electronSurfFluxID2));
  eventTotalDose2 = (G4THitsMap<G4double>*)(HCE->GetHC(totalDoseID2));
  eventSecondaryCurrent2 = (G4THitsMap<G4double>*)(HCE->GetHC(secondaryCurrentID2));
  eventEnergy2 = (G4THitsMap<G4double>*)(HCE->GetHC(energyID2));
  totalSurfFlux2 += *eventTotalSurfFlux2;
  electronSurfFlux2 += *eventelectronSurfFlux2;
  totalDose2 += *eventTotalDose2;
  secondaryCurrent2 += *eventSecondaryCurrent2;
  energy2 += *eventEnergy2;

}

G4double GEMRun::GetFluxTemplate(G4THitsMap<G4double> temp)
{
  G4int key;
  G4double val=0;
  std::map<G4int,G4double*>::iterator itr = temp.GetMap()->begin();
  for( ; itr!=temp.GetMap()->end() ; itr++)
  {
    key = (itr->first);
    val += *(itr->second);
  G4double* pVal = (temp)[key];
  if(pVal) val+=*pVal;
  }


  return val;
}

G4double GEMRun::GetTotalSurfFlux(G4int id)
{
  if(id==1){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = totalSurfFlux1.GetMap()->begin();
	  for( ; itr!=totalSurfFlux1.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	    val += *(itr->second);
	  G4double* pVal = (totalSurfFlux1)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
	  return val;
  }
  else if(id==2){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = totalSurfFlux2.GetMap()->begin();
	  for( ; itr!=totalSurfFlux2.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	    val += *(itr->second);
	  G4double* pVal = (totalSurfFlux2)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
	  return val;
  }
  else return 1;
}

G4double GEMRun::GetElectronSurfFlux(G4int id)
{
  if(id==1){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = electronSurfFlux1.GetMap()->begin();
	  for( ; itr!=electronSurfFlux1.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	    val += *(itr->second);
	  G4double* pVal = (electronSurfFlux1)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
  return val;
  }
  else if(id==2){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = electronSurfFlux2.GetMap()->begin();
	  for( ; itr!=electronSurfFlux2.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	    val += *(itr->second);
	  G4double* pVal = (electronSurfFlux2)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
 	 return val;
  }
  else return 1;
}

G4double GEMRun::GetTotalDose(G4int id)
{
  if(id==1){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = totalDose1.GetMap()->begin();
	  for( ; itr!=totalDose1.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	    val += *(itr->second);
	  G4double* pVal = (totalDose1)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
	  return val;
  }
  else if(id==2){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = totalDose2.GetMap()->begin();
	  for( ; itr!=totalDose2.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	    val += *(itr->second);
	  G4double* pVal = (totalDose2)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
	  return val;
  }
  else return 1;
}

G4double GEMRun::GetCurrent(G4int id)
{
  G4int key;
  G4double val=0;
  std::map<G4int,G4double*>::iterator itr = current.GetMap()->begin();
  for( ; itr!=current.GetMap()->end() ; itr++)
  {
    key = (itr->first);
    val += *(itr->second);
  G4double* pVal = (current)[key];
  if(pVal) val+=*pVal;
  }


  return val;
}

G4double GEMRun::GetSecondaryCurrent(G4int id)
{
  if(id==1){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = secondaryCurrent1.GetMap()->begin();
	  for( ; itr!=secondaryCurrent1.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	    val += *(itr->second);
	  G4double* pVal = (secondaryCurrent1)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
	  return val;
  }
  else if(id==2){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = secondaryCurrent2.GetMap()->begin();
	  for( ; itr!=secondaryCurrent2.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	    val += *(itr->second);
	  G4double* pVal = (secondaryCurrent2)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
	  return val;
  }
  else return 1;
}

G4double GEMRun::GetEnergyTemplate(G4THitsMap<G4double> temp)
{
  G4int key;
  G4int n=0;
  G4double val=0;
  std::map<G4int,G4double*>::iterator itr = temp.GetMap()->begin();
  for( ; itr!=temp.GetMap()->end() ; itr++)
  {
    key = (itr->first);
    val += *(itr->second);
  G4double* pVal = (temp)[key];
  if(pVal) val+=*pVal;
    n++;
  }


  return val/n;
}

G4double GEMRun::GetEnergyAverage(G4int id)
{
  if(id==1){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = energy1.GetMap()->begin();
	  for( ; itr!=energy1.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	    val += *(itr->second);
	  G4double* pVal = (energy1)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
	  return val/n;
  }
  else if(id==2){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = energy2.GetMap()->begin();
	  for( ; itr!=energy2.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	    val += *(itr->second);
	  G4double* pVal = (energy2)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
	  return val/n;
  }
  else return 1;


}
