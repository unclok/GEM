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
// $Id: GEMElectricField.cc,v 1.7 2009-11-21 00:22:55 perl Exp $
// --------------------------------------------------------------
//

#include "GEMElectricField.hh"
//#include "GEMElectricFieldMessenger.hh"
//#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include <string>
#include <fstream>
#include <iostream>

GEMElectricField::GEMElectricField()
{
//  messenger = new GEMElectricFieldMessenger(this);
//  By = 1.0*tesla;

	ifstream infile;
	double GEMElec[6][648025];
	double temp[6];
	double blank[3];
        infile.open("/home/unclok/example/model/Field_map.txt");
        string str="";
        for(int i=0;i<2;i++){
                getline(infile, str);
        }

        for(int i=0;i<648025;i++){
                getline(infile, str);
                sscanf(str.c_str(),"%lf %lf %lf %lf %lf %lf %lf %lf %lf",&temp[0],&temp[1],&temp[2],&temp[3],&temp[4],&temp[5],&blank[0],&blank[1],&blank[2]);
		for(G4int j=0;j<3;j++){
			GEMElec[j][i]=temp[j]*um;
			if(i==0)min[j]=GEMElec[j][i];
		}
		for(G4int j=3;j<6;j++){
			GEMElec[j][i]=temp[j]*coulomb/m2;
		}
        }
        infile.close();

  min[0] = temp[0]*um;
  min[1] = temp[1]*um;
  min[2] = temp[2]*um;

  G4cout << "\n ---> ... done reading " << endl;

  // G4cout << " Read values of field from file " << filename << endl; 
  G4cout << " ---> assumed the order:  x, y, z, Dx, Dy, Dz "
         << "\n ---> Min values x,y,z: " 
         << min[0]/cm << " " << min[1]/cm << " " << min[2]/cm << " um "
         << "\n ---> Max values x,y,z: "
         << max[0]/cm << " " << max[1]/cm << " " << max[2]/cm << " um "
         << endl;

  // Should really check that the limits are not the wrong way around.
  if (max[0] < min[0]) {swap(max[0],min[0]); invertX = true;}
  if (max[1] < min[1]) {swap(max[1],min[1]); invertY = true;}
  if (max[2] < min[2]) {swap(max[2],min[2]); invertZ = true;}
  G4cout << "\nAfter reordering if neccesary"
         << "\n ---> Min values x,y,z: "
         << min[0]/um << " " << min[1]/um << " " << min[2]/um << " um "
         << " \n ---> Max values x,y,z: "
         << max[0]/um << " " << max[1]/um << " " << max[2]/um << " um ";

  dx = max[0] - min[0];
  dy = max[1] - min[1];
  dz = max[2] - min[2];
  G4cout << "\n ---> Dif values x,y,z (range): "
         << dx/um << " " << dy/um << " " << dz/um << " um in z "
         << "\n-----------------------------------------------------------" << endl;

}

GEMElectricField::~GEMElectricField()
{// delete messenger; 
}

void GEMElectricField::GetFieldValue(const double point[4],double *Bfield) const
{
  
  double x = point[0];
  double y = point[1];
  double z = point[2];
	double minx=min[0];
	double miny=min[1];
	double minz=min[2];
	double maxx=max[0];
	double maxy=max[1];
	double maxz=max[2];

  // Check that the point is within the defined region 
  if ( x>=minx && x<=maxx &&
       y>=miny && y<=maxy && 
       z>=minz && z<=maxz ) {
    
    // Position of given point within region, normalized to the range
    // [0,1]
    double xfraction = (x - minx) / dx;
    double yfraction = (y - miny) / dy; 
    double zfraction = (z - minz) / dz;

    if (invertX) { xfraction = 1 - xfraction;}
    if (invertY) { yfraction = 1 - yfraction;}
    if (invertZ) { zfraction = 1 - zfraction;}

    // Need addresses of these to pass to modf below.
    // modf uses its second argument as an OUTPUT argument.
    double xdindex, ydindex, zdindex;
    
    // Position of the point within the cuboid defined by the
    // nearest surrounding tabulated points
    double xlocal = ( std::modf(xfraction*(nx-1), &xdindex));
    double ylocal = ( std::modf(yfraction*(ny-1), &ydindex));
    double zlocal = ( std::modf(zfraction*(nz-1), &zdindex));
    
    // The indices of the nearest tabulated point whose coordinates
    // are all less than those of the given point
    int xindex = static_cast<int>(xdindex);
    int yindex = static_cast<int>(ydindex);
    int zindex = static_cast<int>(zdindex);
    

#ifdef DEBUG_INTERPOLATING_FIELD
    G4cout << "Local x,y,z: " << xlocal << " " << ylocal << " " << zlocal << endl;
    G4cout << "Index x,y,z: " << xindex << " " << yindex << " " << zindex << endl;
    double valx0z0, mulx0z0, valx1z0, mulx1z0;
    double valx0z1, mulx0z1, valx1z1, mulx1z1;
    valx0z0= table[xindex  ][0][zindex];  mulx0z0=  (1-xlocal) * (1-zlocal);
    valx1z0= table[xindex+1][0][zindex];  mulx1z0=   xlocal    * (1-zlocal);
    valx0z1= table[xindex  ][0][zindex+1]; mulx0z1= (1-xlocal) * zlocal;
    valx1z1= table[xindex+1][0][zindex+1]; mulx1z1=  xlocal    * zlocal;
#endif

        // Full 3-dimensional version
    Bfield[3] =
      xField[xindex  ][yindex  ][zindex  ] * (1-xlocal) * (1-ylocal) * (1-zlocal) +
      xField[xindex  ][yindex  ][zindex+1] * (1-xlocal) * (1-ylocal) *    zlocal  +
      xField[xindex  ][yindex+1][zindex  ] * (1-xlocal) *    ylocal  * (1-zlocal) +
      xField[xindex  ][yindex+1][zindex+1] * (1-xlocal) *    ylocal  *    zlocal  +
      xField[xindex+1][yindex  ][zindex  ] *    xlocal  * (1-ylocal) * (1-zlocal) +
      xField[xindex+1][yindex  ][zindex+1] *    xlocal  * (1-ylocal) *    zlocal  +
      xField[xindex+1][yindex+1][zindex  ] *    xlocal  *    ylocal  * (1-zlocal) +
      xField[xindex+1][yindex+1][zindex+1] *    xlocal  *    ylocal  *    zlocal ;
    Bfield[4] =
      yField[xindex  ][yindex  ][zindex  ] * (1-xlocal) * (1-ylocal) * (1-zlocal) +
      yField[xindex  ][yindex  ][zindex+1] * (1-xlocal) * (1-ylocal) *    zlocal  +
      yField[xindex  ][yindex+1][zindex  ] * (1-xlocal) *    ylocal  * (1-zlocal) +
      yField[xindex  ][yindex+1][zindex+1] * (1-xlocal) *    ylocal  *    zlocal  +
      yField[xindex+1][yindex  ][zindex  ] *    xlocal  * (1-ylocal) * (1-zlocal) +
      yField[xindex+1][yindex  ][zindex+1] *    xlocal  * (1-ylocal) *    zlocal  +
      yField[xindex+1][yindex+1][zindex  ] *    xlocal  *    ylocal  * (1-zlocal) +
      yField[xindex+1][yindex+1][zindex+1] *    xlocal  *    ylocal  *    zlocal ;
    Bfield[5] =
      zField[xindex  ][yindex  ][zindex  ] * (1-xlocal) * (1-ylocal) * (1-zlocal) +
      zField[xindex  ][yindex  ][zindex+1] * (1-xlocal) * (1-ylocal) *    zlocal  +
      zField[xindex  ][yindex+1][zindex  ] * (1-xlocal) *    ylocal  * (1-zlocal) +
      zField[xindex  ][yindex+1][zindex+1] * (1-xlocal) *    ylocal  *    zlocal  +
      zField[xindex+1][yindex  ][zindex  ] *    xlocal  * (1-ylocal) * (1-zlocal) +
      zField[xindex+1][yindex  ][zindex+1] *    xlocal  * (1-ylocal) *    zlocal  +
      zField[xindex+1][yindex+1][zindex  ] *    xlocal  *    ylocal  * (1-zlocal) +
      zField[xindex+1][yindex+1][zindex+1] *    xlocal  *    ylocal  *    zlocal ;

  } else {
    Bfield[3] = 0.0;
    Bfield[4] = 0.0;
    Bfield[5] = 0.0;
  }
	G4cout << "-------------------------GetFieldValue Check---------------------" << endl;
	G4cout << "Dx : " << Bfield[3] << endl;
	G4cout << "Dy : " << Bfield[4] << endl;
	G4cout << "Dz : " << Bfield[5] << endl;
}

