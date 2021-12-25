# macOS
g++ -std=c++11 -dynamiclib -O3 math.cpp -o ../../../build/modules/math/math.so
sudo cp ../../../build/modules/math/math.so /Library/Dinfio/3.1/modules/math/

# Linux
# g++ -fPIC -shared math.cpp -o ../../../build/math.so
# sudo cp ../../../build/math.so /usr/local/dinfio/

# Windows
# g++ -shared math.cpp -o math.dll
