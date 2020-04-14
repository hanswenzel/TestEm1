
/// \file EnergyDepositHit.cc
/// \brief Implementation of the EnergyDepositHit class

#include "EnergyDepositHit.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Box.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal G4Allocator<EnergyDepositHit>* EnergyDepositHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EnergyDepositHit::EnergyDepositHit()
: G4VHit(), fEdep(0),
xpos(0),
ypos(0),
zpos(0),
time(0) {
}



EnergyDepositHit::EnergyDepositHit(G4double zedep,
        G4double zx,
        G4double zy,
        G4double zz,
        G4double zt) : G4VHit(),
fEdep(zedep),
xpos(zx),
ypos(zy),
zpos(zz),
time(zt) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EnergyDepositHit::~EnergyDepositHit() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EnergyDepositHit::EnergyDepositHit(const EnergyDepositHit &right)
: G4VHit(),
fEdep(right.fEdep),
xpos(right.xpos),
ypos(right.ypos),
zpos(right.zpos),
time(right.time) {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const EnergyDepositHit& EnergyDepositHit::operator=(
        const EnergyDepositHit &right) {
    fEdep = right.fEdep;
    xpos = right.xpos;
    ypos = right.ypos;
    zpos = right.zpos;
    time = right.time;
    return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool EnergyDepositHit::operator==(const EnergyDepositHit &right) const {

    return (
            fEdep == right.fEdep &&
            xpos == right.xpos &&
            ypos == right.ypos &&
            zpos == right.zpos &&
            time == right.time);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const std::map<G4String, G4AttDef>* EnergyDepositHit::GetAttDefs() const {
    G4bool isNew;
    auto store = G4AttDefStore::GetInstance("EnergyDepositHit", isNew);
    if (isNew) {
        (*store)["HitType"] = G4AttDef("HitType", "Hit Type", "Physics", "", "G4String");
        (*store)["Energy"] = G4AttDef("Energy", "Energy Deposited", "Physics", "G4BestUnit", "G4double");
        (*store)["xPos"] = G4AttDef("xPos", "x Position", "Physics", "G4BestUnit", "G4double");
        (*store)["yPos"] = G4AttDef("yPos", "y Position", "Physics", "G4BestUnit", "G4double");
        (*store)["zPos"] = G4AttDef("zPos", "z Position", "Physics", "G4BestUnit", "G4double");
        (*store)["Time"] = G4AttDef("Time", "Time", "Physics", "G4BestUnit", "G4double");
    }
    return store;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

std::vector<G4AttValue>* EnergyDepositHit::CreateAttValues() const {
    auto values = new std::vector<G4AttValue>;

    values ->push_back(G4AttValue("HitType", "EnergyHit", ""));
    values ->push_back(G4AttValue("Energy", G4BestUnit(fEdep, "Energy"), ""));
    values ->push_back(G4AttValue("xPos", G4BestUnit(xpos, "Length"), ""));
    values ->push_back(G4AttValue("yPos", G4BestUnit(ypos, "Length"), ""));
    values ->push_back(G4AttValue("zPos", G4BestUnit(zpos, "Length"), ""));
    values ->push_back(G4AttValue("Time", G4BestUnit(time, "Time"), ""));

    return values;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EnergyDepositHit::Print() {
    G4cout << fEdep / MeV << " (MeV) " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
