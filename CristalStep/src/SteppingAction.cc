#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Track.hh"
#include "G4Event.hh"
#include "RunAction.hh"
#include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"

#include "G4Step.hh"
#include "G4EmCalculator.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "G4Ions.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* event, DetectorConstruction* det, RunAction* run)
  : G4UserSteppingAction(), fEventAction(event), fDetector(det), fRunAction(run)
{
  //myFile1.open("LET_All_Stepping.dat", std::ios::out);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void SteppingAction::UserSteppingAction(const G4Step* step)
{
  //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
  //G4ParticleDefinition* pli7 = G4ParticleTable::GetParticleTable()->FindParticle("Li7");
  //G4int nGamma=0, nAlpha=0, nLitio=0, nOthers=0;
    G4int nElectron=0, nOthers=0;
    
  //Number of events
  //G4int nofEvents = run->GetNumberOfEvent();

  //Get Event number 
  //G4int eID = 0;
  //const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();
  //if(evt) eID = evt->GetEventID();
  
  G4Track* track = step->GetTrack();
  if(track->GetVolume()->GetName() != "Crystal_physical2" ) return; //dentro del blanco

  //Tamaño del paso
  G4double steplength = step->GetStepLength();
  G4double edep = step->GetTotalEnergyDeposit();
  
  //G4StepPoint* preStepPoint = step->GetPreStepPoint();
  //G4StepPoint* postStepPoint = step->GetPostStepPoint();
  
  //G4Track * theTrack = step->GetTrack();
  G4int trackID = track->GetTrackID();
  G4int parentID = track->GetParentID();
  
  G4ParticleDefinition *particleDef = track->GetDefinition();
   
  const G4TrackVector* secondaries = fpSteppingManager->GetSecondary();
 
  //Primary
  //if( (particleDef == G4Electron::Electron()) && (trackID == 1) && (parentID == 0) ){
  if( (particleDef == G4Proton::Proton()) && (trackID == 1) && (parentID == 0) ){
    fEventAction->AddEventsReaction0(1); //Contador para reacciones
    size_t nmbSecTracks = (*secondaries).size();
    //Loop over secondaries
    for (size_t lp = 0; lp < nmbSecTracks; lp++) {
      if((*secondaries)[lp]->GetDefinition() == G4Electron::Definition())  nElectron++;
        else nOthers++;}
    
    G4double z1 = step->GetPreStepPoint()->GetPosition().z();// + zmax*0.5;
    G4double z2 = step->GetPostStepPoint()->GetPosition().z();// + zmax*0.5;
    G4double z  = ((z1 + z2)*0.5);// G4UniformRand()*(z2-z1);
    

    //G4int N = 100, i = -1;
    G4int i = -1;
    G4int N = fDetector->GetZPartition();
    G4double DZ = fDetector->GetAbsorSizeZ();
    G4double Div = DZ/N;
      
    /*G4double zaux = (z - 0.0)/Div;
    if( (zaux - floor(zaux)) < 0.5 )
      i = (int) floor(zaux);
    else
    i = (int) ceil(zaux);*/
    
    for(int xx=0; xx < N; xx++){
      if((z > xx*Div) && (z <= (xx+1)*Div))
      i=xx; }
      
      
    fEventAction->AddEdep(edep);
    fEventAction->AddStep(steplength);
    fEventAction->Addedepstep(i, edep, steplength);
      
    
      

  
  // get the material
  //G4Material * materialStep = step -> GetPreStepPoint() -> GetMaterial();

  // Get the pre-step kinetic energy
  //G4double eKinPre = step->GetPreStepPoint()->GetKineticEnergy();

  // Get the post-step kinetic energy
  //G4double eKinPost = step->GetPostStepPoint()->GetKineticEnergy();

  // Get the step average kinetic energy
  //G4double eKinMean = (eKinPre + eKinPost) * 0.5;
  //G4double eKinMean = G4UniformRand()*(eKinPre - eKinPost);
  //G4EmCalculator emCal;
  //G4double Lsn = emCal.ComputeElectronicDEDX(eKinMean, particleDef, materialStep);

  
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
