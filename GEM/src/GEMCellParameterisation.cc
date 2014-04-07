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
// $Id: GEMCellParameterisation.cc,v 1.4 2006-06-29 16:31:45 gunter Exp $
// --------------------------------------------------------------
//

#include "GEMCellParameterisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"

GEMCellParameterisation::GEMCellParameterisation()
{
  for(int copyNo=0;copyNo<80;copyNo++)
  {
    G4int column = copyNo / 4;
    G4int row = copyNo % 4;
    xCell[copyNo] = (column-9)*15.*um - 7.5*um;
    yCell[copyNo] = (row-1)*15*um - 7.5*um;
  }
}

GEMCellParameterisation::~GEMCellParameterisation()
{;}

void GEMCellParameterisation::ComputeTransformation
(const G4int copyNo,G4VPhysicalVolume *physVol) const
{
  physVol->SetTranslation(G4ThreeVector(xCell[copyNo],yCell[copyNo],0.));
}

