package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    deps = [
        ":camera",
        ":color",
        ":hittable",
        ":ray",
        ":sphere",
        ":util",
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

cc_library(
    name = "ray",
    hdrs = ["ray.h"],
)

cc_library(
    name = "hittable",
    hdrs = [
        "hittable.h",
        "hittable_list.h",
        "material.h",
    ],
)

cc_library(
    name = "sphere",
    hdrs = ["sphere.h"],
    deps = [":hittable"],
)

cc_library(
    name = "util",
    hdrs = ["util.h"],
)

cc_library(
    name = "camera",
    hdrs = ["camera.h"],
    deps = [
        ":ray",
        ":util",
    ],
)
