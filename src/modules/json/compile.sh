# macOS
g++ -std=c++11 -O3 -dynamiclib json.cpp -o ../../../build/modules/json/json.so
sudo cp ../../../build/modules/json/json.so /Library/Dinfio/3.1/modules/json/

# Linux
# g++ -std=c++11 -O3 -fPIC -shared json.cpp -o ../../../build/json.so
# sudo cp ../../../build/json.so /usr/local/dinfio/

# Windows
# g++ -std=c++11 -O3 -shared src\modules\json\json.cpp -o build\json.dll
