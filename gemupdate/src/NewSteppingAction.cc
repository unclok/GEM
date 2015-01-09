#include "NewSteppingAction.hh"
#include "BeamAnalysisManager.hh"

#include "G4RunManager.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "CLHEP/Units/PhysicalConstants.h"

using namespace CLHEP;

NewSteppingAction::NewSteppingAction() : G4UserSteppingAction()
{
	G4TransportationManager* transportMgr = G4TransportationManager::GetTransportationManager();
	fFieldPropagator = transportMgr->GetPropagatorInField();
	Field=0;
}

NewSteppingAction::~NewSteppingAction()
{
	delete BeamAnalysisManager::Instance();
}

void NewSteppingAction::UserSteppingAction(const G4Step* step)
{
	// get analysis manager
	BeamAnalysisManager* man = BeamAnalysisManager::Instance();
	//fill de from ionization
	if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="eIoni")
	man->FillH1(0,step->GetDeltaEnergy()/eV);
	//fill hand writed de from ionization
	if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="eIoni")
	man->FillH1(2,step->GetPreStepPoint()->GetTotalEnergy()/eV-step->GetPostStepPoint()->GetTotalEnergy()/eV);
	//fill de from multiple scattering
	if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="msc")
	man->FillH1(5,step->GetDeltaEnergy()/eV);
	//fill de from electron bremsstrahlung
	if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="eBrem")
	man->FillH1(6,step->GetDeltaEnergy()/eV);
//	if(step->GetPostStepPoint()->GetProcessDefinedStep()!=0)
	G4ThreeVector pos = step->GetPostStepPoint()->GetPosition();
	G4double position[4] = {pos.x(),pos.y(),pos.z(),step->GetPostStepPoint()->GetGlobalTime()};
	G4double field[6];
	G4FieldManager* fieldMgr=0;
	//fieldMgr = fFieldPropagator->FindAndSetFieldManager(step->GetTrack()->GetVolume());
	//Field = fieldMgr->GetDetectorField();
	//Field->GetFieldValue(position,field);
//	G4cout<<"fieldz : "<<field[5]<<G4endl;
	G4double dx = step->GetPreStepPoint()->GetMomentum().x()-step->GetPostStepPoint()->GetMomentum().x();
	G4double dy = step->GetPreStepPoint()->GetMomentum().y()-step->GetPostStepPoint()->GetMomentum().y();
	G4double dz = step->GetPreStepPoint()->GetMomentum().z()-step->GetPostStepPoint()->GetMomentum().z();
	G4double theta = step->GetPreStepPoint()->GetMomentum().angle(step->GetPostStepPoint()->GetMomentum());
	G4double mass = step->GetPreStepPoint()->GetMass();
	G4double vel = step->GetPreStepPoint()->GetVelocity();
	//man->FillH2(0,field[5]*cm/kilovolt,step->GetPostStepPoint()->GetVelocity()*second/m);
	//man->FillH2(1,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	//G4cout<<"theta : "<<G4ThreeVector(dx,dy,dz).theta()<<" dx : "<<dx<<" dy : "<<dy<<" dz : "<<dz<<G4endl;
	//G4cout<<pi/18<<", "<<pi<<G4endl;
	//if(theta>pi/18 && theta<pi && step->GetTrack()->GetParentID()==1){G4cout<<"theta : "<<theta<<" dcs : "<<(18*electron_charge*electron_charge/(8*pi*epsilon0*mass*vel*vel))*(18*electron_charge*electron_charge/(8*pi*epsilon0*mass*vel*vel))*asin(theta/2)*asin(theta/2)*asin(theta/2)*asin(theta/2)/cm2*sr<<" pi : "<<pi<<" epsilon : "<<epsilon0<<" mass : "<<mass<<" vel : "<<vel<<" asin(theta) : "<<asin(theta/2)<<G4endl;
//	if(theta>0 && theta<pi && step->GetPreStepPoint()->GetKineticEnergy()==step->GetTrack()->GetVertexKineticEnergy() && step->GetTrack()->GetTrackID()==1){G4cout<<"theta : "<<theta<<" dcs : "<<(18*electron_charge*electron_charge/(8*pi*epsilon0*mass*vel*vel))*(18*electron_charge*electron_charge/(8*pi*epsilon0*mass*vel*vel))*asin(theta/2)*asin(theta/2)*asin(theta/2)*asin(theta/2)/cm2*sr<<" pi : "<<pi<<" epsilon : "<<epsilon0<<" mass : "<<mass<<" vel : "<<vel<<" asin(theta) : "<<asin(theta/2)<<" energy  : "<<step->GetPreStepPoint()->GetKineticEnergy()<<" gun energy : "<<step->GetTrack()->GetVertexKineticEnergy()<<G4endl;

	//fill scattering angle for each process
	man->FillH1(7,theta*180/pi);
	if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="eIoni")
	//man->FillH2(2,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(8,theta*180/pi);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="msc")
	//man->FillH2(3,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(9,theta*180/pi);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="conv")
	//man->FillH2(4,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(10,theta*180/pi);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="compt")
	//man->FillH2(5,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(11,theta*180/pi);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="eBrem")
	//man->FillH2(6,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(12,theta*180/pi);
	if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="phot")
	//man->FillH2(7,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(13,theta*180/pi);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="hIoni")
	//man->FillH2(8,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(14,theta*180/pi);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="ionIoni")
	//man->FillH2(9,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(15,theta*180/pi);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="transportation")
	man->FillH1(25,theta*180/pi);
//}

	//fill energy after scattering for each process
	if(theta!=0){
	man->FillH1(16,step->GetPreStepPoint()->GetKineticEnergy()/eV);
	if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="eIoni")
	//man->FillH2(2,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(17,step->GetPreStepPoint()->GetKineticEnergy()/eV);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="msc")
	//man->FillH2(3,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(18,step->GetPreStepPoint()->GetKineticEnergy()/eV);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="conv")
	//man->FillH2(4,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(19,step->GetPreStepPoint()->GetKineticEnergy()/eV);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="compt")
	//man->FillH2(5,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(20,step->GetPreStepPoint()->GetKineticEnergy()/eV);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="eBrem")
	//man->FillH2(6,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(21,step->GetPreStepPoint()->GetKineticEnergy()/eV);
	if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="phot")
	//man->FillH2(7,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(22,step->GetPreStepPoint()->GetKineticEnergy()/eV);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="hIoni")
	//man->FillH2(8,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(23,step->GetPreStepPoint()->GetKineticEnergy()/eV);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="ionIoni")
	//man->FillH2(9,step->GetPostStepPoint()->GetKineticEnergy()/eV,step->GetStepLength()/cm);
	man->FillH1(24,step->GetPreStepPoint()->GetKineticEnergy()/eV);
	else if(step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName()=="transportation")
	man->FillH1(26,step->GetPreStepPoint()->GetKineticEnergy()/eV);}

	//hand writed dedx
	man->FillH2(10,(step->GetPostStepPoint()->GetMomentum().beta()*step->GetPostStepPoint()->GetMomentum().gamma()),-(step->GetDeltaEnergy()/(step->GetStepLength()))*g/(MeV*cm2));
//	G4cout<<"beta : "<<step->GetPostStepPoint()->GetMomentum().beta()<<G4endl;
//	G4cout<<"gamma : "<<step->GetPostStepPoint()->GetMomentum().gamma()<<G4endl;
//	G4cout<<(step->GetDeltaEnergy()/step->GetStepLength())<<G4endl;

	//G4double zpos = step->GetPostStepPoint()->GetPosition().z();
	G4double zpos = step->GetTrack()->GetPosition().z();
//	G4cout<<"zpos : "<<zpos<<G4endl;
	//fill energy of electron between 50~55um
	if(zpos<55*um && zpos>50*um && step->GetTrack()->GetDefinition()->GetParticleName()=="e-"){
//		G4cout<<"filling"<<G4endl;
	}
	//fill z position of electron after 55um
	if(zpos>55*um && step->GetTrack()->GetDefinition()->GetParticleName()=="e-" && step->GetSecondary()->size()==0){
		man->FillH1(1,step->GetTrack()->GetDefinition()->GetParticleName());
		man->FillH1(3,step->GetTrack()->GetKineticEnergy()/eV);
		man->FillH1(4,zpos);
		man->FillH2(12,step->GetTrack()->GetTrackID(),step->GetTrack()->GetParentID());
	}

//	G4RunManager::GetRunManager()->AbortEvent();
}
