#include <iostream>
#include "G4Types.hh"
#include "globals.hh"
#include "G4Element.hh"
#include "G4Isotope.hh"
#include "G4Material.hh"

// HERE 
#include "G4NistManager.hh"


int main() { 

  const G4String elName = "Al"; 
  G4NistManager::Instance()->PrintElement(elName); 

  const G4String matCName = "simple"; 
  G4NistManager::Instance()->ListMaterials(matCName); 

  const G4String matName = "G4_Si"; 
  const G4Material* theSi = G4NistManager::Instance()->FindOrBuildMaterial(matName); 

  if (theSi != nullptr) { 
    G4cout << theSi << G4endl; 
  } else { 
    G4cout << " nothing: " << matName << G4endl; 
  } 
  
  
  
  
  G4Element* elC = new G4Element("Carbon", "C", 6., 12.01*CLHEP::g/CLHEP::mole); 
  
  // create the isotopes: iz = number of protons and n=number of nucleons 
  G4Isotope* U5 = new G4Isotope("U235", 92, 235); 
  G4Isotope* U8 = new G4Isotope("U238", 92, 238); 
  // create the element and build up by adding the isotopes with their abundance:  
  G4Element* elU = new G4Element("Enriched Uranium", "U", 2); 
  elU->AddIsotope(U5,90.*CLHEP::perCent); 
  elU->AddIsotope(U8,10.*CLHEP::perCent); 
  
  G4Material* matU = new G4Material("Uranium", 92., 238.03*CLHEP::g/CLHEP::mole, 18.950*CLHEP::g/CLHEP::cm3); 
  
  //agua
  G4Element* elH = new G4Element("Hydrogen", "H", 1.00, 1.01*CLHEP::g/CLHEP::mole); 
  G4Element* elO = new G4Element("Oxygen", "O", 8.00, 16*CLHEP::g/CLHEP::mole);
  
  G4Material* matH2O = new G4Material("water", 1.0*CLHEP::g/CLHEP::cm3, 2);
  
  matH2O->AddElement(elH, 2); 
  matH2O->AddElement(elO, 1); 
  
  //aire
  G4Element* elN = new G4Element("Nytrogen", "N", 7.00, 14.0067*CLHEP::g/CLHEP::mole); 

  G4Material* matAir = new G4Material("Air", 1.290*CLHEP::mg/CLHEP::cm3, 2);  
  matAir->AddElement(elN, 0.7); 
  matAir->AddElement(elO, 0.3); 
  
  //aerogel: primero crear SiO2
  
  G4Element* elSi = new G4Element("Silicon", "Si", 14.00, 28.085*CLHEP::g/CLHEP::mole);
  G4Material* matSiO2 = new G4Material("Silicon Oxide", 2.634*CLHEP::g/CLHEP::cm3, 2);
  matSiO2->AddElement(elSi, 1);
  matSiO2->AddElement(elO, 2);
  
  // create aerogel material: 
  G4Material* matAerog = new G4Material("Aerogel",  0.2*CLHEP::g/CLHEP::cm3, 3);  

 
  // add the elements to the material with their fractional mass:  
  matAerog->AddMaterial(matSiO2,62.5*CLHEP::perCent); 
  matAerog->AddMaterial(matH2O, 37.4*CLHEP::perCent); 
  matAerog->AddElement(elC, 0.1*CLHEP::perCent); 
  
  // NIST
  G4NistManager* nistMGR = G4NistManager::Instance(); 

 
  // get the pre-defined liquid argon (“G4_lAr”) from the NIST DB 
  G4Material* matLAr = nistMGR->FindOrBuildMaterial("G4_lAr");
  // get the pre-defined concrete (“G4_CONCRETE”) from the NIST DB 
  G4Material* matConcr = nistMGR->FindOrBuildMaterial("G4_CONCRETE");
  
  
  return 0;
}
