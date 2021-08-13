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

//...........Librerias añadidas para estructura Cristalina................
#include "G4Material.hh"
#include "G4CrystalExtension.hh"
#include "G4ExtendedMaterial.hh"
#include "G4LogicalCrystalVolume.hh"
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
  G4NistManager* man = G4NistManager::Instance();

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
  G4double world_sizeZ  = 16*cm;
  
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
    
    
  //........................................CONSTRUCCION CRISTAL................................................
    
  
  //0000000000000oooooooooooo Material Cristal oooooooooooo0000000
  //Material del Cristal (NaI con impurezas de Tl)
      
    G4double z, a, fractionmass, density;
    G4String name, symbol;
    G4int ncomponents;
      
      
      G4double zI, aI;
      G4String nameI, symbolI;
      
      G4double zTl, aTl;
      G4String nameTl, symbolTl;
      
      G4String nameCris;
    
      
    ////////Compuesto sin impureza //////////////////////
      
    G4Material* NaI = man->FindOrBuildMaterial("G4_SODIUM_IODIDE");
      
      
    ////////Compuesto con impureza para la celda unitaria////////////
    
    a=22.989769*g/mole;
    G4Element* Na = new G4Element (name="sodio", symbol="Na", z=11, a);
    
    aI=126.90*g/mole;
    G4Element* I = new G4Element (nameI="Yodo", symbolI="I", zI=53, aI);
      
    aTl=204.383*g/mole;
    G4Element* Tl = new G4Element (nameTl="Talio", symbolTl="Tl", zTl=80 , aTl);

    density = 3.67*g/cm3;
    G4Material* NaI_Tl = new G4Material(name="NaI(Tl) ",density,ncomponents=3);
    NaI_Tl->AddElement(Na, fractionmass=10.0168*perCent);
    NaI_Tl->AddElement(I, fractionmass=80.49*perCent);
    NaI_Tl->AddElement(Tl, fractionmass=9.4932*perCent);
    
    /*NaI_Tl->AddElement(Na, fractionmass=13.8815*perCent);
    NaI_Tl->AddElement(I, fractionmass=76.6253*perCent);
    NaI_Tl->AddElement(Tl, fractionmass=9.4932*perCent);*/
      
    /////////Compuesto total para el cristal//////////////////////
      
   G4Material* Sci_NaI_Tl = new G4Material (nameCris="Compuesto_NaI(Tl)", density, ncomponents=2 );
      Sci_NaI_Tl->AddMaterial(NaI, fractionmass=99.99*perCent);
      Sci_NaI_Tl->AddMaterial(NaI_Tl, fractionmass=0.01*perCent);

  
   //imprima Material

    G4cout << *(G4Material::GetMaterialTable()) << G4endl;

   
            
     
  
   
  
   //imprima Material

    G4cout << *(G4Material::GetMaterialTable()) << G4endl;

    //VolumenSolidoCristal.......................................
    G4Tubs* Cristal1 = new G4Tubs ("Cristal.NaI",
                                   0.00*cm,
                                   0.635*cm,
                                   1.27*cm,
                                   0*CLHEP::pi,
                                   2*CLHEP::pi);
      
      G4Box* Cristal2 = new G4Box ("Cristal.NaI2",
                       0.2*mm,
                       0.2*mm,
                       1.27*cm);
      
      G4SubtractionSolid* CrisSubtraction =
      new G4SubtractionSolid("CristalGrande", Cristal1, Cristal2);
    
    
  
    //VolumenLogicoCristal.........................
    G4LogicalVolume* crystalLogic =
      new G4LogicalVolume(CrisSubtraction,
                                Sci_NaI_Tl,
                                 "Crystal_logic");
    
    //VolumenFisicoCristal.........................
         new G4PVPlacement(0,
                      G4ThreeVector(),
                      crystalLogic,
                      "Crystal_physical",
                      logicWorld,
                      false,
                           0);
    
    //.....................FINALIZACION CRISTAL...................................................................
    
    
    //.......................CONSTRUCCION NUCLEO DEL CRISTAL......................................................
    
    //Volumen Solido nucleo del cristal..................
    
    G4Box* NucleoCristal = new G4Box ("Cristal.NaI3",
                                      Crystal_x,
                                      Crystal_y,
                                      Crystal_z);

    
    //VolumenLogicoCristal.........................
    G4LogicalVolume* crystalLogic2 =
      new G4LogicalVolume(NucleoCristal,
                          Sci_NaI_Tl,
                                 "Crystal_logic2");
    
    //VolumenFisicoCristal.........................
         new G4PVPlacement(0,
                      G4ThreeVector(),
                      crystalLogic2,
                      "Crystal_physical2",
                      logicWorld,
                      false,
               0);
    //.......................FINALIZACION NUCLEO DEL CRISTAL......................................................
    
    
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
    
    //...................FIN DE PLACA CONTADORA DE FLUJO DE PARTICULAS INCIDENTES......................
    

 

  //retorna objeto apuntador a la clase G4VPhysicalVolume
  return physWorld; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{

  //...................................SDetectores cristal.........................................
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  //auto absDetector = new G4MultiFunctionalDetector("CDetector");
  G4MultiFunctionalDetector* CrisDetector = new G4MultiFunctionalDetector("CDetector");
  G4SDManager::GetSDMpointer()->AddNewDetector(CrisDetector);
    
  //..........Contador(EnergiaDepositada)...................
  G4PSEnergyDeposit* scorer = new G4PSEnergyDeposit("EneDep");
  CrisDetector->RegisterPrimitive(scorer);

  //Hacer Sencible el Detector
  SetSensitiveDetector("Crystal_logic",CrisDetector);
    
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









  
