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
/// \file eventgenerator/exgps/src/HistoManager.cc
/// \brief Implementation of the HistoManager class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("DatosCris.dat")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  //
  G4AnalysisManager* analysis = G4AnalysisManager::Instance();
  
  analysis->SetFileName(fFileName);
  analysis->SetVerboseLevel(1);
  analysis->SetActivation(true);     //enable inactivation of histos, nTuples
    
  // Default values (to be reset via /analysis/h1/set command)               
  G4int nbins = 100.;
  G4double vmin = 0.;
  G4double vmax = 100.;
    
    /*G4int nxbins = 100;
    G4double xmin = 0.;
    G4double xmax = 100.;
    
    G4int nybins = 100;
    G4double ymin = 0.;
    G4double ymax = 100.;*/
    

  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  //
  analysis->SetHistoDirectoryName("HistogramasCristal");
  analysis->SetFirstHistoId(1);
    
  G4int id = analysis->CreateH1("h1.1", "Contador Flujo de Parti", nbins, vmin, vmax);
  analysis->SetH1Activation(id, false);


  id = analysis->CreateH1("h1.2","Energia Abs", nbins, vmin, vmax);
  analysis->SetH1Activation(id, false);
    
  id = analysis->CreateH1("h1.3","Profundidad", nbins, vmin, vmax);
    analysis->SetH1Activation(id, false);
    
  /*id = analysis->CreateH2("h2.4","EDep Vs Profundidad", nxbins, xmin, xmax, nybins, ymin, ymax);
    analysis->SetH2Activation(id, false);*/
    
    // Creacion de Ntuplas
    //
    analysis->SetNtupleDirectoryName("StepCrisNtuple");//Creacion directorio Ntuplas
    analysis->CreateNtuple("Ntuple1", "DatosStepCristal");
    analysis->CreateNtupleDColumn("Energia_Abs_MeV");//Canvas
    analysis->CreateNtupleDColumn("Profundidad");//Canvas
    analysis->CreateNtupleDColumn("EDep_en_el_Nucleo");//Canvas
    analysis->CreateNtupleDColumn("LET");//Canvas
    
    
    analysis->FinishNtuple();//FinalizacionCanvas
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
