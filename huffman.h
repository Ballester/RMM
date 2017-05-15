#include <map>
#include <string>
#include <utility>
#include <vector>


std::map<char, std::string> codes;
class Tree {

	public:
		void insertLeft(Tree*);
		void insertRight(Tree*);
		void printTree(int);
		Tree();
		Tree(char, float);
		void createAlphabetCodes(int spaces, std::string str_codes);

		Tree *left;
		Tree *right;
		char value;
		float prob;
};

class Coder {
	public:
			std::map<char, std::string> codes;
	    std::map<char, float> calcProbabilities(std::string);
	    std::string generateCode(std::string);
			std::string decode(std::string);
			Tree* createTree(std::map<char, float>);


};
