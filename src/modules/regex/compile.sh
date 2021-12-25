# macOS
g++ -std=c++11 -O3 -dynamiclib regex.cpp -o ../../../build/modules/regex/regex.so
sudo cp ../../../build/modules/regex/regex.so /Library/Dinfio/3.1/modules/regex/

# Linux
# g++ -std=c++11 -fPIC -shared regex.cpp -o ../../../build/regex.so
# sudo cp ../../../build/regex.so /usr/local/dinfio/

# Windows
# g++ -std=c++11 -shared src\modules\regex\regex.cpp -o build\regex.dll
