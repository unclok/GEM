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
// $Id: GEMDetectorConstruction.cc,v 1.10 2009-11-21 00:22:55 perl Exp $
// --------------------------------------------------------------
//

#include "GEMDetectorConstruction.hh"

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
//#include "G4Mag_UsualEqRhs.hh"
#include "G4UniformElectricField.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4UserLimits.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

#include "GEMElectricField.hh"

#include "G4PVReplica.hh"
#include "G4NistManager.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4PSFlatSurfaceFlux.hh"
#include "G4PSFlatSurfaceCurrent.hh"
#include "G4PSPassageCellCurrent.hh"
#include "G4PSDoseDeposit.hh"
#include "G4PSNofSecondary.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4VSDFilter.hh"
#include "G4SDParticleFilter.hh"

GEMDetectorConstruction::GEMDetectorConstruction()
 : air(0), 
h2Gas(0),
argonGas(0), scintillator(0), CsI(0), lead(0), Kapton(0), galactic(0),arco2Gas(0),
   worldVisAtt(0), electricVisAtt(0),argonVisAtt(0),
hodoscopeVisAtt(0), 
kaptonVisAtt(0), copperVisAtt(0)//,
{
  electricField = new GEMElectricField();
//  globalfieldMgr = GetGlobalFieldManager(); 
  fieldMgr = new G4FieldManager();
}

GEMDetectorConstruction::~GEMDetectorConstruction()
{
  delete electricField;
//  delete globalfieldMgr;
//  delete fieldMgr;

  DestroyMaterials();

  delete worldVisAtt;
  delete electricVisAtt;
  delete hodoscopeVisAtt;
  delete kaptonVisAtt;
  delete copperVisAtt;
//  delete propInField;
//  delete pChordFinder;
//  delete pIntgrDriver;
//  delete pEquation;
//  delete pStepper;
}

G4VPhysicalVolume* GEMDetectorConstruction::Construct()
{
  // All managed (deleted) by SDManager

  G4MultiFunctionalDetector* hodoscope1;
  G4MultiFunctionalDetector* hodoscope2;

  G4ThreeVector offset;
  G4VSolid * kapton_solid;
  G4LogicalVolume * kapton_logical;
  G4VPhysicalVolume * kapton_physical;
  G4VSolid * copper1_solid;
  G4LogicalVolume * copper1_logical;
  G4VPhysicalVolume * copper1_physical;
  G4VSolid * copper2_solid;
  G4LogicalVolume * copper2_logical;
  G4VPhysicalVolume * copper2_physical;
  G4VSolid * argon1_solid;
  G4LogicalVolume * argon1_logical;
  G4VPhysicalVolume * argon1_physical;
  G4VSolid * argon2_solid;
  G4LogicalVolume * argon2_logical;
  G4VPhysicalVolume * argon2_physical;
  G4LogicalVolume * hit_counter1;
  G4VPhysicalVolume * hc_physical1;
  G4LogicalVolume * hit_counter2;
  G4VPhysicalVolume * hc_physical2;

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  Load external 3d files;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  offset = G4ThreeVector(0*um, 0, 0);

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  G4VSensitiveDetector* HadCalorimeter;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//  Make an Electric Field;
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


  ConstructMaterials();

  // Local Electric Field
  static G4bool fieldIsInitialized = false;

  if(!fieldIsInitialized)
  {
//	electricField = new GEMElectricField();
	electricField = new G4UniformElectricField(G4ThreeVector(0.,0.,-10*kilovolt/m));
  	pEquation = new G4EqMagElectricField(electricField);
  	pStepper = new G4ClassicalRK4(pEquation, 8);
      fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
      fieldMgr->SetDetectorField(electricField); 
//	fieldMgr->CreateChordFinder(electricField);
	G4double minEps = 1.*um;
	G4double maxEps = 10.*um;

//	fieldMgr->SetMinimumEpsilonStep(minEps);
//	fieldMgr->SetMaximumEpsilonStep(maxEps);
//	fieldMgr->SetDeltaOneStep(1.*um);
	G4cout << "EpsilonStep : set min= " << minEps << " max= " << maxEps << endl;
  	pIntgrDriver = new G4MagInt_Driver(minEps,pStepper,pStepper->GetNumberOfVariables() );
//  	pChordFinder = new G4ChordFinder(electricField);
  	pChordFinder = new G4ChordFinder(pIntgrDriver);
	fieldMgr->SetChordFinder(pChordFinder);
	G4cout << "Field Exist : " << fieldMgr->DoesFieldExist() << endl;
	G4cout << "Field Changes E : " << fieldMgr->DoesFieldChangeEnergy() << endl;
	G4cout << "--------------------GEM Field Initialized------------------" << endl;

      // FOLLOWING PARAMETERS TUNED FROM RAY-TRACING SIMULATIONS OF THE AIFIRA NANOBEAM LINE
//
//      fieldMgr->GetChordFinder()->SetDeltaChord(1.*um);
//      fieldMgr->SetDeltaIntersection(1e-9*m);
//      fieldMgr->SetDeltaOneStep(1e-9*m);

//      propInField =
//        G4TransportationManager::GetTransportationManager()->GetPropagatorInField();
//      propInField->SetMinimumEpsilonStep(minEps);
//      G4cout<<"Minimum Epsilon : "<<propInField->GetMinimumEpsilonStep();
//      G4cout<<"Maximum Epsilon : "<<propInField->GetMaximumEpsilonStep()<<G4endl;
//      propInField->SetMaximumEpsilonStep(maxEps);
//	propInField->SetLargestAcceptableStep(1.*um);

//      fieldMgr->SetDetectorField(electricField); 
//	fieldMgr->CreateChordFinder(electricField);

    fieldIsInitialized = true;

  }

  // geometries --------------------------------------------------------------
  // experimental hall (world volume)
  
  G4VSolid* worldSolid = new G4Box("worldBox",50.*um,50.*um,1000.*um);
  G4LogicalVolume* worldLogical
    = new G4LogicalVolume(worldSolid,galactic,"worldLogical",0,0,0);
  G4VPhysicalVolume* worldPhysical
    = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"worldPhysical",0,0,0);
  // GEM Mother volume
  G4VSolid* GEMSolid
    = new G4Box("GEMBox",50.*um,50.*um,1000.*um);
  G4LogicalVolume* GEMLogical
    = new G4LogicalVolume(GEMSolid,arco2Gas,"GEMLogical",fieldMgr,0,0);
	GEMLogical->SetFieldManager(fieldMgr, true);
	G4cout << "Field Exist : " << fieldMgr->DoesFieldExist() << endl;

  new G4PVPlacement(0,G4ThreeVector(0.,0.,0.*um),GEMLogical,
                    "GEMPhysical",worldLogical,0,0);
//  new G4PVPlacement(0,G4ThreeVector(0.,0.,40.*um),GEMLogical,
//                    "GEMPhysical2",worldLogical,0,0);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

  // sensitive detectors -----------------------------------------------------
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4String SDname;
/*  G4VSolid* gem_box_surf = new G4Box("gem_box_surf",50.*um,50.*um,2.5*um);
  copper1_solid =  new G4Box("gem_box_surf",50.*um,50.*um,2.5*um);
  copper1_logical = new G4LogicalVolume(gem_box_surf, lead, "copper1_logical", 0, 0, 0);
  copper1_physical = new G4PVPlacement(0, G4ThreeVector(0.,0.,27.5*um), copper1_logical,
                                         "copper1_physical", GEMLogical, false, 0);

  copper2_solid = new G4Box("gem_box_surf",50.*um,50.*um,2.5*um);
  copper2_logical = new G4LogicalVolume(copper2_solid, arco2Gas, "copper2_logical", 0, 0, 0);
  copper2_physical = new G4PVPlacement(0, G4ThreeVector(0.,0.,-27.5*um), copper2_logical,
                                         "copper2_physical", GEMLogical, false, 0);
  G4VSolid* gem_hole_surf = new G4Tubs("gem_hole_surf",0.*um,35.*um,2.5*um,0.,360.*deg);
  argon2_solid = new G4UnionSolid("argon2_solid",gem_hole_surf,gem_hole_surf,0,G4ThreeVector(0.*um,0.*um,55.*um));

  G4VSolid* hit_counter_solid = new G4Box("hit_counter1",50.*um,50.*um,0.1*um);
//  G4VSolid* hit_counter_solid = new G4Tubs("hit_counter1",0.*um,35.*um,2.5*um,0.,360.*deg);
  hit_counter1 = new G4LogicalVolume(hit_counter_solid, arco2Gas, "hit_counter1", 0, 0, 0);
  hc_physical1 = new G4PVPlacement(0, G4ThreeVector(0.,0.,-30.25*um), hit_counter1,
					"hit_counter1_physical", GEMLogical, false, 0);

  hit_counter2 = new G4LogicalVolume(hit_counter_solid, arco2Gas, "hit_counter2", 0, 0, 0);
//  hc_physical2 = new G4PVPlacement(0, G4ThreeVector(0.,0.,49.95*um), hit_counter2,
  hc_physical2 = new G4PVPlacement(0, G4ThreeVector(0.,0.,31.25*um), hit_counter2,
					"hit_counter2_physical", GEMLogical, false, 0);

  G4VSolid* kapton_hole1 = new G4Cons("kapton_hole1",0.*um,35.*um,0.*um,20.*um,12.5*um,0.,360.*deg);
  G4VSolid* kapton_hole2 = new G4Cons("kapton_hole2",0.*um,20.*um,0.*um,35.*um,12.5*um,0.,360.*deg);
//  argon1_solid = new G4UnionSolid("argon1_solid",kapton_hole1,kapton_hole2,0,G4ThreeVector(0.*um,0.*um,25.*um));
  argon1_solid = new G4Tubs("kapton_hole1",0.*um,35.*um,25.*um,0.,360.*deg);

  kapton_solid = new G4Box("kapton_box",50.*um,50.*um,25.*um);
  kapton_logical = new G4LogicalVolume(kapton_solid, Kapton, "kapton_logical", 0, 0, 0);
  kapton_physical = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.*um), kapton_logical,
                                         "kapton_physical", GEMLogical, false, 0);


  argon1_logical = new G4LogicalVolume(argon1_solid, arco2Gas, "surf_hole_logical", 0, 0, 0);
//  argon1_physical = new G4PVPlacement(0, G4ThreeVector(0.,0.,-12.5*um), argon1_logical,
  argon1_physical = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.*um), argon1_logical,
                                         "argon1_physical", GEMLogical, false, 0);

  argon2_logical = new G4LogicalVolume(argon2_solid, arco2Gas, "argon2_logical", 0, 0, 0);
  argon2_physical = new G4PVPlacement(0, G4ThreeVector(0.,0.,-27.5*um), argon2_logical,
                                         "argon2_physical", GEMLogical, false, 0);
*/
  hodoscope1 = new G4MultiFunctionalDetector(SDname="/myCellScorer");
//  hodoscope1 = new GEMEmCalorimeter(SDname="/EMcalorimeter");
  SDman->AddNewDetector(hodoscope1);
//  hit_counter1->SetSensitiveDetector(hodoscope1);
  GEMLogical->SetSensitiveDetector(hodoscope1);
/*
  hodoscope2 = new GEMHodoscope(SDname="/hodoscope2");
  SDman->AddNewDetector(hodoscope2);
  hit_counter2->SetSensitiveDetector(hodoscope2);
*/

  G4VPrimitiveScorer* totalSurfFlux = new G4PSFlatSurfaceFlux("TotalSurfFlux",1);
  hodoscope1->RegisterPrimitive(totalSurfFlux); 
  G4VPrimitiveScorer* electronSurfFlux = new G4PSFlatSurfaceFlux("ElectronSurfFlux",1);
  G4SDParticleFilter* electronFilter = new G4SDParticleFilter("electronFilter");
  electronFilter->add("e-");
  electronSurfFlux->SetFilter(electronFilter);
  hodoscope1->RegisterPrimitive(electronSurfFlux);
  G4VPrimitiveScorer* totalDose = new G4PSDoseDeposit("TotalDose",1);
  hodoscope1->RegisterPrimitive(totalDose);
  G4PSPassageCellCurrent* scorerCurrent = new G4PSPassageCellCurrent("Current");
  hodoscope1->RegisterPrimitive(scorerCurrent);
  G4PSNofSecondary* totalscorerCurrent = new G4PSNofSecondary("TotalCurrent");
  hodoscope1->RegisterPrimitive(totalscorerCurrent);
  G4VPrimitiveScorer* energyscorer = new G4PSEnergyDeposit("Energy");
  hodoscope1->RegisterPrimitive(energyscorer);
/*
  G4MultiFunctionalDetector* myScorer2=new G4MultiFunctionalDetector("myScorer2");
  SDman->AddNewDetector(myScorer2);
  hit_counter2->SetSensitiveDetector(myScorer2);
  myScorer2->RegisterPrimitive(totalSurfFlux); 
  myScorer2->RegisterPrimitive(electronSurfFlux);

  SetupScoring(hit_counter1,hit_counter2);
*/
  // visualization attributes ------------------------------------------------
  // visualization attributes ------------------------------------------------

  worldVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
  worldVisAtt->SetVisibility(true);
  worldLogical->SetVisAttributes(worldVisAtt);
/*
  electricVisAtt = new G4VisAttributes(G4Colour(0.4,0.4,0.4));   // LightGray
  hodoscopeVisAtt = new G4VisAttributes(G4Colour(0.8,0.0,0.0));
  hit_counter1->SetVisAttributes(hodoscopeVisAtt);
  hit_counter2->SetVisAttributes(hodoscopeVisAtt);
  kaptonVisAtt = new G4VisAttributes(G4Colour(0.0, 0.5, 0.5));
  kapton_logical->SetVisAttributes(argonVisAtt);
  argonVisAtt = new G4VisAttributes(G4Colour(0.0, 0.0, 0.0));
  argon1_logical->SetVisAttributes(argonVisAtt);
  argon2_logical->SetVisAttributes(argonVisAtt);
  copperVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.0));
  copper1_logical->SetVisAttributes(copperVisAtt);
  copper2_logical->SetVisAttributes(copperVisAtt);
*/
  // return the world physical volume ----------------------------------------

  G4cout << G4endl << "The geometrical tree defined are : " << G4endl << G4endl;
  DumpGeometricalTree(worldPhysical);

  return worldPhysical;
}

void GEMDetectorConstruction::ConstructMaterials()
{
  G4double a;
  G4double z;
  G4double density;
  G4double weightRatio;
  G4double pressure;
  G4double temperature;
  G4String name;
  G4String symbol;
  G4int nElem;

  G4NistManager* man = G4NistManager::Instance();

  // Argon gas
  a = 39.95*g/mole;
  density = 1.782e-03*g/cm3;
  pressure = 1*atmosphere;
  temperature = 273*kelvin;
//  argonGas =  man->FindOrBuildMaterial("G4_Ar"); 
//  argonGas = new G4Material(name="ArgonGas", z=18., a, density);
  argonGas = new G4Material(name="ArgonGas", z=18., a, density, kStateGas, temperature, pressure);

  // h2 gas
  a = 1*g/mole;
  density = 0.0898e-03*g/cm3;
  h2Gas = new G4Material(name="H2Gas", z=1., a, density, kStateGas, temperature, pressure);

  // xenon gas
  a = 131.293*g/mole;
  density = 5.894e-03*g/cm3;
  xenonGas = new G4Material(name="XenonGas", z=54., a, density, kStateGas, temperature, pressure);

  // elements for mixtures and compounds
  a = 1.01*g/mole;
  G4Element* elH = new G4Element(name="Hydrogen", symbol="H", z=1., a);
  a = 12.01*g/mole;
  G4Element* elC = new G4Element(name="Carbon", symbol="C", z=6., a);
  a = 14.01*g/mole;
  G4Element* elN = new G4Element(name="Nitrogen", symbol="N", z=7., a);
  a = 16.00*g/mole;
  G4Element* elO = new G4Element(name="Oxigen", symbol="O", z=8., a);
  a = 126.9*g/mole;
  G4Element* elI = new G4Element(name="Iodine", symbol="I", z=53., a);
  a = 132.9*g/mole;
  G4Element* elCs= new G4Element(name="Cesium", symbol="Cs", z=55., a);

  // co2 gas
  density = 1.976e-3*g/cm3;
  G4Material* co2Gas = new G4Material(name="CO2gas", density, nElem=2);
  co2Gas->AddElement(elC, 1);
  co2Gas->AddElement(elO, 2);

  // argon + co2 gas
  density = 4.719e-3*g/cm3;
//  density = 5.110e-3*g/cm3;
  arco2Gas = new G4Material(name="Argon+CO2gas", density, nElem=2);
  arco2Gas->AddMaterial(argonGas, weightRatio=.7);
  arco2Gas->AddMaterial(co2Gas, weightRatio=.3);
//  arco2Gas->AddMaterial(argonGas, weightRatio=.8);
//  arco2Gas->AddMaterial(co2Gas, weightRatio=.2);

  // Air
//  density = 1.29*mg/cm3;
//  air = new G4Material(name="Air", density, nElem=2);

//  air->AddElement(elN, weightRatio=.7);
//  air->AddElement(elO, weightRatio=.3);

  // vacuum
  density     = universe_mean_density;                //from PhysicalConstants.h
  galactic = new G4Material(name="Galactic", z=1., a=1.01*g/mole, density);


  // Scintillator
  density = 1.032*g/cm3;
  scintillator = new G4Material(name="Scintillator", density, nElem=2);
  scintillator->AddElement(elC, 9);
  scintillator->AddElement(elH, 10);

  // CsI
  density = 4.51*g/cm3;
  CsI = new G4Material(name="CsI", density, nElem=2);
  CsI->AddElement(elI, weightRatio=.5);
  CsI->AddElement(elCs,weightRatio=.5);

  // Lead
  a = 207.19*g/mole;
  density = 11.35*g/cm3;
  lead = new G4Material(name="Lead", z=82., a, density);

  // Kapton Dupont de Nemur (density: 1.396-1.430, get middle )
  density = 1.413*g/cm3;
  Kapton = new G4Material(name="Kapton", density, nElem=4);
  Kapton->AddElement(elO,5);
  Kapton->AddElement(elC,22);
  Kapton->AddElement(elN,2);
  Kapton->AddElement(elH,10);

  air = man->FindOrBuildMaterial("G4_AIR");

  G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
  G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

void GEMDetectorConstruction::DestroyMaterials()
{
  // Destroy all allocated elements and materials
  size_t i;
  G4MaterialTable* matTable = (G4MaterialTable*)G4Material::GetMaterialTable();
  for(i=0;i<matTable->size();i++)
  { delete (*(matTable))[i]; }
  matTable->clear();
  G4ElementTable* elemTable = (G4ElementTable*)G4Element::GetElementTable();
  for(i=0;i<elemTable->size();i++)
  { delete (*(elemTable))[i]; }
  elemTable->clear();
}

void GEMDetectorConstruction::DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth)
{
  for(int isp=0;isp<depth;isp++)
  { G4cout << "  "; }
  G4cout << aVolume->GetName() << "[" << aVolume->GetCopyNo() << "] "
         << aVolume->GetLogicalVolume()->GetName() << " "
         << aVolume->GetLogicalVolume()->GetNoDaughters() << " "
         << aVolume->GetLogicalVolume()->GetMaterial()->GetName();
  if(aVolume->GetLogicalVolume()->GetSensitiveDetector())
  {
    G4cout << " " << aVolume->GetLogicalVolume()->GetSensitiveDetector()
                            ->GetFullPathName();
  }
  G4cout << G4endl;
  for(int i=0;i<aVolume->GetLogicalVolume()->GetNoDaughters();i++)
  { DumpGeometricalTree(aVolume->GetLogicalVolume()->GetDaughter(i),depth+1); }
}

