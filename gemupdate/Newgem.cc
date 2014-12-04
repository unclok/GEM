#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4PhysListFactory.hh"

#include "NewDetectorConstruction.hh"
#include "NewPrimaryGeneratorAction.hh"
#include "NewSteppingAction.hh"
#include "NewRunAction.hh"
#include "BeamEventAction.hh"
#include "NewPhysicsList.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#include "G4UItcsh.hh"
#include "G4UIterminal.hh"
#endif

int main(int argc, char** argv)
{
	// RunManager construction
	G4RunManager* runManager = new G4RunManager;

#ifdef G4VIS_USE
	// Visualization manager construction
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
#endif
	//choose the Random engine
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
	//set random seed with system time
	G4long seed = time(NULL);
	CLHEP::HepRandom::setTheSeed(seed);

	NewDetectorConstruction* det;
	runManager->SetUserInitialization(det = new NewDetectorConstruction);

	//If you want to use a physics list using physics factory, use physlist and comment out ExN02PhysicsList.
//	G4PhysListFactory factory;
//	G4VModularPhysicsList* physlist = factory.GetReferencePhysList("FTFP_BERT");
//	runManager->SetUserInitialization(physlist);
	runManager->SetUserInitialization(new ExN02PhysicsList);

	// initialize Geant4 kernel
	runManager->Initialize();

	// mandatory user action class
	NewPrimaryGeneratorAction* prim;
	runManager->SetUserAction(prim = new NewPrimaryGeneratorAction);

	// optianal user action classes
	runManager->SetUserAction(new BeamEventAction);

	// optianal user action classes
	runManager->SetUserAction(new NewRunAction(det, prim));

	// optianal user action classes
	runManager->SetUserAction(new NewSteppingAction);

	if(argc>1)
	// execute an argument macro file if exist
	{
		G4UImanager* UImanager = G4UImanager::GetUIpointer();
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command+fileName);
	}
	else	
	// start interactive session
	{
#ifdef G4UI_USE
		//Use tcsh only
		G4UIterminal* ui = new G4UIterminal(new G4UItcsh);
		ui->SessionStart();
		delete ui;
#endif
	}

#ifdef G4VIS_USE
	delete visManager;
#endif

	delete runManager;

	return 0;
}
