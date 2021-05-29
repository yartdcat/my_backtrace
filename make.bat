set DEPOT_TOOLS_WIN_TOOLCHAIN=0
set GYP_MSVS_VERSION=2017
set GYP_MSVS_OVERRIDE_PATH=D:\soft\vs2017
gn gen --ide=vs2017 --filters=//test:ly_test out/test --args="is_debug = true enable_nacl = false target_cpu = \"x86\" use_jumbo_build = true root_extra_deps=[\"//test:ly_test\"]"
