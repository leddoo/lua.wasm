import sys
import subprocess


args = set(sys.argv[1:])



build_flags = "-O3 -DNDEBUG -flto".split()
if "debug" in args:
    build_flags = "-g".split()


target = "-o main.wasm".split()
if "lto" in args:
    assert False


lua_flags = "-DMAKE_LIB -DLUA_NOCVTS2N".split()


exports = """
    -Wl,--export=c_call_indirect_2
    -Wl,--export=malloc
    -Wl,--export=push_string
    -Wl,--export=push_number
    -Wl,--export=push_boolean
    -Wl,--export=push_nil
    -Wl,--export=do_string
    -Wl,--export=resume
    -Wl,--export=on_event
""".split()

subprocess.run(["clang",
    "--target=wasm32",
    "-D__wasm__", "-D__wasi__",
    "-nostdlib",
    "-std=c11",
    *build_flags,
    *lua_flags,
    *exports,
    *target,
    "-Istdlib",
    "-Imimalloc-1.8.2/include/",
    "-Ilua-5.4.6",
    "stdlib/lib.c",
    "stdlib/snprintf.c",
    "mimalloc-1.8.2/src/alloc.c",
    "mimalloc-1.8.2/src/alloc-aligned.c",
    "mimalloc-1.8.2/src/alloc-posix.c",
    "mimalloc-1.8.2/src/arena.c",
    "mimalloc-1.8.2/src/bitmap.c",
    "mimalloc-1.8.2/src/heap.c",
    "mimalloc-1.8.2/src/init.c",
    "mimalloc-1.8.2/src/options.c",
    "mimalloc-1.8.2/src/os.c",
    "mimalloc-1.8.2/src/page.c",
    "mimalloc-1.8.2/src/random.c",
    "mimalloc-1.8.2/src/segment.c",
    "mimalloc-1.8.2/src/segment-map.c",
    "mimalloc-1.8.2/src/stats.c",
    "mimalloc-1.8.2/src/prim/prim.c",
    "lua-5.4.6/onelua.c",
])


