# macOS
g++ -std=c++11 -O3 -dynamiclib rl.cpp -o ../../../build/modules/rl/rl.so
sudo cp ../../../build/modules/rl/rl.so /Library/Dinfio/3.1/modules/rl/

# Linux
# g++ -std=c++11 -O3 -fPIC -shared rl.cpp -o ../../../build/modules/rl/rl.so
# sudo cp ../../../build/modules/rl/rl.so /usr/local/dinfio/modules/rl/

# Windows
# g++ -std=gnu++11 -O3 -shared src\modules\rl\rl.cpp -o build\modules\rl\rl.dll
