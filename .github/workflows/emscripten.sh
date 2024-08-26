sudo apt-get update && sudo apt-get install git -y
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest