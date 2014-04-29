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
#include "GEMElectricFieldMessenger.hh"
//#include "G4SystemOfUnits.hh"
#include "globals.hh"
#include <string>
#include <fstream>
#include <iostream>
#include "G4UserLimits.hh"
#include "G4ThreeVector.hh"

GEMElectricField::GEMElectricField()
{
  messenger = new GEMElectricFieldMessenger(this);
//  By = 1.0*tesla;
	ifstream infile;
	double temp[6];
	double blank[3];
	if(fEfield=10)infile.open("model/GEM_70_10_400V_extension.txt");
	else if(fEfield=30)infile.open("model/GEM_70_30_400V_extension.txt");
	else if(fEfield=50)infile.open("model/GEM_70_50_400V_extension.txt");
	else if(fEfield=40)infile.open("model/GEM_70_40_400V_extension.txt");
	else if(fEfield=70)infile.open("model/GEM_70_70_400V_extension.txt");
	else{
		G4cout<<"You can only use 10, 30, 40, 50, 70 for field"<<G4endl;
		infile.open("model/GEM_70_40_400V_extension.txt");
	}
	G4cout << system("pwd") << G4endl;
	if(infile==false)G4cout << "file not found\n" << G4endl;
        string str="";
        for(int i=0;i<2;i++){
                getline(infile, str);
        }

        for(int i=0;i<41;i++){
		for(int j=0;j<41;j++){
			for(int k=0;k<801;k++){
     	         	  getline(infile, str);
     	         	  sscanf(str.c_str(),"%lf %lf %lf %lf %lf %lf %lf %lf %lf",&temp[0],&temp[1],&temp[2],&temp[3],&temp[4],&temp[5],&blank[0],&blank[1],&blank[2]);
//				if(k>5 && k<35)
				for(int p=0;p<3;p++){
					GEMPosition[p][i][j][k]=temp[p]*um;
					GEMElec[p][i][j][k]=temp[p+3]*volt/m;
//					if(p==1)GEMElec[p][i][j][k]+10000*volt/m;
					if(i==40 && j==40 && k==800)std::cout<<GEMPosition[p][i][j][k]<<std::endl;
				}
//				std::cout<<k<<std::endl;
			}
		}
        }
        infile.close();

  min[0] = GEMPosition[0][0][0][0];
  min[1] = GEMPosition[1][0][0][0];
  min[2] = GEMPosition[2][0][0][0];
  max[0] = temp[0]*um;
  max[1] = temp[1]*um;
  max[2] = temp[2]*um;

  std::cout<<max[0]<<" "<<max[1]<<" "<<max[2]<<" "<<min[0]<<" "<<min[1]<<" "<<min[2]<<std::endl;
  std::cout<<"volt/m :"<<volt/m<<std::endl;

  G4cout << "\n ---> ... done reading " << endl;

  // G4cout << " Read values of field from file " << filename << endl; 
  G4cout << " ---> assumed the order:  x, y, z, Ex, Ey, Ez "
         << "\n ---> Min values x,y,z: " 
         << min[0]/um << " " << min[1]/um << " " << min[2]/um << " um "
         << "\n ---> Max values x,y,z: "
         << max[0]/um << " " << max[1]/um << " " << max[2]/um << " um "
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

//	G4double uStepMax = 1.0*um;
}

GEMElectricField::~GEMElectricField()
{
 delete messenger; 
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

	// Initialize Field
	Bfield[0] = 0.0;
	Bfield[1] = 0.0;
	Bfield[2] = 0.0;
	Bfield[3] = 0.0;
	Bfield[4] = 0.0;
	Bfield[5] = 0.0;

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
//	G4cout << "----------------------GetFieldValue Working----------------------" << endl;
	Bfield[3] = 0.0;
	Bfield[4] = 0.0;
	Bfield[5] = 0.0;
        // Full 3-dimensional version
    Bfield[3] =
      GEMElec[0][xindex  ][yindex  ][zindex  ] * (1-xlocal) * (1-ylocal) * (1-zlocal) +
      GEMElec[0][xindex  ][yindex  ][zindex+1] * (1-xlocal) * (1-ylocal) *    zlocal  +
      GEMElec[0][xindex  ][yindex+1][zindex  ] * (1-xlocal) *    ylocal  * (1-zlocal) +
      GEMElec[0][xindex  ][yindex+1][zindex+1] * (1-xlocal) *    ylocal  *    zlocal  +
      GEMElec[0][xindex+1][yindex  ][zindex  ] *    xlocal  * (1-ylocal) * (1-zlocal) +
      GEMElec[0][xindex+1][yindex  ][zindex+1] *    xlocal  * (1-ylocal) *    zlocal  +
      GEMElec[0][xindex+1][yindex+1][zindex  ] *    xlocal  *    ylocal  * (1-zlocal) +
      GEMElec[0][xindex+1][yindex+1][zindex+1] *    xlocal  *    ylocal  *    zlocal ;
    Bfield[4] =
      GEMElec[1][xindex  ][yindex  ][zindex  ] * (1-xlocal) * (1-ylocal) * (1-zlocal) +
      GEMElec[1][xindex  ][yindex  ][zindex+1] * (1-xlocal) * (1-ylocal) *    zlocal  +
      GEMElec[1][xindex  ][yindex+1][zindex  ] * (1-xlocal) *    ylocal  * (1-zlocal) +
      GEMElec[1][xindex  ][yindex+1][zindex+1] * (1-xlocal) *    ylocal  *    zlocal  +
      GEMElec[1][xindex+1][yindex  ][zindex  ] *    xlocal  * (1-ylocal) * (1-zlocal) +
      GEMElec[1][xindex+1][yindex  ][zindex+1] *    xlocal  * (1-ylocal) *    zlocal  +
      GEMElec[1][xindex+1][yindex+1][zindex  ] *    xlocal  *    ylocal  * (1-zlocal) +
      GEMElec[1][xindex+1][yindex+1][zindex+1] *    xlocal  *    ylocal  *    zlocal ;
    Bfield[5] =
      GEMElec[2][xindex  ][yindex  ][zindex  ] * (1-xlocal) * (1-ylocal) * (1-zlocal) +
      GEMElec[2][xindex  ][yindex  ][zindex+1] * (1-xlocal) * (1-ylocal) *    zlocal  +
      GEMElec[2][xindex  ][yindex+1][zindex  ] * (1-xlocal) *    ylocal  * (1-zlocal) +
      GEMElec[2][xindex  ][yindex+1][zindex+1] * (1-xlocal) *    ylocal  *    zlocal  +
      GEMElec[2][xindex+1][yindex  ][zindex  ] *    xlocal  * (1-ylocal) * (1-zlocal) +
      GEMElec[2][xindex+1][yindex  ][zindex+1] *    xlocal  * (1-ylocal) *    zlocal  +
      GEMElec[2][xindex+1][yindex+1][zindex  ] *    xlocal  *    ylocal  * (1-zlocal) +
      GEMElec[2][xindex+1][yindex+1][zindex+1] *    xlocal  *    ylocal  *    zlocal; 

//	G4cout << "-----------------------Acceptable!!---------------------" << endl;
  } else {
	Bfield[0] = 0.0;
	Bfield[1] = 0.0;
	Bfield[2] = 0.0;
    Bfield[3] = 0.0;
    Bfield[4] = 0.0;
    Bfield[5] = 0.0;
  }
	G4cout << "-------------------------GetFieldValue Check---------------------" << endl;
	G4cout << "x : " << x << endl;
	G4cout << "y : " << y << endl;
	G4cout << "z : " << z << endl;
	G4cout << "minx : " << minx << endl;
	G4cout << "miny : " << miny << endl;
	G4cout << "minz : " << minz << endl;
	G4cout << "maxx : " << maxx << endl;
	G4cout << "maxy : " << maxy << endl;
	G4cout << "maxz : " << maxz << endl;
	G4cout << "Hx : " << Bfield[0] << endl;
	G4cout << "Hy : " << Bfield[1] << endl;
	G4cout << "Hz : " << Bfield[2] << endl;
	G4cout << "Dx : " << Bfield[3] << endl;
	G4cout << "Dy : " << Bfield[4] << endl;
	G4cout << "Dz : " << Bfield[5] << endl;

}

