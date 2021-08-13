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
//
//
//
//Globales
#include "globals.hh"
#include "PhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4UniversalFluctuation.hh"

#include "G4EmLowEPPhysics.hh"
#include "G4PhysicsListHelper.hh"
#include "G4VLowEnergyModel.hh"
#include "G4EmStandardPhysics_option3.hh"

//Procesos estandar para gammas
#include "G4PhotoElectricEffect.hh"
#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4RayleighScattering.hh"

//Procesos bajas energias gamas
#include "G4LivermorePhotoElectricModel.hh"
#include "G4LivermoreComptonModel.hh"
#include "G4BetheHeitler5DModel.hh"

//Procesos estadar para electrones
#include "G4eBremsstrahlung.hh"
#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eplusAnnihilation.hh"

//Procesos de bajas energias para electrones
#include "G4LivermoreIonisationModel.hh"

//Procesos estandar para hadrones
#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"

//Procesos para hadrones bajas energias
#include "G4hImpactIonisation.hh"
#include "G4hBetheBlochModel.hh"
#include "G4ionIonisation.hh"

//Librerias para Centelleo
#include "G4Scintillation.hh"
#include "G4OpBoundaryProcess.hh"
#include "G4OpAbsorption.hh"

//Librerias para desexcitacion
#include "G4LossTableManager.hh"
#include "G4UAtomicDeexcitation.hh"

//Producciones de corte
#include "G4ProductionCutsTable.hh"




PhysicsList::PhysicsList():  G4VUserPhysicsList()
{
  // Deexcitation
    
   // G4VAtomDeexcitation* de = new G4UAtomicDeexcitation();
   // G4LossTableManager::Instance()->SetAtomDeexcitation(de);
    
   defaultCutValue = 0.0*mm;
   OpVerbLevel = 0;
   SetVerboseLevel(1);

}


PhysicsList::~PhysicsList()
{}


void PhysicsList::ConstructParticle()
{
  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();
}


void PhysicsList::ConstructBosons()
{
  // pseudo-particles
  //G4Geantino::GeantinoDefinition();
  //G4ChargedGeantino::ChargedGeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();
}


void PhysicsList::ConstructLeptons()
{
  // leptons
  //  e+/-
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  // mu+/-
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();
  // nu_e
  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  // nu_mu
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}


void PhysicsList::ConstructMesons()
{
  //  mesons
  //    light mesons
  //G4PionPlus::PionPlusDefinition();
  //G4PionMinus::PionMinusDefinition();
  //G4PionZero::PionZeroDefinition();
  //G4Eta::EtaDefinition();
  //G4EtaPrime::EtaPrimeDefinition();
  //G4KaonPlus::KaonPlusDefinition();
  //G4KaonMinus::KaonMinusDefinition();
  //G4KaonZero::KaonZeroDefinition();
  //G4AntiKaonZero::AntiKaonZeroDefinition();
  //G4KaonZeroLong::KaonZeroLongDefinition();
  //G4KaonZeroShort::KaonZeroShortDefinition();
}


void PhysicsList::ConstructBaryons()
{
  //  barions
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();

  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();
}


void PhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
  ConstructGeneral();
  ConstructOp();

  //AddStepMax();
    
}



void PhysicsList::ConstructEM()
{
    
    
    auto theParticleIterator=GetParticleIterator();
    theParticleIterator->reset();
    while( (*theParticleIterator)() ){
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* processManager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();
     
        if( particleName == "proton" ) {
            //proton
        
            //G4hImpactIonisation* hIonisation = new G4hImpactIonisation();
            //hIonisation->SetPixeCrossSectionK("ecpssr");
            //hIonisation->SetPixeCrossSectionL("ecpssr");
            //hIonisation->SetPixeCrossSectionM("ecpssr");
            //hIonisation->SetPixeProjectileMinEnergy(1.* keV);
            //hIonisation->SetPixeProjectileMaxEnergy(200. * MeV);
            //hIonisation->SetCutForSecondaryPhotons(200 * eV);
            //hIonisation->SetCutForAugerElectrons(250. * eV);
            //processManager -> AddDiscreteProcess(hIonisation);
        
            G4hIonisation* hpIonisation = new G4hIonisation();
            processManager -> AddProcess(hpIonisation, -1, 1, 2);
          
            G4hMultipleScattering* hMultipleScattering = new G4hMultipleScattering();
            processManager -> AddProcess(hMultipleScattering, -1, 2, 1);
            
        
       
        } else if (particleName == "e-") {

            // electron

            G4eMultipleScattering* eMultipleScattering = new G4eMultipleScattering();
            eMultipleScattering->SetStepLimitType(fUseDistanceToBoundary);
            processManager -> AddProcess(eMultipleScattering, -1, 1, -1);
            //processManager -> AddDiscreteProcess(eMultipleScattering/*, -1, 1, -1*/);
            
            G4eIonisation* eIonisation = new G4eIonisation();
            G4VEmModel* theIoniLiv = new G4LivermoreIonisationModel();
            theIoniLiv->SetHighEnergyLimit(0.1*MeV);
            eIonisation->AddEmModel(0, theIoniLiv, new G4UniversalFluctuation());
            eIonisation->SetStepFunction(0.2, 100*um);
            processManager -> AddProcess(eIonisation, -1, 2, 2);
            //processManager -> AddDiscreteProcess(eIonisation/*, -1, 2, 2*/);
          
            G4eBremsstrahlung* eBremsstrahlung = new G4eBremsstrahlung();
            processManager -> AddProcess(eBremsstrahlung, -1, 2, 2);
          
        } else if (particleName == "gamma") {
        
            // photon

            G4PhotoElectricEffect* photoelectric = new G4PhotoElectricEffect;
                photoelectric->SetEmModel(new G4LivermorePhotoElectricModel());
         
            // photoelectric->ActivateAuger(true);
            // photoelectric->SetCutForLowEnSecPhotons(0.250 * keV);
            //photoelectric->SetCutForLowEnSecElectrons(0.250 * keV);
          
            G4ComptonScattering* compton = new G4ComptonScattering;
            compton->SetEmModel(new G4LivermoreComptonModel());
          
            G4GammaConversion* gammaConversion = new G4GammaConversion;
            gammaConversion->SetEmModel(new G4BetheHeitler5DModel());
          
            G4RayleighScattering* rayleigh = new G4RayleighScattering;

            processManager -> AddDiscreteProcess(photoelectric);
            processManager -> AddDiscreteProcess(compton);
            processManager -> AddDiscreteProcess(gammaConversion);
            processManager -> AddDiscreteProcess(rayleigh);
      
        }
    }
    
}


void PhysicsList::ConstructGeneral()
{
    G4LossTableManager* man = G4LossTableManager::Instance();
    man->SetAtomDeexcitation(new G4UAtomicDeexcitation());
}
 
void PhysicsList::ConstructOp()
{/*
    // default scintillation process
      G4Scintillation* theScintProcessDef = new G4Scintillation("Scintillation");
      // theScintProcessDef->DumpPhysicsTable();
      theScintProcessDef->SetTrackSecondariesFirst(true);
      theScintProcessDef->SetScintillationYieldFactor(1.0); //
      theScintProcessDef->SetScintillationExcitationRatio(0.0); //
      theScintProcessDef->SetVerboseLevel(OpVerbLevel);
    
    // default scintillation process
      G4Scintillation* etheScintProcessDef = new G4Scintillation("eScintillation");
      // theScintProcessDef->DumpPhysicsTable();
      etheScintProcessDef->SetTrackSecondariesFirst(true);
      etheScintProcessDef->SetScintillationYieldFactor(0.90); //
      etheScintProcessDef->SetScintillationExcitationRatio(0.0); //
      etheScintProcessDef->SetVerboseLevel(OpVerbLevel);
    
    
    // optical processes
      G4OpAbsorption* theAbsorptionProcess = new G4OpAbsorption();
      //  G4OpRayleigh* theRayleighScatteringProcess = new G4OpRayleigh();
      G4OpBoundaryProcess* theBoundaryProcess = new G4OpBoundaryProcess();
      //  theAbsorptionProcess->DumpPhysicsTable();
      //  theRayleighScatteringProcess->DumpPhysicsTable();
      theAbsorptionProcess->SetVerboseLevel(OpVerbLevel);
      // theRayleighScatteringProcess->SetVerboseLevel(OpVerbLevel);
      theBoundaryProcess->SetVerboseLevel(OpVerbLevel);
    
    auto particleIterator=GetParticleIterator();
      particleIterator->reset();
      while( (*particleIterator)() )
        {
          G4ParticleDefinition* particle = particleIterator->value();
          G4ProcessManager* pmanager = particle->GetProcessManager();
          G4String particleName = particle->GetParticleName();
            if (theScintProcessDef->IsApplicable(*particle)){
            
                if (particleName == "e-"){
                    pmanager->AddProcess(etheScintProcessDef);
                    pmanager->SetProcessOrderingToLast(etheScintProcessDef,idxAtRest);
                    pmanager->SetProcessOrderingToLast(etheScintProcessDef,idxPostStep);
                    
                } else {
                      pmanager->AddProcess(theScintProcessDef);
                      pmanager->SetProcessOrderingToLast(theScintProcessDef,idxAtRest);
                      pmanager->SetProcessOrderingToLast(theScintProcessDef,idxPostStep);
                    }
            } if (particleName == "opticalphoton") {
                    pmanager->AddDiscreteProcess(theAbsorptionProcess);
                    //    pmanager->AddDiscreteProcess(theRayleighScatteringProcess);
                    pmanager->AddDiscreteProcess(theBoundaryProcess);
                      }
            
        }
 */}


void PhysicsList::SetCuts()
{
  //G4VUserPhysicsList::SetCutsWithDefault method sets
  //the default cut value for all particle types
  
  //SetCutsWithDefault();
    
    SetCutValue(0.10*mm, "proton");
    SetCutValue(10.0*micrometer, "e-");
    SetCutValue(10.0*micrometer, "gamma");

  // Set the secondary production cut lower than 990. eV
  // Very important for processes at low energies
 
  G4double lowLimit = 2. * eV;
  G4double highLimit = 100. * GeV;
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(lowLimit, highLimit);
     
  if (verboseLevel>0) DumpCutValuesTable();
}

