// Simple Geant4 template to start learning it
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
//#include "PhysicsList.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "ActionInitialization.hh"
//Librerias Scoring
#include "G4ScoringManager.hh"

#include "EventAction.hh" 



int main(int argc, char** argv)
//int main()
{

  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }


  // Construct the default run manager
  //
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  //G4ScoringManager* scManager = G4ScoringManager::GetScoringManager();
  //scManager->SetVerboseLevel(1); 


  
  // set mandatory initialization classes
  //physicsList->RegisterPhysics(new PhysicsList);
  runManager->SetUserInitialization(new DetectorConstruction);
    G4VUserPhysicsList* physics = new PhysicsList;
    runManager->SetUserInitialization(physics);
    
  //runManager->SetUserInitialization(new PhysicsList);
  runManager->SetUserInitialization(new ActionInitialization);

  
  
  // set mandatory user action class
  //runManager->SetUserAction(new PrimaryGeneratorAction);
  //runManager->SetUserAction(new EventAction);



  // Initialize G4 kernel
  runManager->Initialize();

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();
  

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  
  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  
  delete visManager;
  delete runManager;
  
  return 0;
}
