#include <tcframe/spec.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, Q;
    vector<int> V, T;
    const int MAX_V = 1000, MAX_T = 1000;
    const int MAX_N = 300000, MAX_Q = 300000;
    vector<int> query;
    vector<int> result;

    void InputFormat() {
        LINE(N, Q);
        LINES(V, T) % SIZE(N);
        LINE(query % SIZE(Q));
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
        CONS(eachElementBetween(V, 1, MAX_V));
        CONS(eachElementBetween(T, 1, MAX_T));
        CONS(eachElementBetween(query, 1, N));
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
            "6 3",
            "1 2",
            "1 3",
            "3 1",
            "4 5",
            "3 1",
            "1 1",
            "3 4 1"
        });
        Output({
            "2",
            "1",
            "1"
        });
    }

    void BeforeTestCase(){
        V.clear();
        T.clear();
        query.clear();
    }

    void TestCases() {
        CASE(N = 1; Q = 1; randomArray(10,10); randomQuery());
        CASE(N = 1; Q = 1; randomArray(); randomQuery());
        CASE(N = 10; Q = 10; randomArray(); randomQuery());
        CASE(N = 10; Q = 10; randomArray(10, 10); uniqueQuery());
        
        CASE(N = MAX_N; Q = MAX_Q; randomArray(); allQuery());
        CASE(N = MAX_N; Q = MAX_Q; randomArray(10, 10); allQuery());
        CASE(N = 100; Q = 100; randomArray(10, 10); allQuery());
        CASE(N = 10000; Q = 10000; randomArray(100, 100); allQuery());

        CASE(N = 1; Q = 1; uniqueArray(10,10); randomQuery());
        CASE(N = 10; Q = 10; uniqueArray(); allQuery());
        CASE(N = 299209; Q = 10; allArray(547, 547); randomQuery());
        
        CASE(N = MAX_N; Q = MAX_Q; uniqueArray(); allQuery());
        CASE(N = 100; Q = 100; allArray(10, 10); uniqueQuery());
        CASE(N = 10000; Q = 10000; uniqueArray(100, 100); randomQuery());
        CASE(N = MAX_N; Q = 10000; allArray(600, 500); uniqueQuery());
        CASE(N = MAX_N; Q = MAX_Q; allArray(600, 500); allQuery());
        CASE(N = 299209; Q = 299209; allArray(547, 547); allQuery());

    }
private:
    void randomArray(int limitV = 1000, int limitT = 1000){
        for(int i = 0; i < N; ++i){
            V.push_back(rnd.nextInt(1, limitV));
            T.push_back(rnd.nextInt(1, limitT));
        }
    }

    void uniqueArray(int limitV = 1000, int limitT = 1000){
        map<pair<int,int>,bool> MAP; 
        for(int i = 0; i < N; ++i){
            int Vnow = rnd.nextInt(1, limitV);
            int Tnow = rnd.nextInt(1, limitT);
            while(MAP.count(make_pair(Vnow, Tnow))){
                Vnow = rnd.nextInt(1, limitV);
                Tnow = rnd.nextInt(1, limitT);
            }
            MAP[make_pair(Vnow, Tnow)] = 1;
            V.push_back(Vnow);
            T.push_back(Tnow);
        }
        MAP.clear();
    }

    void allArray(int limitV, int limitT){
        assert(limitV * limitT == N);
        for(int i = 1;i <= limitV; ++i){
            for(int j = 1;j <= limitT; ++j){
                V.push_back(i);
                T.push_back(j);
            }
        }
    }
    void randomQuery(){
        for(int i = 0;i < Q; ++i){
            query.push_back(rnd.nextInt(1, N));
        }
        if(rnd.nextInt(3)) random_shuffle(query.begin(), query.end());
    }

    void uniqueQuery(){
        map<int, bool> MAP;
        for(int i = 0;i < Q; ++i){
            int Qnow = rnd.nextInt(1, N);
            while(MAP.count(Qnow)){
                Qnow = rnd.nextInt(1, N);
            }
            MAP[Qnow] = 1;
            query.push_back(Qnow);
        }
        MAP.clear();
        if(rnd.nextInt(3)) random_shuffle(query.begin(), query.end());
    }

    void allQuery(){
        assert(Q == N);
        for(int i = 0;i < Q; ++i){
            query.push_back(i+1);
        }
        if(rnd.nextInt(4)) random_shuffle(query.begin(), query.end());
    }
};