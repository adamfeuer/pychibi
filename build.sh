#!/bin/bash

BUILD='build'
BASE_URL='http://abrek.synthcode.com'
RELEASE='chibi-scheme-0.7'
EXTENSION='tgz'
RELEASE_FILE="$RELEASE.$EXTENSION"
if [ ! -e $RELEASE_FILE ]; then
        wget "$BASE_URL/$RELEASE_FILE"
fi
if [ ! -e $RELEASE ]; then
        tar zxf $RELEASE_FILE
fi
pushd $RELEASE
make PREFIX="$(pwd)/$BUILD" install 
popd
python setup.py install
FILE=$(find $BUILD -iname '_chibi_scheme.so')
cp $FILE .
