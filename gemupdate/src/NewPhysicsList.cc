//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: ExN02PhysicsList.cc 69899 2013-05-17 10:05:33Z gcosmo $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "globals.hh"
#include "NewPhysicsList.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"
#include "G4IonConstructor.hh"
#include "G4ProductionCutsTable.hh"
#include "G4LossTableManager.hh"
#include "CLHEP/Units/PhysicalConstants.h"

using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02PhysicsList::ExN02PhysicsList():  G4VUserPhysicsList()
{
  defaultCutValue = 5*um;
   SetVerboseLevel(1);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ExN02PhysicsList::~ExN02PhysicsList()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();
  G4IonConstructor pIonConstructor;
  pIonConstructor.ConstructParticle(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructBosons()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructLeptons()
{
  // leptons
  //  e+/-
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  // mu+/-
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  // nu_e
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  // nu_mu
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructMesons()
{
  //  mesons
  //    light mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
  G4Eta::EtaDefinition();
  G4EtaPrime::EtaPrimeDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
  G4KaonZero::KaonZeroDefinition();
  G4AntiKaonZero::AntiKaonZeroDefinition();
  G4KaonZeroLong::KaonZeroLongDefinition();
  G4KaonZeroShort::KaonZeroShortDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructBaryons()
{
  //  barions
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();

  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
  ConstructGeneral();
  AddStepMax();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4PhysicsListHelper.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"
#include "G4CoulombScattering.hh"

#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4ionIonisation.hh"
#include "G4UrbanMscModel.hh"
#include "G4eSingleCoulombScatteringModel.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4PenelopeComptonModel.hh"
#include "G4PenelopeBremsstrahlungModel.hh"
#include "G4PenelopeGammaConversionModel.hh"
#include "G4PenelopePhotoElectricModel.hh"
#include "G4LivermoreBremsstrahlungModel.hh"
#include "G4LivermoreComptonModel.hh"
#include "G4LivermoreComptonModifiedModel.hh"
#include "G4LivermoreGammaConversionModel.hh"
//#include G4LivermoreGammaConversionModelRC.hh"
#include "G4LivermoreIonisationModel.hh"
#include "G4LivermoreNuclearGammaConversionModel.hh"
#include "G4LivermorePhotoElectricModel.hh"
//#include "G4LivermorePolarizedComptonModel.hh"
//#include "G4LivermorePolarizedGammaConversionModel.hh"
//#include "G4LivermorePolarizedPhotoElectricModel.hh"
//#include "G4LivermorePolarizedRayleighModel.hh"
#include "G4LivermoreRayleighModel.hh"
//#include "G4eBremsstrahlungModel.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::ConstructEM()
{
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    G4String particleName = particle->GetParticleName();
    
	//load physics process for each particle
    if (particleName == "gamma") {
      // gamma         
	G4PhotoElectricEffect* photo = new G4PhotoElectricEffect();
	//photo->SetEmModel(new G4PenelopePhotoElectricModel);
//	photo->SetEmModel(new G4LivermorePhotoElectricModel);
	photo->SetMinKinEnergyPrim(0.8*eV);
      //ph->RegisterProcess(new G4PhotoElectricEffect, particle);
      ph->RegisterProcess(photo, particle);
	G4ComptonScattering* compton = new G4ComptonScattering();
	//compton->SetEmModel(new G4PenelopeComptonModel);
//	compton->SetEmModel(new G4LivermoreComptonModel);
	compton->SetMinKinEnergyPrim(0.8*eV);
      //ph->RegisterProcess(new G4ComptonScattering,   particle);
      ph->RegisterProcess(compton,   particle);
	G4GammaConversion* conv = new G4GammaConversion();
//	conv->SetEmModel(new G4LivermoreGammaConversionModel);
	//conv->SetEmModel(new G4PenelopeGammaConversionModel);
	conv->SetMinKinEnergyPrim(0.8*eV);
      //ph->RegisterProcess(new G4GammaConversion,     particle);
      ph->RegisterProcess(conv,     particle);
      
    } else if (particleName == "e-") {
      //electron
	//G4LossTableManager* man = G4LossTableManager::Instance();
	//man->SetMinEnergy(0.8*eV);
	//G4cout<<"Urban : "<<man->MinKinEnergy()<<G4endl;
	//G4eSingleCoulombScatteringModel* scs = new G4eSingleCoulombScatteringModel();
	//scs->SetLowEnergyLimit(0.8*eV);
	//scs->SetActivationLowEnergyLimit(0.8*eV);
	//G4CoulombScattering* cs = new G4CoulombScattering();
	//cs->SetEmModel(scs);
//	G4cout<<"Urban low energy : "<<urban->LowEnergyLimit()<<" activation : "<<urban->LowEnergyActivationLimit()<<G4endl;
	G4UrbanMscModel* urban = new G4UrbanMscModel();
	urban->SetLowEnergyLimit(0.8*eV);
	urban->SetActivationLowEnergyLimit(0.8*eV);
	G4eMultipleScattering *emsc = new G4eMultipleScattering();
	emsc->SetEmModel(urban);
	//emsc->SetDEDXBinning(100);
      //ph->RegisterProcess(new G4eMultipleScattering, particle);
	G4eIonisation* eioni = new G4eIonisation();
	//eioni->SetEmModel(urban);
	//man->SetMinEnergy(0.8*eV);
	eioni->SetMinKinEnergy(0.8*eV);
//	eioni->SetEmModel(new G4LivermoreIonisationModel());
	//eioni->SetEmModel(new G4PenelopeIonisationModel());
	eioni->SetMinKinEnergy(0.8*eV);
	//eioni->SetMinKinEnergy(14.53414*eV);
	//eioni->SetDEDXBinning(100);
	//emsc->SetIonisation((G4VEnergyLossProcess*)eioni);
	emsc->SetEmModel(urban);
      ph->RegisterProcess(emsc, particle);
      //ph->RegisterProcess(cs, particle);
      //ph->RegisterProcess(new G4eIonisation,         particle);
      ph->RegisterProcess(eioni,         particle);
	G4eBremsstrahlung* ebrem = new G4eBremsstrahlung();
//	ebrem->SetEmModel(new G4LivermoreBremsstrahlungModel);
	//ebrem->SetEmModel(new G4PenelopeBremsstrahlungModel);
	ebrem->SetMinKinEnergy(0.8*eV);
      //ph->RegisterProcess(new G4eBremsstrahlung,     particle);      
      ph->RegisterProcess(ebrem,     particle);      

    } else if (particleName == "e+") {
      //positron
      ph->RegisterProcess(new G4eMultipleScattering, particle);
      ph->RegisterProcess(new G4eIonisation,         particle);
      ph->RegisterProcess(new G4eBremsstrahlung,     particle);
      ph->RegisterProcess(new G4eplusAnnihilation,   particle);
    
    } else if( particleName == "mu+" || 
               particleName == "mu-"    ) {
      //muon  
      ph->RegisterProcess(new G4MuMultipleScattering, particle);
      ph->RegisterProcess(new G4MuIonisation,         particle);
      ph->RegisterProcess(new G4MuBremsstrahlung,     particle);
      ph->RegisterProcess(new G4MuPairProduction,     particle);
             
    } else if( particleName == "proton" || 
               particleName == "pi-" ||
               particleName == "pi+"    ) {
      //proton  
	G4UrbanMscModel* urban = new G4UrbanMscModel();
	urban->SetLowEnergyLimit(0.8*eV);
	urban->SetActivationLowEnergyLimit(0.8*eV);
	G4hMultipleScattering* hmsc = new G4hMultipleScattering();
	hmsc->SetEmModel(urban);
      ph->RegisterProcess(hmsc, particle);
      //ph->RegisterProcess(new G4hMultipleScattering, particle);
	G4ionIonisation* ionioni = new G4ionIonisation();
	//ionioni->SetMinKinEnergy(14.53414*eV);
	ionioni->SetMinKinEnergy(0.8*eV);
      ph->RegisterProcess(ionioni,       particle);     
      //ph->RegisterProcess(new G4hIonisation,         particle);
      ph->RegisterProcess(new G4hBremsstrahlung,     particle);
      ph->RegisterProcess(new G4hPairProduction,     particle);       
     
    } else if( particleName == "alpha" || 
               particleName == "He3" )     {
      //alpha 
      ph->RegisterProcess(new G4hMultipleScattering, particle);
      ph->RegisterProcess(new G4ionIonisation,       particle);
     
    } else if( particleName == "GenericIon" ) { 
      //Ions 
	G4UrbanMscModel* urban = new G4UrbanMscModel();
	urban->SetLowEnergyLimit(0.8*eV);
	urban->SetActivationLowEnergyLimit(0.8*eV);
	G4hMultipleScattering* hmsc = new G4hMultipleScattering();
	hmsc->SetEmModel(urban);
      ph->RegisterProcess(hmsc, particle);
      //ph->RegisterProcess(new G4hMultipleScattering, particle);
	G4ionIonisation* ionioni = new G4ionIonisation();
	ionioni->SetMinKinEnergy(0.8*eV);
      ph->RegisterProcess(ionioni,       particle);     
      //ph->RegisterProcess(new G4ionIonisation,       particle);     
      
      } else if ((!particle->IsShortLived()) &&
               (particle->GetPDGCharge() != 0.0) && 
               (particle->GetParticleName() != "chargedgeantino")) {
      //all others charged particles except geantino
	G4UrbanMscModel* urban = new G4UrbanMscModel();
	urban->SetLowEnergyLimit(0.8*eV);
	urban->SetActivationLowEnergyLimit(0.8*eV);
	G4hMultipleScattering* hmsc = new G4hMultipleScattering();
	hmsc->SetEmModel(urban);
      ph->RegisterProcess(hmsc, particle);
      //ph->RegisterProcess(new G4hMultipleScattering, particle);
	G4ionIonisation* ionioni = new G4ionIonisation();
	ionioni->SetMinKinEnergy(0.8*eV);
      ph->RegisterProcess(ionioni,       particle);     
      //ph->RegisterProcess(new G4hIonisation,         particle);        
    }     
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4Decay.hh"

void ExN02PhysicsList::ConstructGeneral()
{
  G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();
  
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
  theParticleIterator->reset();
  while( (*theParticleIterator)() ){
    G4ParticleDefinition* particle = theParticleIterator->value();
    if (theDecayProcess->IsApplicable(*particle)) { 
      ph->RegisterProcess(theDecayProcess, particle);    
    }
  }
}
  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "G4StepLimiter.hh"
#include "G4UserSpecialCuts.hh"

void ExN02PhysicsList::AddStepMax()
{
  // Step limitation seen as a process
  G4StepLimiter* stepLimiter = new G4StepLimiter();
  ////G4UserSpecialCuts* userCuts = new G4UserSpecialCuts();
  
  theParticleIterator->reset();
  while ((*theParticleIterator)()){
      G4ParticleDefinition* particle = theParticleIterator->value();
      G4ProcessManager* pmanager = particle->GetProcessManager();

      if (particle->GetPDGCharge() != 0.0)
        {
          pmanager ->AddDiscreteProcess(stepLimiter);
          ////pmanager ->AddDiscreteProcess(userCuts);
        }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ExN02PhysicsList::SetCuts()
{
  //G4VUserPhysicsList::SetCutsWithDefault method sets 
  //the default cut value for all particle types 
  //
  SetCutsWithDefault();
	G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(0.8*eV,G4ProductionCutsTable::GetProductionCutsTable()->GetHighEdgeEnergy());
     
  if (verboseLevel>0) DumpCutValuesTable();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

