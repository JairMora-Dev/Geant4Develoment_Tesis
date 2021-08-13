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
/// \file eventgenerator/exgps/include/RunAction.hh
/// \brief Definition of the RunAction class
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"

//Added
#include <fstream>
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Run;
class HistoManager;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RunAction : public G4UserRunAction
{
  public:
   RunAction();
  ~RunAction();

   virtual void BeginOfRunAction(const G4Run*);
   virtual void EndOfRunAction(const G4Run*);
    
    //Added
    void AddEdepAllRun(G4double edep, G4double step){
      fedepAll += edep;
      fstepAll += step;
    }
    
    void TotalEventsR0(G4int R0) {fEventR0 += R0; }

    void nAddEdepAll(G4int i, G4double edep, G4double step){
      fEdepNAll[i] += edep;
      fStepNAll[i] += step;
    }

    G4int nofevents;
    
  private:
    
      
    const G4int Divisions2 = 10000;
    G4int fEventR0;

    G4double fEdepNAll[10000];
    G4double fStepNAll[10000];

    G4double fedepAll;
    G4double fstepAll;
    G4double let_all;

  
    HistoManager* fHistoManager;
    
    //data members
    std::ofstream myFileNAll;
        
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif



