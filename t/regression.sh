#!/bin/bash

./REDonFDTD

diff dimensions2.txt $1/$2
if [[ $? != 0 ]]; then
    exit 1
fi

diff ExXZ.txt $1/$3
if [[ $? != 0 ]]; then
    exit 2
fi

rm -f dimensions2.txt
rm -f ExXZ.txt

exit 0
