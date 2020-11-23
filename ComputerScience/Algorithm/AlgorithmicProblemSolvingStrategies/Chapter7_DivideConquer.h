#pragma once
#include "Utilities.h"

/*■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
Pardigm 2 : 분할 정복 (Divide and Conquer)
1. 둘 이상의 부분 문제로 나눈 뒤, 각 문제에 대한 답을 재귀 호출로 계산
   => 각 부분 문제의 답으로 부터 전체 문제의 답을 도출

2. 분할 정복 : 거의 크기가 같은 부분 문제로 나눈다
   일반 재귀호출(e.g 완전 탐색) : 문제를 한 조각과 나머지로 나눈다

3. 분할정복을 적용할 수 있는 문제의 특성
- 둘 이상의 부분 문제로 나누는 자연스러운 방법이 존재해야한다
- 부분 문제의 답을 조합해 원래 문제의 답을 계산하는 효율적인 방법이 존재해야한다
  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■*/


// Example 1 : 1+2+...+n (p176)
int sumDivideConquer(int n) {
	/*
	n : even
	sum(n) = 1+2+...+n = (1+2+..+n/2) + ((n/2+1) + ...+n)
	= sum(n/2) + (n/2+1) + (n/2 +1) + ...+(n/2 +n/2)
	= sum(n/2) + (n/2)(n/2) + sum(n/2)
	= 2*sum(n/2) + (n/2)(n/2)
	*/

	// Base case : n==1
	if (n == 1) {
		return 1;
	}

	// Odd number
	if (n % 2 == 1) {
		return n + sumDivideConquer(n - 1);
	}

	return n*n / 4 + 2 * sumDivideConquer(n / 2);
}

// Example 2 : Karatsuba Product
class KaratsubaProduct {
private:
	static const int baseCaseNum = 50;

	static void normalize(vector<int>& v) {
		/*
		v[i]>=10||v[i]<0 인 경우 v[i+1]++을 해줌으로써 자릿수 올림을 처리해주는 함수
		- Ex1:{4,13,2,11} = (11,2,13,4)=11*1000+2*100+13*10+4
		=>{4,3,3,1,1}=1*10000+1*1000+3*100+3*10+4
		- Ex2:{-4,1,1} = (1,1,-4)=1*100+1*10+(-4)
		=> {6,0,1}=1*100+6
		*/

		// 자릿수를 하나 올린다 e.g 4001=>04001
		v.push_back(0);

		// 자릿수 올림 처리를 한다
		for (int i = 0; i < v.size() - 1; i++) {
			// 음수인 경우 : 받아내림 처리 
			if (v[i] < 0) {
				int borrow = (abs(v[i]) + 9) / 10;
				v[i + 1] -= borrow;
				v[i] += 10 * borrow;
			}
			// 요소가 10이상인 경우도 처리해준다
			else {
				v[i + 1] += v[i] / 10;
				v[i] = v[i] % 10;
			}
		}

		// 가장 높은 자릿수의 수가 0인 경우 삭제 : 00123 => 123
		while (v.size() > 1 && v.back() == 0) {
			v.pop_back();
		}
	}

	static void addTo(vector<int>&a, const vector<int>& b, int k, bool isNormalized = true) {
		/*
		a+=b*(10^k) 구현 (a>=b 라고 가정)
		*/

		// 우선 자리수를 채워 준다
		for (int i = 0; i <= k + b.size(); i++) {
			a.push_back(0);
		}

		// a+=b*(10^k) 구현
		for (int i = 0; i < b.size(); i++) {
			a[i + k] += b[i];
		}

		if (isNormalized) {
			normalize(a);
		}
			
	}

	static void subFrom(vector<int>&a, const vector<int>& b, bool isNormalized = true) {
		/*
		a-=b 구현 (a>=b 라고 가정)
		*/
		for (int i = 0; i < b.size(); i++) {
			a[i] -= b[i];
		}

		if (isNormalized) {
			normalize(a);
		}
	}

public:
	static vector<int> elementaryMultiply(const vector<int>& a, const vector<int>& b, bool isNormalized = true) {
		// 일반적인 곱셈 방법 : O(nm)
		vector<int> ret(a.size() + b.size() + 1, 0);
		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < b.size(); j++) {
				ret[i + j] += a[i] * b[j];
			}
		}

		if (isNormalized) {
			normalize(ret);
		}
		
		return ret;
	}

	static vector<int> multiply(const vector<int>& a, const vector<int>& b, bool isNormalized = true) {
		/*
		Let d be the deree of a.
		Divide a and b as a=(a1,a0) and b=(b1,b0) where deg(a1)=d/2
		Then a*b=a1*b1*pow(10,d/2+d/2) + (a0*b1+a1*b0)*pow(10,d-d/2) + a0*b0
		=z2*pow(10,d/2+d/2) + z1*pow(10,d-d/2) +z2
		Here, z2 = a1*b1
		z0 = a0*b0
		z1 = a0*b1+a1*b0 = (a0+a1)(b0+b1) - z0 - z2
		*/

		int an = a.size(), bn = b.size();

		// Assumption : a>=b
		if (an < bn) {
			return multiply(b, a, isNormalized);
		}

		// Base case 1 : a or b is empty
		if (an == 0 || bn == 0) {
			return vector<int>();
		}

		// Base case 2 : a,b가 작은 수면 elementaryMultiply 적용
		if (an <= baseCaseNum) {
			return elementaryMultiply(a, b, isNormalized);
		}

		// Divide : a_0,a_1,b_0,b_1로 쪼갠다
		int half = an / 2;
		vector<int> a0(a.begin(), a.begin() + half);
		vector<int> a1(a.begin() + half, a.end());
		vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));
		vector<int> b1(b.begin() + min<int>(b.size(), half), b.end());

		// z2 = a1*b1
		vector<int> z2 = multiply(a1, b1, isNormalized);
		// z0 = a0*b0
		vector<int> z0 = multiply(a0, b0, isNormalized);

		// z1 = (a0+a1)(b0+b1) - z0 -z1

		// Step1 : a0<-a0+a1 , b0<-b0+b1
		addTo(a0, a1, 0, isNormalized);
		addTo(b0, b1, 0, isNormalized);

		// Step2 : z1<-a0*b0
		vector<int> z1 = multiply(a0, b0, isNormalized);

		// Step3 : z1 = z1-z0-z2
		subFrom(z1, z0, isNormalized);
		subFrom(z1, z2, isNormalized);

		// result = z2*pow(10,half+half) +z1*pow(10, half) + z0
		vector<int> ret;
		addTo(ret, z0, 0, isNormalized);
		addTo(ret, z1, half, isNormalized);
		addTo(ret, z2, half + half, isNormalized);

		return ret;
	}

	static string multiply(const string& a, const string& b) {
		vector<int> vecA = convertStoI(a);
		vector<int> vecB = convertStoI(b);
		vector<int> vecRet = multiply(vecA, vecB);

		string ret = convertItoS(vecRet);
		return ret;
	}

	static string convertItoS(const vector<int>& v) {
		// 정수 벡터를 문자열로 변환
		string result;
		vector<int> temp = v;

		while (!temp.empty()) {
			result.append(to_string(temp.back()));
			temp.pop_back();
		}

		return result;
	}

	static vector<int> convertStoI(const string& s) {
		// 문자열을 정수 벡터로 변환
		vector<int> result;

		for (int i = s.size() - 1; i >= 0; i--) {
			result.push_back(atoi(s.substr(i, 1).c_str()));
		}
		return result;
	}
};


/*
<쿼드 트리 뒤집기 -p191>
- 좌표 데이터를 메모리 안에 압축해 저장하는 기법
- 검,흰 픽셀만 있는 흑백 그림을 압축
- 2^N * 2^N 크기의 흑백 그림이 주어질 때 이것을 w,x,b로 구성된 문자열로 압축.
- 문제 : 쿼드 트리로 압축된 문자열을 입력받아 상하반전 결과를 쿼드 트리로 압축하여 출력
- 서브 문제 : 쿼드 트리로 압축된 문자열을 통해 원래 그림으로 복원
*/
class QuadTree {
	/*
	< Solution >
	0. Idea
	- 쿼드 트리의 각 노드가 우상단,좌상단,우하단,좌하단에 해당하는 sub쿼드 트리
	- 각각의 쿼드 트리가 하나의 분할된 문제
	- 즉, 4개의 sub-QuadTree(자식 도느)에 대해서 재귀 호출을 해준다

	1. Main 문제
	- 현재 문자열이 w,b이면(리프 노드임) 그 값을 반환
	- x이면 자식 노드를 가지고 있는 것 => 재귀 호출
	- 최종 return 값 : x+ f(좌하단) + f(우하단) + f(좌상단) + f(우하단)

	2. sub 문제
	- Main 문제와 매우 비슷한 형태
	- 이미지 복원을 하기 위해서는 몇가지 변수가 필요
	- 복원할 이미지 크기
	- 현재 어느 위치인지 : (y,x)좌표
	- quadTree에서 현재 탐색 위치
	*/
private:
	// MainProblem
	string quadTree;

	void setProblem(const string& quadTree) {
		this->quadTree = quadTree;
	}

	string recursiveReverse(int& pos) {
		pos++;
		// Base case : w나 b문자열을 만나는 경우 그 값을 반환
		if (quadTree[pos] == 'b' || quadTree[pos] == 'w') {
			return quadTree.substr(pos, 1);
		}

		// x를 만나면 x를 root로 갖는 sub-quadTree를 생각할 수 있음
		// => 재귀 호출
		string leftTop = recursiveReverse(pos);
		string rightTop = recursiveReverse(pos);
		string leftBot = recursiveReverse(pos);
		string rightBot = recursiveReverse(pos);

		// 뒤집어준다
		string ret;
		ret = "x" + leftBot + rightBot + leftTop + rightTop;
		return ret;
	}

	// SubProblem :
	vector<vector<bool>> originalPicture;

	int picSize;

	void setSubProblem(const string& quadTree, int picSize) {
		this->quadTree = quadTree;
		this->picSize = picSize;
		originalPicture = vector<vector<bool>>(picSize, vector<bool>(picSize));
	}

	void recursiveDecoding(int& pos, int y, int x, int size) {
		pos++;

		// Base case : w나 b문자열을 만나는 경우 그 값을 반환
		if (quadTree[pos] == 'b' || quadTree[pos] == 'w') {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					originalPicture[y + i][x + j] = (quadTree[pos] == 'b') ? false : true;
				}
			}
			return;
		}

		// x를 만나면 x를 root로 갖는 sub-quadTree를 생각할 수 있음
		// => 재귀 호출 : x의 4개의 child node에 대해서
		int halfSize = size / 2;
		recursiveDecoding(pos, y, x, halfSize);
		recursiveDecoding(pos, y, x + halfSize, halfSize);
		recursiveDecoding(pos, y + halfSize, x, halfSize);
		recursiveDecoding(pos, y + halfSize, x + halfSize, halfSize);

	}

public:
	string solveProblem(const string& quad) {
		setProblem(quad);

		int x = -1;
		return recursiveReverse(x);
	}

	void solveSubProblem(const string& quad, int picSize) {
		setSubProblem(quad, picSize);

		int x = -1;
		recursiveDecoding(x, 0, 0, picSize);
	}

	void example() {
		string s1 = "w";
		string s2 = "xbwwb";
		string s3 = "xbwxwbbwb";

		cout << solveProblem(s1) << endl;
		cout << solveProblem(s2) << endl;
		cout << solveProblem(s3) << endl;
	}

	void example_sub() {
		string s1 = "w";
		string s2 = "xbwwb";
		string s3 = "xbwxwbbwb";

		solveSubProblem(s1, 1);
		printVector2d(originalPicture);

		solveSubProblem(s2, 2);
		printVector2d(originalPicture);

		solveSubProblem(s3, 4);
		printVector2d(originalPicture);
	}
};


/*
< 울타리 자르기 - p195 >
- 너비가 같은 N개의 나무판자가 이어져 있는 울타리가 주어진다 (N<2*10^4)
- 각 나무판자의 높이가 주어진다
- 울타리 안에 포함된 직사각형의 최대 넓이를 구하는 문제
*/
class Fence {
	/*
	< Solution >
	0. Idea
	- 완전 탐색의 경우 O(N^2)=4*10^8 => 시간 초과
	- 분할 정복을 위해 울타리를 절반으로 쪼갠다
	=> f(leftCase) + f(rightCase) + f(midCase)
	- f(midCase) : 가운데에서 양쪽으로 탐색. 높이가 더 큰 방향으로 탐색한다
	- merge sort처럼 탐색할 범위 위치(start,end)를 알아야 한다
	- 최댓값을 구하는 문제 => 최적화 문제(6단원 salesmanproblem 참고)
	*/
private:
	int minInf;
	int nFence;
	vector<int> fenceHeight;

	void setProblem(int nFence, const vector<int>& fenceH) {
		this->nFence = nFence;
		fenceHeight = fenceH;
	}

	int recursiveCount(int start, int end) {

		// Base case : 탐색할 범위의 길이가 1일때
		if (start == end) {
			return fenceHeight[start];
		}

		// 중간을 기준으로 좌,우로 문제를 나눈다 => 문제는 3개로 분할
		int mid = (start + end) / 2;

		// subProblem 1&2 : 좌, 우에 대한 문제
		int subRet = max(recursiveCount(start, mid), recursiveCount(mid + 1, end));

		// subProblem : mid 인덱스에서 좌우로 직사각형이 겹치는 경우
		int left = mid;
		int right = mid + 1;
		int curHeight = min(fenceHeight[left], fenceHeight[right]);
		int curArea = 0;

		// start+1~end-1 범위 안에서 탐색
		while (left > start || right < end) {
			/*
			왼쪽 순회
			- 왼쪽 순회가 가능한 상태??
			- 오른쪽 순회가 끝났거나, 왼쪽 높이 > 오른쪽 높이
			- left > start 조건이 들어간 이유는 ?
			A:left > start
			B: right == end
			C: enceHeight[left-1] > fenceHeight[right+1]
			~A: left<=start  => while문 조건에서 무조건 false
			~B: right<end    <= ~A 때문
			~C: fenceHeight[left-1] < fenceHeight[right+1]
			~(A && (B || C) = ~A || ( ~B && ~C)
			= (~A||~B) && ( ~A || ~C)
			where ~A || ~B : ~B <=> right<end  (while문 조건 때문에)
			= ~B && (
			*/
			if (left > start && ((right == end) || fenceHeight[left - 1] > fenceHeight[right + 1])) {
				left--;
				curHeight = min(fenceHeight[left], curHeight);
			}
			/*
			오른쪽 순회
			- 오른쪽 순회가 가능한 상태??
			- 왼쪽 순회가 끝났거나, 왼쪽 높이 < 오른쪽 높이
			*/
			else {
				right++;
				curHeight = min(fenceHeight[right], curHeight);
			}

			curArea = max(curArea, curHeight*(right - left + 1));
		}

		return max(subRet, curArea);

	}
public:
	int solveProblem(int nFence, const vector<int>& info) {
		setProblem(nFence, info);
		return recursiveCount(0, nFence - 1);
	}

	void example() {
		int nF1 = 7;
		vector<int> v1{ 7,1,5,9,6,7,3 };

		int nF2 = 7;
		vector<int> v2{ 1,4,4,4,4,1,1 };

		int nF3 = 4;
		vector<int> v3{ 1,8,2,2 };

		int nF4 = 9;
		vector<int> v4 = { 1,2,4,8,16,9,5,3,1 };

		//20 16 8
		cout << solveProblem(nF1, v1) << endl;
		cout << solveProblem(nF2, v2) << endl;
		cout << solveProblem(nF3, v3) << endl;
		cout << solveProblem(nF4, v4) << endl;
	}

};


/*
< 팬미팅 - p201>
- 혼성그룹과 팬들의 성별 정보가 문자열로 구성
- 팬들이 한칸씩 움직이면서 멤버들과 인사
- (남,남)의 경우 악수. 그 외는 포옹
- 모든 멤버가 동시에 포옹하는 횟수를 구하는 문제
*/
class FanMeeting {
	/*
	< Solution >
	- 혼성 그룹 A={a_0, a_1, ... , a_N} 팬 그룹 B={b_0, b_1, ... , b_M}
	- a_i,b_j : 남자일 때 1, 여자일 때 0 => a_i*b_j: 둘 다 남자의 경우만 non-zero
	- (AB)_k : sum(i+j=k)a_i*b_j
	- (AB)_k ==0 <=> 모두가 포옹하는 상황
	- nomalize안한 AB에서 zero 갯수를 구하면 된다.
	*/
private:
	vector<int> groupMembers;
	vector<int> fans;

	void setProblem(const string& groupMembers, const string& fans) {
		this->groupMembers = vector<int>(groupMembers.size(), 0);
		this->fans = vector<int>(fans.size(), 0);

		// 남자면 1, 여자면 0으로 저장
		for (int i = 0; i < groupMembers.size(); i++) {
			if (groupMembers.at(i) == 'M') {
				this->groupMembers[i] = 1;
			}
		}

		// 팬은 역순으로 이동하기 때문에 역순으로 저장해야함
		for (int i = 0; i < fans.size(); i++) {
			if (fans.at(i) == 'M') {
				this->fans[fans.size() - 1 - i] = 1;
			}
		}

	}

	int karatsubaCount() {

		vector<int> karatsubaMultiple = KaratsubaProduct::multiply(groupMembers, fans, false);
		int ret = 0;

		if (karatsubaMultiple.size() < groupMembers.size()) {
			return 0;
		}

		// 0 인 엔트리의 갯수 
		for (int i = groupMembers.size() - 1; i < fans.size(); i++) {
			if (karatsubaMultiple[i] == 0) {
				ret++;
			}
		}

		return ret;
	}

public:
	int solveProblem(const string& groupMembers, const string& fans) {
		setProblem(groupMembers, fans);
		return karatsubaCount();
	}

	void example() {
		string m1 = "FFFMMM"; string f1 = "MMMFFF";
		string m2 = "FFFFF"; string f2 = "FFFFFFFFFF";
		string m3 = "FFFFM"; string f3 = "FFFFFMMMMF";
		string m4 = "MFMFMFFFMMMFMF"; string f4 = "MMFFFFFMFFFMFFFFFFMFFFMFFFFMFMMFFFFFFF";


		cout << solveProblem(m1, f1) << endl;
		cout << solveProblem(m2, f2) << endl;
		cout << solveProblem(m3, f3) << endl;
		cout << solveProblem(m4, f4) << endl;
	}
};
