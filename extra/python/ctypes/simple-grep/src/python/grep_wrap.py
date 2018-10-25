import ctypes

# Cargo el dll
_grepDLL = ctypes.CDLL('build/libsimplegrep.so')
# Configuro la firma de la función
_grepDLL.simple_grep_fd.argtypes = (ctypes.c_int, ctypes.c_char_p)

def grepWrap(file, expr):
    fd = file.fileno()
    result = _grepDLL.simple_grep_fd(ctypes.c_int(fd),
        ctypes.c_char_p(bytes(expr, "UTF-8")))
