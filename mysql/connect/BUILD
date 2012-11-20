cc_library(
    name = 'connect',
    srcs = 'connect.cc',
    deps = [
        '#mysqlcppconn',
    ]
)

cc_binary(
    name = 'test',
    srcs = 'connect_test.cc',
    deps = [
        ':connect',
    ]
)
