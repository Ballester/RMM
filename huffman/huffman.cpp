#include "huffman.h"
#include <iostream>
#include <vector>
#include <algorithm>

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

void Coder::createTree(std::map<char, float> prob) {
	Tree *head;
	
	//FALTA IMPLEMENTAR O SORT POR PROBABILIDADE
	// std::sort(prob.begin(), prob.end());
	std::map<char, float>::iterator it;
	float min = 0;
	float min_pos = 0;	
	float pos_counter;
	std::vector<Tree*> alphabet;
	Tree *t, *s0, *s1;
	for(it=prob.begin(); it!=prob.end(); it++) {
		t->value = it->first;
		t->prob = it->second;
		alphabet.push_back(t);

	}

	while (alphabet.size() > 1) {
		for(int i=0; i<alphabet.size(); i++) {
			if (i == 0) {
				min = it->second;
				min_pos = 0;
				
			}

			if (alphabet[i]->prob < min) {
				min_pos = i;
				min = it->second;
			}

		}
		s0->value = alphabet[i]->value;
		s0->prob = alphabet[i]->prob; 

		for(it=prob.begin(); it!=prob.end(); it++) {
			for(int i=0; i<alphabet.size(); i++) {
				if (i == 0) {
					min = it->second;
					min_pos = 0;
					
				}

				if (alphabet[i]->prob < min) {
					min_pos = i;
					min = it->second;
				}
			
			}
		}
		s1->value = alphabet[i]->value;
		s1->prob = alphabet[i]->prob;
	}

}

void Tree::insertLeft(Tree* node) {
	this->left = node;
}

void Tree::insertRight(Tree* node) {
	this->right = node;
}



int main() {
	Coder *coder = new Coder();
	std::map<char, float> prob = coder->calcProbabilities("aaaadddddbbbbcde");
	coder->createTree(prob);

	return 0;
}