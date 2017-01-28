#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    string A;
    int B;
    int ans;

    void InputFormat() {
        LINE(A);
        LINE(B);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= A.size() && A.size() <= 100000);
        CONS(1 <= B && B <= 1000000000);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
      Input({
        "4\n2"
      });
      Output({
        "0"
      });
    }
    void SampleTestCase2() {
      Input({
        "15\n4"
      });
      Output({
        "3"
      });
    }
    void SampleTestCase3() {
      Input({
        "19837409812374182379234\n1003"
      });
      Output({
        "70"
      });
    }

    void TestCases() {
        CASE(A = "1", B = 1);
        CASE(A = "0", B = 109764);
        CASE(A = "0", B = 1);
        CASE(A = "1000", B = 1000);
        CASE(A = "42", B = 100);
        CASE(A = "123123", B = 123);
        for (int i = 0; i < 5; i++) {
          CASE(generate(generate_length()), B = rnd.nextInt(900000000, 1000000000));
        }
        for (int i = 0; i < 35; i++) {
          CASE(generate(generate_length()), B = rnd.nextInt(1, 1000000000));
        }
    }
private:
  int generate_length() {
    return rnd.nextInt(1, 100000);
  }
  void generate(int n) {
    A.clear();
    A.push_back('0' + rnd.nextInt(1, 9));
    for (int i = 1; i < n; i++) {
      A.push_back('0' + rnd.nextInt(0, 9));
    }
  }
};
