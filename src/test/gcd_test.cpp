#ifdef _TEST
#include "gcd_test.h"

// public functions
GCDTest::GCDTest ()
{
  m_result = 0;
  m_expected = 0;
}

bool
GCDTest::test_cases ()
{
  std::cout << "---------------------------------" << std::endl;
  std::cout << "Starting GCD Test" << std::endl;
  std::cout << "---------------------------------" << std::endl;
  std::vector<bool> passed;
  passed.push_back (test_gcd ());
  passed.push_back (test_length_1 ());
  passed.push_back (test_length_2 ());
  passed.push_back (test_length_3 ());
  passed.push_back (test_length_4 ());
  passed.push_back (test_length_5 ());
  passed.push_back (test_length_8 ());
  return asserter.check_asserts (passed, 7);
}

GCDTest::~GCDTest ()
{

}

// private functions
bool
GCDTest::test_gcd ()
{
  std::vector<uint16_t> values;
  m_result = Calculation::gcd (4, 8);
  m_expected = 4;
  std::cout << "\nTest single GCD: " << "\nExpected: " << m_expected
      << "\tResult: " << m_result << std::endl;
  return asserter.assert (m_expected, m_result);
}
bool
GCDTest::test_length_1 ()
{
  std::vector<uint16_t> values;
  values.push_back (8);
  m_expected = 8;
  m_result = Calculation::gcd_vector (values, 0, values.size ());
  std::cout << "\nTest GCD list of length 1: " << "\nExpected: " << m_expected
      << "\tResult: " << m_result << std::endl;
  return asserter.assert (m_expected, m_result);
}
bool
GCDTest::test_length_2 ()
{
  std::vector<uint16_t> values;
  values.push_back (8);
  values.push_back (6);
  m_expected = 2;
  m_result = Calculation::gcd_vector (values, 0, values.size ());
  std::cout << "\nTest GCD list of length 2: " << "\nExpected: " << m_expected
      << "\tResult: " << m_result << std::endl;
  return asserter.assert (m_expected, m_result);
}
bool
GCDTest::test_length_3 ()
{
  std::vector<uint16_t> values;
  values.push_back (9);
  values.push_back (81);
  values.push_back (27);
  m_expected = 9;
  m_result = Calculation::gcd_vector (values, 0, values.size ());
  std::cout << "\nTest GCD list of length 3: " << "\nExpected: " << m_expected
      << "\tResult: " << m_result << std::endl;
  return asserter.assert (m_expected, m_result);
}
bool
GCDTest::test_length_4 ()
{
  std::vector<uint16_t> values;
  values.push_back (15);
  values.push_back (30);
  values.push_back (66);
  values.push_back (100);
  m_expected = 1;
  m_result = Calculation::gcd_vector (values, 0, values.size ());
  std::cout << "\nTest GCD list of length 4: " << "\nExpected: " << m_expected
      << "\tResult: " << m_result << std::endl;
  return asserter.assert (m_expected, m_result);
}
bool
GCDTest::test_length_5 ()
{
  std::vector<uint16_t> values;
  values.push_back (15);
  values.push_back (21);
  values.push_back (9);
  values.push_back (12);
  values.push_back (3);
  m_expected = 3;
  m_result = Calculation::gcd_vector (values, 0, values.size ());
  std::cout << "\nTest GCD list of length 5: " << "\nExpected: " << m_expected
      << "\tResult: " << m_result << std::endl;
  return asserter.assert (m_expected, m_result);
}
bool
GCDTest::test_length_8 ()
{
  std::vector<uint16_t> values;
  values.push_back (16);
  values.push_back (8);
  values.push_back (12);
  values.push_back (4);
  values.push_back (18);
  values.push_back (9);
  values.push_back (81);
  values.push_back (243);
  m_expected = 1;
  m_result = Calculation::gcd_vector (values, 0, values.size ());
  std::cout << "\nTest GCD list of length 8: " << "\nExpected: " << m_expected
      << "\tResult: " << m_result << std::endl;
  return asserter.assert (m_expected, m_result);
}
#endif
