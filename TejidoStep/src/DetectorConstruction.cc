//Construcción del target, detector

#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

//...........Librerias añadidas para Pancreas................
#include "G4Ellipsoid.hh"
#include "G4RotationMatrix.hh"


//........................................................................

//SensitiveDetector.......................................................
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSFlatSurfaceCurrent.hh"
#include "G4SDParticleFilter.hh"
#include "G4PSTrackLength.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4PSNofSecondary.hh"
//........................................................................
#include "G4SubtractionSolid.hh"

//Step size
#include "G4UserLimits.hh"

//......................De-exitation.....................................
#include "G4EmParameters.hh"
#include "G4EmLowEParameters.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
  : G4VUserDetectorConstruction(),
    fCheckOverlaps(true)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{delete fStepLimit; }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Llamado a la base de datos del NIST
  //G4NistManager* man = G4NistManager::Instance();

  //Definición del "vacío"
  G4double presion, temperatura, densidad;
  densidad     = universe_mean_density;    //from PhysicalConstants.h
  presion    = 3.e-18*pascal;
  temperatura = 2.73*kelvin;
  G4Material* Vacuum   = new G4Material("Vacuum",
                                        1., 1.01*g/mole, densidad,
                                        kStateGas,temperatura,presion);

  


  // World ()
  //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
  G4double world_sizeXY = 10*cm;
  G4double world_sizeZ  = 50*cm;
  
  //Solid volume
  G4Box* solidWorld = new G4Box("SolWorld",
				0.5*world_sizeXY,
				0.5*world_sizeXY,
				0.5*world_sizeZ); //its size
  
  //Logical volume
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        Vacuum,         //its material
                        "LogWorld");            //its name
  
  //Physical volume
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "PhysWorld",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      fCheckOverlaps);       // checking overlaps
    
    
  //........................................CONSTRUCCION PANCREAS................................................
  
 
  G4double A;  // atomic mass
  G4double Z;  // atomic number
  G4double d;  // density

  A = 1.01*g/mole;
  G4Element* elH = new G4Element ("Hydrogen","H",Z = 1.,A);

  A = 12.011*g/mole;
  G4Element* elC = new G4Element("Carbon","C",Z = 6.,A);  

  A = 14.01*g/mole;
  G4Element* elN = new G4Element("Nitrogen","N",Z = 7.,A);

  A = 16.00*g/mole;
  G4Element* elO = new G4Element("Oxygen","O",Z = 8.,A);

  A = 22.99*g/mole;
  G4Element* elNa = new G4Element("Sodium","Na",Z = 11.,A);

  A = 24.305*g/mole;
  G4Element* elMg = new G4Element("Magnesium","Mg",Z = 12.,A);

  A = 30.974*g/mole;
  G4Element* elP = new G4Element("Phosphorus","P",Z = 15.,A);
 
  A = 32.064*g/mole;
  G4Element* elS = new G4Element("Sulfur","S",Z = 16.,A);
 
  A = 35.453*g/mole;
  G4Element* elCl = new G4Element("Chlorine","Cl",Z = 17.,A);
 
  A = 39.098*g/mole;
  G4Element* elK = new G4Element("Potassium","K",Z = 19.,A);

  A = 55.85*g/mole;
  G4Element* elFe  = new G4Element("Iron","Fe",Z = 26.,A);
 
  A = 65.38*g/mole;
  G4Element* elZn = new G4Element("Zinc","Zn",Z = 30.,A);

  A = 85.47 *g/mole;
  G4Element* elRb = new G4Element("Rb","Rb",Z = 37.,A);

  A = 87.62 *g/mole;
  G4Element* elSr = new G4Element("Sr","Sr",Z = 38.,A);

  A = 91.22 *g/mole;
  G4Element* elZr = new G4Element("Zr","Zr",Z = 40.,A);

  A = 207.19 *g/mole;
  G4Element* elPb = new G4Element("Lead","Pb", Z = 82.,A);

  d= 0.9869 *g/cm3;
  G4Material* soft = new G4Material("soft_tissue", d, 16);
  soft->AddElement(elH,0.1047);
  soft->AddElement(elC,0.2302);
  soft->AddElement(elN,0.0234);
  soft->AddElement(elO,0.6321);
  soft->AddElement(elNa,0.0013);
  soft->AddElement(elMg,0.00015);
  soft->AddElement(elP,0.0024);
  soft->AddElement(elS,0.0022);
  soft->AddElement(elCl,0.0014);
  soft->AddElement(elK,0.0021);
  soft->AddElement(elFe,0.000063);
  soft->AddElement(elZn,0.000032);
  soft->AddElement(elRb,0.0000057);
  soft->AddElement(elSr,0.00000034);
  soft->AddElement(elZr,0.000008);
  soft->AddElement(elPb,0.00000016);
  
  G4Ellipsoid* pancreas =  new G4Ellipsoid("Pancreas1",
			       ax,
			       by,
			       cz,
			       zcut1,
			       zcut2);

  G4LogicalVolume* logicPancreas = new G4LogicalVolume(pancreas, soft,
						       "logicalP",
						       0, 0, 0);


  G4RotationMatrix* rm = new G4RotationMatrix();
  rm->rotateY(180.*degree);
   new G4PVPlacement(rm,
		     G4ThreeVector(0*cm, 0*cm, 0*cm),//x0, 0, 2 cm
		     logicPancreas,
		     "physicalPancreas",
		     logicWorld,
		     false,
		     0);
  
  
     //imprima Material

    G4cout << *(G4Material::GetMaterialTable()) << G4endl;


    //......................PLACA CONTADORA DE FLUJO DE PARTICULAS INCIDENTES..........................
    //Volumen solido placa contadora
    G4Box* Placa = new G4Box ("PlacaCont",
                              3.0*mm,
                              3.0*mm,
                              0.001*mm);
    
    //Volumen logico Placa
    G4LogicalVolume* LogPlaca =
        new G4LogicalVolume(Placa,
                            Vacuum,
                            "Placa_Logic");
    
    //Volumen fisico Placa
        new G4PVPlacement(0,
                          G4ThreeVector(0.0, 0.0, -2.10*cm),
                          LogPlaca,
                          "Phys_Placa",
                          logicWorld,
                          false,
                          0);


    
  return physWorld; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{

  //...................................SDetectores cristal.........................................
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  //auto absDetector = new G4MultiFunctionalDetector("CDetector");
  G4MultiFunctionalDetector* PancreasDetector = new G4MultiFunctionalDetector("PDetector");
  G4SDManager::GetSDMpointer()->AddNewDetector(PancreasDetector);
    
  //..........Contador(EnergiaDepositada)...................
  G4PSEnergyDeposit* scorer = new G4PSEnergyDeposit("EneDep");
  PancreasDetector->RegisterPrimitive(scorer);

  //Hacer Sencible el Detector
  SetSensitiveDetector( "logicalP",PancreasDetector);
    
  //..................................SDetectores Placa............................................
    G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
    G4MultiFunctionalDetector* PlacaDetector = new G4MultiFunctionalDetector("SD_Placa");
    G4SDManager::GetSDMpointer()->AddNewDetector(PlacaDetector);
    //............Contador Flujo en la placa...............
    G4PSFlatSurfaceCurrent* PlacaScorer = new G4PSFlatSurfaceCurrent("Flux", fCurrent_In);
    PlacaScorer->DivideByArea(false);
    PlacaDetector->RegisterPrimitive(PlacaScorer);
    
    //............HacerSencible el Placadetector
    SetSensitiveDetector("Placa_Logic", PlacaDetector);

  }









  
