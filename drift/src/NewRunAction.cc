#include "NewRunAction.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Run.hh"
#include "NewRun.hh"
#include "NewRunActionMessenger.hh"
#include "BeamAnalysisManager.hh"
#include "G4UserRunAction.hh"
#include <cmath>

NewRunAction::NewRunAction() : G4UserRunAction(), nRun(0)
{
	messenger = new NewRunActionMessenger(this);
}

NewRunAction::~NewRunAction()
{
	delete BeamAnalysisManager::Instance();
	delete messenger;
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
	G4String fname = name + G4String(num) + ".root";
	G4cout<<fname<<","<<nRun<<G4endl;
	analysisManager->OpenFile(fname);

	// Create histograms
	analysisManager->CreateH1("h1d1","Particle amount at z=-35um", 3, 1, 3);
	analysisManager->CreateH1("h1d2","Particle amount at z=35um", 3, 1, 3);

	analysisManager->CreateH2("h1","2D Energy deposit distribution at z=-25um", 100, -50*um, 50*um, 100, -50*um, 50*um);
	analysisManager->CreateH2("h2","2D Energy deposit distribution at z=25um", 100, -50*um, 50*um, 100, -50*um, 50*um);
	analysisManager->CreateH2("h3","2D position distribution at z=-25um", 100, -50*um, 50*um, 100, -50*um, 50*um);
	analysisManager->CreateH2("h4","2D position distribution at z=25um", 100, -50*um, 50*um, 100, -50*um, 50*um);
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

void NewRunAction::SetFileName(G4String val){
	name = val;
}
