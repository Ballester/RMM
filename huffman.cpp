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

Tree* Coder::createTree(std::map<char, float> prob) {
	std::cout << "In Create Tree\n";
	Tree *head;

	std::map<char, float>::iterator it;
	float min_prob;
	int min_pos = 0;
	float pos_counter;
	std::vector<Tree*> alphabet;
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
		min_prob = alphabet[0]->prob;
		min_pos = 0;
		for(int i=0; i<alphabet.size(); i++) {
			if (alphabet[i]->prob < min_prob) {
				min_pos = i;
				min_prob = alphabet[i]->prob;
			}

		}
		std::cout << "MIN: ";
		std::cout << alphabet[min_pos]->value << " " << min_prob << std::endl;
		s0->value = alphabet[min_pos]->value;
		s0->prob = alphabet[min_pos]->prob;
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
		std::cout << "MIN: ";
		std::cout << alphabet[min_pos]->value << " " << min_prob << std::endl;
		s1->value = alphabet[min_pos]->value;
		s1->prob = alphabet[min_pos]->prob;
		alphabet.erase(alphabet.begin() + min_pos);

		for (int i=0; i<alphabet.size(); i++) {
			std::cout << alphabet[i]->value << std::endl;
		}

		x = new Tree();
		x->prob = s0->prob + s1->prob;
		std::cout << "s0->value: " << s0->value << std::endl;
		std::cout << "s1->value: " << s1->value << std::endl;
		//x->value = s0->value + s1->value;
		x->left = s0;
		x->right = s1;
		std::cout << "X->value: " << x->value << std::endl;
		alphabet.push_back(x);
	}

	return alphabet[0];
	// Tree::printTree(x);

}

void Tree::printTree() {
	std::cout << "PRINT TREE" << std::endl;
	std::cout << this->value << " " << this->prob << std::endl;
	if (this->left != NULL)
		this->left->printTree();
	if (this->right != NULL)
		this->right->printTree();
}

void Tree::insertLeft(Tree* node) {
	this->left = node;
}

void Tree::insertRight(Tree* node) {
	this->right = node;
}



int main() {
	Coder *coder = new Coder();
	std::map<char, float> prob = coder->calcProbabilities("abaaaacccdddawdawdwadawdawdawdawdae");
	Tree* t = coder->createTree(prob);
	t->printTree();

	return 0;
}
