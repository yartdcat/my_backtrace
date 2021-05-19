#!/bin/bash

cd ..
export PATH="`pwd`/../depot_tools:$PATH"
./out/test/ly_test
