#include <iostream>
using namespace std;
#include <bits/stdc++.h>
#include <string.h>
#include <math.h>

const int maxqueue = 1024;

class queueue{
public:
	queueue();
	void enqueue(int e, int arg);
	int dequeue(int arg);
	int front(int arg);
	int first();
	int last();
	bool isempty();
	bool isfull(int arg);
	bool isit(int e,int arg);
	int nextpos(int p, int arg);
	int maxselect(int n);
	bool repeated(int g,int arg);
	int continous(int arg);
	int priority(int e,int arg);
	void priority2(int x,int arg);
	void sort(int arg);
	int siz(int arg);
private:
	int f;
	int r;
	int packets[maxqueue];
};

bool isnum(char *y);
int change(char *c);
int warp(int s1,int s2,int arg);
int warp2(int a1,int a2);

int main(int argc ,char **argv) {
	bool error = false;
	bool seqerr = false;
	if (argc < 5){
		cout << "Invalid number of arguments ";
		error = true;
	}
	if (argc > 1 && (!isnum(argv[1]) || change(argv[1]) <= 0)){
		cout << "Invalid seqNumBits ";
		error = true;
		seqerr = true;
	}
	if (argc > 2 && !seqerr && (!isnum(argv[2]) || change(argv[2]) >= pow(2,change(argv[1])) || change(argv[2]) < 1)){
		cout << "Invalid winSize ";
		error = true;
	} else if (argc > 2 && (!isnum(argv[2]) || change(argv[2]) < 1)){
		cout << "Invalid winSize ";
		error = true;
	}
	if (argc > 3 && !seqerr && (!isnum(argv[3]) || change(argv[3]) >= pow(2,change(argv[1])) || change(argv[3]) < 0)){
		cout << "Invalid initSeq ";
		error = true;
	} else if (argc > 3 && (!isnum(argv[3]) || change(argv[3]) < 0)){
		cout << "Invalid initSeq ";
		error = true;
	}
	for (int i = 4;i < argc;i++){
		if (!seqerr && (!isnum(argv[i]) || change(argv[i]) >= pow(2,change(argv[1])) || change(argv[i]) < 0)){
			cout << "Invalid packet ID";
			error = true;
			break;
		} else if (!isnum(argv[i]) || change(argv[i]) < 0){
			cout << "Invalid packet ID";
			error = true;
			break;
		}
	}
	if (error == true)
		return 0;

	queueue q;

	int L = change(argv[2]);
	int E = change(argv[3]);
	for (int i = 4;i < argc;i++)
		q.enqueue(change(argv[i]),argc-4);
	q.sort(argc-4);
	bool C = q.isit(E,argc-4);
	q.priority2(E,argc-4);
	int c = q.continous(argc-4);
	int m = pow(2,change(argv[1]));
	int R[m];
	int r = 0;
	int W[L];
	int w = 0;
	int D[m];
	int d = 0;
	if (C){
		for (int i = q.first();i != c;){
			int z = q.dequeue(argc-4);
			if (q.repeated(z,argc-4)){
				D[d] = z;
				d++;
			}
			else{
				R[r] = z;
				r++;
				E++;
				E = warp2(E,pow(2,change(argv[1])));
			}
			i = q.nextpos(i,argc-4);
			if (i == 0)
				i++;
		}
		if (c == argc-4 && q.front(argc-4) == 0){
			int c2 = q.continous(argc-4);
			for (int i = q.first();i != c2;){
				int z = q.dequeue(argc-4);
				if (q.repeated(z,argc-4)){
					D[d] = z;
					d++;
				}
				else{
					R[r] = z;
					r++;
					E++;
					E = warp2(E,pow(2,change(argv[1])));
				}
				i = q.nextpos(i,argc-4);
				if (i == 0)
					i++;
			}
		}
		for (int i = q.first();i != q.last();){
			int z = q.dequeue(argc-4);
			if (q.repeated(z,argc-4) || (warp(E,L,pow(2,change(argv[1]))) > E && (z > warp(E,L,pow(2,change(argv[1]))) || z < E)) || (z > warp(E,L,pow(2,change(argv[1]))) && (z < E))){
				D[d] = z;
				d++;
			}
			else{
				W[w] = z;
				w++;
			}
			i = q.nextpos(i,argc-4);
			if (i == 0)
				i++;
		}
		int D2[d];
		for (int i = 0;i < d;i++){
			int n;
			for (int j = 4;j < argc;j++){
				if (D[i] == change(argv[j])){
					n = j;
				}
			}
			D2[i] = n;
		}
		for (int j = 0;j < d;j++){
			for (int i = 0;i < d-1;i++){
				if (D2[i] > D2[i+1]){
					int temp = D[i];
					D[i] = D[i+1];
					D[i+1] = temp;
					int temp2 = D2[i];
					D2[i] = D2[i+1];
					D2[i+1] = temp2;
				}
			}
		}
		cout << "R";
		for (int i = 0;i < r;i++)
			cout << " " << R[i];
		cout << " E " << E << " W";
		for (int i = 0;i < w;i++)
			cout << " " << W[i];
		cout << " D";
		for (int i = 0;i < d;i++)
			cout << " " << D[i];
	}
	else {
		cout << "R E " << E << " W";
		if (q.first() == q.last()){
			int z = q.dequeue(argc-4);
			if (q.repeated(z,argc-4) || (warp(E,L,pow(2,change(argv[1]))) > E && (z > warp(E,L,pow(2,change(argv[1]))) || z < E)) || (z > warp(E,L,pow(2,change(argv[1]))) && (z < E))){
				D[d] = z;
				d++;
			}
			else{
				W[w] = z;
				w++;
			}
		}
		for (int i = q.first();i != q.last();){
			int z = q.dequeue(argc-4);
			if (q.repeated(z,argc-4) || (warp(E,L,pow(2,change(argv[1]))) > E && (z > warp(E,L,pow(2,change(argv[1]))) || z < E)) || (z > warp(E,L,pow(2,change(argv[1]))) && (z < E))){
				D[d] = z;
				d++;
			}
			else{
				W[w] = z;
				w++;
			}
			i = q.nextpos(i,argc-4);
			if (i == 0)
				i++;
		}
		int D2[d];
		for (int i = 0;i < d;i++){
			int n;
			for (int j = 4;j < argc;j++){
				if (D[i] == change(argv[j])){
					n = j;
				}
			}
			D2[i] = n;
		}
		for (int j = 0;j < d;j++){
			for (int i = 0;i < d-1;i++){
				if (D2[i] > D2[i+1]){
					int temp = D[i];
					D[i] = D[i+1];
					D[i+1] = temp;
					int temp2 = D2[i];
					D2[i] = D2[i+1];
					D2[i+1] = temp2;
				}
			}
		}
		for (int i = 0;i < w;i++)
			cout << " " << W[i];
		cout << " D";
		for (int i = 0;i < d;i++)
			cout << " " << D[i];
	}

	return 0;
}

bool isnum(char *y){
	string x = y;
	int t = x.length();
	for (int i = 0;i < t;i++){
		if (x[i] == '0' || x[i] == '1' || x[i] == '2' || x[i] == '3' || x[i] == '4' || x[i] == '5' || x[i] == '6' || x[i] == '7' || x[i] == '8' || x[i] == '9'){

		} else{
			return false;
		}
	}
	return true;
}

int change(char *c){
	string s = c;
	int e = s.length();
	int q = 0;
	int l = 0;
	for (int i = e-1;i >= 0;i--){
		int z = s[i] - '0';
		q = q + z*pow(10,l);
		l++;
	}
	return q;
}

int warp(int s1,int s2,int arg){
	if (s1+s2 <= arg)
		return s1+s2-1;
	else
		return s1+s2-arg-1;
}

int warp2(int a1,int a2){
	if (a1 < a2)
		return a1;
	else
		return a2-a1;
}


int queueue::nextpos(int p ,int arg){
	if (p == arg)
		return 0;
	else
		return p+1;
}

int queueue::first(){
	return f;
}

int queueue::last(){
	int o = r;
	if (o == 0)
		o++;
	return r;
}

queueue::queueue(){
	f = 0;
	r = 0;
}

int queueue::siz(int arg){
	if (f > r)
		return arg;
	else
		return arg;
}

void queueue::enqueue(int e , int arg){
	r = this->nextpos(r,arg);
	packets[r] = e;
}

int queueue::dequeue(int arg){
	f = this->nextpos(f,arg);
	if (f == 0)
		f++;
	return packets[f];
}

int queueue::front(int arg){
	int x = this->nextpos(f,arg);
	if (x == 0)
		x++;
	return packets[x];
}

bool queueue::isempty(){
	return bool(f == r);
}

bool queueue::isfull(int arg){
	return bool(f == this->nextpos(r,arg));
}

int queueue::maxselect(int n){
	int maxpos(f+1),currentpos(f+2);
	while (currentpos <= n){
		if (packets[currentpos] >= packets[maxpos])
			maxpos = currentpos;
		currentpos++;
	}
	return maxpos;
}

void queueue::sort(int arg){
	int last = this->siz(arg);
	int maxpos;
	while (last > 1){
		maxpos = this->maxselect(last);
		int temp = packets[maxpos];
		packets[maxpos] = packets[last];
		packets[last] = temp;
		last--;
	}
}

bool queueue::repeated(int g,int arg){
	if (f == r)
		return false;
	int x = this->nextpos(f,arg);
	if (x == 0)
		x++;
	for (int i = x;i != r;i = this->nextpos(i,arg)){
		if (g == packets[i]){
			return true;
		}
	}
	if (g == packets[r])
		return true;
	else
		return false;
}

int queueue::continous(int arg){
	if (this->siz(arg) == 1)
		return r;
	if (this->siz(arg) == 2){
		if (packets[2]-packets[1] == 1)
			return r;
		else
			return r-1;
	}
	int x = this->nextpos(f,arg);
	if (x == 0)
		x++;
	for (int i = x;i != r-1;i = this->nextpos(i,arg)){
		int x1 = i;
		if (x1 == 0)
			x1++;
		int x2 = this->nextpos(x1,arg);
		if (x2 == 0)
			x2++;
		int x3 = this->nextpos(x2,arg);
		if (x3 == 0)
			x3++;
		if (((packets[x3]-packets[x2] != 1) && (packets[x3]-packets[x2] != 0)) || ((packets[x2]-packets[x1] != 1) && (packets[x2]-packets[x1] != 0))){
			if ((packets[x2]-packets[x1] != 1) && (packets[x2]-packets[x1] != 0))
				return x1;
			else if ((packets[x3]-packets[x2] != 1) && (packets[x3]-packets[x2] != 0))
				return x2;
		}
	}
	return r;
}

bool queueue::isit(int e,int arg){
	for (int i = 1;i <= arg;i++)
		if (packets[i] == e)
			return true;
	return false;
}

int queueue::priority(int e,int arg){
	int v = 0;
	if (this->isit(e,arg)){
		for (int i = 1;i <= arg;i++)
			if (packets[i] == e){
				v = i;
				break;
			}
			else{

			}
	}
	else{
	v = this->priority(e+1,arg);
	}
	return v;
}

void queueue::priority2(int x,int arg){
	int b = this->priority(x,arg);
	f = b - 1;
	if (f == 0)
		r = arg;
	else
		r = b - 1;
}
