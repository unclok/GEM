#include "BeamDetectorConstruction.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4UniformElectricField.hh"

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

#include "G4MultiFunctionalDetector.hh"
#include "G4PSFlatSurfaceCurrent.hh"
#include "G4PSPassageCellCurrent.hh"
#include "G4PSNofSecondary.hh"
#include "BeamEnergyDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4VSDFilter.hh"
#include "G4SDParticleFilter.hh"

#include "G4VSensitiveDetector.hh"
#include "A01DriftChamber.hh"

BeamDetectorConstruction::BeamDetectorConstruction()
{
	fieldMgr = new G4FieldManager();
}

BeamDetectorConstruction::~BeamDetectorConstruction()
{
	DestroyMaterials();

	delete worldVisAtt;
	delete argonVisAtt;
}

G4VPhysicalVolume* BeamDetectorConstruction::Construct()
{
	ConstructMaterials();

	// Make an Electric Field
	// Local Electric Field
	static G4bool fieldIsInitialized = false;

	if(!fieldIsInitialized)
	{
		electricField = new G4UniformElectricField(G4ThreeVector(0., 100*kilovolt/cm, 0.));
		pEquation = new G4EqMagElectricField(electricField);
		pStepper = new G4ClassicalRK4(pEquation, 8);
		fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
//		fieldMgr->SetDetectorField(electricField);

		G4double minEps = 1.*um;

		pIntgrDriver = new G4MagInt_Driver(minEps,pStepper,pStepper->GetNumberOfVariables());
		pChordFinder = new G4ChordFinder(pIntgrDriver);
		fieldMgr->SetChordFinder(pChordFinder);

		fieldIsInitialized = true;
	}

	// geometries
	// experimental hall (world volume)

	G4VSolid* worldSolid = new G4Box("worldBox",3.*m,3.*m,3.*m);
	G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid,air,"worldLogical",0,0,0);
	G4VPhysicalVolume* worldPhysical = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"worldPhysical",0,0,0);

	// scat Mother volume
	G4VSolid* scatSolid = new G4Tubs("scattub",0.*cm,5.*cm,0.1*cm,0.,360*deg);
	G4LogicalVolume* scatLogical = new G4LogicalVolume(scatSolid,au,"GEMLogical",0,0,0);

	new G4PVPlacement(0,G4ThreeVector(0.,0.,0.*um),scatLogical,"GEMPhysical",worldLogical,0,0);

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

	hit_solid = new G4Tubs("hit_counter",0.*cm,1.*m,0.1*cm,0.,360*deg);
	hit_counter1 = new G4LogicalVolume(hit_solid,air,"hit_counter1",0,0,0);
	hc_physical1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,10.1*cm),hit_counter1,"hit_counter1_physical",worldLogical,false,0);
	hit_counter2 = new G4LogicalVolume(hit_solid,air,"hit_counter2",0,0,0);
	hc_physical2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,50.1*cm),hit_counter2,"hit_counter2_physical",worldLogical,false,0);
	driftchamber1 = new G4LogicalVolume(hit_solid,air,"driftchamber1",0,0,0);
	dc_physical1 = new G4PVPlacement(0,G4ThreeVector(0.,0.,10.3*cm),driftchamber1,"driftchamber1_physical",worldLogical,false,0);
	driftchamber2 = new G4LogicalVolume(hit_solid,air,"driftchamber2",0,0,0);
	dc_physical2 = new G4PVPlacement(0,G4ThreeVector(0.,0.,50.3*cm),driftchamber2,"driftchamber1_physical",worldLogical,false,0);


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
	scatLogical->SetSensitiveDetector(hodoscope3);

	drift1 = new A01DriftChamber(SDname="/drift1");
	SDman->AddNewDetector(drift1);
	driftchamber1->SetSensitiveDetector(drift1);
	drift2 = new A01DriftChamber(SDname="/drift2");
	SDman->AddNewDetector(drift2);
	driftchamber2->SetSensitiveDetector(drift2);

	G4PSFlatSurfaceCurrent* totalSurfCurrent1 = new G4PSFlatSurfaceCurrent("TotalSurfCurrent1",1);
	totalSurfCurrent1->Weighted(false);
	totalSurfCurrent1->DivideByArea(false);
	hodoscope1->RegisterPrimitive(totalSurfCurrent1);
	G4PSFlatSurfaceCurrent* electronSurfCurrent1 = new G4PSFlatSurfaceCurrent("ElectronSurfCurrent1",1);
	electronSurfCurrent1->Weighted(false);
	electronSurfCurrent1->DivideByArea(false);
	hodoscope1->RegisterPrimitive(electronSurfCurrent1);
	BeamEnergyDetector* energyscorer1 = new BeamEnergyDetector("Energy1");
	hodoscope1->RegisterPrimitive(energyscorer1);

	G4PSFlatSurfaceCurrent* totalSurfCurrent2 = new G4PSFlatSurfaceCurrent("TotalSurfCurrent2",1);
	totalSurfCurrent2->Weighted(false);
	totalSurfCurrent2->DivideByArea(false);
	hodoscope2->RegisterPrimitive(totalSurfCurrent2);
	G4PSFlatSurfaceCurrent* electronSurfCurrent2 = new G4PSFlatSurfaceCurrent("ElectronSurfCurrent2",1);
	electronSurfCurrent2->Weighted(false);
	electronSurfCurrent2->DivideByArea(false);
	hodoscope2->RegisterPrimitive(electronSurfCurrent2);
	G4VPrimitiveScorer* energyscorer2 = new BeamEnergyDetector("Energy2");
	hodoscope2->RegisterPrimitive(energyscorer2);

	G4PSPassageCellCurrent* scorerCurrent = new G4PSPassageCellCurrent("Current");
	hodoscope3->RegisterPrimitive(scorerCurrent);
	G4PSNofSecondary* secondaryscorerCurrent = new G4PSNofSecondary("SecondaryCurrent");
	hodoscope3->RegisterPrimitive(secondaryscorerCurrent);


	// visualization attributes
	worldVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
	worldVisAtt->SetVisibility(true);
	worldLogical->SetVisAttributes(worldVisAtt);
	argonVisAtt = new G4VisAttributes(G4Colour(2.0,1.0,3.0));
	scatLogical->SetVisAttributes(argonVisAtt);

	// return the world physical volume
	G4cout << G4endl << "The geometrical tree defined are : " << G4endl << G4endl;
	DumpGeometricalTree(worldPhysical);

	return worldPhysical;
}

void BeamDetectorConstruction::ConstructMaterials()
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

	// Fe
	a = 55.845*g/mole;
	density = 7.86*g/cm3;
	fe = new G4Material(name="Fe", z=26., a, density);

	// gold
	a = 196.967*g/mole;
	density = 19.3*g/cm3;
	au = new G4Material(name="Gold", z=79., a, density);
}

void BeamDetectorConstruction::DestroyMaterials()
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

void BeamDetectorConstruction::DumpGeometricalTree(G4VPhysicalVolume* aVolume,G4int depth)
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

