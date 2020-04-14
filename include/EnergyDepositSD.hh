
/// \file EnergyDepositSD.hh
/// \brief Definition of the EnergyDepositSD class

#ifndef EnergyDepositSD_h
#define EnergyDepositSD_h 1

#include "G4VSensitiveDetector.hh"

#include "EnergyDepositHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

/// Hadron calorimeter sensitive detector

class EnergyDepositSD : public G4VSensitiveDetector
{    
  public:
    EnergyDepositSD(G4String name);
    virtual ~EnergyDepositSD();
    
    virtual void Initialize(G4HCofThisEvent*HCE);
    virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
    
  private:
    EnergyDepositHitsCollection* fHitsCollection;
    G4int fHCID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
