# macOS
g++ -std=c++11 -O3 -dynamiclib url.cpp -o ../../../build/modules/url/url.so -lcurl
sudo cp ../../../build/modules/url/url.so /Library/Dinfio/3.1/modules/url/

# Linux
# g++ -fPIC -shared url.cpp -o ../../../build/url.so -lcurl
# sudo cp ../../../build/url.so /usr/local/dinfio/

# Windows
# g++ -shared fileio.cpp -o fileio.dll
