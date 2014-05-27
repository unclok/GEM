#ifndef NewDetectorConstruction_h
#define NewDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4FieldManager.hh"
#include "G4ElectricField.hh"

#include "G4EqMagElectricField.hh"
#include "G4PropagatorInField.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"
#include "G4ClassicalRK4.hh"
#include "G4ThreeVector.hh"

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4ElectricField;

class NewDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	NewDetectorConstruction();
	virtual ~NewDetectorConstruction();
	virtual G4VPhysicalVolume* Construct();

private:
	void ConstructMaterials();
	void DestroyMaterials();
	void DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth=0);

	G4ElectricField* electricField;
	G4FieldManager* fieldMgr;

	G4Material* air;
	G4Material* argonGas;
	G4Material* galactic;

	G4VisAttributes* worldVisAtt;
	G4VisAttributes* argonVisAtt;

	G4MagIntegratorStepper* pStepper;
	G4EqMagElectricField* pEquation;
	G4MagInt_Driver* pIntgrDriver;
	G4ChordFinder* pChordFinder;
	G4PropagatorInField* propInField;
};

#endif
