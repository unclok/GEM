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
    G4int totalSurfFluxID1, electronSurfFluxID1, totalDoseID1, secondaryCurrentID1, energyID1;
    G4THitsMap<G4double> totalSurfFlux1;
    G4THitsMap<G4double> electronSurfFlux1;
    G4THitsMap<G4double> totalDose1;
    G4THitsMap<G4double> secondaryCurrent1;
    G4THitsMap<G4double> energy1;
    G4THitsMap<G4double>* eventTotalSurfFlux1;
    G4THitsMap<G4double>* eventelectronSurfFlux1;
    G4THitsMap<G4double>* eventTotalDose1;
    G4THitsMap<G4double>* eventSecondaryCurrent1;
    G4THitsMap<G4double>* eventEnergy1;

    G4int currentID;
    G4THitsMap<G4double> current;
    G4THitsMap<G4double>* eventCurrent;

    G4int totalSurfFluxID2, electronSurfFluxID2, totalDoseID2, secondaryCurrentID2, energyID2;
    G4THitsMap<G4double> totalSurfFlux2;
    G4THitsMap<G4double> electronSurfFlux2;
    G4THitsMap<G4double> totalDose2;
    G4THitsMap<G4double> secondaryCurrent2;
    G4THitsMap<G4double> energy2;
    G4THitsMap<G4double>* eventTotalSurfFlux2;
    G4THitsMap<G4double>* eventelectronSurfFlux2;
    G4THitsMap<G4double>* eventTotalDose2;
    G4THitsMap<G4double>* eventSecondaryCurrent2;
    G4THitsMap<G4double>* eventEnergy2;

  public:
    G4double GetTotalSurfFlux(G4int);
    G4double GetElectronSurfFlux(G4int);
    G4double GetTotalDose(G4int);
    G4double GetCurrent(G4int);
    G4double GetSecondaryCurrent(G4int);
    G4double GetEnergyAverage(G4int);
    G4double GetFluxTemplate(G4THitsMap<G4double>);
    G4double GetEnergyTemplate(G4THitsMap<G4double>);
};
