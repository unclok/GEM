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
// $Id: GEMEMPhysics.cc,v 1.9 2009-11-21 01:00:19 perl Exp $
// --------------------------------------------------------------
//
//
// 09-Oct-2003 Change gamma, electron, positorn process T. Koi
// 10-Jan-2004 Add Brems. of AlongStepDoIt for e+- T. Koi


#include "GEMEMPhysics.hh"

#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>


GEMEMPhysics::GEMEMPhysics(const G4String& name)
               :  G4VPhysicsConstructor(name)
{
}

GEMEMPhysics::~GEMEMPhysics()
{
}

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4Gamma.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"

#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"

#include "G4UniversalFluctuation.hh"

#include "G4VProcess.hh"
#include "G4ProcessManager.hh"

#include "G4UAtomicDeexcitation.hh"

void GEMEMPhysics::ConstructProcess()
{
   G4ProcessManager * pManager = 0;
	double highEnergyLimit = 1.0*GeV;

   //Gamma
   pManager = G4Gamma::Gamma()->GetProcessManager();
      G4GammaConversion* conv = new G4GammaConversion();
      G4PenelopeGammaConversionModel* convModel = new G4PenelopeGammaConversionModel();
      convModel->SetHighEnergyLimit(highEnergyLimit);
      conv->AddEmModel(0, convModel);
   pManager->AddDiscreteProcess(conv);
      G4ComptonScattering* compt = new G4ComptonScattering();
      G4PenelopeComptonModel* comptModel = new G4PenelopeComptonModel();
      comptModel->SetHighEnergyLimit(highEnergyLimit);
      compt->AddEmModel(0, comptModel);
   pManager->AddDiscreteProcess(compt);
      G4PhotoElectricEffect* phot = new G4PhotoElectricEffect();
      G4PenelopePhotoElectricModel* photModel = new G4PenelopePhotoElectricModel();
      photModel->SetHighEnergyLimit(highEnergyLimit);
      phot->AddEmModel(0, photModel);
   pManager->AddDiscreteProcess(phot);

   //Electorn
   pManager = G4Electron::Electron()->GetProcessManager();
   G4VProcess* theeminusMultipleScattering = new G4eMultipleScattering();
      G4eIonisation* eIoni = new G4eIonisation();
      G4PenelopeIonisationModel* eIoniModel = new G4PenelopeIonisationModel();
      eIoniModel->SetHighEnergyLimit(highEnergyLimit); 
      eIoni->AddEmModel(0, eIoniModel, new G4UniversalFluctuation() );
      G4eBremsstrahlung* eBrem = new G4eBremsstrahlung();
      G4PenelopeBremsstrahlungModel* eBremModel = new G4PenelopeBremsstrahlungModel();
      eBremModel->SetHighEnergyLimit(highEnergyLimit);
      eBrem->AddEmModel(0, eBremModel);
   // 
   //  add process
   pManager->AddProcess(theeminusMultipleScattering);
   pManager->AddProcess(eIoni);
   pManager->AddProcess(eBrem);
   //
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theeminusMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(eIoni,         idxAlongStep,2);
   pManager->SetProcessOrdering(eBrem,     idxAlongStep,3);
   //
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theeminusMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(eIoni,         idxPostStep,2);
   pManager->SetProcessOrdering(eBrem,     idxPostStep,3);

   //Positron
   pManager = G4Positron::Positron()->GetProcessManager();
   G4VProcess* theeplusMultipleScattering = new G4eMultipleScattering();
      G4eIonisation* pIoni = new G4eIonisation();
      G4PenelopeIonisationModel* pIoniModel = new G4PenelopeIonisationModel();
      eIoniModel->SetHighEnergyLimit(highEnergyLimit); 
      eIoni->AddEmModel(0, pIoniModel, new G4UniversalFluctuation() );
      G4eBremsstrahlung* pBrem = new G4eBremsstrahlung();
      G4PenelopeBremsstrahlungModel* pBremModel = new G4PenelopeBremsstrahlungModel();
      eBremModel->SetHighEnergyLimit(highEnergyLimit);
      eBrem->AddEmModel(0, pBremModel);
      G4eplusAnnihilation* eAnni = new G4eplusAnnihilation();
      G4PenelopeAnnihilationModel* eAnniModel = new G4PenelopeAnnihilationModel();
      eAnniModel->SetHighEnergyLimit(highEnergyLimit); 
      eAnni->AddEmModel(0, eAnniModel);

   pManager->AddProcess(theeplusMultipleScattering);
   pManager->AddProcess(pIoni);
   pManager->AddProcess(pBrem);
   pManager->AddProcess(eAnni);
   //
   // set ordering for AtRestDoIt
   pManager->SetProcessOrderingToFirst(eAnni, idxAtRest);
   //
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theeplusMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(eIoni,         idxAlongStep,2);
   pManager->SetProcessOrdering(eBrem,     idxAlongStep,3);
   //
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theeplusMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(eIoni,         idxPostStep,2);
   pManager->SetProcessOrdering(eBrem,     idxPostStep,3);
   pManager->SetProcessOrdering(eAnni,       idxPostStep,4);

  // Deexcitation
  //
  G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
  de->SetFluo(true);
  de->SetAuger(false);
  de->SetPIXE(false);
  G4LossTableManager::Instance()->SetAtomDeexcitation(de);

}
