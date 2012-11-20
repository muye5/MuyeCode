
#ifndef _EXAMPLES_H
#define	_EXAMPLES_H

namespace MuyeProperty {
    // Connection properties
#define EXAMPLE_DB   "test"
#define EXAMPLE_HOST "tcp://127.0.0.1:3306"
#define EXAMPLE_USER "muye"
#define EXAMPLE_PASS "muye"

    // Sample data
#define EXAMPLE_NUM_TEST_ROWS 4
    struct _test_data {
        int id;
        const char* label;
    };
    static _test_data test_data[EXAMPLE_NUM_TEST_ROWS] = {
        {1, ""}, {2, "a"}, {3, "b"}, {4, "c"},
    };
} // namespace MuyeProperty

#endif	/* _EXAMPLES_H */

