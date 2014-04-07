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
// $Id: GEMPrimaryGeneratorAction.cc,v 1.5 2006-06-29 16:33:05 gunter Exp $
// --------------------------------------------------------------
//

#include "GEMPrimaryGeneratorAction.hh"
#include "GEMPrimaryGeneratorMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

GEMPrimaryGeneratorAction::GEMPrimaryGeneratorAction()
{
<<<<<<< HEAD
   G4int n_particle = 1;
  energy = 1.*eV;
  direction = G4ThreeVector(0.,0.,1.);
  particleGun  = new G4ParticleGun(n_particle);

  gunMessenger = new GEMPrimaryGeneratorMessenger(this);
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
                    = particleTable->FindParticle(particleName="gamma");
  particleGun->SetParticlePosition(G4ThreeVector(0.,0.,-300.*um));
  particleGun->SetParticleDefinition(particle);
=======
  momentum = 1.*keV;
  sigmaMomentum = 50.*eV;
  sigmaAngle = .1*deg;
  randomizePrimary = false;

  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);

  //create a messenger for this class
  gunMessenger = new GEMPrimaryGeneratorMessenger(this);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  positron = particleTable->FindParticle(particleName="e+");
  electron = particleTable->FindParticle(particleName="e-");
  muon = particleTable->FindParticle(particleName="mu-");
  pion = particleTable->FindParticle(particleName="pi-");
  kaon = particleTable->FindParticle(particleName="kaon-");
  proton = particleTable->FindParticle(particleName="proton");

  // default particle kinematics
  particleGun->SetParticlePosition(G4ThreeVector(0.,0.,-300.*um));
  particleGun->SetParticleDefinition(electron);
>>>>>>> 4b15fd3620995b195aef0bb7f2adaa3f4806acb8
}

GEMPrimaryGeneratorAction::~GEMPrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
}

void GEMPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
<<<<<<< HEAD
 
 particleGun->SetParticleEnergy(energy);
 particleGun->SetParticleMomentumDirection(direction);
//  G4cout<<"energy : "<<particleGun->GetParticleEnergy()<<" momentum : "<<particleGun->GetParticleMomentum()<<G4endl;
=======
  G4ParticleDefinition* particle;

  if(randomizePrimary)
  {
    /////////////////////////////////////////////G4int i = (int)(5.*G4UniformRand());
    G4int i = (int)(2.*G4UniformRand());
    switch(i)
    {
      case 0:
        particle = electron;
        break;
      case 1:
        particle = muon;
        break;
      case 2:
        particle = pion;
        break;
      case 3:
        particle = kaon;
        break;
      default:
        particle = proton;
        break;
    }
    particleGun->SetParticleDefinition(particle);
  }
  else
  {
    particle = particleGun->GetParticleDefinition();
  }

  G4double pp = momentum + (G4UniformRand()-0.5)*sigmaMomentum;
  G4double mass = particle->GetPDGMass();
  G4double Ekin = std::sqrt(pp*pp+mass*mass)-mass;
  particleGun->SetParticleEnergy(Ekin);

  G4double angle = (G4UniformRand()-0.5)*sigmaAngle;
  particleGun->SetParticleMomentumDirection(G4ThreeVector(std::sin(angle),0.,std::cos(angle)));

>>>>>>> 4b15fd3620995b195aef0bb7f2adaa3f4806acb8
  particleGun->GeneratePrimaryVertex(anEvent);
}

