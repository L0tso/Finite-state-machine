#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

void readAlphabet(string str, deque<char> & alphabet)
{
	for (size_t i = 0; i < str.size(); i++) 
		alphabet.push_back(str[i]);

}
void readStates(string str, deque<int> & states)
{
	for (size_t i = 0; i < str.size(); i++)
		states.push_back((int)str[i] - 48);

}
struct node
{
	node(char _letter, int _state) :letter(_letter), state(_state) {};
	char letter;
	int state;
};
string Result;
void findWords(int finish, map<int, deque<node>>& tree, int start)
{
	deque<node> parents;
	for (auto i : tree)
		for (size_t j = 0; j < i.second.size(); j++)
			if (finish == i.second[j].state && finish != i.first)
				parents.push_back(node(i.second[j].letter, i.first));

	for (size_t i = 0; i < parents.size(); i++) {
		Result += parents[i].letter;

		if (parents[i].state == start) {
			for (int k = Result.size() - 1; k > -1; k--)
				cout << Result[k];

			cout << endl;
			Result.clear();
			break;
		}
		findWords(parents[i].state, tree, start);
	}
}

void fileParsing(deque<char>& alphabet, deque<int>&states, int &start, deque <int>& finalStates, map<int, deque<node>>& tree)
{
	ifstream inputFile("inputs.txt");
	deque <string> inputs;
	for (int i = 0; i < 2; i++)
	{
		string bufferStr;
		getline(inputFile, bufferStr);
		bufferStr.erase(remove_if(bufferStr.begin(), bufferStr.end(), isspace), bufferStr.end());
		inputs.push_back(bufferStr);
	}
	inputFile >> start;

	int finalCount;
	inputFile >> finalCount;
	for (size_t i = 0; i < finalCount; i++)
	{
		int buffer;
		inputFile >> buffer;
		finalStates.push_back(buffer);
	}

	while (!inputFile.eof()) {
		int firstState;
		char letter;
		int secondState;
		inputFile >> firstState >> letter >> secondState;
		tree[firstState].push_back(node(letter, secondState));
	}
	readAlphabet(inputs[0], alphabet);
	readStates(inputs[1], states);
}

int main() {
	map<int, deque<node>> tree;
	deque<char> alphabet;
	deque<int>  states;
	deque<int>  finalStates;
	int startState = 0;
	fileParsing(alphabet, states, startState, finalStates, tree);

	if (finalStates.empty())
		for (size_t i = 0; i < states.size(); i++)
			findWords(states[i], tree, startState);
	else
		for (size_t i = 0; i < finalStates.size(); i++)
			findWords(finalStates[i], tree, startState);

	system("pause");
}
