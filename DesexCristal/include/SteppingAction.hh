#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include "G4Run.hh"

class EventAction;
class RunAction;

//Added
class G4LogicalVolume;
class DetectorConstruction; 


class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(EventAction*, DetectorConstruction*, RunAction*);
  virtual ~SteppingAction();
  
  // method from the base class
  virtual void UserSteppingAction(const G4Step*);

  //inline G4int GetZPartition()  const {return N;}
  
  //private:
  EventAction*  fEventAction;
  RunAction*  fRunAction;
  
  //Added
  DetectorConstruction* fDetector;

  //G4int N = 20000; //Número de divisiones en z (like a mesh...)

//std::ofstream myFile1;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
