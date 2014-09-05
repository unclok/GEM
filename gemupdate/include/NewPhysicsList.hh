#ifndef NewPhysicsList_h
#define NewPhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "G4PhysListFactory.hh"

class G4VModularPhysicsList;

class NewPhysicsList : public G4VModularPhysicsList
{
public:
	NewPhysicsList();
	virtual ~NewPhysicsList();

//	void ConstructProcess();
//	void ConstructParticle();
	void SetCuts();
private:
	G4PhysListFactory factory;
};
#endif
