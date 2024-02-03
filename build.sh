mkdir -p build
cd build

    #-Wl,--export-all \
    #-O1 \
    #-g \

/opt/homebrew/Cellar/llvm/16.0.6/bin/clang \
    --target=wasm32 \
    -O3 -DNDEBUG -flto \
    -nostdlib \
    -std=c11 \
    -Wl,--export=c_call_indirect_2 \
    -Wl,--export=malloc \
    -Wl,--export=push_string \
    -Wl,--export=push_number \
    -Wl,--export=push_boolean \
    -Wl,--export=push_nil \
    -Wl,--export=do_string \
    -Wl,--export=resume \
    -Wl,--export=on_event \
    -D__wasm__ -D__wasi__ \
    -DMAKE_LIB -DLUA_NOCVTS2N \
    -o main.wasm \
    -I../stdlib \
    -I../mimalloc-1.8.2/include/ \
    -I../lua-5.4.6 \
    ../stdlib/lib.c \
    ../stdlib/snprintf.c \
    ../mimalloc-1.8.2/src/alloc.c \
    ../mimalloc-1.8.2/src/alloc-aligned.c \
    ../mimalloc-1.8.2/src/alloc-posix.c \
    ../mimalloc-1.8.2/src/arena.c \
    ../mimalloc-1.8.2/src/bitmap.c \
    ../mimalloc-1.8.2/src/heap.c \
    ../mimalloc-1.8.2/src/init.c \
    ../mimalloc-1.8.2/src/options.c \
    ../mimalloc-1.8.2/src/os.c \
    ../mimalloc-1.8.2/src/page.c \
    ../mimalloc-1.8.2/src/random.c \
    ../mimalloc-1.8.2/src/segment.c \
    ../mimalloc-1.8.2/src/segment-map.c \
    ../mimalloc-1.8.2/src/stats.c \
    ../mimalloc-1.8.2/src/prim/prim.c \
    ../lua-5.4.6/onelua.c

