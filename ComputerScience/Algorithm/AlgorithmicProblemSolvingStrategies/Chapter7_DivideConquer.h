#pragma once
#include "Utilities.h"

/*�����������������������������������������������������������������������������������
Pardigm 2 : ���� ���� (Divide and Conquer)
1. �� �̻��� �κ� ������ ���� ��, �� ������ ���� ���� ��� ȣ��� ���
   => �� �κ� ������ ������ ���� ��ü ������ ���� ����

2. ���� ���� : ���� ũ�Ⱑ ���� �κ� ������ ������
   �Ϲ� ���ȣ��(e.g ���� Ž��) : ������ �� ������ �������� ������

3. ���������� ������ �� �ִ� ������ Ư��
- �� �̻��� �κ� ������ ������ �ڿ������� ����� �����ؾ��Ѵ�
- �κ� ������ ���� ������ ���� ������ ���� ����ϴ� ȿ������ ����� �����ؾ��Ѵ�
  �����������������������������������������������������������������������������������*/


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
		v[i]>=10||v[i]<0 �� ��� v[i+1]++�� �������ν� �ڸ��� �ø��� ó�����ִ� �Լ�
		- Ex1:{4,13,2,11} = (11,2,13,4)=11*1000+2*100+13*10+4
		=>{4,3,3,1,1}=1*10000+1*1000+3*100+3*10+4
		- Ex2:{-4,1,1} = (1,1,-4)=1*100+1*10+(-4)
		=> {6,0,1}=1*100+6
		*/

		// �ڸ����� �ϳ� �ø��� e.g 4001=>04001
		v.push_back(0);

		// �ڸ��� �ø� ó���� �Ѵ�
		for (int i = 0; i < v.size() - 1; i++) {
			// ������ ��� : �޾Ƴ��� ó�� 
			if (v[i] < 0) {
				int borrow = (abs(v[i]) + 9) / 10;
				v[i + 1] -= borrow;
				v[i] += 10 * borrow;
			}
			// ��Ұ� 10�̻��� ��쵵 ó�����ش�
			else {
				v[i + 1] += v[i] / 10;
				v[i] = v[i] % 10;
			}
		}

		// ���� ���� �ڸ����� ���� 0�� ��� ���� : 00123 => 123
		while (v.size() > 1 && v.back() == 0) {
			v.pop_back();
		}
	}

	static void addTo(vector<int>&a, const vector<int>& b, int k, bool isNormalized = true) {
		/*
		a+=b*(10^k) ���� (a>=b ��� ����)
		*/

		// �켱 �ڸ����� ä�� �ش�
		for (int i = 0; i <= k + b.size(); i++) {
			a.push_back(0);
		}

		// a+=b*(10^k) ����
		for (int i = 0; i < b.size(); i++) {
			a[i + k] += b[i];
		}

		if (isNormalized) {
			normalize(a);
		}
			
	}

	static void subFrom(vector<int>&a, const vector<int>& b, bool isNormalized = true) {
		/*
		a-=b ���� (a>=b ��� ����)
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
		// �Ϲ����� ���� ��� : O(nm)
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

		// Base case 2 : a,b�� ���� ���� elementaryMultiply ����
		if (an <= baseCaseNum) {
			return elementaryMultiply(a, b, isNormalized);
		}

		// Divide : a_0,a_1,b_0,b_1�� �ɰ���
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
		// ���� ���͸� ���ڿ��� ��ȯ
		string result;
		vector<int> temp = v;

		while (!temp.empty()) {
			result.append(to_string(temp.back()));
			temp.pop_back();
		}

		return result;
	}

	static vector<int> convertStoI(const string& s) {
		// ���ڿ��� ���� ���ͷ� ��ȯ
		vector<int> result;

		for (int i = s.size() - 1; i >= 0; i--) {
			result.push_back(atoi(s.substr(i, 1).c_str()));
		}
		return result;
	}
};


/*
<���� Ʈ�� ������ -p191>
- ��ǥ �����͸� �޸� �ȿ� ������ �����ϴ� ���
- ��,�� �ȼ��� �ִ� ��� �׸��� ����
- 2^N * 2^N ũ���� ��� �׸��� �־��� �� �̰��� w,x,b�� ������ ���ڿ��� ����.
- ���� : ���� Ʈ���� ����� ���ڿ��� �Է¹޾� ���Ϲ��� ����� ���� Ʈ���� �����Ͽ� ���
- ���� ���� : ���� Ʈ���� ����� ���ڿ��� ���� ���� �׸����� ����
*/
class QuadTree {
	/*
	< Solution >
	0. Idea
	- ���� Ʈ���� �� ��尡 ����,�»��,���ϴ�,���ϴܿ� �ش��ϴ� sub���� Ʈ��
	- ������ ���� Ʈ���� �ϳ��� ���ҵ� ����
	- ��, 4���� sub-QuadTree(�ڽ� ����)�� ���ؼ� ��� ȣ���� ���ش�

	1. Main ����
	- ���� ���ڿ��� w,b�̸�(���� �����) �� ���� ��ȯ
	- x�̸� �ڽ� ��带 ������ �ִ� �� => ��� ȣ��
	- ���� return �� : x+ f(���ϴ�) + f(���ϴ�) + f(�»��) + f(���ϴ�)

	2. sub ����
	- Main ������ �ſ� ����� ����
	- �̹��� ������ �ϱ� ���ؼ��� ��� ������ �ʿ�
	- ������ �̹��� ũ��
	- ���� ��� ��ġ���� : (y,x)��ǥ
	- quadTree���� ���� Ž�� ��ġ
	*/
private:
	// MainProblem
	string quadTree;

	void setProblem(const string& quadTree) {
		this->quadTree = quadTree;
	}

	string recursiveReverse(int& pos) {
		pos++;
		// Base case : w�� b���ڿ��� ������ ��� �� ���� ��ȯ
		if (quadTree[pos] == 'b' || quadTree[pos] == 'w') {
			return quadTree.substr(pos, 1);
		}

		// x�� ������ x�� root�� ���� sub-quadTree�� ������ �� ����
		// => ��� ȣ��
		string leftTop = recursiveReverse(pos);
		string rightTop = recursiveReverse(pos);
		string leftBot = recursiveReverse(pos);
		string rightBot = recursiveReverse(pos);

		// �������ش�
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

		// Base case : w�� b���ڿ��� ������ ��� �� ���� ��ȯ
		if (quadTree[pos] == 'b' || quadTree[pos] == 'w') {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < size; j++) {
					originalPicture[y + i][x + j] = (quadTree[pos] == 'b') ? false : true;
				}
			}
			return;
		}

		// x�� ������ x�� root�� ���� sub-quadTree�� ������ �� ����
		// => ��� ȣ�� : x�� 4���� child node�� ���ؼ�
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
< ��Ÿ�� �ڸ��� - p195 >
- �ʺ� ���� N���� �������ڰ� �̾��� �ִ� ��Ÿ���� �־����� (N<2*10^4)
- �� ���������� ���̰� �־�����
- ��Ÿ�� �ȿ� ���Ե� ���簢���� �ִ� ���̸� ���ϴ� ����
*/
class Fence {
	/*
	< Solution >
	0. Idea
	- ���� Ž���� ��� O(N^2)=4*10^8 => �ð� �ʰ�
	- ���� ������ ���� ��Ÿ���� �������� �ɰ���
	=> f(leftCase) + f(rightCase) + f(midCase)
	- f(midCase) : ������� �������� Ž��. ���̰� �� ū �������� Ž���Ѵ�
	- merge sortó�� Ž���� ���� ��ġ(start,end)�� �˾ƾ� �Ѵ�
	- �ִ��� ���ϴ� ���� => ����ȭ ����(6�ܿ� salesmanproblem ����)
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

		// Base case : Ž���� ������ ���̰� 1�϶�
		if (start == end) {
			return fenceHeight[start];
		}

		// �߰��� �������� ��,��� ������ ������ => ������ 3���� ����
		int mid = (start + end) / 2;

		// subProblem 1&2 : ��, �쿡 ���� ����
		int subRet = max(recursiveCount(start, mid), recursiveCount(mid + 1, end));

		// subProblem : mid �ε������� �¿�� ���簢���� ��ġ�� ���
		int left = mid;
		int right = mid + 1;
		int curHeight = min(fenceHeight[left], fenceHeight[right]);
		int curArea = 0;

		// start+1~end-1 ���� �ȿ��� Ž��
		while (left > start || right < end) {
			/*
			���� ��ȸ
			- ���� ��ȸ�� ������ ����??
			- ������ ��ȸ�� �����ų�, ���� ���� > ������ ����
			- left > start ������ �� ������ ?
			A:left > start
			B: right == end
			C: enceHeight[left-1] > fenceHeight[right+1]
			~A: left<=start  => while�� ���ǿ��� ������ false
			~B: right<end    <= ~A ����
			~C: fenceHeight[left-1] < fenceHeight[right+1]
			~(A && (B || C) = ~A || ( ~B && ~C)
			= (~A||~B) && ( ~A || ~C)
			where ~A || ~B : ~B <=> right<end  (while�� ���� ������)
			= ~B && (
			*/
			if (left > start && ((right == end) || fenceHeight[left - 1] > fenceHeight[right + 1])) {
				left--;
				curHeight = min(fenceHeight[left], curHeight);
			}
			/*
			������ ��ȸ
			- ������ ��ȸ�� ������ ����??
			- ���� ��ȸ�� �����ų�, ���� ���� < ������ ����
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
< �ҹ��� - p201>
- ȥ���׷�� �ҵ��� ���� ������ ���ڿ��� ����
- �ҵ��� ��ĭ�� �����̸鼭 ������ �λ�
- (��,��)�� ��� �Ǽ�. �� �ܴ� ����
- ��� ����� ���ÿ� �����ϴ� Ƚ���� ���ϴ� ����
*/
class FanMeeting {
	/*
	< Solution >
	- ȥ�� �׷� A={a_0, a_1, ... , a_N} �� �׷� B={b_0, b_1, ... , b_M}
	- a_i,b_j : ������ �� 1, ������ �� 0 => a_i*b_j: �� �� ������ ��츸 non-zero
	- (AB)_k : sum(i+j=k)a_i*b_j
	- (AB)_k ==0 <=> ��ΰ� �����ϴ� ��Ȳ
	- nomalize���� AB���� zero ������ ���ϸ� �ȴ�.
	*/
private:
	vector<int> groupMembers;
	vector<int> fans;

	void setProblem(const string& groupMembers, const string& fans) {
		this->groupMembers = vector<int>(groupMembers.size(), 0);
		this->fans = vector<int>(fans.size(), 0);

		// ���ڸ� 1, ���ڸ� 0���� ����
		for (int i = 0; i < groupMembers.size(); i++) {
			if (groupMembers.at(i) == 'M') {
				this->groupMembers[i] = 1;
			}
		}

		// ���� �������� �̵��ϱ� ������ �������� �����ؾ���
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

		// 0 �� ��Ʈ���� ���� 
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
