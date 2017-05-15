#include "huffman.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

std::map<char, float> Coder::calcProbabilities(std::string str) {
	std::map<char, int> count;
	std::cout << "Calculating probabilities for " << str << std::endl;
	std::map<char, int>::iterator it;
	for (int i=0; i<str.size(); i++) {
		it = count.find(str[i]);
		if (it == count.end()) {
			count[str[i]] = 0;
		}
		count[str[i]] += 1;
	}

	std::map<char, float> probabilities;
	for(it=count.begin(); it!=count.end(); ++it) {
		probabilities[it->first] = it->second/((float) str.size());
		// std::cout << it->first << std::endl;
		// std::cout << probabilities[it->first] << std::endl;
	}
	return probabilities;
}

Tree::Tree() {

}
Tree::Tree(char value, float prob) {
	this->value = value;
	this->prob = prob;
	// this->value = value;
	// this->prob = prob;
}

Tree* Coder::createTree(std::map<char, float> prob) {
	std::cout << "In Create Tree\n";
	Tree *head;

	std::map<char, float>::iterator it;
	float min_prob;
	int min_pos = 0;
	float pos_counter;
	std::vector<Tree*> alphabet;
	std::vector<Tree*> saver;
	Tree *t, *s0, *s1, *x;
	t = new Tree();
	s0 = new Tree();
	s1 = new Tree();
	x = new Tree();
	//std::cout << "Instanced\n";
	for(it=prob.begin(); it!=prob.end(); it++) {
		t = new Tree();

		t->value = it->first;
		t->prob = it->second;
		alphabet.push_back(t);

	}
	std::cout << "Input: " << std::endl;
	for (int i=0; i<alphabet.size(); i++) {
		std::cout << alphabet[i]->value << " " << alphabet[i]->prob << std::endl;
	}

	t = new Tree();
	while (alphabet.size() > 1) {
		s0 = new Tree();
		s1 = new Tree();
		x = new Tree();

		min_prob = alphabet[0]->prob;
		min_pos = 0;
		for(int i=0; i<alphabet.size(); i++) {
			if (alphabet[i]->prob < min_prob) {
				min_pos = i;
				min_prob = alphabet[i]->prob;
			}

		}
		s0 = alphabet[min_pos];
		// s0->value = alphabet[min_pos]->value;
		// s0->prob = alphabet[min_pos]->prob;
		alphabet.erase(alphabet.begin() + min_pos);
		if(alphabet.size() == 0){

		}
		min_prob = alphabet[0]->prob;
		min_pos = 0;
		for(int i=0; i<alphabet.size(); i++) {
			if (alphabet[i]->prob < min_prob) {
				min_pos = i;
				min_prob = alphabet[i]->prob;
			}

		}
		s1 = alphabet[min_pos];
		// s1->value = alphabet[min_pos]->value;
		// s1->prob = alphabet[min_pos]->prob;
		// saver.push_back(alphabet[min_pos]);
		alphabet.erase(alphabet.begin() + min_pos);

		for (int i=0; i<alphabet.size(); i++) {
			std::cout << alphabet[i]->value << std::endl;
		}

		x->prob = s0->prob + s1->prob;
		//x->value = s0->value + s1->value;
		x->left = s0;
		x->right = s1;
		// std::cout << "Previous neighbours: " << std::endl << s0->left << " " << s0->right << std::endl << s1->left << " " << s1->right << std::endl;
		// x->left = new Tree(s0->value, s0->prob);
		// x->right = new Tree(s1->value, s1->prob);
		// std::cout << "Created node: " << x->value << " " << x->prob << std::endl;
		// std::cout << "Left: " << x->left->value << " " << x->left->prob << std::endl;
		// std::cout << "Right: " << x->right->value << " " << x->right->prob << std::endl;
		alphabet.push_back(x);
	}

	return alphabet[0];
	// Tree::printTree(x);

}

void Tree::printTree(int spaces) {
	for (int i=0; i<spaces; i++) {
		std::cout << " ";
	}
	if (this->value) {
		std::cout << " ";
	}
	std::cout << this->value << " " << this->prob << std::endl;
	if (this->left != NULL)
		this->left->printTree(spaces+2);
	if (this->right != NULL)
		this->right->printTree(spaces+2);
}

void Tree::insertLeft(Tree* node) {
	this->left = node;
}

void Tree::insertRight(Tree* node) {
	this->right = node;
}

void Tree::createAlphabetCodes(int spaces, std::string str_codes){
	for (int i=0; i<spaces; i++) {
		std::cout << " ";
	}
	if (this->value) {
		std::cout << " " << str_codes << " ";
	}
	std::cout << this->value << " " << this->prob << std::endl;
	if (this->left != NULL){
		str_codes += "0";
		this->left->createAlphabetCodes(spaces+2,str_codes);
	}
	str_codes.erase(str_codes.end() -1);

	if (this->right != NULL){
		str_codes += "1";
		this->right->createAlphabetCodes(spaces+2, str_codes);
	}
	str_codes.erase(str_codes.end() -1);
}


int main() {
	Coder *coder = new Coder();

	std::map<char, float> prob = coder->calcProbabilities("aaaaaaaaabbbbcccdddeef");
	Tree* t = coder->createTree(prob);
	std::cout << "Printing all nodes..." << std::endl;
	t->printTree(0);
	t->createAlphabetCodes(0, str_codes);


	return 0;
}
