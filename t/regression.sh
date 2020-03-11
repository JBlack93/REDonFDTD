#!/bin/bash

./REDonFDTD

diff output/ExXY10.txt $1/$2
if [[ $? != 0 ]]; then
    exit 1
fi

diff output/ExXY25.txt $1/$3
if [[ $? != 0 ]]; then
    exit 2
fi

rm -rf output

exit 0
