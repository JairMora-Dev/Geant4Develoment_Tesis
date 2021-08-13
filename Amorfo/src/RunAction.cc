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
/// \file eventgenerator/exgps/src/RunAction.cc
/// \brief Implementation of the RunAction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//RevisarLibreiras de B1RunAction
#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4Run.hh"

//Added
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
 : G4UserRunAction(), fHistoManager(0)
{
 fHistoManager = new HistoManager(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
  //delete fHistoManager;

    fHistoManager = new HistoManager();
        
      const G4double letunit = 1.0*keV/um;
      const G4double stepunit = 1.0*um;
      const G4double edepunit = 1.0*keV;
      
      new G4UnitDefinition("keV/micra", "keV/micra" , "Let", letunit);
      new G4UnitDefinition("micras", "micras" , "step", stepunit);
      new G4UnitDefinition("keV", "keV" , "edep", edepunit);
      
      myFileNAll.open("LET_Cristal.dat", std::ios::out);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{
    fEventR0 = 0;
   
    fedepAll = 0.0;
    fstepAll = 0.0;
    
    for(int i=0; i<Divisions2; i++){
      fEdepNAll[i] = 0.0;
      fStepNAll[i] = 0.0;
    }
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
  //histograms
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->OpenFile();
  }
   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
    nofevents =  run->GetNumberOfEvent();
    G4cout << "nofevents: " << nofevents << G4endl;
    
      G4double uDz =0.000127;
      G4double uDzMed =0.0000635;
    for(int i=0; i<Divisions2; i++){
      if(fStepNAll[i] <= 0.0) continue;
        myFileNAll << i <<" "<< (i*uDz) + uDzMed << " " << fEdepNAll[i] <<" "<< fStepNAll[i] << " "<< fEdepNAll[i]/fStepNAll[i] << G4endl;
    
        //****** COMENTAR ESTA lÍNEA *******
        G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
        //**********************************
        G4double PZmed = (i*uDz) + uDzMed;
        //analysisManager->FillH1(3, fEdepNAll[i]/fStepNAll[i]);
        //analysisManager->FillH1(4, fEdepNAll[i]);
        analysisManager->FillH1(3, PZmed);
        
        
        
        
        analysisManager->FillNtupleDColumn(0, 1, PZmed);
        analysisManager->FillNtupleDColumn(0, 2, fEdepNAll[i]);
        analysisManager->FillNtupleDColumn(0, 3, fEdepNAll[i]/fStepNAll[i]);
        
        analysisManager->AddNtupleRow();
        
        G4cout << PZmed <<"\t"<< fEdepNAll[i]/fStepNAll[i] <<"\t" << G4endl;
    }

    let_all = fedepAll/fstepAll;
     
      
    G4cout
      << G4endl
      << " The run consists of " << nofevents << " events. "
      << G4endl
      << " Cumulated LET per run, in scoring volume: "
      << G4endl
      << "------------------------------------------------------------"
      << G4endl
      << G4endl;

    
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
  //save histograms
  //      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->Write();
    analysisManager->CloseFile();
  }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
