#include "G4Run.hh"
#include "G4Event.hh"
#include "G4THitsMap.hh"
#include "G4ThreeVector.hh"

class GEMRun : public G4Run
{
  public:
    GEMRun();
    virtual ~GEMRun();
    virtual void RecordEvent(const G4Event*);
  private:
    G4int nEvent;
    G4int totalSurfCurrentID1, electronSurfCurrentID1, totalDoseID1, secondaryCurrentID1, energyID1;
    G4THitsMap<G4double> totalSurfCurrent1;
    G4THitsMap<G4double> electronSurfCurrent1;
    G4THitsMap<G4double> totalDose1;
    G4THitsMap<G4double> secondaryCurrent1;
    G4THitsMap<G4double> energy1;
    G4THitsMap<G4double>* eventTotalSurfCurrent1;
    G4THitsMap<G4double>* eventelectronSurfCurrent1;
    G4THitsMap<G4double>* eventTotalDose1;
    G4THitsMap<G4double>* eventSecondaryCurrent1;
    G4THitsMap<G4double>* eventEnergy1;

    G4int currentID;
    G4THitsMap<G4double> current;
    G4THitsMap<G4double>* eventCurrent;

    G4int totalSurfCurrentID2, electronSurfCurrentID2, totalDoseID2, secondaryCurrentID2, energyID2;
    G4THitsMap<G4double> totalSurfCurrent2;
    G4THitsMap<G4double> electronSurfCurrent2;
    G4THitsMap<G4double> totalDose2;
    G4THitsMap<G4double> secondaryCurrent2;
    G4THitsMap<G4double> energy2;
    G4THitsMap<G4double>* eventTotalSurfCurrent2;
    G4THitsMap<G4double>* eventelectronSurfCurrent2;
    G4THitsMap<G4double>* eventTotalDose2;
    G4THitsMap<G4double>* eventSecondaryCurrent2;
    G4THitsMap<G4double>* eventEnergy2;

  public:
    G4double GetTotalSurfCurrent(G4int);
    G4double GetElectronSurfCurrent(G4int);
    G4double GetTotalDose(G4int);
    G4double GetCurrent(G4int);
    G4double GetSecondaryCurrent(G4int);
    G4double GetEnergyAverage(G4int);
    G4double GetCurrentTemplate(G4THitsMap<G4double>);
    G4double GetEnergyTemplate(G4THitsMap<G4double>);
};
