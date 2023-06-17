cc_library(
    name = "rational",
    srcs = ["rational.cc"],
    hdrs = ["rational.h"],
)

cc_test(
    name = "rational_test",
    srcs = ["rational_test.cc"],
    deps = [
        ":rational",
        "@catch2//:catch2_main",
    ],
)
