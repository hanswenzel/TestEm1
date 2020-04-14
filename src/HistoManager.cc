
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
#include "G4UnitsTable.hh"
#include <iostream>   // std::cout
#include <string>     // std::string, std::to_string
//#include <stringstream>   

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
: fFileName("testem1") {
    Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager() {
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book() {
    // Create or get analysis manager
    // The choice of analysis technology is done via selection of a namespace
    // in HistoManager.hh
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->SetFileName(fFileName);
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFirstHistoId(1); // start histogram numbering from 1
    analysisManager->SetActivation(true); // enable inactivation of histograms

    // Define histograms start values
    const G4int kMaxHisto = 208;
    const G4int nonslice = 8;

    std::string id[kMaxHisto];
    std::string title[kMaxHisto];
    id[0] = "1";
    id[1] = "2";
    id[2] = "3";
    id[3] = "4";
    id[4] = "5";
    id[5] = "6";
    id[6] = "8";
    id[7] = "9";
    title[0] = "total track length of primary particle"; //1
    title[1] = "nb steps of primary particle"; //2
    title[2] = "step size of primary particle"; //3
    title[3] = "total energy deposit"; //4
    title[4] = "energy of charged secondaries at creation"; //5
    title[5] = "energy of neutral secondaries at creation"; //6
    title[6] = "NIEL energy deposit"; //8
    title[7] = "dE/dx vs tracklength"; //9    
    int beg = 0;
    int end = 5;
    for (G4int k = nonslice; k < kMaxHisto; k++) {
        title[k] = "dEdx slize " + std::to_string(beg) + " to " + std::to_string(end) + " mm";
        id[k] = std::to_string(k);
        beg = end;
        end = end + 5;
    }

    std::cout << id << std::endl;
    std::cout << title << std::endl;
    // Default values (to be reset via /analysis/h1/set command)
    G4int nbins = 100;
    G4double vmin = 0.;
    G4double vmax = 100.;

    // Create all histograms as inactivated 
    // as we have not yet set nbins, vmin, vmax
    for (G4int k = 0; k < kMaxHisto; k++) {
        G4int ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
        analysisManager->SetH1Activation(ih, false);
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
