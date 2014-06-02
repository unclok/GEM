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
// $Id: GEMDetectorConstruction.hh,v 1.6 2009-11-21 00:22:55 perl Exp $
// --------------------------------------------------------------
//

#ifndef GEMDetectorConstruction_h
#define GEMDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include "G4FieldManager.hh"
#include "G4ElectricField.hh"

#include "G4EqMagElectricField.hh"
#include "G4PropagatorInField.hh"
#include "G4TransportationManager.hh"
#include "G4ChordFinder.hh"
//#include "G4SimpleHeum.hh"
#include "G4ClassicalRK4.hh"
#include "G4ThreeVector.hh"

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class GEMDetectorConstMessenger;
class GEMElectricField;
class G4ElectricField;

class GEMDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    GEMDetectorConstruction();
    virtual ~GEMDetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    inline void ConstructMaterials();
    inline void DestroyMaterials();
    inline void SetUniformField(G4ThreeVector val) { fEUfield=val; }
    inline G4ThreeVector GetUniformField() const { G4cout << fEUfield << G4endl;
						  return fEUfield; }

  private:
    void DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth=0);

  private:
    GEMDetectorConstMessenger* messenger;
    G4ThreeVector fEUfield;
//    GEMElectricField* electricField;
    G4ElectricField* electricField;
    G4FieldManager* globalfieldMgr;
    G4FieldManager* fieldMgr;

    G4Material* air;
    G4Material* h2Gas;
    G4Material* argonGas;
    G4Material* arco2Gas;
    G4Material* xenonGas;
    G4Material* scintillator;
    G4Material* CsI;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    G4Material* copper;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    G4Material* Kapton;
    G4Material* galactic;

    G4VisAttributes* worldVisAtt;
    G4VisAttributes* electricVisAtt;
    G4VisAttributes* hodoscopeVisAtt;
    G4VisAttributes* kaptonVisAtt;
    G4VisAttributes* copperVisAtt;
    G4VisAttributes* argonVisAtt;

  G4MagIntegratorStepper * pStepper;
  G4EqMagElectricField * pEquation;
  G4MagInt_Driver * pIntgrDriver;
  G4ChordFinder *pChordFinder ;
  G4PropagatorInField *propInField;

};

#endif

