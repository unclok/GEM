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
#include "G4ComptonScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eMultipleScattering.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"

#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"

#include "G4ProcessManager.hh"

#include "G4EmStandardPhysics.hh"

 #include "G4PenelopeAnnihilationModel.hh"
 #include "G4PenelopeBremsstrahlungAngular.hh"
 #include "G4PenelopeBremsstrahlungFS.hh"
 #include "G4PenelopeBremsstrahlungModel.hh"
 #include "G4PenelopeComptonModel.hh"
 #include "G4PenelopeCrossSection.hh"
 #include "G4PenelopeGammaConversionModel.hh"
 #include "G4PenelopePhotoElectricModel.hh"
 #include "G4PenelopeRayleighModel.hh"
 #include "G4PenelopeIonisationModel.hh"

#include "G4LivermorePhotoElectricModel.hh"
#include "G4LivermoreComptonModel.hh"
#include "G4LivermoreGammaConversionModel.hh"
#include "G4LivermoreBremsstrahlungModel.hh"
#include "G4LivermoreIonisationModel.hh"
#include "G4EmProcessOptions.hh"

void GEMEMPhysics::ConstructProcess()
{
   G4EmProcessOptions emOptions;
   emOptions.SetFluo(true);
   emOptions.SetAuger(true);
   emOptions.SetPIXE(true);
   G4ProcessManager * pManager = 0;

   //Gamma
   pManager = G4Gamma::Gamma()->GetProcessManager();
   G4GammaConversion* gammaGammaconversion = new G4GammaConversion();
   G4ComptonScattering* gammaComptonscattering = new G4ComptonScattering();
   G4PhotoElectricEffect* gammaPhotoelectric = new G4PhotoElectricEffect();
   pManager->AddDiscreteProcess(gammaGammaconversion);
   pManager->AddDiscreteProcess(gammaComptonscattering);
   pManager->AddDiscreteProcess(gammaPhotoelectric);

   gammaGammaconversion->SetEmModel(new G4LivermoreGammaConversionModel());
   gammaGammaconversion->SetEmModel(new G4LivermoreComptonModel());
   gammaGammaconversion->SetEmModel(new G4LivermorePhotoElectricModel());

   //Electorn
   pManager = G4Electron::Electron()->GetProcessManager();
//   pManager->AddDiscreteProcess(new G4PhotoElectricEffect());
   G4VProcess* theeminusMultipleScattering = new G4eMultipleScattering();
   G4eIonisation* theeminusIonisation         = new G4eIonisation();
   G4eBremsstrahlung* theeminusBremsstrahlung     = new G4eBremsstrahlung();
   //
   //  set Electromagnetic Model
   theeminusIonisation->SetEmModel(new G4LivermoreIonisationModel());
   theeminusBremsstrahlung->SetEmModel(new G4LivermoreBremsstrahlungModel());
   // 
   //  add process
   pManager->AddProcess(theeminusMultipleScattering);
   pManager->AddProcess(theeminusIonisation);
   pManager->AddProcess(theeminusBremsstrahlung);
   //
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theeminusMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theeminusIonisation,         idxAlongStep,2);
   pManager->SetProcessOrdering(theeminusBremsstrahlung,     idxAlongStep,3);
   //
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theeminusMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theeminusIonisation,         idxPostStep,2);
   pManager->SetProcessOrdering(theeminusBremsstrahlung,     idxPostStep,3);
   
   G4cout<<"GetProcessActivation():"<<pManager->GetProcessActivation(theeminusIonisation)<<G4endl;
   G4cout<<"GetProcessList():"<<pManager->GetProcessList()<<G4endl;
   G4cout<<"GetVerboseLevel():"<<pManager->GetVerboseLevel()<<G4endl;

   //Positron
   pManager = G4Positron::Positron()->GetProcessManager();
//   pManager->AddDiscreteProcess(new G4PhotoElectricEffect());
   G4VProcess* theeplusMultipleScattering = new G4eMultipleScattering();
   G4eIonisation* theeplusIonisation         = new G4eIonisation();
   G4eBremsstrahlung* theeplusBremsstrahlung     = new G4eBremsstrahlung();
   G4VProcess* theeplusAnnihilation       = new G4eplusAnnihilation();

   pManager->AddProcess(theeplusMultipleScattering);
   pManager->AddProcess(theeplusIonisation);
   pManager->AddProcess(theeplusBremsstrahlung);
   pManager->AddProcess(theeplusAnnihilation);
   //
   // set ordering for AtRestDoIt
   pManager->SetProcessOrderingToFirst(theeplusAnnihilation, idxAtRest);
   //
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theeplusMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theeplusIonisation,         idxAlongStep,2);
   pManager->SetProcessOrdering(theeplusBremsstrahlung,     idxAlongStep,3);
   //
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theeplusMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theeplusIonisation,         idxPostStep,2);
   pManager->SetProcessOrdering(theeplusBremsstrahlung,     idxPostStep,3);
   pManager->SetProcessOrdering(theeplusAnnihilation,       idxPostStep,4);

//   AddTransportation();
}
