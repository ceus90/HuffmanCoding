#include "stdafx.h"
#include <iostream>
#include <limits>
#include <cctype>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <cctype>
#include <ctime>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#include <iterator>
#include <algorithm>
using namespace std;

//Structure for nodes
struct node
{
	node * leftChild;
	node * rightChild;
	double frequency;
	string content;
	string code;
};

// To record all the nodes that may be created in the whole process
vector<node> nodeArray;

node  extractMin()
{
	double temp = (double)INT_MAX;
	vector<node>::iterator i1, pos;
	for (i1 = nodeArray.begin(); i1 != nodeArray.end(); i1++)
	{
		if (temp>(*i1).frequency)
		{
			pos = i1;
			temp = (*i1).frequency;
		}
	}
	node tempNode = (*pos);
	nodeArray.erase(pos);
	return tempNode;
}

node getHuffmanTree()
{
	while (!nodeArray.empty())
	{
		node * tempNode = new node;
		node * tempNode1 = new node;
		node * tempNode2 = new node;
		*tempNode1 = extractMin();
		*tempNode2 = extractMin();
		tempNode->leftChild = tempNode1;
		tempNode->rightChild = tempNode2;
		tempNode->frequency = tempNode1->frequency + tempNode2->frequency;
		nodeArray.push_back(*tempNode);
		if (nodeArray.size() == 1)//only the root node exsits
			break;
	}
	return nodeArray[0];
}

void BFS(node * temproot, string s)
{
	node * root1 = new node;
	root1 = temproot;
	root1->code = s;
	if (root1 == NULL)
	{
	}
	else if (root1->leftChild == NULL && root1->rightChild == NULL)
	{
		std::ofstream outfile;
		outfile.open("CodeTable.txt", std::ios_base::app);
		outfile << root1->content << "  --->  "<<root1->code << endl;
	}
	else
	{
		root1->leftChild->code = s.append("0");
		s.erase(s.end() - 1);
		root1->rightChild->code = s.append("1");
		s.erase(s.end() - 1);
		BFS(root1->leftChild, s.append("0"));
		s.erase(s.end() - 1);
		BFS(root1->rightChild, s.append("1"));
		s.erase(s.end() - 1);
	}
}

void main()
{
	int tempInt, B[7], i, j; //7 is the number of lines in the input text file. Change here for different input file
	string A[14], C[7], tempString = ""; //7 is the number of lines in the input text file. Change here for different input file
	char D[7]; //7 is the number of lines in the input text file. Change here for different input file
	ifstream myfile("freq.txt"); //Opening the the input file
	while (!myfile.eof())
		for (i = 0; i < 14; i++)
			myfile >> A[i]; //Copying from input file
	j = 0;
	i = 0;
	while (j < 14)
	{
		C[i++] = A[j]; //Taking the character list or the first column of the input file
		j = j + 2;
	}
	j = 1;
	i = 0;
	while (j < 14)
	{
		B[i++] = stoi(A[j]);//Taking the integer list or the second column of the input file
		j = j + 2;
	}
	for (i = 0; i < 7; i++) //7 is the number of lines in the input text file. Change here for different input file
	{
		node tempNode;
		tempString = C[i];
		tempInt = B[i];
		tempNode.frequency = tempInt;
		tempNode.content = tempString;
		tempNode.leftChild = NULL;
		tempNode.rightChild = NULL;
		nodeArray.push_back(tempNode);
	}
	node root = getHuffmanTree();
	BFS(&root, "");
	cout << endl << "CodeTable.txt is ready" << endl;
	getchar();
}