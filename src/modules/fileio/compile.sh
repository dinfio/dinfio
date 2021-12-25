# macOS
g++ -std=c++11 -O3 -dynamiclib fileio.cpp -o ../../../build/modules/fileio/fileio.so
sudo cp ../../../build/modules/fileio/fileio.so /Library/Dinfio/3.1/modules/fileio/

# Linux
# g++ -fPIC -shared fileio.cpp -o ../../../build/fileio.so
# sudo cp ../../../build/fileio.so /usr/local/dinfio/

# Windows
# g++ -shared fileio.cpp -o fileio.dll
