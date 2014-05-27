#include "NewRunAction.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Run.hh"
#include "NewRun.hh"
#include <cmath>

NewRunAction::NewRunAction()
{
}

NewRunAction::~NewRunAction()
{
}

G4Run* NewRunAction::GenerateRun()
{
	return (new NewRun());
}

void NewRunAction::BeginOfRunAction(const G4Run* aRun)
{
}

void NewRunAction::EndOfRunAction(const G4Run* aRun)
{
	NewRun* theRun = (NewRun*)aRun;
	G4cout << " # of total surface current of hodoscope1 : " << theRun->GetTotalSurfCurrent(1) << G4endl;
	G4cout << " # of electron surface current hodoscope1 : " << theRun->GetElectronSurfCurrent(1) << G4endl;
	G4cout << " # of energy averagy hodoscope1 : " << std::sqrt(theRun->GetEnergyAverage(1)) << "MeV" << G4endl;
	G4cout << "\n" << G4endl;

	G4cout << " # of total surface current of hodoscope2 : " << theRun->GetTotalSurfCurrent(2) << G4endl;
	G4cout << " # of electron surface current hodoscope2 : " << theRun->GetElectronSurfCurrent(2) << G4endl;
	G4cout << " # of energy averagy hodoscope2 : " << std::sqrt(theRun->GetEnergyAverage(2)) << "MeV" << G4endl;
	G4cout << "\n" << G4endl;

	G4cout << " # of current hodoscope3 : " << theRun->GetCurrent() << G4endl;
	G4cout << " # of secondary hodoscope3 : " << theRun->GetSecondaryCurrent() << G4endl;
	G4cout << "\n" << G4endl;

	G4cout << " gain : " << theRun->GetElectronSurfCurrent(2)/theRun->GetElectronSurfCurrent(1) << G4endl;
}
