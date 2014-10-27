#ifndef NewElectricField_h
#define NewElectricField_h 1

#include "G4ElectricField.hh"
#include "G4ThreeVector.hh"

class NewElectricField : public G4ElectricField
{
public:
	NewElectricField(const G4ThreeVector &fieldVector);
	virtual ~NewElectricField();

	void SetFieldValue(const G4ThreeVector& newFieldValue);
	void GetFieldValue(const G4double[4],G4double *fieldBandE) const;

private:
	G4double fFieldComponents[6];
};

#endif
