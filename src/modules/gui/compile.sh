# macOS
# g++ -std=c++11 -O3 -dynamiclib gui.cpp -o ../../../build/modules/gui/gui.so -I/Users/faruq/Documents/Dinfio/resources/wxwidgets/lib/lib/wx/include/osx_cocoa-unicode-3.1 -I/Users/faruq/Documents/Dinfio/resources/wxwidgets/lib/include/wx-3.1 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__ -L/Users/faruq/Documents/Dinfio/resources/wxwidgets/lib/lib -framework IOKit -framework Carbon -framework Cocoa -framework AudioToolbox -framework System -framework OpenGL -lwx_osx_cocoau_core-3.1 -lwx_baseu-3.1

g++ -std=c++11 -O3 -dynamiclib gui.cpp -o ../../../build/modules/gui/gui.so -I/Users/faruq/Documents/Resources/wxwidgets/lib/lib/wx/include/osx_cocoa-unicode-3.1 -I/Users/faruq/Documents/Resources/wxwidgets/lib/include/wx-3.1 -D_FILE_OFFSET_BITS=64 -DWXUSINGDLL -D__WXMAC__ -D__WXOSX__ -D__WXOSX_COCOA__ -L/Users/faruq/Documents/Resources/wxwidgets/lib/lib -framework IOKit -framework Cocoa -framework System -lwx_osx_cocoau_core-3.1 -lwx_baseu-3.1
sudo cp ../../../build/modules/gui/gui.so /Library/Dinfio/3.1/modules/gui/

# Linux
# g++ -std=c++11 -fPIC -shared gui.cpp -o ../../../build/gui.so `wx-config --cxxflags --libs`
# sudo cp ../../../build/gui.so /usr/local/dinfio/

# Windows
# see ./.vscode/
