cmd_Release/o_flattenexplode.node := ./gyp-mac-tool flock ./Release/linker.lock c++ -bundle -Wl,-search_paths_first -mmacosx-version-min=10.5 -arch x86_64 -L./Release  -o Release/o_flattenexplode.node Release/obj.target/o_flattenexplode/o_flattenexplode.o -undefined dynamic_lookup /usr/local/lib/libo.a
