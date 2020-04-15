
/// \file EnergyDepositSD.cc
/// \brief Implementation of the EnergyDepositSD class

#include "EnergyDepositSD.hh"
#include "EnergyDepositHit.hh"
// Geant4 includes 
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EnergyDepositSD::EnergyDepositSD(G4String name)
: G4VSensitiveDetector(name),
fHitsCollection(nullptr), fHCID(-1) {
    collectionName.insert("EnergyDepositColl");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EnergyDepositSD::~EnergyDepositSD() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EnergyDepositSD::Initialize(G4HCofThisEvent* hce) {
    fHitsCollection
            = new EnergyDepositHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHCID < 0) {
        fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    hce->AddHitsCollection(fHCID, fHitsCollection);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool EnergyDepositSD::ProcessHits(G4Step* aStep, G4TouchableHistory*) {
    auto edep = aStep->GetTotalEnergyDeposit();
    if (edep == 0.) return true;
    auto hit = new EnergyDepositHit(edep,
            aStep->GetPostStepPoint()->GetPosition().getX(),
            aStep->GetPostStepPoint()->GetPosition().getY(),
            aStep->GetPostStepPoint()->GetPosition().getZ(),
            aStep->GetPostStepPoint()->GetProperTime());
    fHitsCollection->insert(hit);
    return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
