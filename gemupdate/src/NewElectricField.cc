#include "NewElectricField.hh"

NewElectricField::NewElectricField(const G4ThreeVector &fieldVector)
{
	fFieldComponents[0] = 0.0;
	fFieldComponents[1] = 0.0;
	fFieldComponents[2] = 0.0;
	fFieldComponents[3] = fieldVector.x();
	fFieldComponents[4] = fieldVector.y();
	fFieldComponents[5] = fieldVector.z();
	fpositionz = -25252;
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

void NewElectricField::GetFieldValue (const G4double position[4],
                                            G4double *fieldBandE ) const
{
   fieldBandE[0]= 0.0;
   fieldBandE[1]= 0.0;
   fieldBandE[2]= 0.0;
   fieldBandE[3]= fFieldComponents[3] ;
   fieldBandE[4]= fFieldComponents[4] ;
   fieldBandE[5]= fFieldComponents[5] ;
/*
	G4cout<<"Uniform Efield x:"<<fieldBandE[3]<<G4endl;
	G4cout<<"Uniform Efield y:"<<fieldBandE[4]<<G4endl;
	G4cout<<"Uniform Efield z:"<<fieldBandE[5]<<G4endl;
	G4cout<<"x:"<<position[0]<<G4endl;
	G4cout<<"y:"<<position[1]<<G4endl;
	G4cout<<"z:"<<position[2]<<G4endl;
*/
/*
	if(fpositionz!=-25252)fpositionz>position[2] ? G4cout<<"->"<<G4endl : G4cout<<"<-";
	else G4cout<<"particle started"<<G4endl;
	const_cast<double&>(fpositionz) = position[2];
*/
}
