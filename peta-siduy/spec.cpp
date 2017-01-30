#include "tcframe/spec.hpp"
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back

class ProblemSpec : public BaseProblemSpec{
protected:
	int R, C;
	const int MAX_R = 1000, MAX_C = 1000;
	vector<vector<char> > V;
	int result;
	void InputFormat(){
		LINE(R, C);
		GRID(V) % SIZE(R, C);

	}
	void OutputFormat(){
		LINE(result);
	}

	void Constraints(){
		CONS(1 <= R && R <= MAX_R);
		CONS(1 <= C && C <= MAX_C);
		CONS(sameSize(V, R, C));
		CONS(oneInputAndOutput(V));
		CONS(validArray(V));
	}

private:
	bool sameSize(const vector<vector<char> > &V, int R, int C){
		if(V.size() != R) return false;
		for(int i = 0;i < R; ++i) if(V[i].size() != C) return false;

		return true;
	}

	bool oneInputAndOutput(const vector<vector<char> > &V){
		int S = 0, F = 0;
		for(int i = 0;i < R; ++i){
			for(int j = 0;j < C; ++j){
				if(V[i][j] == 'S') S++;
				if(V[i][j] == 'F') F++;
			}
		}
		return S == 1 && F == 1;
	}
	bool validArray(const vector<vector<char> > &V){
		for(int i = 0;i < R; ++i){
			for(int j = 0; j < C; ++j){
				const char &c =  V[i][j];
				if(c != 'S' && c != 'F' && c != '*' && c != '.') return false;
			}
		}
		return true;
	}
};


class TestSpec : public BaseTestSpec<ProblemSpec>{
protected:
	void SampleTestCase1(){
		Input({"3 3", "S..", "...", "..F"});
		Output({"4"});
	}

	void SampleTestCase2(){
		Input({"3 4", "S*.F", "..*.", "...."});
		Output({"7"});
	}
	void BeforeTestCase(){
		V.clear();
	}
	void TestCases(){
		CASE(R = 2; C = 1; randomGrid());
		CASE(R = MAX_R; C = MAX_C; randomGrid());
		CASE(R = MAX_R; C = MAX_C; randomGrid(100));
		CASE(R = MAX_R; C = MAX_C; randomGrid(70));
		CASE(R = MAX_R; C = MAX_C; randomGrid(30));
		CASE(R = MAX_R; C = MAX_C; randomGrid(5));

		CASE(R = 100; C = 100; randomGrid());
		CASE(R = 100; C = 100; randomGrid(100));
		CASE(R = 100; C = 100; randomGrid(70));
		CASE(R = 100; C = 100; randomGrid(30));
		CASE(R = 100; C = 100; randomGrid(5));

		CASE(R = 10; C = 10; randomGrid());
		CASE(R = 10; C = 10; randomGrid(100));
		CASE(R = 10; C = 10; randomGrid(70));
		CASE(R = 10; C = 10; randomGrid(30));
		CASE(R = 10; C = 10; randomGrid(5));

		for(int i = 0;i < 2; ++i){
			CASE(R = rnd.nextInt(9) + 2; C = rnd.nextInt(9) + 2;randomGrid());
			CASE(R = rnd.nextInt(9) + 2; C = rnd.nextInt(9) + 2;randomGrid(100));
			CASE(R = rnd.nextInt(9) + 2; C = rnd.nextInt(9) + 2;randomGrid(70));
			CASE(R = rnd.nextInt(9) + 2; C = rnd.nextInt(9) + 2;randomGrid(30));
			CASE(R = rnd.nextInt(9) + 2; C = rnd.nextInt(9) + 2;randomGrid(5));
		}

		CASE(R = MAX_R; C = MAX_C; emptyGrid());
		CASE(R = MAX_R; C = MAX_C; zigZagValid());
		CASE(R = MAX_R; C = MAX_C; zigZagInvalid());
		CASE(R = MAX_R; C = MAX_C; snakeValid());
		CASE(R = MAX_R; C = MAX_C; snakeInvalid());

		CASE(R = 100; C = 100; emptyGrid());
		CASE(R = 100; C = 100; zigZagValid());
		CASE(R = 100; C = 100; zigZagInvalid());
		CASE(R = 100; C = 100; snakeValid());
		CASE(R = 100; C = 100; snakeInvalid());

		CASE(R = 10; C = 10; emptyGrid());
		CASE(R = 10; C = 10; zigZagValid());
		CASE(R = 10; C = 10; zigZagInvalid());
		CASE(R = 10; C = 10; snakeValid());
		CASE(R = 10; C = 10; snakeInvalid());

		for(int i = 0;i < 2; ++i){
			CASE(R = rnd.nextInt(9) + 2; C = rnd.nextInt(9) + 2;emptyGrid());
			CASE(R = rnd.nextInt(9) + 2; C = R;zigZagValid());
			CASE(R = rnd.nextInt(9) + 2; C = R;zigZagInvalid());
			CASE(R = rnd.nextInt(9) + 2; C = R;snakeValid());
			CASE(R = rnd.nextInt(9) + 2; C = R;snakeInvalid());
		}

	}
private:

	void randomGrid(int chance = 50){
		pii s = {rnd.nextInt(0,R-1), rnd.nextInt(0, C-1)};
		pii f = {rnd.nextInt(0,R-1), rnd.nextInt(0, C-1)};
		while(s == f){
			f = {rnd.nextInt(0,R-1), rnd.nextInt(0, C-1)};
		}
		for(int i = 0; i < R; ++i){
			vector<char> vc;
			for(int j = 0; j < C; ++j){
				if(s == mp(i,j)){
					vc.push_back('S');
				}
				else if(f == mp(i,j)){
					vc.push_back('F');
				}
				else{
					vc.push_back(rnd.nextInt(100) > chance ? '*' : '.');
				}
			}
			V.push_back(vc);
		}
	}

	void fixSTRandomGrid(pii s, pii f){
		for(int i = 0; i < R; ++i){
			vector<char> vc;
			for(int j = 0; j < C; ++j){
				if(s == mp(i,j)){
					vc.push_back('S');
				}
				else if(f == mp(i,j)){
					vc.push_back('F');
				}
				else{
					vc.push_back(rnd.nextInt(2) ? '*' : '.');
				}
			}
			V.push_back(vc);
		}
	}

	void emptyGrid(){
		pii s = {rnd.nextInt(0,R-1), rnd.nextInt(0, C-1)};
		pii f = {rnd.nextInt(0,R-1), rnd.nextInt(0, C-1)};
		while(s == f){
			f = {rnd.nextInt(0,R-1), rnd.nextInt(0, C-1)};
		}
		for(int i = 0; i < R; ++i){
			vector<char> vc;
			for(int j = 0; j < C; ++j){
				if(s == mp(i,j)){
					vc.push_back('S');
				}
				else if(f == mp(i,j)){
					vc.push_back('F');
				}
				else{
					vc.push_back('.');
				}
			}
			V.push_back(vc);
		}
	}

	void snake(){
		pii s = mp(0,0);
		if(rnd.nextInt(2)){
			for(int i = 0; i < R; ++i){
				vector<char> vc;
				for(int j = 0; j < C; ++j){
					if(s == mp(i,j)){
						vc.push_back('S');
					}
					else{
						if(i == 0){
							if((j&3) == 1) vc.push_back('*');
							else vc.push_back('.');
						}
						else if(i == R-1){
							if((j&3) == 3) vc.push_back('*');
							else vc.push_back('.');
						}
						else{
							if(j&1) vc.push_back('*');
							else vc.push_back('.');	
						}
					}
				}
				V.push_back(vc);
			}
		}
		else{
			for(int i = 0; i < R; ++i){
				vector<char> vc;
				for(int j = 0; j < C; ++j){
					if(s == mp(i,j)){
						vc.push_back('S');
					}
					else{
						if(j == 0){
							if((i&3) == 1) vc.push_back('*');
							else vc.push_back('.');
						}
						else if(j == C-1){
							if((i&3) == 3) vc.push_back('*');
							else vc.push_back('.');
						}
						else{
							if(i&1) vc.push_back('*');
							else vc.push_back('.');	
						}
					}
				}
				V.push_back(vc);
			}
		}
		int maks_R_C = 0;
		pii R_C_now = mp(-1,-1);
		for(int i = 0;i < 100; ++i){
			int r_rand = rnd.nextInt(R);
			int c_rand = rnd.nextInt(C);
			while(V[r_rand][c_rand] != '.'){
				r_rand = rnd.nextInt(R);
				c_rand = rnd.nextInt(C);
			}
			if(max(r_rand, c_rand) > maks_R_C){
				maks_R_C = max(r_rand, c_rand);
				R_C_now = mp(r_rand, c_rand);
			}
		}

		V[R_C_now.fi][R_C_now.se] = 'F';
	}
	void snakeValid(){
		snake();
		if(rnd.nextInt(4)){
			for(int i = 0;i < 5; ++i){
				int r_rand = rnd.nextInt(R);
				int c_rand = rnd.nextInt(C);
				while(V[r_rand][c_rand] != '*'){
					r_rand = rnd.nextInt(R);
					c_rand = rnd.nextInt(C);
				}

				V[r_rand][c_rand] = '.';
			}
		}
	}	
	void snakeInvalid(){
		snake();
		for(int i = 0;i < 5; ++i){
			int r_rand = rnd.nextInt(R);
			int c_rand = rnd.nextInt(C);
			while(V[r_rand][c_rand] != '.'){
				r_rand = rnd.nextInt(R);
				c_rand = rnd.nextInt(C);
			}

			V[r_rand][c_rand] = '*';
		}
	}

	void zigZag(){
		assert(R == C);
		pii s = mp(0,0);
		pii f = mp(R-1, C-1);
		if((R&1) == 0){
			if((R&3) == 2){
				f = mp(0, C-1);
			}
			else{
				f = mp(R-1, 0);
			}
		}
		else{
			if(rnd.nextInt(2)){
				f = mp(R-1, rnd.nextInt(C));
			}
			else{
				f = mp(rnd.nextInt(R), C-1);
			}
		}

		for(int i = 0; i < R;++i){
			vector<char> vc;
			for(int j = 0;j < C; ++j){
				if(s == mp(i,j)){
					vc.push_back('S');
				}
				else if(f == mp(i,j)){
					vc.push_back('F');
				}
				else{
					if((max(i,j) & 1) == 0){
						if((((max(i,j) & 3) == 2) && (i == 0)) || (((max(i,j) & 3) == 0) && (j == 0))) {
							vc.push_back('.');
						}
						else vc.push_back('*');
					}
					else{
						vc.push_back('.');
					}
				}
			}
			V.push_back(vc);
		}
	}
	void zigZagValid(){
		
		zigZag();
		if(rnd.nextInt(4)){
			for(int i = 0;i < 5; ++i){
				int r_rand = rnd.nextInt(R);
				int c_rand = rnd.nextInt(C);
				while(V[r_rand][c_rand] != '*'){
					r_rand = rnd.nextInt(R);
					c_rand = rnd.nextInt(C);
				}

				V[r_rand][c_rand] = '.';
			}
		}
	}

	void zigZagInvalid(){
		zigZag();
		int r_rand = rnd.nextInt(R);
		int c_rand = rnd.nextInt(C);
		while(V[r_rand][c_rand] != '.'){
			r_rand = rnd.nextInt(R);
			c_rand = rnd.nextInt(C);
		}

		V[r_rand][c_rand] = '*';
	}
};