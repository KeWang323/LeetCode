/*

208. Implement Trie (Prefix Tree) (Medium)

Implement a trie with insert, search, and startsWith methods.

Note:
You may assume that all inputs are consist of lowercase letters a-z.

*/
class TrieNode {
public:
	TrieNode *next[26];
	bool isWord;
	TrieNode() :isWord(false), next({ NULL }) {}
};
class Trie {
public:
	/** Initialize your data structure here. */
	Trie() {
		root = new TrieNode();
	}

	/** Inserts a word into the trie. */
	void insert(string word) {
		TrieNode *p = root;
		for (int i = 0; i < word.size(); i++) {
			if (p->next[word[i] - 'a'] == NULL) {
				p->next[word[i] - 'a'] = new TrieNode();
			}
			p = p->next[word[i] - 'a'];
		}
		p->isWord = true;
	}

	/** Returns if the word is in the trie. */
	bool search(string word) {
		TrieNode *p = find(word);
		return p != NULL && p->isWord == true;
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		return find(prefix) != NULL;
	}
private:
	TrieNode *root;
	TrieNode* find(string word) {
		TrieNode *p = root;
		for (int i = 0; i < word.size() && p != NULL; i++) {
			p = p->next[word[i] - 'a'];
		}
		return p;
	}
};
/**
* Your Trie object will be instantiated and called as such:
* Trie obj = new Trie();
* obj.insert(word);
* bool param_2 = obj.search(word);
* bool param_3 = obj.startsWith(prefix);
*/