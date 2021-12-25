# macOS
g++ -std=c++11 -dynamiclib -O3 time.cpp -o ../../../build/modules/time/time.so
sudo cp ../../../build/modules/time/time.so /Library/Dinfio/3.1/modules/time/

# Linux
# g++ -fPIC -shared math.cpp -o ../../../build/math.so
# sudo cp ../../../build/math.so /usr/local/dinfio/

# Windows
# g++ -std=c++11 -O3 -shared -D _WIN32_WINNT=0x0501 src\modules\time\time.cpp -o build\modules\time\time.dll
