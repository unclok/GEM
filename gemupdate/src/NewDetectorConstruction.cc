#include "NewDetectorConstruction.hh"
#include "NewDetectorConstMessenger.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "NewElectricField.hh"
#include "GEMElectricField.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4SubtractionSolid.hh" 
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4AssemblyVolume.hh"

#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

#include "G4PVReplica.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4PSFlatSurfaceCurrent.hh"
#include "G4PSPassageCellCurrent.hh"
#include "G4PSNofSecondary.hh"
#include "NewEnergyDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4VSDFilter.hh"
#include "G4SDParticleFilter.hh"

#include "G4VSensitiveDetector.hh"
#include "A01DriftChamber.hh"

NewDetectorConstruction::NewDetectorConstruction()
:fefield(-100.),fefielddirection(0.,0.,1.)
{
	messenger = new NewDetectorConstMessenger(this);
	//fieldMgr1 = new G4FieldManager();
	fieldMgr2 = G4TransportationManager::GetTransportationManager()->GetFieldManager();
	//fieldMgr3 = G4TransportationManager::GetTransportationManager()->GetFieldManager();
	electricField = new NewElectricField(G4ThreeVector(fefield*kilovolt/cm*fefielddirection.x()/fefielddirection.r(),fefield*kilovolt/cm*fefielddirection.y()/fefielddirection.r(),fefield*kilovolt/cm*fefielddirection.z()/fefielddirection.r()));
	gemField = new GEMElectricField();
}

NewDetectorConstruction::~NewDetectorConstruction()
{
	DestroyMaterials();

	delete pEquation1; 
	delete pStepper1;
	delete pIntgrDriver1;
	delete pChordFinder1;
	delete pEquation2; 
	delete pStepper2;
	delete pIntgrDriver2;
	delete pChordFinder2;
	delete pEquation3; 
	delete pStepper3;
	delete pIntgrDriver3;
	delete pChordFinder3;
	delete messenger;
	delete worldVisAtt;
	delete argonVisAtt;
	delete electricField;
	delete gemField;
}

G4VPhysicalVolume* NewDetectorConstruction::Construct()
{
	ConstructMaterials();

	// geometries
	// experimental hall (world volume)
	G4double xlength = 50.*um;
	G4double ylength = 50.*um;
	G4double argon_thic = 60.*um;

	G4VSolid* worldSolid = new G4Box("worldBox",xlength,ylength,argon_thic);
//	G4VSolid* worldSolid = new G4Box("worldBox",4050.*um,2500.*um,4060.*um);
	worldLogical = new G4LogicalVolume(worldSolid,argonGas,"worldLogical",0,0,0);
//	fParser.Read("gem.gdml");
//	G4VPhysicalVolume* worldPhysical = fParser.GetWorldVolume();
	G4VPhysicalVolume* worldPhysical = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"worldPhysical",0,0,0);

	// GEM Mother volume
	G4VSolid* GEMSolid = new G4Box("GEMBox",xlength,ylength,argon_thic);
	//G4LogicalVolume* GEMLogical = new G4LogicalVolume(GEMSolid,galactic,"GEMLogical",0,0,0);
	//G4PVPlacement *GEMPhysical = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.*um),GEMLogical,"GEMPhysical",worldLogical,0,0);
/*	G4VSolid* GEMRepSolid1 = new G4Box("GEMRepBox1",4000.*um,50.*um,30.*um);
	G4VSolid* GEMRepSolid2 = new G4Box("GEMRepBox2",4050.*um,50.*um,30.*um);
	G4LogicalVolume* GEMRepLogical1[25];
	G4LogicalVolume* GEMRepLogical2[25];
	G4PVReplica *repgem[50];

	G4PVPlacement *GEMPhysical[50];
	for(G4int i=0;i<50;i++){
		if(i%2==0){
			GEMRepLogical1[i/2] = new G4LogicalVolume(GEMRepSolid1,galactic,"GEMRepLogical",0,0,0);
			GEMPhysical[i] = new G4PVPlacement(0,G4ThreeVector(0.,2450*um-2*50*i*um,0.),GEMRepLogical1[i/2],"GEMPhysical",worldLogical,0,0);
			repgem[i] = new G4PVReplica("GEMRep",GEMLogical,GEMPhysical[i],kXAxis,80,100.*um);
		}
		else{
			GEMRepLogical2[i/2] = new G4LogicalVolume(GEMRepSolid2,galactic,"GEMRepLogical",0,0,0);
			GEMPhysical[i] = new G4PVPlacement(0,G4ThreeVector(0.,2450*um-2*50*i*um,0.*um),GEMRepLogical2[i/2],"GEMPhysical",worldLogical,0,0);
			repgem[i] = new G4PVReplica("GEMRep",GEMLogical,GEMPhysical[i],kXAxis,81,100.*um);
		}
	}
*/
	// GEM Drifit volume
	G4double Drift_thic = 500.*um;
	G4VSolid* Drift1_Solid = new G4Box("Drift1_solid",xlength,ylength,Drift_thic);
	G4VSolid* Drift2_Solid = new G4Box("Drift2_solid",xlength,ylength,Drift_thic);
//	G4VSolid* Drift1_Solid = new G4Box("Drift1_solid",4050.*um,2500.*um,2000.*um);
//	G4VSolid* Drift2_Solid = new G4Box("Drift2_solid",4050.*um,2500.*um,1000.*um);
	Drift1_logical = new G4LogicalVolume(Drift1_Solid,argonGas,"Drift1_logical",0,0,0);
	Drift2_logical = new G4LogicalVolume(Drift2_Solid,argonGas,"Drift2_logical",0,0,0);
//	G4VPhysicalVolume* Drift1_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,-2060.*um),Drift1_logical,"Drift1_physical",worldLogical,0,0);
//	G4VPhysicalVolume* Drift2_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,1060.*um),Drift2_logical,"Drift2_physical",worldLogical,0,0);
	//G4VPhysicalVolume* Drift1_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,-45.*um),Drift1_logical,"Drift1_physical",worldLogical,0,0);
	//G4VPhysicalVolume* Drift2_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,45.*um),Drift2_logical,"Drift2_physical",worldLogical,0,0);

	// Box
	G4VSolid* argon_solid;
	G4VPhysicalVolume* argon_physical;

	G4VSolid* copper_hole;
	G4VSolid* copper_box;
	G4VSolid* copper_solidtemp;
	G4VSolid* copper_solid;
	G4LogicalVolume* copper_logical;
	G4VPhysicalVolume* copper1_physical;
	G4VPhysicalVolume* copper2_physical;
	G4VSolid* kapton_box;
	G4VSolid* kapton_hole1;
	G4VSolid* kapton_hole2;
	G4VSolid* kapton_hole;
	G4VSolid* kapton_solid;
	G4LogicalVolume* kapton_logical;
	G4VPhysicalVolume* kapton_physical;

	G4double outdia = 35.*um;
	G4double middia = 15*um;
	G4double kapton_thic = 12.5*um;
	G4double copper_thic = 2.5*um;
	G4double kapton_offset = 9.375*um;

	argon_solid = new G4Box("argon_solid",xlength,ylength,argon_thic);
	argon_logical = new G4LogicalVolume(argon_solid,Kapton,"argon_logical",0,0,0);
	//argon_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.*um),argon_logical,"argon_physical",GEMLogical,false,0);

	//G4VPhysicalVolume* Drift1_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,-(Drift_thic+copper_thic*2+kapton_thic*2)),Drift1_logical,"Drift1_physical",argon_logical,0,0);
	//G4VPhysicalVolume* Drift2_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,Drift_thic+copper_thic*2+kapton_thic*2),Drift2_logical,"Drift2_physical",argon_logical,0,0);

	copper_box = new G4Box("copper_box",xlength,ylength,copper_thic);
	copper_hole = new G4Tubs("copper_hole",0.*um,outdia,copper_thic,0,360.*deg);
	copper_solidtemp = new G4SubtractionSolid("copper_solidtemp",copper_box,copper_hole,0,G4ThreeVector(0.,0.*um,copper_thic*2 - 0.1*um));
	copper_solid = new G4SubtractionSolid("copper_solid",copper_solidtemp,copper_hole,0,G4ThreeVector(0.,0.*um, -copper_thic*2 + 0.1*um));
	copper_logical = new G4LogicalVolume(copper_solid,copper,"copper_logical",0,0,0);
	G4LogicalVolume* copper2_logical = new G4LogicalVolume(copper_solid,copper,"copper2_logical",0,0,0);
	copper1_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,-(kapton_thic*2+copper_thic)),copper_logical,"copper1_physical",worldLogical,false,0);
	copper2_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,(kapton_thic*2+copper_thic)),copper2_logical,"copper2_physical",worldLogical,false,0);
	G4LogicalVolume* copper_graphic = new G4LogicalVolume(copper_hole,argonGas,"copper_graphic",0,0,0);
	G4LogicalVolume* copper2_graphic = new G4LogicalVolume(copper_hole,argonGas,"copper_graphic",0,0,0);
	G4VPhysicalVolume* coppergr1_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,0),copper_graphic,"coppergr_physical",copper_logical,false,0);
	G4VPhysicalVolume* coppergr2_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,0),copper2_graphic,"coppergr2_physical",copper2_logical,false,0);


	kapton_box = new G4Box("kapton_box",xlength,ylength,kapton_thic*2);
	G4VSolid* kapton_solidtemp = new G4SubtractionSolid("kapton_solidtemp",kapton_box,copper_hole,0,G4ThreeVector(0,0,kapton_thic*4 - 0.1*um));
	kapton_solid = new G4SubtractionSolid("kapton_solid",kapton_solidtemp,copper_hole,0,G4ThreeVector(0,0,-kapton_thic*4 + 0.1*um));
	//G4VSolid* kapton_mid = new G4Tubs("kapton_mid",0.*um,middia,0.1*um,0,360.*deg);
	kapton_hole1 = new G4Cons("kapton_hole1",0*um,outdia,0*um,0,kapton_thic+kapton_offset,0.,360.*deg);
	kapton_hole2 = new G4Cons("kapton_hole2",0*um,0,0*um,outdia,kapton_thic+kapton_offset,0.,360.*deg);
	kapton_hole = new G4UnionSolid("kapton_hole",kapton_hole1,kapton_hole2,0,G4ThreeVector(0,0,kapton_thic-kapton_offset/2));
	//G4VSolid*  kapton_half = new G4UnionSolid("kapton_half",kapton_hole,kapton_mid,0,G4ThreeVector(0.*um,0.*um,kapton_thic));
	//kapton_hole = new G4SubtractionSolid("kapton_hole",kapton_box,kapton_hole2,0,G4ThreeVector(0.*um,0.*um,6.25*um));
	//kapton_solid = new G4SubtractionSolid("kapton_solid",kapton_hole,kapton_hole1,0,G4ThreeVector(0.,0.,-6.25*um));
	//kapton_solid = new G4SubtractionSolid("kapton_solid",kapton_box,kapton_half,0,G4ThreeVector(0.,0.,-kapton_thic));
	kapton_logical = new G4LogicalVolume(kapton_box,Kapton,"kapton_logical",0,0,0);
	kapton_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,0),kapton_logical,"kapton_physical",worldLogical,false,0);
	G4LogicalVolume* kapton_graphic = new G4LogicalVolume(kapton_hole,argonGas,"kapton_logical",0,0,0);
	G4VPhysicalVolume* kaptongr_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,-kapton_thic+kapton_offset),kapton_graphic,"kaptongr_physical",kapton_logical,false,0);

	//Use G4AssemblyVolume
	/*
	G4Transform3D Tr;
	G4AssemblyVolume *gemargon = new G4AssemblyVolume();
	Tr = G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,-(kapton_thic*2+copper_thic)));
	gemargon->AddPlacedVolume(copper_box,Tr);
	Tr = G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,0));
	gemargon->AddPlacedVolume(kapton_box,Tr);
	Tr = G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,(kapton_thic*2+copper_thic)));
	gemargon->AddPlacedVolume(copper_box,Tr);
	Tr = G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,0));
	gemargon->MakeImprint(argon_logical,Tr);
	
	G4LogicalVolume *kapton_halflog = new G4LogicalVolume(kapton_hole,argonGas,"kapton_halflog",0,0,0);
	Tr = G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,-kapton_thic));
	gemargon->AddPlacedVolume(kapton_halflog,Tr);
	G4LogicalVolume *copper_holelog = new G4LogicalVolume(copper_hole,argonGas,"copper_holelog",0,0,0);
	Tr = G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,-(kapton_thic*2+copper_thic)));
	gemargon->AddPlacedVolume(copper_holelog,Tr);
	Tr = G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,(kapton_thic*2+copper_thic)));
	gemargon->AddPlacedVolume(copper_holelog,Tr);
	Tr = G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,-(argon_thic-Drift_thic)));
	gemargon->AddPlacedVolume(Drift1_logical,Tr);
	Tr = G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,argon_thic-Drift_thic));
	gemargon->AddPlacedVolume(Drift2_logical,Tr);
	Tr = G4Transform3D(G4RotationMatrix(),G4ThreeVector(0,0,0));
	gemargon->MakeImprint(argon_logical,Tr);
	*/

	G4VSolid* all1 = new G4UnionSolid("all1",Drift1_Solid,copper_hole,0,G4ThreeVector(0*um,0*um,Drift_thic+copper_thic));
	G4VSolid* all2 = new G4UnionSolid("all2",all1,kapton_hole,0,G4ThreeVector(0*um,0*um,Drift_thic+copper_thic*2+kapton_thic));
	G4VSolid* all3 = new G4UnionSolid("all3",all2,copper_hole,0,G4ThreeVector(0*um,0*um,Drift_thic+copper_thic*2+kapton_thic*4+copper_thic));
	G4VSolid* all4 = new G4UnionSolid("all4",all3,Drift2_Solid,0,G4ThreeVector(0*um,0*um,Drift_thic+copper_thic*2+kapton_thic*4+copper_thic*2+Drift_thic));

	gem = new G4LogicalVolume(all4,argonGas,"gem_logical",0,0,0);
//	G4VPhysicalVolume* gemphys = new G4PVPlacement(0,G4ThreeVector(0*um,0*um,-Drift_thic-copper_thic*2-kapton_thic*2),gem,"gem_physical",worldLogical,false,0);

	// Hodoscope declaration
	G4VSolid* hit_solid;
	G4LogicalVolume* hit_counter1;
	G4VPhysicalVolume* hc_physical1;
	G4LogicalVolume* hit_counter2;
	G4VPhysicalVolume* hc_physical2;

	G4LogicalVolume* dc_logical1;
	G4VPhysicalVolume* dc_physical1;
	G4LogicalVolume* dc_logical2;
	G4VPhysicalVolume* dc_physical2;

	hit_solid = new G4Box("hit_counter",xlength,ylength,0.1*um);
//	hit_solid = new G4Box("hit_counter",4050.*um,2500.*um,0.1*um);
	hit_counter1 = new G4LogicalVolume(hit_solid,galactic,"hit_counter1",0,0,0);
	hc_physical1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,-30.1*um),hit_counter1,"dc1_physical",worldLogical,false,0);
//	hc_physical1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,-999.7*um),hit_counter1,"dc1_physical",Drift1_logical,false,0);
	hit_counter2 = new G4LogicalVolume(hit_solid,galactic,"hit_counter2",0,0,0);
	hc_physical2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,30.1*um),hit_counter2,"dc2_physical",worldLogical,false,0);
//	hc_physical2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,499.9*um),hit_counter2,"dc2_physical",Drift2_logical,false,0);

	dc_logical1 = new G4LogicalVolume(hit_solid,galactic,"dc1",0,0,0);
	dc_physical1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,-30.3*um),dc_logical1,"dc1_physical",worldLogical,false,0);
//	dc_physical1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,-999.5*um),dc_logical1,"dc1_physical",Drift1_logical,false,0);
	dc_logical2 = new G4LogicalVolume(hit_solid,galactic,"dc2",0,0,0);
	dc_physical2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,30.3*um),dc_logical2,"dc2_physical",worldLogical,false,0);
//	dc_physical2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,499.7*um),dc_logical2,"dc2_physical",Drift2_logical,false,0);

	// multifunctional detectors
	G4MultiFunctionalDetector* hodoscope1;
	G4MultiFunctionalDetector* hodoscope2;
	G4MultiFunctionalDetector* hodoscope3;

	G4VSensitiveDetector* drift1;
	G4VSensitiveDetector* drift2;
	
	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	G4String SDname;

	hodoscope1 = new G4MultiFunctionalDetector(SDname="/hodoscope1");
	SDman->AddNewDetector(hodoscope1);
	hit_counter1->SetSensitiveDetector(hodoscope1);

	hodoscope2 = new G4MultiFunctionalDetector(SDname="/hodoscope2");
	SDman->AddNewDetector(hodoscope2);
	hit_counter2->SetSensitiveDetector(hodoscope2);

	hodoscope3 = new G4MultiFunctionalDetector(SDname="/hodoscope3");
	SDman->AddNewDetector(hodoscope3);
	kapton_logical->SetSensitiveDetector(hodoscope3);

	drift1 = new A01DriftChamber(SDname="/drift1");
	SDman->AddNewDetector(drift1);
	dc_logical1->SetSensitiveDetector(drift1);
	drift2 = new A01DriftChamber(SDname="/drift2");
	SDman->AddNewDetector(drift2);
	dc_logical2->SetSensitiveDetector(drift2);

	G4PSFlatSurfaceCurrent* totalSurfCurrent1 = new G4PSFlatSurfaceCurrent("TotalSurfCurrent1",1);
	totalSurfCurrent1->Weighted(false);
	totalSurfCurrent1->DivideByArea(false);
	hodoscope1->RegisterPrimitive(totalSurfCurrent1);
	G4PSFlatSurfaceCurrent* electronSurfCurrent1 = new G4PSFlatSurfaceCurrent("ElectronSurfCurrent1",1);
	electronSurfCurrent1->Weighted(false);
	electronSurfCurrent1->DivideByArea(false);
	G4SDParticleFilter* electronFilter = new G4SDParticleFilter("electronFilter");
	electronFilter->add("e-");
	electronSurfCurrent1->SetFilter(electronFilter);
	hodoscope1->RegisterPrimitive(electronSurfCurrent1);
	NewEnergyDetector* energyscorer1 = new NewEnergyDetector("Energy1");
	energyscorer1->SetFilter(electronFilter);
	hodoscope1->RegisterPrimitive(energyscorer1);

	G4PSFlatSurfaceCurrent* totalSurfCurrent2 = new G4PSFlatSurfaceCurrent("TotalSurfCurrent2",1);
	totalSurfCurrent2->Weighted(false);
	totalSurfCurrent2->DivideByArea(false);
	hodoscope2->RegisterPrimitive(totalSurfCurrent2);
	G4PSFlatSurfaceCurrent* electronSurfCurrent2 = new G4PSFlatSurfaceCurrent("ElectronSurfCurrent2",1);
	electronSurfCurrent2->Weighted(false);
	electronSurfCurrent2->DivideByArea(false);
	electronSurfCurrent2->SetFilter(electronFilter);
	hodoscope2->RegisterPrimitive(electronSurfCurrent2);
	G4VPrimitiveScorer* energyscorer2 = new NewEnergyDetector("Energy2");
	energyscorer2->SetFilter(electronFilter);
	hodoscope2->RegisterPrimitive(energyscorer2);

	G4PSPassageCellCurrent* scorerCurrent = new G4PSPassageCellCurrent("Current");
	hodoscope3->RegisterPrimitive(scorerCurrent);
	G4PSNofSecondary* secondaryscorerCurrent = new G4PSNofSecondary("SecondaryCurrent");
	secondaryscorerCurrent->SetFilter(electronFilter);
	hodoscope3->RegisterPrimitive(secondaryscorerCurrent);

	// Make an Electric Field
	//SetEfield(argon_logical, fieldMgr2, pStepper2, pEquation2, pIntgrDriver2, pChordFinder2, G4ThreeVector(0,0,-1), 50);
	SetGEMfield(worldLogical, fieldMgr2, pStepper2, pEquation2, pIntgrDriver2, pChordFinder2);
	//SetEfield(Drift2_logical, fieldMgr2, pStepper3, pEquation3, pIntgrDriver3, pChordFinder3, G4ThreeVector(0,0,1), -1000);
	//SetEfield(hit_counter2, fieldMgr3, G4ThreeVector(0,0,-1), 3000*fefield*6/400);
	//SetEfield(dc_logical2, fieldMgr3, G4ThreeVector(0,0,-1), 3000*fefield*6/400);
	//SetEfield(Drift1_logical, fieldMgr2, pStepper1, pEquation1, pIntgrDriver1, pChordFinder1, G4ThreeVector(0,0,1), 4);
	//SetEfield(hit_counter1, fieldMgr1, G4ThreeVector(0,0,-1), 1000);
	//SetEfield(dc_logical1, fieldMgr1, G4ThreeVector(0,0,-1), 1000);
	//if(worldLogical->GetFieldManager()->DoesFieldChangeEnergy())G4cout<<"dc 1 has a field"<<G4endl;
	//if(copper_graphic->GetFieldManager()->DoesFieldChangeEnergy())G4cout<<"dc 2 has a field"<<G4endl;


	// visualization attributes
	worldVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,1.0));
	worldVisAtt->SetVisibility(true);
	worldLogical->SetVisAttributes(worldVisAtt);
	worldPhysical->GetLogicalVolume()->SetVisAttributes(worldVisAtt);
	argonVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,0.0));
	copperVisAtt = new G4VisAttributes(G4Colour(0.0,1.0,1.0));
	argon_logical->SetVisAttributes(copperVisAtt);
	kapton_logical->SetVisAttributes(copperVisAtt);
	copper_logical->SetVisAttributes(copperVisAtt);
	copper2_logical->SetVisAttributes(copperVisAtt);
	hit_counter1->SetVisAttributes(argonVisAtt);
	hit_counter2->SetVisAttributes(argonVisAtt);
	dc_logical1->SetVisAttributes(argonVisAtt);
	dc_logical2->SetVisAttributes(argonVisAtt);
	gem->SetVisAttributes(argonVisAtt);
	kapton_graphic->SetVisAttributes(argonVisAtt);
	copper_graphic->SetVisAttributes(argonVisAtt);
	copper2_graphic->SetVisAttributes(argonVisAtt);
	Drift1_logical->SetVisAttributes(argonVisAtt);
	Drift2_logical->SetVisAttributes(argonVisAtt);

	// return the world physical volume
	G4cout << G4endl << "The geometrical tree defined are : " << G4endl << G4endl;
	DumpGeometricalTree(worldPhysical);

	return worldPhysical;
}

void NewDetectorConstruction::ConstructMaterials()
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
//	pressure = 0.680*atmosphere;
	pressure = 1*atmosphere;
//	temperature = 273*kelvin;
	temperature = 300*kelvin;

	argonGas = new G4Material(name="ArgonGas", z=18., a, density, kStateGas, temperature, pressure);
	//argonGas = man->FindOrBuildMaterial("G4_Ar");

	// vacuum
	density = universe_mean_density; // from PhysicalConstants.h
	galactic = new G4Material(name="Galactic",z=1.,a=1.01*g/mole,density);

	air = man->FindOrBuildMaterial("G4_AIR");

	G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
	G4cout << *(G4Material::GetMaterialTable()) << G4endl;

	// copper
	a = 63.546*g/mole;
	density = 8.96*g/cm3;
	//copper = new G4Material(name="Copper", z=29., a, density);	
	copper = man->FindOrBuildMaterial("G4_Cu");

	// elements for mixtures and compounds
	a = 1.01*g/mole;
	G4Element* elH = new G4Element(name="Hydrogen", symbol="H", z=1., a);
	a = 12.01*g/mole;
	G4Element* elC = new G4Element(name="Carbon", symbol="C", z=6., a);
	a = 14.01*g/mole;
	G4Element* elN = new G4Element(name="Nitrogen", symbol="N", z=7., a);
	a = 16.00*g/mole;
	G4Element* elO = new G4Element(name="Oxigen", symbol="O", z=8., a);

	// Kapton Dupont de Nemur (density: 1.396-1.430, get middle )
		density = 1.413*g/cm3;
		Kapton = new G4Material(name="Kapton", density, nElem=4);
		Kapton->AddElement(elO,5);
		Kapton->AddElement(elC,22);
		Kapton->AddElement(elN,2);
		Kapton->AddElement(elH,10);

}

void NewDetectorConstruction::DestroyMaterials()
{
	// Destroy all allocated elements and materials
	size_t i;
	G4MaterialTable* matTable = (G4MaterialTable*)G4Material::GetMaterialTable();
	for(i=0;i<matTable->size();i++)
	{
		delete(*(matTable))[i];
	}
	matTable->clear();

	G4ElementTable* elemTable = (G4ElementTable*)G4Element::GetElementTable();
	for(i=0;i<elemTable->size();i++)
	{
		delete(*(elemTable))[i];
	}
	elemTable->clear();
}

void NewDetectorConstruction::DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth)
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

void NewDetectorConstruction::SetEfield(G4LogicalVolume* glogical, G4FieldManager* fieldMgr, G4MagIntegratorStepper* pStepper, G4EqMagElectricField* pEquation, G4MagInt_Driver* pIntgrDriver, G4ChordFinder* pChordFinder, G4ThreeVector fdirection, G4double field)
{
	// Local Electric Field
//	static G4bool fieldIsInitialized = false;

//	if(!fieldIsInitialized)
//	{
		pEquation = new G4EqMagElectricField(electricField);
		pStepper = new G4ClassicalRK4(pEquation, 8);
		pIntgrDriver = new G4MagInt_Driver(0.1*um,pStepper,pStepper->GetNumberOfVariables());
		pChordFinder = new G4ChordFinder(pIntgrDriver);
		electricField->SetFieldValue(G4ThreeVector(field*kilovolt/cm*fdirection.x()/fdirection.r(),field*kilovolt/cm*fdirection.y()/fdirection.r(),field*kilovolt/cm*fdirection.z()/fdirection.r()));
		G4cout<<field*kilovolt/cm*fdirection.x()/fdirection.r()<<","<<field*kilovolt/cm*fdirection.y()/fdirection.r()<<","<<field*kilovolt/cm*fdirection.z()/fdirection.r()<<","<<fdirection<<G4endl;
		//electricField->SetFieldValue(G4ThreeVector(0.,1000*kilovolt/cm,0.));
		pEquation->SetFieldObj(electricField);
		pStepper->SetEquationOfMotion(pEquation);
		fieldMgr->SetDetectorField(electricField);

		pIntgrDriver->RenewStepperAndAdjust(pStepper);
		pChordFinder->SetIntegrationDriver(pIntgrDriver);
		fieldMgr->SetChordFinder(pChordFinder);
		fieldMgr->SetFieldChangesEnergy(true);

//		glogical->SetFieldManager(fieldMgr,true);

		G4cout<<fieldMgr->GetMaximumEpsilonStep()<<G4endl;
	
//		fieldIsInitialized = true;
//	}

	
}

void NewDetectorConstruction::SetGEMfield(G4LogicalVolume* glogical, G4FieldManager* fieldMgr, G4MagIntegratorStepper* pStepper, G4EqMagElectricField* pEquation, G4MagInt_Driver* pIntgrDriver, G4ChordFinder* pChordFinder)
{
	// Local Electric Field
//	static G4bool fieldIsInitialized = false;

//	if(!fieldIsInitialized)
//	{
//		electricField->SetFieldValue(G4ThreeVector(0,0,500*kilovolt/cm));
		pEquation = new G4EqMagElectricField(gemField);
		pStepper = new G4ClassicalRK4(pEquation, 8);
		pIntgrDriver = new G4MagInt_Driver(1*um,pStepper,pStepper->GetNumberOfVariables());
		pChordFinder = new G4ChordFinder(pIntgrDriver);
		//electricField->SetFieldValue(G4ThreeVector(0.,1000*kilovolt/cm,0.));
		pEquation->SetFieldObj(gemField);
		pStepper->SetEquationOfMotion(pEquation);
		fieldMgr->SetDetectorField(gemField);

		pIntgrDriver->RenewStepperAndAdjust(pStepper);
		pChordFinder->SetIntegrationDriver(pIntgrDriver);
		fieldMgr->SetChordFinder(pChordFinder);
		fieldMgr->SetFieldChangesEnergy(true);

		glogical->SetFieldManager(fieldMgr,true);

		G4cout<<"Max epsilon : "<<fieldMgr->GetMaximumEpsilonStep()<<G4endl;
	
//		fieldIsInitialized = true;
//	}
}
