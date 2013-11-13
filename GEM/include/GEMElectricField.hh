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
// $Id: GEMElectricField.hh,v 1.5 2009-11-21 00:22:55 perl Exp $
// --------------------------------------------------------------
//

#ifndef GEMElectricField_H
#define GEMElectricField_H 1

#include "globals.hh"
#include "G4ElectricField.hh"
#include "G4ios.hh"
#include <vector>

using namespace std;

class GEMElectricFieldMessenger;

class GEMElectricField : public G4ElectricField
{
  // Storage space for the table
	double GEMPosition[3][41][41][801];
	double GEMElec[3][41][41][801];

  // The dimensions of the table
  int nx,ny,nz; 
  // The physical extent of the defined region
  double dx, dy, dz;
  double min[3];
  double max[3];
  bool invertX, invertY, invertZ;

  public:
    GEMElectricField();
    ~GEMElectricField();

    virtual void GetFieldValue(const double point[4],double *Bfield ) const;

  private:
    GEMElectricFieldMessenger* messenger;
   
};

#endif

