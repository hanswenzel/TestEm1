# TestEm1
(slightly) modified version of the Geant4 TestEm1 example to extract quantities of interest to the  protoDune or other liquid Argon TPC experiments.

First make sure that root and geant4 are set up. 
git clone https://github.com/hanswenzel/TestEm1.git
mkdir TestEm1-build 
cd TestEm1-build
cmake ../TestEm1/  -DWITH_GEANT4_UIVIS=ON -DCMAKE_INSTALL_PREFIX=../TestEm1-install
make install
cd ../TestEm1-install/bin/
./TestEm1 protoDune.mac


Then have a look at the histograms in protoDune.root