#include "YourSteppingAction.hh"

#include "YourDetectorConstruction.hh"
#include "YourEventAction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

YourSteppingAction::YourSteppingAction(YourDetectorConstruction* det, YourEventAction* evtAction) 
:   G4UserSteppingAction(), 
    fYourDetector(det),
    fYourEventAction(evtAction) { }


YourSteppingAction::~YourSteppingAction() {}


//
// Score only if the step was done in the Target:
//  - cllect energy deposit for the mean (per-event) energy deposit computation
//  - same for the charged particle track length
void YourSteppingAction::UserSteppingAction(const G4Step* theStep) {
  // Score steps done only in the target: i.e. pre-step point was in target
  
  if (theStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume() 
      != fYourDetector->GetTargetPhysicalVolume() )  return; 

  // energy deposit
  auto eDep   = theStep->GetTotalEnergyDeposit();
  
  // track length (only for charged particles)
  auto trackL = 0.;   
  if ( theStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    trackL = theStep->GetStepLength(); 
  }
  
  // place the information inside the event action
  fYourEventAction->Add( eDep, trackL );
}
