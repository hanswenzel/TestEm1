//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file electromagnetic/TestEm1/src/EventAction.cc
/// \brief Implementation of the EventAction class
//
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"

#include "HistoManager.hh"
#include "G4RunManagerKernel.hh"
#include "G4TrackingManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "TrackingAction.hh"
#include "EnergyDepositHit.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
: G4UserEventAction() {
    fTotalEnergyDeposit = 0.;
    fNIEL = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction() {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*) {
    fTotalEnergyDeposit = 0.;
    fNIEL = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* event) {
    TrackingAction* tra = (TrackingAction*) G4RunManagerKernel::GetRunManagerKernel()->GetTrackingManager()->GetUserTrackingAction();
    //std::cout << "********* " << tra->GetTrackLength() << std::endl;
    double tracklength = tra->GetTrackLength() ;
    //G4TrackingManager* GetTrackingManager()
    auto hce = event->GetHCofThisEvent();
    auto hc = hce->GetHC(0);
    double dEdx[200];
    for(int i=0;i<200;i++){
        dEdx[i]=0.0;
    } 
     for(unsigned int i=0;i<hc->GetSize();i++){ 
         unsigned int slice =(tracklength-(((EnergyDepositHit*)(hc->GetHit(i)))->GetZpos()))/5;
         if (slice>199) slice=199;
         dEdx[slice]=dEdx[slice]+((EnergyDepositHit*)(hc->GetHit(i)))->GetEdep();
//       std::cout<<"999999999999999999:  "<<   ((EnergyDepositHit*)(hc->GetHit(i)))->GetEdep()<<std::endl;
     }
   for(int i=0;i<200;i++){
        G4AnalysisManager::Instance()->FillH1(8+i,dEdx[i]);
    } 
   // std::cout << "********* hc size:  " << hc->GetSize() << std::endl;
    G4AnalysisManager::Instance()->FillH1(4, fTotalEnergyDeposit);
    G4AnalysisManager::Instance()->FillH1(7, fNIEL);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

