#include <tcframe/spec.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<int> U, V, C;
    int Q;
    vector<int> X, W;
    vector<int> result;
    const int MAX_N = 1000, MAX_Q = 100000, MAX_C = 1000;

    void InputFormat() {
        LINE(N);
        LINE(C % SIZE(N));
        LINES(U, V) % SIZE(N - 1);
        LINE(Q);
        LINES(X, W) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(result) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(1 <= N && N <= MAX_N);
        CONS(1 <= Q && Q <= MAX_Q);
        /*CONS(U.size() == N-1);
        CONS(V.size() == N-1);
        CONS(C.size() == N);
        CONS(X.size() == Q);
        CONS(W.size() == Q);
        */
        CONS(eachElementBetween(U, 1, N));
        CONS(eachElementBetween(V, 1, N));
        CONS(eachElementBetween(C, 1, MAX_C));
        CONS(eachElementBetween(X, 1, N));
        CONS(eachElementBetween(W, 1, MAX_C));
        //CONS(isTree(U, V));
    }
private:
    bool eachElementBetween(const vector<int> &V, int lo, int hi){
        for(int v : V){
            if(v < lo || v > hi){
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
            "4",
            "1 5 2 5",
            "1 3",
            "3 4",
            "3 2",
            "3",
            "1 1",
            "3 5",
            "2 5"
        });
        Output({
            "1",
            "2",
            "1"
        });
    }

    void BeforeTestCase(){
        U.clear();
        V.clear();
        C.clear();
        W.clear();
        X.clear();
    }

    void TestCases() {
        CASE(N = 1; Q = 1; randomColor(); randomTree(); randomQuery());
        CASE(N = MAX_N; Q = MAX_Q; randomColor(); randomTree(); randomQuery());
        CASE(N = MAX_N; Q = 1; randomColor(); randomTree(); randomQuery());
        CASE(N = MAX_N; Q = 1000; randomColor(); randomTree(); randomQuery());
        CASE(N = MAX_N; Q = MAX_Q; randomColor(); linearTree(); randomQuery()); 
        CASE(N = MAX_N; Q = 1000; randomColor(); linearTree(); randomQuery()); 
        CASE(N = MAX_N; Q = MAX_Q; randomColor(); linearTree(); allExistedColorQuery()); 

        CASE(N = MAX_N; Q = MAX_Q; allSameColor(); linearTree(); randomQuery());
        CASE(N = MAX_N; Q = MAX_Q; allSameColor(); randomTree(); randomQuery());
        CASE(N = 100; Q = 100; allSameColor(); linearTree(); randomQuery());
        CASE(N = MAX_N; Q = MAX_Q; allSameColor(); linearTree(); randomQuery());
        CASE(N = MAX_N; Q = MAX_Q; halfAllSameColor(); linearTree(); randomQuery());
        CASE(N = 100; Q = 100; halfAllSameColor(); randomTree(); randomQuery());
        CASE(N = 100; Q = 100; halfAllSameColor(); linearTree(); randomQuery());

        CASE(N = 100; Q = 100; allSameColor(); linearTree(); allExistedColorQuery());
        CASE(N = MAX_N; Q = MAX_Q; allSameColor(); linearTree(); allExistedColorQuery());
        CASE(N = MAX_N; Q = MAX_Q; halfAllSameColor(); linearTree(); allExistedColorQuery());
        CASE(N = MAX_N; Q = MAX_Q; halfAllSameColor(); randomTree(); allExistedColorQuery());
        CASE(N = 100; Q = MAX_Q; halfAllSameColor(); randomTree(); allExistedColorQuery());
        CASE(N = 450; Q = 500; halfAllSameColor(); randomTree(); allExistedColorQuery());

        CASE(N = MAX_N; Q = MAX_N; allSameColor(); linearTree(); allNodeSameColorQuery());
        CASE(N = MAX_N; Q = MAX_N; allSameColor(); randomTree(); allNodeSameColorQuery());
        CASE(N = 100; Q = 100; allSameColor(); linearTree(); allNodeSameColorQuery());
        CASE(N = 10; Q = 10; allSameColor(); linearTree(); allNodeSameColorQuery());

        CASE(N = 100; Q = 100; allSameColor(); randomTree(); allNodeSameColorQuery());
        CASE(N = 10; Q = 10; allSameColor(); randomTree(); allNodeSameColorQuery());
    }
private:
    void randomColor(){
        for(int i = 0;i < N; ++i) C.push_back(rnd.nextInt(1, MAX_C));
    }
    
    void allSameColor(){
        int clr = rnd.nextInt(1, MAX_C);
        for(int i = 0;i < N; ++i) C.push_back(clr);
    }

    void halfAllSameColor(){
        int divide = rnd.nextInt(1, (int)sqrt(N));
        for(int i = 0;i < divide; ++i){
            C.push_back(rnd.nextInt(1, MAX_C));
        }
        for(int i = divide; i < N; ++i) C.push_back(C[i%divide]);
        random_shuffle(C.begin(), C.end());
    }

    void randomTree(){
        for(int i = 2;i <= N; ++i){
            U.push_back(i);
            V.push_back(rnd.nextInt(1, i-1));
        }
        if(N == 1) return;
        int n_shuf = rnd.nextInt(0, N);
        for(int i = 0; i < n_shuf; ++i){
            int idx_1 = rnd.nextInt(0, N-2);
            int idx_2 = rnd.nextInt(0, N-2);
            swap(U[idx_1], U[idx_2]);
            swap(V[idx_1], V[idx_2]);
            if(rnd.nextInt(3)){
                swap(U[idx_1], V[idx_1]);
            }
        }
    }

    void linearTree(){
        for(int i = 2;i <= N; ++i){
            U.push_back(i);
            V.push_back(i-1);
            if(rnd.nextInt(6) > 4) swap(U.back(), V.back());
        }
    }
    void randomQuery(){
        vector<int> ve(C);
        sort(ve.begin(), ve.end());
        ve.resize(unique(ve.begin(), ve.end()) - ve.begin());
        int SAIZ = ve.size();
        for(int i = 0;i < Q; ++i){
            if(rnd.nextInt(100) > 90){
                W.push_back(rnd.nextInt(1, MAX_C));
            }
            else{
                int idx = rnd.nextInt(SAIZ);
                W.push_back(ve[idx]);
            }
            X.push_back(rnd.nextInt(1, N));
        }
    }

    void allExistedColorQuery(){
        vector<int> ve(C);
        sort(ve.begin(), ve.end());
        ve.resize(unique(ve.begin(), ve.end()) - ve.begin());
        int SAIZ = ve.size();
        for(int i = 0;i < Q; ++i){
            int idx = rnd.nextInt(SAIZ);
            W.push_back(ve[idx]);
            X.push_back(rnd.nextInt(1, N));
        }
    }

    void allNodeSameColorQuery(){
        assert(N == Q);
        int clr = C.back();
        for(int i = 1;i <= N; ++i){
            W.push_back(clr);
            X.push_back(i);
        }
        random_shuffle(X.begin(),X.end());
    }
};