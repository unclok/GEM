#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4PhysListFactory.hh"

#include "NewDetectorConstruction.hh"
#include "NewPrimaryGeneratorAction.hh"
#include "NewRunAction.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
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

	runManager->SetUserInitialization(new NewDetectorConstruction);
	G4PhysListFactory factory;
	G4VModularPhysicsList* physlist = factory.GetReferencePhysList("FTFP_BERT_LIV");
	runManager->SetUserInitialization(physlist);

	// initialize Geant4 kernel
	runManager->Initialize();

	// mandatory user action class
	runManager->SetUserAction(new NewPrimaryGeneratorAction);

	// optianal user action classes
	runManager->SetUserAction(new NewRunAction);

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
		G4UIExecutive* ui = new G4UIExecutive(argc, argv);
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
