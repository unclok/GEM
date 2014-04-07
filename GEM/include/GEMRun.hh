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
    G4int totalSurfFluxID, electronSurfFluxID, totalDoseID, currentID, totalCurrentID, energyID;
    G4THitsMap<G4double> totalSurfFlux;
    G4THitsMap<G4double> electronSurfFlux;
    G4THitsMap<G4double> totalDose;
    G4THitsMap<G4double> current;
    G4THitsMap<G4double> totalCurrent;
    G4THitsMap<G4double> energy;
    G4THitsMap<G4double>* eventTotalSurfFlux;
    G4THitsMap<G4double>* eventelectronSurfFlux;
    G4THitsMap<G4double>* eventTotalDose;
    G4THitsMap<G4double>* eventCurrent;
    G4THitsMap<G4double>* eventTotalCurrent;
    G4THitsMap<G4double>* eventEnergy;

  public:
    G4double GetTotalSurfFlux();
    G4double GetElectronSurfFlux();
    G4double GetTotalDose();
    G4double GetCurrent();
    G4double GetTotalCurrent();
    G4double GetEnergyAverage();
};
