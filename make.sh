#!/bin/bash

cd ..
export PATH="`pwd`/../depot_tools:$PATH"
if [ "$1" == "re" ];then
  gn gen out/test --args='root_extra_deps=["//test:ly_test"]'
fi
ninja -C out/test ly_test
