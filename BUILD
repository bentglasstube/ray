package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "ray",
    srcs = ["main.cc"],
    deps = [
        ":color",
        ":vec3",
    ],
)

cc_library(
    name = "vec3",
    hdrs = ["vec3.h"],
)

cc_library(
    name = "color",
    hdrs = ["color.h"],
    deps = [":vec3"],
)
