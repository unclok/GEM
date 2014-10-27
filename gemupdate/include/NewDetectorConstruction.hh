#ifndef NewDetectorConstruction_h
#define NewDetectorConstruction_h 1

#include "NewDetectorConstMessenger.hh"
#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4FieldManager.hh"
#include "NewElectricField.hh"
#include "GEMElectricField.hh"

#include "G4EqMagElectricField.hh"
#include "G4PropagatorInField.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"
#include "G4ClassicalRK4.hh"
#include "G4ThreeVector.hh"
#include "G4GDMLParser.hh"

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
	//						SetEfield(argon_logical, fieldMgr2, fefielddirection, fefield);	 }
}
	inline void SetUniformFieldDirection(G4ThreeVector val) { fefielddirection=val;
	//						SetEfield(argon_logical, fieldMgr2, fefielddirection, fefield); }
}
	inline G4double GetUniformField() const { G4cout << fefield << "*kilovolt/cm" << G4endl;
						  return fefield; }
	inline G4ThreeVector GetUniformFieldDirection() const { G4cout << fefielddirection << fefielddirection.r() << G4endl;
							return fefielddirection; }

private:
	void ConstructMaterials();
	void DestroyMaterials();
	void DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth=0);
	void SetEfield(G4LogicalVolume* glogical, G4FieldManager* fieldMgr, G4MagIntegratorStepper* pStepper, G4EqMagElectricField* pEquation, G4MagInt_Driver* pIntgrDriver, G4ChordFinder* pChordFinder, G4ThreeVector fdirection, G4double field);
	void SetGEMfield(G4LogicalVolume* glogical, G4FieldManager* fieldMgr, G4MagIntegratorStepper* pStepper, G4EqMagElectricField* pEquation, G4MagInt_Driver* pIntgrDriver, G4ChordFinder* pChordFinder);

	NewDetectorConstMessenger* messenger;

	NewElectricField* electricField;
	GEMElectricField* gemField;
	G4FieldManager* fieldMgr1;
	G4FieldManager* fieldMgr2;
	G4FieldManager* fieldMgr3;
	G4MagIntegratorStepper* pStepper1;
	G4EqMagElectricField* pEquation1;
	G4MagInt_Driver* pIntgrDriver1;
	G4ChordFinder* pChordFinder1;
	G4PropagatorInField* propInField1;
	G4MagIntegratorStepper* pStepper2;
	G4EqMagElectricField* pEquation2;
	G4MagInt_Driver* pIntgrDriver2;
	G4ChordFinder* pChordFinder2;
	G4PropagatorInField* propInField2;
	G4MagIntegratorStepper* pStepper3;
	G4EqMagElectricField* pEquation3;
	G4MagInt_Driver* pIntgrDriver3;
	G4ChordFinder* pChordFinder3;
	G4PropagatorInField* propInField3;




	G4Material* air;
	G4Material* argonGas;
	G4Material* galactic;
	G4Material* copper;
	G4Material* Kapton;

	G4LogicalVolume* argon_logical;
	G4LogicalVolume* gem;
	G4LogicalVolume* worldLogical;
	G4LogicalVolume* Drift1_logical;
	G4LogicalVolume* Drift2_logical;

	G4VisAttributes* worldVisAtt;
	G4VisAttributes* argonVisAtt;
	G4VisAttributes* copperVisAtt;

	G4ThreeVector fefielddirection;
	G4double fefield;
	G4GDMLParser fParser;
};

#endif
