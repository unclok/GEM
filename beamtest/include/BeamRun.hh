#include "G4Run.hh"
#include "G4Event.hh"
#include "G4THitsMap.hh"
#include "A01DriftChamberHit.hh"
#include "G4ThreeVector.hh"
#include "BeamAnalysis.hh"

#ifndef BeamRun_h
#define BeamRun_h 1


class BeamRun : public G4Run
{
public:
	BeamRun();
	virtual ~BeamRun();
	virtual void RecordEvent(const G4Event*);

private:
	G4int nEvent;
	G4int totalSurfCurrentID1, electronSurfCurrentID1, energyID1;

	G4THitsMap<G4double> totalSurfCurrent1;
	G4THitsMap<G4double> electronSurfCurrent1;
	G4THitsMap<G4double> energy1;
	G4THitsMap<G4double>* eventTotalSurfCurrent1;
	G4THitsMap<G4double>* eventelectronSurfCurrent1;
	G4THitsMap<G4double>* eventEnergy1;

	G4int totalSurfCurrentID2, electronSurfCurrentID2, energyID2;

	G4THitsMap<G4double> totalSurfCurrent2;
	G4THitsMap<G4double> electronSurfCurrent2;
	G4THitsMap<G4double> energy2;
	G4THitsMap<G4double>* eventTotalSurfCurrent2;
	G4THitsMap<G4double>* eventelectronSurfCurrent2;
	G4THitsMap<G4double>* eventEnergy2;

	G4int currentID, secondaryCurrentID;

	G4THitsMap<G4double> current;
	G4THitsMap<G4double> secondaryCurrent;
	G4THitsMap<G4double>* eventCurrent;
	G4THitsMap<G4double>* eventSecondaryCurrent;

public:
	G4double GetTotalSurfCurrent(G4int);
	G4double GetElectronSurfCurrent(G4int);
	G4double GetEnergyAverage(G4int);
	G4double GetCurrent();
	G4double GetSecondaryCurrent();
};

#endif
