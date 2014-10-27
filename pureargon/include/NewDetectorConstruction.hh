#ifndef NewDetectorConstruction_h
#define NewDetectorConstruction_h 1

#include "NewDetectorConstMessenger.hh"
#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4FieldManager.hh"
#include "NewElectricField.hh"

#include "G4EqMagElectricField.hh"
#include "G4PropagatorInField.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"
#include "G4ClassicalRK4.hh"
#include "G4ThreeVector.hh"

class NewDetectorConstMessenger;
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

	inline void SetUniformField(G4double val) { fefield=val;
							SetEfield(argon_logical, fefielddirection, fefield);	 }
	inline void SetUniformFieldDirection(G4ThreeVector val) { fefielddirection=val;
							SetEfield(argon_logical, fefielddirection, fefield); }
	inline G4double GetUniformField() const { G4cout << fefield << "*kilovolt/cm" << G4endl;
						  return fefield; }
	inline G4ThreeVector GetUniformFieldDirection() const { G4cout << fefielddirection << fefielddirection.r() << G4endl;
							return fefielddirection; }

private:
	void ConstructMaterials();
	void DestroyMaterials();
	void DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth=0);
	void SetEfield(G4LogicalVolume* glogical, G4ThreeVector fdirection, G4double field);

	NewDetectorConstMessenger* messenger;

	NewElectricField* electricField;
	G4FieldManager* fieldMgr;

	G4Material* air;
	G4Material* argonGas;
	G4Material* galactic;
	G4Material* copper;
	G4Material* Kapton;

	G4LogicalVolume* argon_logical;

	G4VisAttributes* worldVisAtt;
	G4VisAttributes* argonVisAtt;
	G4VisAttributes* copperVisAtt;

	G4MagIntegratorStepper* pStepper;
	G4EqMagElectricField* pEquation;
	G4MagInt_Driver* pIntgrDriver;
	G4ChordFinder* pChordFinder;
	G4PropagatorInField* propInField;

	G4ThreeVector fefielddirection;
	G4double fefield;
};

#endif
