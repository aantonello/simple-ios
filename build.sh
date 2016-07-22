#!/bin/bash

BUILD_DIR=$PWD/build
OUTDIR="OBJROOT=$BUILD_DIR SYMROOT=$BUILD_DIR DSTROOT=$BUILD_DIR"
PROJECT=Simple.xcodeproj

if [ "$1" = "clean" ]; then
    rm -fR build
    rm ./build.log
elif [ "$1" = "release" ]; then
    xcodebuild -project $PROJECT -configuration Release -sdk iphonesimulator install $OUTDIR
    xcodebuild -project $PROJECT -configuration Release -sdk iphoneos install $OUTDIR
else
    xcodebuild -project $PROJECT -configuration Debug -sdk iphonesimulator $OUTDIR
    xcodebuild -project $PROJECT -configuration Debug -sdk iphoneos $OUTDIR
fi
