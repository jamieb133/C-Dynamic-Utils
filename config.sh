#!bin/bash

BUILD_DIR="build"

if [ ! -d "$BUILD_DIR" ]; then
    echo "Creating build directory..."
    mkdir $BUILD_DIR
fi

cd $BUILD_DIR
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

# Copy the json file so that the LSP gets the include dirs, flags etc.
cp compile_commands.json ..
