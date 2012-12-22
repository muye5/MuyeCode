cc_library(
    name = 'querybysql',
    srcs = 'querybysql.cc',
    deps = [
        '//mysql/connect:connect'
    ]
)

cc_library(
    name = 'querybygroup',
    srcs = 'querybygroup.cc',
    deps = [
        '//mysql/connect:connect'
    ]
)

cc_library(
    name = 'treequery',
    srcs = 'treequery.cc',
    deps = [
        '//mysql/connect:connect'
    ]
)

cc_library(
    name = 'arrayquery',
    srcs = 'arrayquery.cc',
    deps = [
        '//mysql/connect:connect'
    ]
)

cc_binary(
    name = 'data_init',
    srcs = 'data_init.cc',
    deps = [
        '//mysql/connect:connect'
    ]
)

cc_binary(
    name = 'score_range_init',
    srcs = 'score_range_init.cc',
    deps = [
        '//mysql/connect:connect'
    ]
)

cc_binary(
    name = 'querytest',
    srcs = 'query_test.cc',
    deps = [
        ':querybysql',
        ':querybygroup',
        ':treequery',
        ':arrayquery',
        '#gtest',
        '#pthread'
    ]
)

cc_binary(
    name = 'inserttest',
    srcs = 'insert_test.cc',
    deps = [
        ':querybysql',
        ':querybygroup',
        ':arrayquery',
        ':treequery',
        '#gtest',
        '#pthread'
    ]
)

