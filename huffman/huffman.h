#include <map>
#include <string>
#include <pair>
#include <vector>

class Coder {
	std::map<char, std::string> codes;
	
	public:
	    std::map<char, float> calcProbabilities(std::string);
	    void createTree(std::map<char, float>);
    
};

class Decoder {

};

class Tree {
	Tree *left;
	Tree *right;
	char value;
	float prob;
	
	public:
		void insertLeft(Tree*);
		void insertRight(Tree*);

};