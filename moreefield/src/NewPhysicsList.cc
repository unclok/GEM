#include "G4VModularPhysicsList.hh"
#include "NewPhysicsList.hh"
#include "G4PhysListFactory.hh"
//#include "G4ProductionCuts.hh"

NewPhysicsList::NewPhysicsList() : G4VModularPhysicsList()
{
	G4VModularPhysicsList* phys = factory.GetReferencePhysList("FTFP_BERT_PEN");

	for(G4int i=0;;++i){
		G4VPhysicsConstructor* elem = const_cast<G4VPhysicsConstructor*>(phys->GetPhysics(i));
		if(elem == NULL) break;
		G4cout << "RegisterPhysics: " << elem->GetPhysicsName() << G4endl;
		RegisterPhysics(elem);
	}
}

NewPhysicsList::~NewPhysicsList()
{;}

//void NewPhysicsList::ConstructProcess()
//{;}

//void NewPhysicsList::ConstructParticle()
//{;}

void NewPhysicsList::SetCuts()
{
	G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(1*eV,G4ProductionCutsTable::GetProductionCutsTable()->GetHighEdgeEnergy());
//	G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(10*eV,"e-");
//	G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(10*eV,"e+");
//	G4ProductionCuts::PhysicsTableUpdated();
}
