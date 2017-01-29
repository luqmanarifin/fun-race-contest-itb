#include "tcframe/spec.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

class ProblemSpec : public BaseProblemSpec {
	protected:
		const int MAX_LEN = 3e5;
		int N;
		string s;
		int result;
		void InputFormat() {
			LINE(s);
		}

		void OutputFormat() {
			LINE(result);
		}

		void Constraints(){
			CONS(1 <= s.length() && s.length() <= MAX_LEN);
			CONS(eachElementValid(s));
		}

	private:
		bool eachElementValid(const string &s){
			int len = s.length();
			for(int i = 0;i < len; ++i){
				if(s[i] != '*' && s[i] != '0' && s[i] != '1' && s[i] != '2' && s[i] != '?') return false; 
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
			Input({"*2*?"});
			Output({"2"});
		}

		void SampleTestCase2(){
			Input({"*2*1??"});
			Output({"2"});
		}

		void SampleTestCase3(){
			Input({"???"});
			Output({"8"});
		}

		void BeforeTestCase(){
			s = "";
		}
		void TestCases(){
			CASE(N = 1; allZero());
			CASE(N = 1; allAsterisk());
			CASE(N = 1; allOne());
			CASE(N = 1; allTwo());
			CASE(N = 2; allAsterisk());
			CASE(N = 2; allOne());
			CASE(N = MAX_LEN; allZero());
			CASE(N = MAX_LEN; randomValid());
			CASE(N = 10000; randomValid());
			CASE(N = 1000; randomValid());
			CASE(N = 5; randomValid());
			CASE(N = 10; randomValid());
			CASE(N = 100; randomValid());
			CASE(N = 12312; randomValid());
			CASE(N = MAX_LEN; randomInvalid());
			CASE(N = 5; randomInvalid());
			CASE(N = 10000; randomInvalid());
			CASE(N = 100000; randomInvalid());
			CASE(N = 100000; allZero());
			CASE(N = 100000; allAsterisk());
		}

	private:

		void allZero(){
			for(int i = 0;i < N; ++i) s += "0";
		}

		void allAsterisk(){
			for(int i = 0;i < N; ++i) s += "*";
		}
		void allOne(){
			for(int i = 0;i < N; ++i) s += "1";
		}

		void allTwo(){
			for(int i = 0;i < N; ++i) s += "2";
		}

		void randomValid(){
			for(int i = 0;i < N; ++i) s += "?";
			int banyak = rnd.nextInt(N);
			for(int i = 0;i < banyak; ++i){
				s[rnd.nextInt(N)] = '*';
			}
			for(int i = 1;i < N-1; ++i){
				if(s[i] != '*' && rnd.nextInt(0,6) > 2){
					s[i] = '0';
					if(s[i-1] == '*') s[i]++;
					if(s[i+1] == '*') s[i]++;
				}
			}

			if(rnd.nextInt(4) > 2){
				if(s[0] != '*'){
					s[0] = '0';
					if(N > 1 && s[1] == '*') s[0]++;
				}
			}
			if(rnd.nextInt(5) > 2){
				if(s[N-1] != '*'){
					s[N-1] = '0';
					if(N > 1 && s[N-2] == '*') s[N-1]++;
				}
			}
		}

		void randomInvalid(){
			if(rnd.nextInt(3)){
				randomValid();
			}
			else{
				for(int i = 0 ;i < N; ++i) s += "?";
				int banyak = rnd.nextInt(N);
				for(int i = 0;i < banyak; ++i){
					s[rnd.nextInt(N)] = '*';
				}
			}
			//mulai bikin invalid
			if(rnd.nextInt(6) > 4){
				s[0] = '2';
			}
			if(N == 5){
				s[0] = '2';
				s[1] = '?';
				s[2] = '1';
				s[3] = '?';
				s[4] = '2';
			}
			else if (N > 2){
				int tempat = rnd.nextInt(0, N-2);
				switch(rnd.nextInt(3)){
					case 0: 
							s[tempat] = '0';
							s[tempat+1] = '*';
							break;
					case 1: s[tempat] = '2';
							s[tempat+1] = '1';
							s[tempat+2] = '*';
							break;
					case 2: s[tempat] = '1';
							s[tempat+1] = '1';
							s[tempat+2] = '0';
							break;
				}
			}

		}
};