#include "huffman.h"
#include <cstdio>
#include <vector>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <string>
#include <fstream>
#include <bitset>

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
	Tree *t, *s0, *s1, *x;

	//Get first value
	for(it=prob.begin(); it!=prob.end(); it++) {
		t = new Tree();

		t->value = it->first;
		t->prob = it->second;
		alphabet.push_back(t);

	}
	std::cout << "Input: " << std::endl;
	for (int i=0; i<alphabet.size(); i++) {
		alphabet[i]->left = alphabet[i]->right = NULL;
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
		alphabet.erase(alphabet.begin() + min_pos);

		//Get second value
		min_prob = alphabet[0]->prob;
		min_pos = 0;
		for(int i=0; i<alphabet.size(); i++) {
			if (alphabet[i]->prob < min_prob) {
				min_pos = i;
				min_prob = alphabet[i]->prob;
			}

		}
		s1 = alphabet[min_pos];
		alphabet.erase(alphabet.begin() + min_pos);


		x->prob = s0->prob + s1->prob;
		x->left = s1;
		x->right = s0;

		std::cout << "Created node: " << x->value << " " << x->prob << std::endl;
		std::cout << "Left: " << x->left->value << " " << x->left->prob << std::endl;
		std::cout << "Right: " << x->right->value << " " << x->right->prob << std::endl;
		alphabet.push_back(x);
		// for (int i=0; i<alphabet.size(); i++) {
		// 	std::cout << alphabet[i]->value << std::endl;
		// }
		// if (s1->value == 'd') {
		// 	std::cout << "BUG: " << s1->value << " " << s1->prob << " " << s1->left << " " << s1->right->value << std::endl;
		// }
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
		codes[this->value] = str_codes;

		std::map<char, std::string>::iterator it;
		// int i=0;
		// for(it=codes.begin(); it!=codes.end(); it++) {
		// 	std::cout << "CREATE NODE: " << i++ << std::endl;
		// 	std::cout << it->first << " " << it->second << std::endl;
		// }

		// std::cout << "CREATE NODE: " << this->value << " " << this->codes[this->value] << std::endl;
	}
	std::cout << this->value << " " << this->prob << std::endl;
	if (this->left != NULL){
		str_codes += "1";
		this->left->createAlphabetCodes(spaces+2,str_codes);
	}
	str_codes.erase(str_codes.end() -1);

	if (this->right != NULL){
		str_codes += "0";
		this->right->createAlphabetCodes(spaces+2, str_codes);
	}
	// str_codes.erase(str_codes.end() -1);
}

std::string Coder::generateCode(std::string input) {
	std::string code = "";
	// std::map<char, std::string>::iterator it;
	// int i=0;
	// for(it=this->codes.begin(); it!=this->codes.end(); it++) {
	// 	std::cout << it->first << " " << it->second << std::endl;
	// }
	for(int i=0; i<input.size(); i++) {
		// std::cout << codes[input[i]] << std::endl;
		code += codes[input[i]];
	}

	return code;
}

std::string Coder::decode(std::string code) {
	std::string to_decode = "";
	std::string output = "";
	std::map<char, std::string>::iterator it;
	for (int i=0; i<code.size(); i++) {
		to_decode += code[i];

		for(it=this->codes.begin(); it!=this->codes.end(); it++) {
			if(it->second == to_decode) {
				output += it->first;
				to_decode = "";
			}
		}
	}

	return output;

}

void saveProbToFile(std::map<char, float> probs) {
	freopen("probs.txt","w",stdout);
	std::map<char, float>::iterator it;
	for(it=probs.begin(); it!=probs.end(); it++) {
		std::cout << it->first << " " << it->second << std::endl;
	}

	freopen ("/dev/tty", "a", stdout);
}

std::map<char, float> loadProbFromFile() {
	char value;
	float prob;
	std::map<char, float> probs;

	std::cout << "OPENING FILE" << std::endl;

	FILE *f = fopen("probs.txt", "r");
	while (fscanf(f, "%c %f", &value, &prob) != -1) {
		std::cout << value << " " << prob << std::endl;
		probs[value] = prob;
	}
	return probs;
}

int main() {
	std::string input = "aaaaaaaaabbbbcccdddeef";
	Coder *coder = new Coder();
	std::map<char, float> prob;
	int controler;
	std::ofstream myfile;


	std::cout << "Entre com uma das entradas abaixo:\n"
	<< "1. Para rodar o teste default com a entrada default\n"
	<< "2. Para rodar com as probabilidades do arquivo\n"
	<< "3. Para salvar as probabilidades no arquivo\n"
 	<< std::endl;
	std:: cin >> controler;

	if(controler == 1){
		myfile.open ("input.bin");
		for (std::size_t i = 0; i < input.size(); ++i){
			myfile << std::bitset<8>(input.c_str()[i]);
		}
		myfile.close();

		prob = coder->calcProbabilities(input);
		Tree* t = coder->createTree(prob);
		std::cout << "Printing all nodes..." << std::endl;
		std::string str_codes;
		t->printTree(0);
		t->createAlphabetCodes(0, str_codes);
		std::cout << "Printing codes..." << std::endl;
		std::map<char, std::string>::iterator it;
		for(it=codes.begin(); it!=codes.end(); it++) {
			coder->codes[it->first] = it->second;
		}
		std::cout << "Probabilidades salva no arquivo probs.txt" << std::endl;
		saveProbToFile(prob);
	}
	if(controler == 2){
			prob = loadProbFromFile();
			Tree* t = coder->createTree(prob);
			std::cout << "Printing all nodes..." << std::endl;
			std::string str_codes;
			t->printTree(0);
			t->createAlphabetCodes(0, str_codes);
			std::cout << "Printing codes..." << std::endl;
			std::map<char, std::string>::iterator it;
			for(it=codes.begin(); it!=codes.end(); it++) {
				coder->codes[it->first] = it->second;
			}
	}
	if(controler == 3){
		prob = coder->calcProbabilities(input);
		Tree* t = coder->createTree(prob);
		std::string str_codes;
		t->printTree(0);
		t->createAlphabetCodes(0, str_codes);
		std::cout << "Printing codes..." << std::endl;
		std::map<char, std::string>::iterator it;
		for(it=codes.begin(); it!=codes.end(); it++) {
			coder->codes[it->first] = it->second;
		}
		std::cout << "Probabilidades salva no arquivo probs.txt" << std::endl;
		saveProbToFile(prob);
	}

	if(controler < 4){
		std::cout << "Enconded: ";
		std::string code = coder->generateCode(input);
		std::cout << code << std::endl;
		std::string toWrite = code;
		myfile.open ("output.bin");
		for (std::size_t i = 0; i < toWrite.size(); ++i){
			myfile << std::bitset<1>(toWrite.c_str()[i]);
		}
		myfile.close();

		std::cout << "Decoded: ";
		std::cout << coder->decode(code) << std::endl;
	}
	return 0;
}
