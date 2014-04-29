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
// $Id: GEMPrimaryGeneratorAction.hh,v 1.4 2006-06-29 16:31:35 gunter Exp $
// --------------------------------------------------------------
//

#ifndef GEMPrimaryGeneratorAction_h
#define GEMPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class G4ParticleDefinition;
class GEMPrimaryGeneratorMessenger;

class GEMPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    GEMPrimaryGeneratorAction();
    virtual ~GEMPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event*);

  private:
    G4ParticleGun* particleGun;
    GEMPrimaryGeneratorMessenger* gunMessenger;
    G4double energy;
    G4ThreeVector direction;

  public:
    inline void SetEnergy(G4double val) { energy = val; }
    inline G4double GetEnergy() const { G4cout << energy << G4endl;
					return energy; }
    inline void SetDirection(G4ThreeVector val) { direction = val; }
    inline G4ThreeVector GetDirection() const { G4cout << direction << G4endl;
						return direction;  }
};

#endif


