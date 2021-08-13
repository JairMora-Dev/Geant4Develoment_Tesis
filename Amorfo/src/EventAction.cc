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
/// \file EventAction.cc
/// \brief Implementation of the B4dEventAction class

#include "EventAction.hh"

#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "DetectorConstruction.hh"

//**********************************
//****** COMENTAR ESTA lÍNEA *******
#include "HistoManager.hh"
//**********************************

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
EventAction::EventAction(RunAction* run, DetectorConstruction* det)
  
 : G4UserEventAction(),
   fEfluxHCID(-1),fEdepHCID(-1), fRunAction(run), fDetector(det)
{
  myFile.open("SalidaCris.dat", std::ios::out);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4THitsMap<G4double>* 
EventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  auto hitsCollection 
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4double EventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
  G4double sumValue = 0.;
  for ( auto it : *hitsMap->GetMap() ) {
    // hitsMap->GetMap() returns the map of std::map<G4int, G4double*>
    sumValue += *(it.second);
  }
  return sumValue;  
}  


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::BeginOfEventAction(const G4Event*)
{
    fNReaction0 = 0;
    fEdepa0 = 0.0;
    fStepa0 = 0.0;

    //Revisar valor de la variable "Divisiones"... debe coincidir con la variable "N" del
    //SteppingAction.cc
    for(int i=0; i<Divisions; i++){
      fEdep[i] = 0.0;
      fStep[i] = 0.0;
    }
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::EndOfEventAction(const G4Event* event)
{
  G4HCofThisEvent* HCE = event->GetHCofThisEvent();
  if(!HCE) return;
  
  // Get hist collections IDs
   if ( fEfluxHCID < 0 ) {
  fEfluxHCID = G4SDManager::GetSDMpointer()->GetCollectionID("SD_Placa/Flux");
   }//Coleccion para la placa
  
  if ( fEdepHCID < 0 ) {
      fEdepHCID = G4SDManager::GetSDMpointer()->GetCollectionID("EneDep");
  }//Coleccion para el cristal


//................Contador de Flujo en la Placa.................................................
G4THitsMap<G4double>* evtMap =
    (G4THitsMap<G4double>*)(HCE->GetHC(fEfluxHCID));

  std::map<G4int,G4double*>::iterator itr;

  //**********************************
  //****** COMENTAR ESTA lÍNEA *******
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //**********************************
  
  //G4double cpn = 0;
   for (itr = evtMap->GetMap()->begin(); itr != evtMap->GetMap()->end(); itr++)
  {
    G4int copyNb  = (itr->first);
    G4double hit = *(itr->second);

    // Fill histograms
    //************************************
    //****** COMENTAR ESTA lÍNEA *********
    analysisManager->FillH1(1, hit);
    //************************************
    
    if (myFile.is_open()) // Check if file is opened
      myFile << copyNb << "\t" <<  hit << G4endl;
    else
      G4cout << " !!!!!!! Error with myFile !!!!!!!! " << G4endl;
  }
//.....................................................................................
    
    
    
//................ENERGIAABS en el Cristal............................................
  myFile << "ENERGIA_ABSORBIDA\n";
  
  G4THitsMap<G4double>* evtMap2 = 
    (G4THitsMap<G4double>*)(HCE->GetHC(fEdepHCID));

  std::map<G4int,G4double*>::iterator itr2;

  
  //G4double cpn = 0;
  for (itr2 = evtMap2->GetMap()->begin(); itr2 != evtMap2->GetMap()->end(); itr2++)
    {
    G4int copyNb  = (itr2->first);
    G4double hit = *(itr2->second);

    // Fill histograms
    //************************************
    //****** COMENTAR ESTA lÍNEA *********
    //G4cout << hit << G4endl;
    analysisManager->FillH1(2,hit);//LlenadoHistos
    analysisManager->FillNtupleDColumn(0, 0, hit);//LlenadoNtuplas
    //************************************
    
    if (myFile.is_open()) // Check if file is opened
      myFile << copyNb  << "\t" << hit << G4endl;
    else
      G4cout << " !!!!!!! Error with myFile !!!!!!!! " << G4endl;
    }
    //................................................................................
    
    //....Final llenado de Ntuplas.......
    analysisManager->AddNtupleRow();//...
    //...................................

    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    
    for(int i=0; i<Divisions; i++){
      if(fStep[i] <= 0.0) continue;
        myFile<< i + 0.5 << "   " <<fEdep[i]/keV<<"  "<<fStep[i]/um<<"  "<<fEdep[i]/fStep[i]/(keV/um)<<G4endl;
      }
    
    fRunAction->TotalEventsR0(fNReaction0);
    fRunAction->AddEdepAllRun(fEdepa0, fStepa0);
     
    for(int i=0; i<Divisions; i++){
      fRunAction->nAddEdepAll(i, fEdep[i], fStep[i]);
    }
    
    //G4int NNN = fDetector->GetZPartition();
    
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
