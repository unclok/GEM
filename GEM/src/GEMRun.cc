#include "GEMRun.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Event.hh"
#include "G4THitsMap.hh"

GEMRun::GEMRun() : nEvent(0)
{
  G4SDManager* SDM = G4SDManager::GetSDMpointer();
  totalSurfCurrentID1 = SDM->GetCollectionID("hodoscope1/TotalSurfCurrent1");
  electronSurfCurrentID1 = SDM->GetCollectionID("hodoscope1/ElectronSurfCurrent1");
  totalDoseID1 = SDM->GetCollectionID("hodoscope1/TotalDose1");
  //secondaryCurrentID1 = SDM->GetCollectionID("hodoscope1/SecondaryCurrent1");
  energyID1 = SDM->GetCollectionID("hodoscope1/Energy1");

  currentID = SDM->GetCollectionID("hodoscope3/Current");
  secondaryCurrentID1 = SDM->GetCollectionID("hodoscope3/SecondaryCurrent1");

  totalSurfCurrentID2 = SDM->GetCollectionID("hodoscope2/TotalSurfCurrent2");
  electronSurfCurrentID2 = SDM->GetCollectionID("hodoscope2/ElectronSurfCurrent2");
  totalDoseID2 = SDM->GetCollectionID("hodoscope2/TotalDose2");
  //secondaryCurrentID2 = SDM->GetCollectionID("hodoscope2/SecondaryCurrent2");
  energyID2 = SDM->GetCollectionID("hodoscope2/Energy2");

}

GEMRun::~GEMRun()
{
}

void GEMRun::RecordEvent(const G4Event* evt)
{
  nEvent++;
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  eventTotalSurfCurrent1 = (G4THitsMap<G4double>*)(HCE->GetHC(totalSurfCurrentID1));
  eventelectronSurfCurrent1 = (G4THitsMap<G4double>*)(HCE->GetHC(electronSurfCurrentID1));
  eventTotalDose1 = (G4THitsMap<G4double>*)(HCE->GetHC(totalDoseID1));
  //eventSecondaryCurrent1 = (G4THitsMap<G4double>*)(HCE->GetHC(secondaryCurrentID1));
  eventEnergy1 = (G4THitsMap<G4double>*)(HCE->GetHC(energyID1));
  totalSurfCurrent1 += *eventTotalSurfCurrent1;
  electronSurfCurrent1 += *eventelectronSurfCurrent1;
  totalDose1 += *eventTotalDose1;
  //secondaryCurrent1 += *eventSecondaryCurrent1;
  energy1 += *eventEnergy1;

  eventCurrent = (G4THitsMap<G4double>*)(HCE->GetHC(currentID));
  current += *eventCurrent;
  eventSecondaryCurrent1 = (G4THitsMap<G4double>*)(HCE->GetHC(secondaryCurrentID1));
  secondaryCurrent1 += *eventSecondaryCurrent1;

  eventTotalSurfCurrent2 = (G4THitsMap<G4double>*)(HCE->GetHC(totalSurfCurrentID2));
  eventelectronSurfCurrent2 = (G4THitsMap<G4double>*)(HCE->GetHC(electronSurfCurrentID2));
  eventTotalDose2 = (G4THitsMap<G4double>*)(HCE->GetHC(totalDoseID2));
  //eventSecondaryCurrent2 = (G4THitsMap<G4double>*)(HCE->GetHC(secondaryCurrentID2));
  eventEnergy2 = (G4THitsMap<G4double>*)(HCE->GetHC(energyID2));
  totalSurfCurrent2 += *eventTotalSurfCurrent2;
  electronSurfCurrent2 += *eventelectronSurfCurrent2;
  totalDose2 += *eventTotalDose2;
  //secondaryCurrent2 += *eventSecondaryCurrent2;
  energy2 += *eventEnergy2;

}

G4double GEMRun::GetCurrentTemplate(G4THitsMap<G4double> temp)
{
  G4int key;
  G4double val=0;
  std::map<G4int,G4double*>::iterator itr = temp.GetMap()->begin();
  for( ; itr!=temp.GetMap()->end() ; itr++)
  {
    key = (itr->first);
  //  val += *(itr->second);
  G4double* pVal = (temp)[key];
  if(pVal) val+=*pVal;
  }


  return val;
}

G4double GEMRun::GetTotalSurfCurrent(G4int id)
{
  if(id==1){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = totalSurfCurrent1.GetMap()->begin();
	  for( ; itr!=totalSurfCurrent1.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	  //  val += *(itr->second);
	  G4double* pVal = (totalSurfCurrent1)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
	  return val;
  }
  else if(id==2){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = totalSurfCurrent2.GetMap()->begin();
	  for( ; itr!=totalSurfCurrent2.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	  //  val += *(itr->second);
	  G4double* pVal = (totalSurfCurrent2)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
	  return val;
  }
  else return 1;
}

G4double GEMRun::GetElectronSurfCurrent(G4int id)
{
  if(id==1){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = electronSurfCurrent1.GetMap()->begin();
	  for( ; itr!=electronSurfCurrent1.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	 //   val += *(itr->second);
	  G4double* pVal = (electronSurfCurrent1)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
  return val;
  }
  else if(id==2){
	  G4int key;
	  G4int n=0;
	  G4double val=0;
	  std::map<G4int,G4double*>::iterator itr = electronSurfCurrent2.GetMap()->begin();
	  for( ; itr!=electronSurfCurrent2.GetMap()->end() ; itr++)
	  {
	    key = (itr->first);
	  //  val += *(itr->second);
	  G4double* pVal = (electronSurfCurrent2)[key];
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
	  //  val += *(itr->second);
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
	  //  val += *(itr->second);
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
  //  val += *(itr->second);
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
	  //  val += *(itr->second);
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
	  //  val += *(itr->second);
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
  //  val += *(itr->second);
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
	  //  val += *(itr->second);
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
	  //  val += *(itr->second);
	  G4double* pVal = (energy2)[key];
	  if(pVal) val+=*pVal;
	    n++;
	  }
	  return val/n;
  }
  else return 1;


}
