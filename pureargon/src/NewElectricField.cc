#include "NewElectricField.hh"

NewElectricField::NewElectricField(const G4ThreeVector &fieldVector)
{
	fFieldComponents[0] = 0.0;
	fFieldComponents[1] = 0.0;
	fFieldComponents[2] = 0.0;
	fFieldComponents[3] = fieldVector.x();
	fFieldComponents[4] = fieldVector.y();
	fFieldComponents[5] = fieldVector.z();
}

NewElectricField::~NewElectricField()
{
}

void NewElectricField::SetFieldValue(const G4ThreeVector& newFieldVector )
{
	fFieldComponents[0] = 0.0;
	fFieldComponents[1] = 0.0;
	fFieldComponents[2] = 0.0;
	fFieldComponents[3] = newFieldVector.x();
	fFieldComponents[4] = newFieldVector.y();
	fFieldComponents[5] = newFieldVector.z();
}	

void NewElectricField::GetFieldValue (const G4double[4],
                                            G4double *fieldBandE ) const
{
   fieldBandE[0]= 0.0;
   fieldBandE[1]= 0.0;
   fieldBandE[2]= 0.0;
   fieldBandE[3]= fFieldComponents[3] ;
   fieldBandE[4]= fFieldComponents[4] ;
   fieldBandE[5]= fFieldComponents[5] ;
/*
	G4cout<<"efieldx : "<<fieldBandE[3]<<G4endl;
	G4cout<<"efieldy : "<<fieldBandE[4]<<G4endl;
	G4cout<<"efieldz : "<<fieldBandE[5]<<G4endl;
*/
}
