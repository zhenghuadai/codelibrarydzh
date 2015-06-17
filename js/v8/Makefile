CCFLAGS=-Wl,--end-group -ldl -lrt  \
		-DCR_CLANG_REVISION=238013-3  -Wshorten-64-to-32 -Wnon-virtual-dtor \
		-DV8_TARGET_ARCH_X64 -DENABLE_GDB_JIT_INTERFACE -DV8_DEPRECATION_WARNINGS \
		-DV8_I18N_SUPPORT -DU_USING_ICU_NAMESPACE=0 -DU_echoENABLE_DYLOAD=0 \
		-DU_STATIC_IMPLEMENTATION -DENABLE_HANDLE_ZAPPING \
		-I. -I./include/icu \
		-Wall -Werror -Wno-unused-parameter -Wno-long-long  \
		-Wno-missing-field-initializers -Wno-format-pedantic \
		-pthread -pedantic \
		-m64 -fdata-sections -ffunction-sections -O3 -fdata-sections  -fno-exceptions -fno-rtti -std=gnu++0x  \
		-pthread -fuse-ld=gold 
CXX=clang++
CXX= /home/david/.subversion/google/v8/third_party/llvm-build/Release+Asserts/bin/clang++ 
V8Libs=  -licui18n -licuuc -lv8_base -lv8_libbase -licudata  -lv8_snapshot -L./libs 
hello-world:hello-world.cc
	$(CXX)   -o $@ -Wl,--start-group $^  -lv8_libplatform  $(V8Libs)  $(CCFLAGS) 
