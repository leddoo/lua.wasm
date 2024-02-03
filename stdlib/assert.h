void js_unimplemented();

#define assert(x) ((x) ? (void)0 : js_unimplemented())

