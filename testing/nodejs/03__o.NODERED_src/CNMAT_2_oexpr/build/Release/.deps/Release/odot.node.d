cmd_Release/odot.node := ./gyp-mac-tool flock ./Release/linker.lock c++ -bundle -Wl,-search_paths_first -mmacosx-version-min=10.5 -arch x86_64 -L./Release  -o Release/odot.node Release/obj.target/odot//src/o_expr.o Release/obj.target/odot//src/o_expr_addon.o -undefined dynamic_lookup /usr/local/lib/libo.a
