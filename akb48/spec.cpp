#include "tcframe/spec.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class ProblemSpec : public BaseProblemSpec {
	protected:
		const int MAXN = 3e5;
		const int MAXV = 1e9;
		const int MAXQ = 3e5;
		int N, Q;
		vector<int> ar;
		vector<int> op;
		vector<vector<int> > data;
		vector<int> res;
		int N_result;
		void InputFormat() {
			LINE(N);
			LINE(ar % SIZE(N));
			LINE(Q);
			LINES(op, data) % SIZE(Q);
		}

		void OutputFormat() {
			LINES(res);
		}

		void Constraints(){
			CONS(1 <= N && N <= MAXN);
			CONS(1 <= Q && Q <= MAXQ);
			CONS(eachElementBetween(op, 1, 2));
			CONS(eachElementBetween(data, 1, MAXV));
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
		bool eachElementBetween(const vector<vector<int> > &A, int lo, int hi){
			for(vector<int> vit: A){
				for(int it : vit){
					if(it < lo || it > hi){
						return false;
					}
				}
			}
			return true;
		}

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
	protected:
		void GradingConfig() {
			TimeLimit(1);
			MemoryLimit(64);
		}

		void SampleTestCase1() {
			Input({"5", "1 2 3 4 5", "3", "2 3", "1 2 4", "2 3"});
			Output({"3", "4"});
		}

		void SampleTestCase2(){
			Input({"6", "6 5 4 3 2 1", "3", "2 4", "1 5 7", "2 4"});
			Output({"6", "6"});
		}

		void BeforeTestCase(){
			ar.clear();
			op.clear();
			data.clear();
		}
		void TestCases(){
			CASE(N = 1; Q = 1; randomArray(); randomQuery());
			CASE(N = MAXN; Q = MAXQ; randomArray(); randomQuery());
			CASE(N = 1000; Q = 1000; randomArray(); randomQuery());
			CASE(N = 1000; Q = 1000; increasingArray(); randomQuery());
			CASE(N = MAXN; Q = 5000; increasingArray(); randomQuery());
			CASE(N = 5000; Q = MAXQ; increasingArray(); randomQuery());
			CASE(N = MAXN; Q = MAXQ; increasingArray(); randomQuery());
			CASE(N = 1000; Q = 1000; decreasingArray(); randomQuery());
			CASE(N = MAXN; Q = 5000; decreasingArray(); randomQuery());
			CASE(N = 5000; Q = MAXQ; decreasingArray(); randomQuery());
			CASE(N = MAXN; Q = MAXQ; decreasingArray(); randomQuery());
		}	
		void AfterTestCase(){
			N_result = 0;
			for(int i = 0;i < (int)op.size(); ++i){
				if(op[i] == 2){
					N_result++;
				}
			}
		}

	private:

		void randomArray() {
			for (int i = 0; i < N; i++) {
				ar.push_back(rnd.nextInt(1, MAXV));
			}
		}

		void increasingArray(){
			int now = 1;
			for(int i = 0;i < N; ++i){
				ar.push_back(rnd.nextInt(now, (MAXV/N) * (i + 1)));
				now = ar.back() + 1;
			}
		}

		void decreasingArray(){
			int now = MAXV;
			for(int i = 0;i < N; ++i){
				ar.push_back(rnd.nextInt(N-i, now));
				now = ar.back() - 1;
			}
		}

		void randomQuery(){
			vector<int> ve(ar);
			for(int i = 0; i < Q; ++i){
				op.push_back(rnd.nextInt(2) + 1);
				vector<int> v;
				if(op.back() == 2){
					v.push_back(rnd.nextInt(1, N));
				}		
				else{
					int idx;
					while(idx = rnd.nextInt(1, N), ve[idx-1] == MAXV); // do nothing
					int _new = rnd.nextInt(ve[idx-1]+1, min(MAXV, ve[idx-1]+(MAXV / Q)));
					v.push_back(idx);
					v.push_back(_new);
					ve[idx-1] = _new;
				}
				data.push_back(v);
				v.clear();
			}
			ve.clear();
		}
};