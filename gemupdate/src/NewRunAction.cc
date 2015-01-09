#include "NewRunAction.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4Run.hh"
#include "NewRun.hh"
#include "NewRunActionMessenger.hh"
#include "BeamAnalysisManager.hh"
#include "G4UserRunAction.hh"
#include <cmath>
#include "CLHEP/Units/PhysicalConstants.h"

using namespace CLHEP;

NewRunAction::NewRunAction(NewDetectorConstruction* det, NewPrimaryGeneratorAction* prim) : G4UserRunAction(), nRun(0), fDetector(det), fPrimary(prim)
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
	analysisManager->CreateH1("h1d1","ionization de from function", 200, -100, 100);
	analysisManager->CreateH1("h1d2","n of electrons", 3, 1, 3);
	analysisManager->CreateH1("h1d3","Ionization energies of each ionization process", 200, -100, 100);
	analysisManager->CreateH1("energyatend","Energy at end",100,0,100);
	analysisManager->CreateH1("pofe","position of electrons at end",200,-100*um,100*um);
	analysisManager->CreateH1("h1d4","de of each multiscattering process", 200, -100, 100);
	analysisManager->CreateH1("h1d5","de of each bremsstrahlung process", 200, -100, 100);
	analysisManager->CreateH1("t1","colision for degree", 1000, 0, 180, 1000);
	analysisManager->CreateH1("t2","colision for degree eIoni", 1000, 0, 180);
	analysisManager->CreateH1("t3","colision for degree msc", 1000, 0, 180);
	analysisManager->CreateH1("t4","colision for degree conv", 1000, 0, 180);
	analysisManager->CreateH1("t5","colision for degree compt", 1000, 0, 180);
	analysisManager->CreateH1("t6","colision for degree eBrem", 1000, 0, 180);
	analysisManager->CreateH1("t7","colision for degree phot", 1000, 0, 180);
	analysisManager->CreateH1("t8","colision for degree hIoni", 1000, 0, 180);
	analysisManager->CreateH1("t9","colision for degree ionIoni", 1000, 0, 180);
	analysisManager->CreateH1("e1","colision for energy", 1000, 0, 180, 1000);
	analysisManager->CreateH1("e2","colision for energy eIoni", 1000, 0, 180);
	analysisManager->CreateH1("e3","colision for energy msc", 1000, 0, 180);
	analysisManager->CreateH1("e4","colision for energy conv", 1000, 0, 180);
	analysisManager->CreateH1("e5","colision for energy compt", 1000, 0, 180);
	analysisManager->CreateH1("e6","colision for energy eBrem", 1000, 0, 180);
	analysisManager->CreateH1("e7","colision for energy phot", 1000, 0, 180);
	analysisManager->CreateH1("e8","colision for energy hIoni", 1000, 0, 180);
	analysisManager->CreateH1("e9","colision for energy ionIoni", 1000, 0, 180);
	analysisManager->CreateH1("t10","colision for degree transportation", 1000, 0, 180);
	analysisManager->CreateH1("e10","colision for energy transportation", 1000, 0, 180);

	analysisManager->CreateH2("h1","e-field vs drift velocity", 1000, -150, 40, 1000, 0, 1.5*1e7);
	analysisManager->CreateH2("h2","colision for degree", 1000, 0, 180, 1000, 0, 1e-15);
	analysisManager->CreateH2("h3","colision for degree eIoni", 1000, 0, 180, 1000, 0, 1e-15);
	analysisManager->CreateH2("h4","colision for degree msc", 1000, 0, 180, 1000, 0, 1e-15);
	analysisManager->CreateH2("h5","colision for degree conv", 1000, 0, 180, 1000, 0, 1e-15);
	analysisManager->CreateH2("h6","colision for degree compt", 1000, 0, 180, 1000, 0, 1e-15);
	analysisManager->CreateH2("h7","colision for degree eBrem", 1000, 0, 180, 1000, 0, 1e-15);
	analysisManager->CreateH2("h8","colision for degree phot", 1000, 0, 180, 1000, 0, 1e-15);
	analysisManager->CreateH2("h9","colision for degree hIoni", 1000, 0, 180, 1000, 0, 1e-15);
	analysisManager->CreateH2("h10","colision for degree ionIoni", 1000, 0, 180, 1000, 0, 1e-15);
	analysisManager->CreateH2("h11","dedx", 1000, 0, 0.05, 1000, 0, 1e20);
	analysisManager->CreateH2("h12","2D position distribution at z=2000um", 100, -4050*um, 4050*um, 100, -2500*um, 2500*um);
	analysisManager->CreateH2("trackid","Track id and Parent id in z > 55 um", 1000, 0, 1000, 1000, 0, 1000);
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
