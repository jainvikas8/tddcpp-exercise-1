


    c_buffer_tests = executable(
      'c_buffer_tests', sources
      : [ 'test_main.cpp', 'buffer_tests.cpp', src ], include_directories
      : inc, dependencies
      : [ gtest_dep, thread_dep ])



test('buffer_tests', c_buffer_tests)
