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
// $Id: GEMEmCalorimeterHit.hh,v 1.5 2006-06-29 16:31:02 gunter Exp $
// --------------------------------------------------------------
//
#ifndef GEMEmCalorimeterHit_h
#define GEMEmCalorimeterHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4AttDef;
class G4AttValue;

class GEMEmCalorimeterHit : public G4VHit
{
  public:

      GEMEmCalorimeterHit();
      GEMEmCalorimeterHit(G4int z);
      virtual ~GEMEmCalorimeterHit();
      GEMEmCalorimeterHit(const GEMEmCalorimeterHit &right);
      const GEMEmCalorimeterHit& operator=(const GEMEmCalorimeterHit &right);
      int operator==(const GEMEmCalorimeterHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

      virtual void Draw();
      virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
      virtual std::vector<G4AttValue>* CreateAttValues() const;
      virtual void Print();

  private:
      G4int cellID;
      G4double edep;
      G4ThreeVector pos;
      G4RotationMatrix rot;
      const G4LogicalVolume* pLogV;

  public:
      inline void SetCellID(G4int z) { cellID = z; }
      inline G4int GetCellID() const { return cellID; }
      inline void SetEdep(G4double de) { edep = de; }
      inline void AddEdep(G4double de) { edep += de; }
      inline G4double GetEdep() const { return edep; }
      inline void SetPos(G4ThreeVector xyz) { pos = xyz; }
      inline G4ThreeVector GetPos() const { return pos; }
      inline void SetRot(G4RotationMatrix rmat) { rot = rmat; }
      inline G4RotationMatrix GetRot() const { return rot; }
      inline void SetLogV(G4LogicalVolume* val) { pLogV = val; }
      inline const G4LogicalVolume* GetLogV() const { return pLogV; }
};

typedef G4THitsCollection<GEMEmCalorimeterHit> GEMEmCalorimeterHitsCollection;

extern G4Allocator<GEMEmCalorimeterHit> GEMEmCalorimeterHitAllocator;

inline void* GEMEmCalorimeterHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*)GEMEmCalorimeterHitAllocator.MallocSingle();
  return aHit;
}

inline void GEMEmCalorimeterHit::operator delete(void* aHit)
{
  GEMEmCalorimeterHitAllocator.FreeSingle((GEMEmCalorimeterHit*) aHit);
}

#endif


