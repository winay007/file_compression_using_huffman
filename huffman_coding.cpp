#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;

// A Tree node
struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

// Function to allocate a new tree node
Node *getNode(char ch, int freq, Node *left, Node *right)
{
	Node *node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

// Comparison object to be used to order the heap
struct comp
{
	bool operator()(Node *l, Node *r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};

// traverse the Huffman Tree and store Huffman Codes
// in a map.
void encode(Node *root, string str,
			unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right)
	{
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

// traverse the Huffman Tree and decode the encoded string
void decode(Node *root, int &index, string str, string &res)
{
	if (root == nullptr)
	{
		return;
	}

	// found a leaf node
	if (!root->left && !root->right)
	{
		res = res + root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str, res);
	else
		decode(root->right, index, str, res);
}

void print(priority_queue<Node *, vector<Node *>, comp> pq)
{
	while (pq.size())
	{
		cout << pq.top()->ch << " " << pq.top()->freq << endl;
		pq.pop();
	}
}

string getEncodedData(string text, Node *root)
{
	// print encoded string
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n"
		 << '\n';
	for (auto pair : huffmanCode)
	{
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n"
		 << text << '\n';

	// print encoded string
	string str = "";
	for (char ch : text)
	{
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n"
		 << str << '\n';
	return str;
}

void getDecodedData(Node *root, string encodedData)
{
	int index = -1;
	cout << "\nDecoded string is: \n";
	string res = "";
	while (index < (int)encodedData.size() - 2)
	{
		decode(root, index, encodedData, res);
	}
	cout<<res;
}

// Builds Huffman Tree and decode given input text
Node *buildHuffmanTree(string text)
{
	// count frequency of appearance of each character
	// and store it in a map
	unordered_map<char, int> freq;
	for (char ch : text)
	{
		freq[ch]++;
	}

	// Create a priority queue to store live nodes of
	// Huffman tree;
	priority_queue<Node *, vector<Node *>, comp> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair : freq)
	{
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// print(pq);

	// do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		// Remove the two nodes of highest priority
		// (lowest frequency) from the queue
		Node *left = pq.top();
		pq.pop();
		Node *right = pq.top();
		pq.pop();

		// Create a new internal node with these two nodes
		// as children and with frequency equal to the sum
		// of the two nodes' frequencies. Add the new node
		// to the priority queue.
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root stores pointer to root of Huffman Tree
	Node *root = pq.top();
	return root;
}

string readData(string fileName)
{
	fstream f;
	string data;
	f.open(fileName, ios ::in);	
	if (!f)
	{
		cout << "Unable to open the file." << endl;
		return data;
	}

	while (!f.eof())
	{
		string temp;
		getline(f,temp);
		data.append("\n" + temp);
	}
	return data;
}

int main()
{

	// string filePath;
	// cout << "Enter text: ";
	// getline(cin, filePath);
	// cout<<filePath<<endl;
	// string text = readData(filePath);
	// Node* root = buildHuffmanTree(text);
	// string encodedMsg = getEncodedData(text,root);
	// cout<<encodedMsg;
	// getDecodedData(root,encodedMsg);

	return 0;
}

//G:\\vit\\2nd year-sem1\\ADS\\tt.txt