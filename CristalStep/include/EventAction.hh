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
//
/// \file EventAction.hh
/// \brief Definition of the B4dEventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"

#include "G4THitsMap.hh"
#include "globals.hh"

#include <fstream>

class RunAction;
//Added
class G4LogicalVolume;
class DetectorConstruction;


// Event action class

class EventAction : public G4UserEventAction
{
public:
  EventAction(RunAction*, DetectorConstruction*);
  virtual ~EventAction();

  virtual void  BeginOfEventAction(const G4Event* event);
  virtual void  EndOfEventAction(const G4Event* event);
    
    void AddEdep(G4double edep) { fEdepa0 += edep; }
    void AddStep(G4double step) { fStepa0 += step; }

    void AddEventsReaction0(G4int eventR) { fNReaction0 += eventR; }
    
    void Addedepstep(G4int i, G4double edep, G4double stepl) {
      fEdep[i] += edep;
      fStep[i] += stepl;
    }
private:
        
//Added
RunAction* fRunAction;
//Added
DetectorConstruction* fDetector;
        
        const G4int Divisions = 10000;
        G4int fNReaction0;
        G4double fEdepa0;
        G4double fStepa0;
        
    G4double fEdep[10000];
    G4double fStep[10000];
        
  // methods
  G4THitsMap<G4double>* GetHitsCollection(G4int hcID,
                                          const G4Event* event) const;
  G4double GetSum(G4THitsMap<G4double>* hitsMap) const;
  
  // data members
  G4int  fEfluxHCID;
  G4int fEdepHCID;
 
  std::ofstream myFile;
};
                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

    
