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
  G4cout << " # of total surface current of hodoscope1 : " << theRun->GetTotalSurfCurrent(1)/100 << G4endl;
  G4cout << " # of electron surface current hodoscope1 : " << theRun->GetElectronSurfCurrent(1)/100 << G4endl;
  G4cout << " # of total dose hodoscope1 : " << theRun->GetTotalDose(1) << G4endl;
//  G4cout << " # of secondary hodoscope1 : " << theRun->GetSecondaryCurrent(1) << G4endl;
  G4cout << " # of energy averagy hodoscope1 : " << theRun->GetEnergyAverage(1)/MeV << "eV" << G4endl;
  G4cout << "\n" << G4endl;

  G4cout << " # of total surface current of hodoscope2 : " << theRun->GetTotalSurfCurrent(2)/100 << G4endl;
  G4cout << " # of electron surface current hodoscope2 : " << theRun->GetElectronSurfCurrent(2)/100 << G4endl;
  G4cout << " # of total dose hodoscope2 : " << theRun->GetTotalDose(2) << G4endl;
//  G4cout << " # of secondary hodoscope2 : " << theRun->GetSecondaryCurrent(2) << G4endl;
  G4cout << " # of energy averagy hodoscope2 : " << theRun->GetEnergyAverage(2)/MeV << "eV" << G4endl;
  G4cout << "\n" << G4endl;

  G4cout << " # of current hodoscope3 : " << theRun->GetCurrent(1) << G4endl;
  G4cout << " # of secondary hodoscope1 : " << theRun->GetSecondaryCurrent(1) << G4endl;
  G4cout << "\n" << G4endl;

  G4cout << " gain : " << theRun->GetElectronSurfCurrent(2)/theRun->GetElectronSurfCurrent(1) << G4endl;
}
