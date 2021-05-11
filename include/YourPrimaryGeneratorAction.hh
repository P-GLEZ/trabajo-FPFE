
#ifndef YOURPRIMARYGENERATORACTION_HH 
#define YOURPRIMARYGENERATORACTION_HH 

#include "G4VUserPrimaryGeneratorAction.hh" 
#include "G4Types.hh"
#include "G4String.hh"

class YourDetectorConstruction;
class G4ParticleGun; 

 
class YourPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction { 
public: 
   YourPrimaryGeneratorAction(YourDetectorConstruction* det); 
  ~YourPrimaryGeneratorAction(); 
	// 
    // Additional custom methods: 

    // Public method to obtain the G4ParticleGun object pointer and some other 
    // primary particle realted values 
    G4ParticleGun*  GetParticleGun() { return fParticleGun; } 
 
    // Public method to get the primary particle name. 
    const G4String& GetParticleName() const; 
 
    // Public method to get the primary particle kinetic energy. 
    G4double        GetParticleEnergy() const; 
 
    // Public method to set the default primary particle kinematics 
    void            SetDefaultKinematic(); 
 
    // Public method to set the position of the particle gun: will be taken for 
    // the actual detector construction 
    void            UpdatePosition(); 
 
  virtual void GeneratePrimaries(G4Event* anEvent); 
 
private: 
   YourDetectorConstruction* fYourDetector; 
   
   G4ParticleGun* fParticleGun;
   
}; 

#endif
