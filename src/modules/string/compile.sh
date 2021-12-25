# macOS
g++ -std=c++11 -O3 -dynamiclib string.cpp -o ../../../build/modules/string/string.so
sudo cp ../../../build/modules/string/string.so /Library/Dinfio/3.1/modules/string/

# Linux
# g++ -std=c++11 -fPIC -shared string.cpp -o ../../../build/string.so
# sudo cp ../../../build/string.so /usr/local/dinfio/

# Windows
# see ./.vscode/
