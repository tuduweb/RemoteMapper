function(OBCFOUNDATION_ADD_TEST TEST_NAME TEST_SOURCE)
    add_executable(${TEST_NAME} ${TEST_SOURCE} catch.hpp ${OBCFOUNDATION_SOURCES})
    target_include_directories(${TEST_NAME}
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        )
    target_link_libraries(
        ${TEST_NAME}
        PRIVATE
        Qt::Core
        )
    add_test(NAME OBCFOUNDATION_TEST_${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}> -s)

    #set_tests_properties(OBCFOUNDATION_TEST_${TEST_NAME} PROPERTIES PASS_REGULAR_EXPRESSION 5)
endfunction()

OBCFOUNDATION_ADD_TEST(converter convert/main.cpp)

#find_package(Catch2 2.3.0 REQUIRED)
