cc_library(
        name = "Ciphertext",
        srcs = [ "Ciphertext.cpp" ],
        hdrs = [ "Ciphertext.hpp" ],
        visibility = [ "//test:__pkg__", ],
)

cc_binary(
        name = "main",
        srcs = [ "main.cpp" ],
        deps = [ ":Ciphertext" ],
)
