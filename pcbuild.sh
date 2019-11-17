mkdir cmake-build-debug
cd cmake-build-debug
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ..
cmake --build . --target v5Craft -- -j 12
