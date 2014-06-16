#include "G4VPrimitiveScorer.hh"
#include "G4THitsMap.hh"

#ifndef BeamEnergyDetector_h
#define BeamEnergyDetector_h 1

class BeamEnergyDetector : public G4VPrimitiveScorer{
public :
	BeamEnergyDetector(G4String name, G4int depth=0);
	BeamEnergyDetector(G4String name, const G4String& unit, G4int depth=0);
	virtual ~BeamEnergyDetector();
	virtual void Initialize(G4HCofThisEvent*);
	virtual void EndOfEvent(G4HCofThisEvent*);
	virtual void clear();
	virtual void DrawAll();
	virtual void PrintAll();
	virtual void SetUnit(const G4String& unit);

protected :
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);

private :
	G4int HCID;
	G4THitsMap<G4double>* EvtMap;
	
};

#endif
