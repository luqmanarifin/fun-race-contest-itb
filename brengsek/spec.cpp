#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, X;
    vector<int> A;
    int ans;

    void InputFormat() {
        LINE(N, X);
        LINE(A);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= 100);
        CONS(0 <= X && X <= 1000);
        CONS(A.size() == N);
        CONS(eachElementBetween(A, 0, 100));
    }

private:
  bool eachElementBetween(const vector<int> &A, int lo, int hi) {
    for (int it : A) {
      if (it < lo || it > hi) {
        return false;
      }
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "5 10",
            "0 8 13 3 1"
        });
        Output({
            "3"
        });
    }

    void TestCases() {
      CASE(N = 100, X = 0, uniformArray(N, 0));
      CASE(N = 100, X = 0, uniformArray(N, 100));
      CASE(N = 100, X = 1000, uniformArray(N, 0));
      CASE(N = 100, X = 1000, uniformArray(N, 100));
      CASE(N = 100, X = 1000, uniformArray(N, 47));
      for (int i = 0; i < 30; i++) {
        CASE(N = rnd.nextInt(1, 100), X = rnd.nextInt(0, 1000), randomArray(N, 0, 100));
      }
    }
private:
  void randomArray(int size, int L = 1, int R = 100000) {
    A.clear();
    for (int i = 0; i < size; i++) {
      A.push_back(rnd.nextInt(L, R));
    }
  }

  void uniformArray(int size, int value) {
    A.assign(size, value);
  }
};
