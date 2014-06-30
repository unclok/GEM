#include "NewRunAction.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Run.hh"
#include "NewRun.hh"
#include "BeamAnalysisManager.hh"
#include "G4UserRunAction.hh"
#include <cmath>

NewRunAction::NewRunAction() : G4UserRunAction(), nRun(0)
{
}

NewRunAction::~NewRunAction()
{
	delete BeamAnalysisManager::Instance();
}

G4Run* NewRunAction::GenerateRun()
{
	return (new NewRun());
}

void NewRunAction::BeginOfRunAction(const G4Run* aRun)
{
	// Create analysis manager
	BeamAnalysisManager* analysisManager = BeamAnalysisManager::Instance();

	// Open an output file
	char num[5];
	sprintf(num,"%d",nRun);
	G4String name = "proton" + G4String(num) + ".root";
	G4cout<<name<<","<<nRun<<G4endl;
	analysisManager->OpenFile(name);

	// Create histograms
	analysisManager->CreateH1("h1d1","Particle amount at z=10cm", 3, 1, 3);
	analysisManager->CreateH1("h1d2","Particle amount at z=50cm", 3, 1, 3);

	analysisManager->CreateH2("h1","2D Energy deposit distribution at z=10cm", 100, -5*cm, 5*cm, 100, -5*cm, 5*cm);
	analysisManager->CreateH2("h2","2D Energy deposit distribution at z=50cm", 100, -5*cm, 5*cm, 100, -5*cm, 5*cm);
	analysisManager->CreateH2("h3","2D position distribution at z=10cm", 100, -5*cm, 5*cm, 100, -5*cm, 5*cm);
	analysisManager->CreateH2("h4","2D position distribution at z=50cm", 100, -5*cm, 5*cm, 100, -5*cm, 5*cm);
}

void NewRunAction::EndOfRunAction(const G4Run* aRun)
{
	nRun++;
	NewRun* theRun = (NewRun*)aRun;
	G4cout << " # of total surface current of hodoscope1 :	 " << theRun->GetTotalSurfCurrent(1) << G4endl;
	G4cout << " # of electron surface current hodoscope1 :	 " << theRun->GetElectronSurfCurrent(1) << G4endl;
	G4cout << " # of energy averagy hodoscope1 :	 " << std::sqrt(theRun->GetEnergyAverage(1)) << "	MeV" << G4endl;
	G4cout << "\n" << G4endl;

	G4cout << " # of total surface current of hodoscope2 :	 " << theRun->GetTotalSurfCurrent(2) << G4endl;
	G4cout << " # of electron surface current hodoscope2 :	 " << theRun->GetElectronSurfCurrent(2) << G4endl;
	G4cout << " # of energy averagy hodoscope2 :	 " << std::sqrt(theRun->GetEnergyAverage(2)) << "	MeV" << G4endl;
	G4cout << "\n" << G4endl;

	G4cout << " # of current hodoscope3 :	 " << theRun->GetCurrent() << G4endl;
	G4cout << " # of secondary hodoscope3 :	 " << theRun->GetSecondaryCurrent() << G4endl;
	G4cout << "\n" << G4endl;

	G4cout << " gain :	 " << theRun->GetElectronSurfCurrent(2)/theRun->GetElectronSurfCurrent(1) << G4endl;

	// save histograms
	BeamAnalysisManager* man = BeamAnalysisManager::Instance();
      	
	man->Write();
	man->CloseFile();
}
