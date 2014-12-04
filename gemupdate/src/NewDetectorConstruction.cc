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
#include "G4Transform3D.hh"

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
#include "CLHEP/Units/PhysicalConstants.h"

using namespace CLHEP;

NewDetectorConstruction::NewDetectorConstruction()
:fefield(-100.),fefielddirection(0.,0.,1.),geometry_on(false)
{
	messenger = new NewDetectorConstMessenger(this);
	//fieldMgr1 = new G4FieldManager();
	fieldMgr2 = 0;
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
	G4double xlength = 49.999999*um;
	G4double ylength = 49.999999*um;
	argon_thic = 59.999999*um;

	G4VSolid* worldSolid = new G4Box("worldBox",xlength,ylength,argon_thic);
	worldLogical = new G4LogicalVolume(worldSolid,argonGas,"worldLogical",0,0,0);
	G4VPhysicalVolume* worldPhysical = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"worldPhysical",0,0,0);

	if(geometry_on){
	// GEM Mother volume
	G4VSolid* GEMSolid = new G4Box("GEMBox",xlength,ylength,argon_thic);

	// GEM Drifit volume
	G4double Drift_thic = 500*um;
	G4VSolid* Drift1_Solid = new G4Box("Drift1_solid",xlength,ylength,Drift_thic);
	G4VSolid* Drift2_Solid = new G4Box("Drift2_solid",xlength,ylength,Drift_thic);
//	G4VSolid* Drift1_Solid = new G4Box("Drift1_solid",4050*um,2500*um,2000*um);
//	G4VSolid* Drift2_Solid = new G4Box("Drift2_solid",4050*um,2500*um,1000*um);
	Drift1_logical = new G4LogicalVolume(Drift1_Solid,argonGas,"Drift1_logical",0,0,0);
	Drift2_logical = new G4LogicalVolume(Drift2_Solid,argonGas,"Drift2_logical",0,0,0);
//	G4VPhysicalVolume* Drift1_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,-2060*um),Drift1_logical,"Drift1_physical",worldLogical,0,0);
//	G4VPhysicalVolume* Drift2_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,1060*um),Drift2_logical,"Drift2_physical",worldLogical,0,0);
	//G4VPhysicalVolume* Drift1_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,-45*um),Drift1_logical,"Drift1_physical",worldLogical,0,0);
	//G4VPhysicalVolume* Drift2_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,45*um),Drift2_logical,"Drift2_physical",worldLogical,0,0);

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

	G4double outdia = 34.999999*um;
	G4double outdia_offset = 4.999999*um;
	G4double middia = 14.999999*um;
	G4double kapton_thic = 12.499999*um;
	G4double copper_thic = 2.499999*um;
	G4double kapton_offset = 9.374999*um;
	G4double hole_offset = (kapton_offset + kapton_thic)/7;

	//make copper layer divided 2 parts
	copper_box = new G4Box("copper_box",xlength,ylength/2,copper_thic);
	copper_hole = new G4Tubs("copper_hole",0*um,outdia,copper_thic*2,0,360*deg);
	copper_solid = new G4SubtractionSolid("copper_solid",copper_box,copper_hole,0,G4ThreeVector(0,ylength/2-0.1*um, 0*um));
	copper_logical = new G4LogicalVolume(copper_solid,copper,"copper_logical",0,0,0);
	G4LogicalVolume* copper2_logical = new G4LogicalVolume(copper_solid,copper,"copper2_logical",0,0,0);
	copper1_physical = new G4PVPlacement(0,G4ThreeVector(0,-ylength/2,-(kapton_thic*2+copper_thic)),copper_logical,"copper1_physical",worldLogical,false,0);
	copper2_physical = new G4PVPlacement(G4Transform3D(G4RotationMatrix(0,0,M_PI*rad),G4ThreeVector(0,ylength/2,-(kapton_thic*2+copper_thic))),copper2_logical,"copper2_physical",worldLogical,false,0);
	G4LogicalVolume* copper_graphic = new G4LogicalVolume(copper_solid,copper,"copper_graphic",0,0,0);
	G4LogicalVolume* copper2_graphic = new G4LogicalVolume(copper_solid,copper,"copper_graphic",0,0,0);
	G4VPhysicalVolume* coppergr1_physical = new G4PVPlacement(0,G4ThreeVector(0,-ylength/2,(kapton_thic*2+copper_thic)),copper_graphic,"coppergr_physical",worldLogical,false,0);
	G4VPhysicalVolume* coppergr2_physical = new G4PVPlacement(G4Transform3D(G4RotationMatrix(0,0,M_PI*rad),G4ThreeVector(0,ylength/2,(kapton_thic*2+copper_thic))),copper2_graphic,"coppergr2_physical",worldLogical,false,0);

	//make kapton foil divided 4 parts
	kapton_box = new G4Box("kapton_box",xlength,ylength/2,kapton_thic);
	kapton_hole1 = new G4Cons("kapton_hole1",0*um,outdia+outdia_offset,0*um,0,kapton_thic+kapton_offset+hole_offset,0,360*deg);
	kapton_solid = new G4SubtractionSolid("kapton_hole",kapton_box,kapton_hole1,0,G4ThreeVector(0*um,ylength/2-0.1*um,-(hole_offset-kapton_offset)));
	kapton_logical = new G4LogicalVolume(kapton_solid,Kapton,"kapton_logical",0,0,0);
	kapton_physical = new G4PVPlacement(0,G4ThreeVector(0,-ylength/2,-kapton_thic),kapton_logical,"kapton_physical",worldLogical,false,0);
	G4LogicalVolume* kapton_graphic = new G4LogicalVolume(kapton_solid,Kapton,"kapton_logical",0,0,0);
	G4VPhysicalVolume* kaptongr_physical = new G4PVPlacement(G4Transform3D(G4RotationMatrix(0,0,M_PI*rad),G4ThreeVector(0,ylength/2,-kapton_thic)),kapton_graphic,"kaptongr_physical",worldLogical,false,0);
	G4VPhysicalVolume* kapton2_physical = new G4PVPlacement(G4Transform3D(G4RotationMatrix(0,M_PI*rad,0),G4ThreeVector(0,ylength/2,kapton_thic)),kapton_graphic,"kaptongr_physical",worldLogical,false,0);
	G4VPhysicalVolume* kaptongr2_physical = new G4PVPlacement(G4Transform3D(G4RotationMatrix(0,M_PI*rad,M_PI*rad),G4ThreeVector(0,-ylength/2,kapton_thic)),kapton_graphic,"kaptongr_physical",worldLogical,false,0);

	//tetrahedral geometry test
	//G4VSolid* kaptontet;
	//Readvector("../kaptonvol.node");
	//Readposition("../kaptonvol.ele",kaptontet,worldLogical,Kapton,G4ThreeVector(0,0,0));
	//kapton_logical = new G4LogicalVolume(kaptontet,Kapton,"kapton_logical",0,0,0);
	//kapton_physical = new G4PVPlacement(0,G4ThreeVector(0,0,0),kapton_logical,"kapton_physical",worldLogical,false,0);

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

	//visual
	worldVisAtt = new G4VisAttributes(G4Colour(0.0,0.0,0.0));
	worldVisAtt->SetVisibility(true);
	worldLogical->SetVisAttributes(worldVisAtt);
	argonVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,0.0));
	copperVisAtt = new G4VisAttributes(G4Colour(0.0,1.0,1.0));
	kapton_logical->SetVisAttributes(argonVisAtt);
	copper_logical->SetVisAttributes(copperVisAtt);
	copper2_logical->SetVisAttributes(copperVisAtt);
	kapton_graphic->SetVisAttributes(argonVisAtt);
	copper_graphic->SetVisAttributes(copperVisAtt);
	copper2_graphic->SetVisAttributes(copperVisAtt);
	Drift1_logical->SetVisAttributes(argonVisAtt);
	Drift2_logical->SetVisAttributes(argonVisAtt);
}

	// Hodoscope declaration
	G4VSolid* hit_solid;
	G4VSolid* hit_solid2;
	G4LogicalVolume* hit_counter1;
	G4VPhysicalVolume* hc_physical1;
	G4LogicalVolume* hit_counter2;
	G4VPhysicalVolume* hc_physical2;

	G4LogicalVolume* dc_logical1;
	G4VPhysicalVolume* dc_physical1;
	G4LogicalVolume* dc_logical2;
	G4VPhysicalVolume* dc_physical2;

	hit_solid = new G4Box("hit_counter",xlength,ylength,1*um);
//	hit_solid = new G4Box("hit_counter",4050*um,2500*um,0.1*um);
	hit_counter1 = new G4LogicalVolume(hit_solid,argonGas,"hit_counter1",0,0,0);
	//hc_physical1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,-30.1*um),hit_counter1,"dc1_physical",worldLogical,false,0);
//	hc_physical1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,-999.7*um),hit_counter1,"dc1_physical",Drift1_logical,false,0);
	hit_counter2 = new G4LogicalVolume(hit_solid,argonGas,"hit_counter2",0,0,0);
	//hc_physical2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,30.1*um),hit_counter2,"dc2_physical",worldLogical,false,0);
//	hc_physical2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,499.9*um),hit_counter2,"dc2_physical",Drift2_logical,false,0);

	hit_solid2 = new G4Box("hit_counter",xlength,ylength,2.5*um);
	dc_logical1 = new G4LogicalVolume(hit_solid,argonGas,"dc1",0,0,0);
	//dc_physical1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,-30.3*um),dc_logical1,"dc1_physical",worldLogical,false,0);
//	dc_physical1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,-999.5*um),dc_logical1,"dc1_physical",Drift1_logical,false,0);
	dc_logical2 = new G4LogicalVolume(hit_solid,argonGas,"dc2",0,0,0);
	//dc_physical2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,52.5*um),dc_logical2,"dc2_physical",worldLogical,false,0);
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
	dc_logical2->SetSensitiveDetector(hodoscope3);

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

	// Make an Electric Field by hardcording
	//SetGEMfield(worldLogical, fieldMgr2, pStepper2, pEquation2, pIntgrDriver2, pChordFinder2);
	//SetEfield(Drift2_logical, fieldMgr2, pStepper3, pEquation3, pIntgrDriver3, pChordFinder3, G4ThreeVector(0,0,1), -1000);
	//SetEfield(hit_counter2, fieldMgr3, G4ThreeVector(0,0,-1), 3000*fefield*6/400);
	//SetEfield(dc_logical2, fieldMgr3, G4ThreeVector(0,0,-1), 3000*fefield*6/400);
	//SetEfield(Drift1_logical, fieldMgr2, pStepper1, pEquation1, pIntgrDriver1, pChordFinder1, G4ThreeVector(0,0,1), 4);
	//SetEfield(hit_counter1, fieldMgr1, G4ThreeVector(0,0,-1), 1000);
	//SetEfield(dc_logical1, fieldMgr1, G4ThreeVector(0,0,-1), 1000);
	//if(worldLogical->GetFieldManager()->DoesFieldChangeEnergy())G4cout<<"dc 1 has a field"<<G4endl;
	//if(copper_graphic->GetFieldManager()->DoesFieldChangeEnergy())G4cout<<"dc 2 has a field"<<G4endl;


	// visualization attributes
	hit_counter1->SetVisAttributes(argonVisAtt);
	hit_counter2->SetVisAttributes(argonVisAtt);
	dc_logical1->SetVisAttributes(argonVisAtt);
	dc_logical2->SetVisAttributes(argonVisAtt);

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
	pressure =1*atmosphere;
//	temperature = 273*kelvin;
	temperature = 300*kelvin;

	//argonGas = new G4Material(name="ArgonGas", z=18., a, density, kStateGas, temperature, pressure);
	argonGas = man->FindOrBuildMaterial("G4_Ar");

	// vacuum
	density = universe_mean_density; // from PhysicalConstants.h
	pressure    = 1.e-19*pascal;
	temperature = 0.1*kelvin;

	galactic = new G4Material(name="Galactic",z=1.,a=1.01*g/mole,density,kStateGas,temperature,pressure);

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

//make unifor electric field
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

//read polygon data. you can make node and ele file from .ply by tetgen
void NewDetectorConstruction::Readvector(G4String filename)
{
	std::ifstream infile;
	infile.open(filename);
	if(!infile)G4cout << ".node file not found!!!!" << G4endl;

	G4String str="";
	G4int numv = 0;
	G4int temp1, temp2, temp3;
	G4double x, y, z;

	getline(infile, str);
	G4cout << str.c_str() << G4endl;
	sscanf(str.c_str(),"%d	%d	%d	%d", &numv, &temp1, &temp2, &temp3);

	tetVector = new G4ThreeVector[numv];

	for(G4int i=0;i<numv;i++){
		G4int j;
		getline(infile, str);
		sscanf(str.c_str(),"%d	%lf	%lf	%lf", &j, &x, &y, &z);
		tetVector[i]=G4ThreeVector(x*um,y*um,z*um);
		if(i!=j)G4cout << "Something is wrong during reading vector sequence!" << G4endl;
	}
	infile.close();
}

void NewDetectorConstruction::Readposition(G4String filename, G4VSolid* sumtet, G4LogicalVolume* placedlog, G4Material* material, G4ThreeVector physplace)
{
	std::ifstream infile;
	infile.open(filename);
	if(!infile)G4cout << ".ele file not found!!!!" << G4endl;

	G4String str="";
	G4String tetname="";
	char num[5];
	G4int numtet=0;
	G4int temp1, temp2, temp3;
	G4int anchor, p1, p2, p3;

	getline(infile, str);
	G4cout << str.c_str() << G4endl;
	sscanf(str.c_str(),"%d	%d	%d	%d", &numtet, &temp1, &temp2, &temp3);

	G4RotationMatrix * element_rotation = new G4RotationMatrix();
	G4ThreeVector element_position = G4ThreeVector();

	for(G4int i=0;i<numtet;i++){
		G4int j;
		getline(infile, str);
		sscanf(str.c_str(),"%d	%d	%d	%d	%d",&j,&anchor,&p1,&p2,&p3);
		sprintf(num,"%d",i);
		tetname = filename + num;
	//	G4cout << tetname << G4endl;
	//	if(G4Tet(tetname.c_str(),tetVector[anchor],tetVector[p1],tetVector[p2],tetVector[p3],0).CheckDegeneracy(tetVector[anchor],tetVector[p1],tetVector[p2],tetVector[p3])){
	//	G4cout<<filename<<G4endl;
		//G4cout<<"i:"<<i<<", tetVector :"<<tetVector[anchor]<<","<<tetVector[p1]<<","<<tetVector[p2]<<","<<tetVector[p3]<<G4endl;
		
		if(i==0){
			origintet = new G4Tet(filename + G4String("_tet"),tetVector[anchor],tetVector[p1],tetVector[p2],tetVector[p3],0);
			sumtet = origintet;
		}
		else if(i==1){
			polytet = new G4Tet(filename + G4String("_tet"),tetVector[anchor],tetVector[p1],tetVector[p2],tetVector[p3],0);
			temp1tet = new G4UnionSolid(filename + G4String("_sum"),origintet,polytet,0,G4ThreeVector(0,0,0));
			sumtet = temp1tet;
		}			
		else if(i%2==0){
			polytet = new G4Tet(filename + G4String("_tet"),tetVector[anchor],tetVector[p1],tetVector[p2],tetVector[p3],0);
			temp2tet = new G4UnionSolid(filename + G4String("_sum"),temp1tet,polytet,0,G4ThreeVector(0,0,0));
			sumtet = temp2tet;
		}			
		else if(i%2==1){
			polytet = new G4Tet(filename + G4String("_tet"),tetVector[anchor],tetVector[p1],tetVector[p2],tetVector[p3],0);
			temp1tet = new G4UnionSolid(filename + G4String("_sum"),temp2tet,polytet,0,G4ThreeVector(0,0,0));
			sumtet = temp1tet;
		}
		else G4cout<<"i:"<<i<<", tetVector :"<<tetVector[anchor]<<","<<tetVector[p1]<<","<<tetVector[p2]<<","<<tetVector[p3]<<G4endl;
			

        	//assembly->AddPlacedVolume(tetLog, element_position, element_rotation);
	//	}
		if(i!=j)G4cout << "Something is wrong during reading position sequence!" << G4endl;
	}
//	tetLog = new G4LogicalVolume(sumtet, material, tetname + G4String("_logical"), 0, 0, 0);
//	tetPhy = new G4PVPlacement(0,physplace,tetLog,filename + G4String("_physical"),placedlog,false,i);
//	tetLog->SetVisAttributes(copperVisAtt);
	infile.close();
}

#include "G4RunManager.hh"

//update geometry
void NewDetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}
