rmdir /s /q build
mkdir build
pushd build
call emcmake cmake ..
popd