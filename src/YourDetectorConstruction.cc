
#include "YourDetectorConstruction.hh"
#include "YourDetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


YourDetectorConstruction::YourDetectorConstruction() 
: G4VUserDetectorConstruction(),
  fTargetMaterial(nullptr), 
  fTargetPhysicalVolume(nullptr)
 {
  SetTargetMaterial("G4_Si");

  
  // set default target thickness
  fTargetThickness = 1.0*CLHEP::cm;  
  fGunXPosition = 0.0;
  fDetMessenger    = new YourDetectorMessenger(this); 
}

YourDetectorConstruction::~YourDetectorConstruction() {
	delete fDetMessenger;
	}


void YourDetectorConstruction::SetTargetMaterial(const G4String& matName) {
	// set default target material
  fTargetMaterial  = G4NistManager::Instance()->FindOrBuildMaterial(matName);
  if (fTargetMaterial == nullptr) {
    G4cerr << "  ERROR YourDetectorConstruction() \n" 
           << "  Material with name " << matName << " was not found! \n"
           << G4endl;
  }
	
	
}


G4VPhysicalVolume* YourDetectorConstruction::Construct() {

  
  G4double targetXSize = fTargetThickness;
  G4double targetYSize = 1.25*fTargetThickness;
  G4double targetZSize = 1.25*fTargetThickness;
  
  G4double worldXSize = 1.1*targetXSize;
  G4double worldYSize = 1.1*targetYSize;
  G4double worldZSize = 1.1*targetZSize;
  

  G4double z        = 1.0; 
  G4double amass    = 1.01*CLHEP::g/CLHEP::mole; 
  G4double density  = CLHEP::universe_mean_density; 
  G4double pressure = 3.0E-18*CLHEP::pascal; 
  G4double temp     = 2.73*CLHEP::kelvin; 
  G4Material* materialWorld = new G4Material("Galactic", z, amass, density, 
                                               kStateGas, temp, pressure); 
  
  G4Material* materialTarget = fTargetMaterial;
  fGunXPosition         = -0.25*( worldXSize + targetXSize );
  
  

  G4Box* worldSolid = new G4Box( "solid-World",   // name 
                                  0.5*worldXSize,  // box half x-size 
                                  0.5*worldYSize, // box half y-size 
                                  0.5*worldZSize // box half z-size 
                                  ); 
  G4LogicalVolume* worldLogical = new G4LogicalVolume( worldSolid,    // solid 
                                                       materialWorld, // material 
                                                      "logic-World"  // name 
                                                      ); 
  G4VPhysicalVolume* worldPhysical = new G4PVPlacement( nullptr,                    // (no) rotation 
                                                          G4ThreeVector(0., 0., 0.),  // translation 
                                                          worldLogical,               // logical volume 
                                                          "World",                    // name 
                                                          nullptr,                    // mother volume (!) 
                                                          false,                      // don't care 
                                                          0                           // cpy number 
                                                        ); 
  
  
  //definir target  
  
  G4Box* targetSolid = new G4Box( "solid-target",   // name 
                                  0.5*targetXSize,  // box half x-size 
                                  0.5*targetYSize, // box half y-size 
                                  0.5*targetZSize // box half z-size 
                                ); 
  G4LogicalVolume* targetLogical = new G4LogicalVolume( targetSolid,    // solid 
                                                        materialTarget , // material 
                                                        "logic-target"  // name 
                                                        ); 
  G4VPhysicalVolume* targetPhysical = new G4PVPlacement( nullptr,                    // (no) rotation 
                                                           G4ThreeVector(0., 0., 0.),  // translation 
                                                           targetLogical,               // logical volume 
                                                           "target",                    // name 
                                                           worldLogical,                    // mother volume (!) 
                                                           false,                      // don't care 
                                                           0                           // cpy number 
                                                        ); 
  fTargetPhysicalVolume = targetPhysical;
  return worldPhysical;
}
