#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <vector>
#include <functional>

class Employees {
public:
    std::vector<double> salaries;

    std::vector<double> HighEarners(std::function<bool(double)> filter) {
        std::vector<double> result;
        for (double salary : salaries) {
            if (filter(salary)) {
                result.push_back(salary);
            }
        }
        return result;
    }
};

class EmployeesTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(EmployeesTest);
    CPPUNIT_TEST(testHighEarners);
    CPPUNIT_TEST(testHighEarnersEmpty);
    CPPUNIT_TEST(testHighEarnersNone);
    CPPUNIT_TEST_SUITE_END();

public:
    void testHighEarners() {
        Employees employees;
        employees.salaries = {50000, 75000, 100000, 120000, 30000};
        auto result = employees.HighEarners([](double salary) { return salary > 75000; });
        CPPUNIT_ASSERT_EQUAL(size_t(2), result.size());
        CPPUNIT_ASSERT_EQUAL(100000.0, result[0]);
        CPPUNIT_ASSERT_EQUAL(120000.0, result[1]);
    }

    void testHighEarnersEmpty() {
        Employees employees;
        employees.salaries = {};
        auto result = employees.HighEarners([](double salary) { return salary > 75000; });
        CPPUNIT_ASSERT_EQUAL(size_t(0), result.size());
    }

    void testHighEarnersNone() {
        Employees employees;
        employees.salaries = {30000, 40000, 50000};
        auto result = employees.HighEarners([](double salary) { return salary > 75000; });
        CPPUNIT_ASSERT_EQUAL(size_t(0), result.size());
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(EmployeesTest);