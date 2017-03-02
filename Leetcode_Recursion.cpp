/*

247. Strobogrammatic Number II (Medium)

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

Find all strobogrammatic numbers that are of length = n.

For example,
Given n = 2, return ["11","69","88","96"].

Hint:

Try to use recursion and notice that it should recurse with n - 2 instead of n - 1.

*/
class Solution {
public:
	vector<string> findStrobogrammatic(int n) {
		return findStrobogrammatic(n, n);
	}
private:
	vector<string> findStrobogrammatic(int n, const int& m) {
		if (n == 0) {
			return{ "" };
		}
		if (n == 1) {
			return{ "0", "1", "8" };
		}
		vector<string> res_sub = findStrobogrammatic(n - 2, m), res;
		for (string s : res_sub) {
			if (n != m) {
				res.push_back("0" + s + "0");
			}
			res.push_back("1" + s + "1");
			res.push_back("6" + s + "9");
			res.push_back("8" + s + "8");
			res.push_back("9" + s + "6");
		}
		return res;
	}
};