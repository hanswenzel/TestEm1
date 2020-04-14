
/// \file EnergyDepositHit.hh
/// \brief Definition of the EnergyDepositHit class

#ifndef EnergyDepositHit_h
#define EnergyDepositHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4AttDef;
class G4AttValue;

/// Hadron Calorimeter hit

class EnergyDepositHit : public G4VHit {
public:
    EnergyDepositHit();

    EnergyDepositHit(G4double zedep,
            G4double zx,
            G4double zy,
            G4double zz,
            G4double zt);
    EnergyDepositHit(const EnergyDepositHit &right);
    virtual ~EnergyDepositHit();

    const EnergyDepositHit& operator=(const EnergyDepositHit &right);
    G4bool operator==(const EnergyDepositHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    virtual const std::map<G4String, G4AttDef>* GetAttDefs() const;
    virtual std::vector<G4AttValue>* CreateAttValues() const;
    virtual void Print();



private:
    G4double fEdep;
    G4double xpos;
    G4double ypos;
    G4double zpos;
    G4double time;

public:

G4double GetEdep() const {
    return fEdep;
}

G4double GetTime() const {
    return time;
}

G4double GetZpos() const {
    return zpos;
}

G4double GetYpos() const {
    return ypos;
}

G4double GetXpos() const {
    return xpos;
}
};
using EnergyDepositHitsCollection = G4THitsCollection<EnergyDepositHit>;

extern G4ThreadLocal G4Allocator<EnergyDepositHit>* EnergyDepositHitAllocator;

inline void* EnergyDepositHit::operator new(size_t){
    if (!EnergyDepositHitAllocator) {
        EnergyDepositHitAllocator = new G4Allocator<EnergyDepositHit>;
    }
    return (void*) EnergyDepositHitAllocator->MallocSingle();
}

inline void EnergyDepositHit::operator delete(void* aHit) {
    EnergyDepositHitAllocator->FreeSingle((EnergyDepositHit*) aHit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
