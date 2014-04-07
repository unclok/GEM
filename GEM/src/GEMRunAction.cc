#include "GEMRunAction.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Run.hh"
#include "GEMRun.hh"

GEMRunAction::GEMRunAction()
{
}

GEMRunAction::~GEMRunAction()
{
}

G4Run* GEMRunAction::GenerateRun()
{
  return (new GEMRun());
}

void GEMRunAction::BeginOfRunAction(const G4Run* aRun)
{
}

void GEMRunAction::EndOfRunAction(const G4Run* aRun)
{
  GEMRun* theRun = (GEMRun*)aRun;
  G4cout << " # of total surface flux : " << theRun->GetTotalSurfFlux() << G4endl;
  G4cout << " # of electron surface flux : " << theRun->GetElectronSurfFlux() << G4endl;
  G4cout << " # of total dose : " << theRun->GetTotalDose() << G4endl;
  G4cout << " # of current : " << theRun->GetCurrent() << G4endl;
  G4cout << " # of secondary : " << theRun->GetTotalCurrent() << G4endl;
  G4cout << " # of energy averagy : " << theRun->GetEnergyAverage() << G4endl;
}
