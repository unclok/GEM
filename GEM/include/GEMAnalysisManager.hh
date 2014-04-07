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
//
// **********************************************************************
// *                                                                    *
// *                    GEANT 4 tutorial 1                              *
// *                                                                    *
// * MODULE:            GEMAnalysisManager.cc                           *
// * -------                                                            *
// *                                                                    *
// * Version:           0.1                                             *
// * Date:              January 28 2002                                 *
// * Author:            T.Johnson                                       *
// * Organisation:      SLAC                                            *
// *                                                                    *
// **********************************************************************
//
// CHANGE HISTORY
// --------------
//
//
// **********************************************************************

#ifndef GEMAnalysisManager_h
#define GEMAnalysisManager_h 1

#include "globals.hh"
#include <vector>
#include "G4ThreeVector.hh"

using namespace AIDA;

class AIDA::IAnalysisFactory;
class AIDA::ITree;
class AIDA::IHistogramFactory;
class AIDA::ITupleFactory;
class AIDA::IPlotter;

class G4Track;

class GEMAnalysisManager {
public:

  virtual ~GEMAnalysisManager();
  static GEMAnalysisManager* getInstance();
  static void dispose();

  IHistogramFactory* getHistogramFactory();
  ITupleFactory* getTupleFactory();
  IPlotter* getPlotter();

private:

  GEMAnalysisManager();
  static GEMAnalysisManager* instance;

  IAnalysisFactory* analysisFactory;
  IHistogramFactory* hFactory;
  ITupleFactory* tFactory;
  IPlotter* plotter;
  ITree* tree;
};

#endif

