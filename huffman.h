#include <map>
#include <string>
#include <utility>
#include <vector>

class Tree {

	public:
		void insertLeft(Tree*);
		void insertRight(Tree*);
		void printTree(int);
		Tree();
		Tree(char, float);

		Tree *left;
		Tree *right;
		char value;
		float prob;
};

class Coder {
	std::map<char, std::string> codes;

	public:
	    std::map<char, float> calcProbabilities(std::string);
	    Tree* createTree(std::map<char, float>);
};

class Decoder {

};
