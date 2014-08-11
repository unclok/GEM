#include "NewDetectorConstruction.hh"
#include "NewDetectorConstMessenger.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "NewElectricField.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh" 
#include "G4UnionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SDManager.hh"
#include "G4RunManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"

#include "G4PVReplica.hh"
#include "G4Transform3D.hh"

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
:fefield(100.),fefielddirection(0.,0.,1.)
{
	messenger = new NewDetectorConstMessenger(this);
	fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
	electricField = new NewElectricField(G4ThreeVector(fefield*kilovolt/cm*fefielddirection.x()/fefielddirection.r(),fefield*kilovolt/cm*fefielddirection.y()/fefielddirection.r(),fefield*kilovolt/cm*fefielddirection.z()/fefielddirection.r()));
	pEquation = new G4EqMagElectricField(electricField);
	pStepper = new G4ClassicalRK4(pEquation, 8);
	pIntgrDriver = new G4MagInt_Driver(1.*um,pStepper,pStepper->GetNumberOfVariables());
	pChordFinder = new G4ChordFinder(pIntgrDriver);
}

NewDetectorConstruction::~NewDetectorConstruction()
{
	DestroyMaterials();

//	delete pEquation; 
//	delete pStepper;
//	delete pIntgrDriver;
//	delete pChordFinder;
	delete messenger;
	delete worldVisAtt;
	delete argonVisAtt;
}

G4VPhysicalVolume* NewDetectorConstruction::Construct()
{
	ConstructMaterials();

	// geometries
	// experimental hall (world volume)

	G4VSolid* worldSolid = new G4Box("worldBox",50.*cm,50.*cm,50.*cm);
	G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid,galactic,"worldLogical",0,0,0);
	G4VPhysicalVolume* worldPhysical = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"worldPhysical",0,0,0);

	// GEM Mother volume
	G4VSolid* GEMSolid = new G4Box("GEMBox",5.*cm,5.*cm,5.*cm);
	G4LogicalVolume* GEMLogical = new G4LogicalVolume(GEMSolid,galactic,"GEMLogical",0,0,0);

	new G4PVPlacement(0,G4ThreeVector(0.,0.,0.*um),GEMLogical,"GEMPhysical",worldLogical,0,0);

	// Hodoscope declaration
	G4VSolid* hit_solid;
	G4LogicalVolume* hit_counter1;
	G4VPhysicalVolume* hc_physical1;
	G4LogicalVolume* hit_counter2;
	G4VPhysicalVolume* hc_physical2;
	G4LogicalVolume* driftchamber1;
	G4VPhysicalVolume* dc_physical1;
	G4LogicalVolume* driftchamber2;
	G4VPhysicalVolume* dc_physical2;
	G4LogicalVolume* slice;
	G4VPhysicalVolume* slice_physical;

	// Box
	G4VSolid* argon_solid;
	G4VPhysicalVolume* argon_physical;

	argon_solid = new G4Box("argon_solid",5.*cm,5.*cm,5.*cm);
	//argon_logical = new G4LogicalVolume(argon_solid,argonGas,"argon_logical",fieldMgr,0,0);
	argon_logical = new G4LogicalVolume(argon_solid,argonGas,"argon_logical",0,0,0);
	argon_physical = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.*um),argon_logical,"argon_physical",GEMLogical,false,0);

	hit_solid = new G4Box("hit_counter",5.*cm,5.*cm,0.1*cm);
	hit_counter1 = new G4LogicalVolume(hit_solid,argonGas,"hit_counter1",0,0,0);
	hc_physical1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,-4.9*cm),hit_counter1,"hit_counter1_physical",argon_logical,false,0);
	hit_counter2 = new G4LogicalVolume(hit_solid,argonGas,"hit_counter2",0,0,0);
	hc_physical2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,4.9*cm),hit_counter2,"hit_counter2_physical",argon_logical,false,0);

	driftchamber1 = new G4LogicalVolume(hit_solid,argonGas,"driftchamber1",0,0,0);
	dc_physical1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,-4.7*cm),driftchamber1,"driftchamber1_physical",argon_logical,false,0);
	driftchamber2 = new G4LogicalVolume(hit_solid,argonGas,"driftchamber2",0,0,0);
	dc_physical2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,4.7*cm),driftchamber2,"driftchamber1_physical",argon_logical,false,0);

	slice = new G4LogicalVolume(hit_solid,argonGas,"driftchamber2",0,0,0);
	slice_physical = new G4PVPlacement(G4Transform3D(G4RotationMatrix(-M_PI/2.*rad,M_PI/2.*rad,M_PI/2.*rad),G4ThreeVector(0.,0.,0.*cm)),slice,"driftchamber1_physical",argon_logical,false,0);

	// multifunctional detectors
	G4MultiFunctionalDetector* hodoscope1;
	G4MultiFunctionalDetector* hodoscope2;
	G4MultiFunctionalDetector* hodoscope3;

	G4VSensitiveDetector* drift1;
	G4VSensitiveDetector* drift2;

	G4VSensitiveDetector* slicehit;
	
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
	argon_logical->SetSensitiveDetector(hodoscope3);

	drift1 = new A01DriftChamber(SDname="/drift1");
	SDman->AddNewDetector(drift1);
	driftchamber1->SetSensitiveDetector(drift1);
	drift2 = new A01DriftChamber(SDname="/drift2");
	SDman->AddNewDetector(drift2);
	driftchamber2->SetSensitiveDetector(drift2);

	slicehit = new A01DriftChamber(SDname="/slice");
	SDman->AddNewDetector(slicehit);
	slice->SetSensitiveDetector(slicehit);

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
	SetEfield(fefielddirection, fefield);


	// visualization attributes
	worldVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
	worldVisAtt->SetVisibility(true);
	worldLogical->SetVisAttributes(worldVisAtt);
	argonVisAtt = new G4VisAttributes(G4Colour(2.0,1.0,3.0));
	argon_logical->SetVisAttributes(argonVisAtt);

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
	pressure = 1*atmosphere;
	temperature = 273*kelvin;

	argonGas = new G4Material(name="ArgonGas", z=18., a, density, kStateGas, temperature, pressure);

	// vacuum
	density = universe_mean_density; // from PhysicalConstants.h
	galactic = new G4Material(name="Galactic",z=1.,a=1.01*g/mole,density);

	air = man->FindOrBuildMaterial("G4_AIR");

	G4cout << G4endl << "The materials defined are : " << G4endl << G4endl;
	G4cout << *(G4Material::GetMaterialTable()) << G4endl;

	// copper
	a = 63.546*g/mole;
	density = 8.96*g/cm3;
	copper = new G4Material(name="Copper", z=29., a, density);	
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

void NewDetectorConstruction::SetEfield(G4ThreeVector fdirection, G4double field)
{
	// Local Electric Field
//	static G4bool fieldIsInitialized = false;

//	if(!fieldIsInitialized)
//	{
		electricField->SetFieldValue(G4ThreeVector(field*kilovolt/cm*fdirection.x()/fdirection.r(),field*kilovolt/cm*fdirection.y()/fdirection.r(),field*kilovolt/cm*fdirection.z()/fdirection.r()));
		G4cout<<field*kilovolt/cm*fdirection.x()/fdirection.r()<<","<<field*kilovolt/cm*fdirection.y()/fdirection.r()<<","<<field*kilovolt/cm*fdirection.z()/fdirection.r()<<","<<fdirection<<G4endl;
		//electricField->SetFieldValue(G4ThreeVector(0.,1000*kilovolt/cm,0.));
		pEquation->SetFieldObj(electricField);
		pStepper->SetEquationOfMotion(pEquation);
		fieldMgr->SetDetectorField(electricField);

		pIntgrDriver->RenewStepperAndAdjust(pStepper);
		pChordFinder->SetIntegrationDriver(pIntgrDriver);
		fieldMgr->SetChordFinder(pChordFinder);

		argon_logical->SetFieldManager(fieldMgr,true);
	
//		fieldIsInitialized = true;
//	}

	
}
