#include "tcframe/spec.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;


class ProblemSpec : public BaseProblemSpec{
protected:
	string s;
	const int MAX_LEN = 1e5;
	int N;
	int result;
	void InputFormat(){
		LINE(s);

	}
	void OutputFormat(){
		LINE(result);
	}

	void Constraints(){
		CONS(1 <= s.length() && s.length() <= MAX_LEN);
		CONS(validArray(s));
	}

private:

	bool validArray(const string &s){
		for(int i = 0;i < s.length(); ++i){
			if(s[i] < 'A' || s[i] > 'Z') return false;
		}
		return true;
	}
};


class TestSpec : public BaseTestSpec<ProblemSpec>{
protected:
	void SampleTestCase1(){
		Input({"TA"});
		Output({"2"});
	}

	void SampleTestCase2(){
		Input({"TADTAOTA"});
		Output({"8"});
	}

	void BeforeTestCase(){
		s = "";
	}
	void TestCases(){
		CASE(N = 1; randomArray());
		CASE(N = 2; randomArray());
		CASE(N = MAX_LEN; randomArray());
		CASE(N = 64; TAOnly());
		
		CASE(N = 99999; TAOnly());
		CASE(N = 128; GTAOnly());
		CASE(N = 1024; DOTAOnly());
		CASE(N = MAX_LEN;All());
		CASE(N = 3984; All());
		CASE(N = 10000; All());
		CASE(N = 1000; randomArray());
		CASE(N = 1001; GTAOnly());
		CASE(N = MAX_LEN; Flipped());
		CASE(N = 10000; Flipped());
	}
private:

	void randomArray(){
		for(int i = 0;i < N; ++i){
			int pil = rnd.nextInt(9);
			switch(pil){
				case 0: s += 'D'; break;
				case 1: s += 'G'; break;
				case 2: s += 'O'; break;
				case 3: s += 'T'; break;
				case 4: s += 'A'; break;
				default:
					char c = rnd.nextInt(26) + 'A';
					s += c;
			}
		}
	}
	void TAOnly(){
		for(int i = 0;i < N; ++i){
			if(i&1) s += 'A';
			else s += 'T';
		}
	}

	void GTAOnly(){
		for(int i = 0;i < N; ++i){
			if(i % 3 == 0) s += 'G';
			else if (i % 3 == 1)s += 'T';
			else s += 'A';
		}
	}

	void DOTAOnly(){
		for(int i = 0;i < N; ++i){
			if(i % 4 == 0) s += 'D';
			else if (i % 4 == 1)s += 'O';
			else if (i % 4 == 2)s += 'T';
			else s += 'A';
		}
	}
	void All(){
		for(int i = 0;i < N; ++i){
			int pil = rnd.nextInt(7);
			switch(pil){
				case 0: s += "TA"; i++; break;
				case 1: s += "DO"; i++; break;
				case 2: s += "GTA"; i+=2; break;
				case 3: s += "G"; break;
				case 4: s += "DOTA"; i += 3;break;
				default: s += "GAT"; i+=2; break;
			}
		}
		s = s.substr(0, N);
	}

	void Flipped(){
		for(int i = 0;i < N; ++i){
			int pil = rnd.nextInt(9);
			switch(pil){
				case 0: s += "TA"; i++; break;
				case 1: s += "DO"; i++; break;
				case 2: s += "GTA"; i+=2; break;
				case 3: s += "G"; break;
				case 4: s += "DOTA"; i += 3;break;
				case 5: s += "DTOA"; i += 3; break;
				case 6: s += "AT"; i++; break;
				case 7 : s +="ODTA"; i+=3; break;
				default: s += "GAT"; i+=2; break;
			}
		}
		s = s.substr(0, N);
	}
};