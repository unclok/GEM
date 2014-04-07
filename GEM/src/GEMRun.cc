#include "GEMRun.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Event.hh"
#include "G4THitsMap.hh"

GEMRun::GEMRun() : nEvent(0)
{
  G4SDManager* SDM = G4SDManager::GetSDMpointer();
  totalSurfFluxID = SDM->GetCollectionID("myCellScorer/TotalSurfFlux");
  electronSurfFluxID = SDM->GetCollectionID("myCellScorer/ElectronSurfFlux");
  totalDoseID = SDM->GetCollectionID("myCellScorer/TotalDose");
  currentID = SDM->GetCollectionID("myCellScorer/Current");
  totalCurrentID = SDM->GetCollectionID("myCellScorer/TotalCurrent");
  energyID = SDM->GetCollectionID("myCellScorer/Energy");
}

GEMRun::~GEMRun()
{
}

void GEMRun::RecordEvent(const G4Event* evt)
{
  nEvent++;
  G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
  eventTotalSurfFlux = (G4THitsMap<G4double>*)(HCE->GetHC(totalSurfFluxID));
  eventelectronSurfFlux = (G4THitsMap<G4double>*)(HCE->GetHC(electronSurfFluxID));
  eventTotalDose = (G4THitsMap<G4double>*)(HCE->GetHC(totalDoseID));
  eventCurrent = (G4THitsMap<G4double>*)(HCE->GetHC(currentID));
  eventTotalCurrent = (G4THitsMap<G4double>*)(HCE->GetHC(totalCurrentID));
  eventEnergy = (G4THitsMap<G4double>*)(HCE->GetHC(energyID));
  totalSurfFlux += *eventTotalSurfFlux;
  electronSurfFlux += *eventelectronSurfFlux;
  totalDose += *eventTotalDose;
  current += *eventCurrent;
  totalCurrent += *eventTotalCurrent;
  energy += *eventEnergy;
}

G4double GEMRun::GetTotalSurfFlux()
{
  G4int key;
  G4double val=0;
  std::map<G4int,G4double*>::iterator itr = totalSurfFlux.GetMap()->begin();
  for( ; itr!=totalSurfFlux.GetMap()->end() ; itr++)
  {
    key = (itr->first);
//    val += *(itr->second);
  G4double* pVal = (totalSurfFlux)[key];
  if(pVal) val+=*pVal;
  }


  return val;
}

G4double GEMRun::GetElectronSurfFlux()
{
  G4int key;
  G4double val=0;
  std::map<G4int,G4double*>::iterator itr = electronSurfFlux.GetMap()->begin();
  for( ; itr!=electronSurfFlux.GetMap()->end() ; itr++)
  {
    key = (itr->first);
//    val += *(itr->second);
  G4double* pVal = (electronSurfFlux)[key];
  if(pVal) val+=*pVal;
  }


  return val;
}

G4double GEMRun::GetTotalDose()
{
  G4int key;
  G4double val=0;
  std::map<G4int,G4double*>::iterator itr = totalDose.GetMap()->begin();
  for( ; itr!=totalDose.GetMap()->end() ; itr++)
  {
    key = (itr->first);
//    val += *(itr->second);
  G4double* pVal = (totalDose)[key];
  if(pVal) val+=*pVal;
  }


  return val;
}

G4double GEMRun::GetCurrent()
{
  G4int key;
  G4double val=0;
  std::map<G4int,G4double*>::iterator itr = current.GetMap()->begin();
  for( ; itr!=current.GetMap()->end() ; itr++)
  {
    key = (itr->first);
//    val += *(itr->second);
  G4double* pVal = (current)[key];
  if(pVal) val+=*pVal;
  }


  return val;
}

G4double GEMRun::GetTotalCurrent()
{
  G4int key;
  G4double val=0;
  std::map<G4int,G4double*>::iterator itr = totalCurrent.GetMap()->begin();
  for( ; itr!=totalCurrent.GetMap()->end() ; itr++)
  {
    key = (itr->first);
//    val += *(itr->second);
  G4double* pVal = (totalCurrent)[key];
  if(pVal) val+=*pVal;
  }


  return val;
}

G4double GEMRun::GetEnergyAverage()
{
  G4int key;
  G4int n=0;
  G4double val=0;
  std::map<G4int,G4double*>::iterator itr = energy.GetMap()->begin();
  for( ; itr!=energy.GetMap()->end() ; itr++)
  {
    key = (itr->first);
//    val += *(itr->second);
  G4double* pVal = (energy)[key];
  if(pVal) val+=*pVal;
    n++;
  }


  return val/n;
}
