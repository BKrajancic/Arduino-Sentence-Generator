export LLVM="/usr/local/opt/llvm/bin"
export BINARYEN="/usr/local/opt/binaryen/bin"
emcc main.cpp -o hello.html -std=c++17  --shell-file shell_minimal.html -s ASSERTIONS=1 -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall']"
emrun --no_browser --port 80 .