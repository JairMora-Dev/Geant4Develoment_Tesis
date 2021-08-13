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
    inline G4double GetAbsorSizeZ()  const {return Crystal_z;}
    inline G4double GetZPartition()  const {return Npart;}
    
private:  
  G4bool  fCheckOverlaps;
    G4UserLimits* fStepLimit;
    //Added
    G4int Npart = 10000;
    
    G4double Crystal_x = 2.0*mm;
    G4double Crystal_y = 2.0*mm;
    G4double Crystal_z  = 1.27*cm;
};

//.............................................................................    



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

