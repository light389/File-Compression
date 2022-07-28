#include<bits/stdc++.h>
using namespace std;

struct Node{
	char character;
	int freq;
	Node *left, *right;

	Node(char character, int freq){
		this->character = character;
		this->freq = freq;
		left = NULL;
		right = NULL;
	}
};

struct compareNode {
	bool operator()(Node* a, Node*b){
		return (a->freq < b->freq);
	}
};


Node* buildHuffmanTree(map<char, int>& frequencies){
	int sz_str = frequencies.size();
	priority_queue<Node*, vector<Node*>, compareNode> minHeap;
	for(pair<char, int> element : frequencies){
		Node* newNode = new Node(element.first, element.second);
		minHeap.push(newNode);
	}
	while(minHeap.size() > 1){
		Node* leftNode = minHeap.top();
		minHeap.pop();
		Node* rightNode = minHeap.top();
		minHeap.pop();
		Node* newNode = new Node('`', leftNode->freq+rightNode->freq);
		newNode->left = leftNode;
		newNode->right = rightNode;
		minHeap.push(newNode);
	}
	return minHeap.top();
}

void getCodes(Node* node, map<char, string>& codes, string str = ""){
	if(!node)
		return;
	if(node->character != '`'){
		codes[node->character] = str;
		return;
	}
	getCodes(node->left, codes, str+"0");
	getCodes(node->right, codes, str+"1");
	return;
}

string decompress(string &binaryCode, Node* root){
	string decompressedStr = "";
	Node* node = root;
	int sz = (int)binaryCode.size();
	for(int index = 0; index < sz; index++){
		if(binaryCode[index]  == '0'){
			node = node->left;
		}
		else{
			node = node->right;
		}
		if(node->character != '`'){
			decompressedStr.push_back(node->character);
			node = root;
		}
	}
	return decompressedStr;
}

int main(){
	string str;
	getline(cin, str);
	map<char, int> frequencies;
	for(auto &ch:str){
		frequencies[ch]++;
	}
	Node* root = buildHuffmanTree(frequencies);
	// '`' used as the character for non-leaf nodes
	// this we will use when we recusively get our codes
	map<char, string> codes;
	getCodes(root, codes);
	const int ASCII_CODE_SIZE = 8;
	int initial_data_size = ASCII_CODE_SIZE*(int)str.size();
	int compressed_data_size = 0;
	for(auto &code:codes){
		compressed_data_size += (code.second.size())*frequencies[code.first];
	}
	string output = "";
	for(auto &ch:str){
		output += codes[ch];
	}
	cout << "Binary codes are as follows: \n";
	for(auto &code : codes){
		cout << code.first  << ": " << code.second << "\n";
	}
	cout << "Original file size was " << initial_data_size << " bits.\nCompressed file size is " << compressed_data_size << " bits.\n";
	cout << "There is a saving of " << initial_data_size - compressed_data_size << " bits.\n";
	cout << "Compressed binary code is: \n";
	cout << output << "\n";
	cout << "Decompressed string corresponding to compressed binary code is: \n";
	cout << decompress(output, root) << "\n";
}
