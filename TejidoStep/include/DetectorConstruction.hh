#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1


#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

//Step size
#include "G4UserLimits.hh"
#include "G4SystemOfUnits.hh"


class G4VPhysicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
  /// constructor
  DetectorConstruction();
  /// destructor
  virtual ~DetectorConstruction();
  
public:
  /// Defines detector geom. and returns a pointer to the physical World Volume
  virtual G4VPhysicalVolume* Construct();
   //y Libreria incluida para el gobal de SensitiveDetector
   virtual void ConstructSDandField();
    inline G4double GetAbsorSizeZ()  const {return cz;}
    inline G4double GetZPartition()  const {return Npart;}
    
private:  
    G4bool  fCheckOverlaps;
    G4UserLimits* fStepLimit;
    //Added
    G4int Npart = 10000;
    
  G4double ax= 3.*cm;
  G4double by= 1.*cm;
  G4double cz= 15.*cm;
  G4double zcut1= -15.0*cm; 
  G4double zcut2= 0.0*cm;
};

//.............................................................................    



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

