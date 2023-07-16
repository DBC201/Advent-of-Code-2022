#include <utils/file_utils.h>
#include <stack>
#include <utils/string_utils.h>
#include <algorithm>

namespace file_utils = utils::file_utils;
namespace string_utils = utils::string_utils;

struct Node {
	Node *previous = nullptr;
	Node *next = nullptr;
	Node *parent = nullptr;
	Node *child = nullptr;
	int val = -1;
};

void print_list(Node* node) {
	while (node != nullptr) {
		if (node->val != -1) {
			std::cout << node->val << ",";
		}
		else if (node->child != nullptr) {
			std::cout << "[";
			print_list(node->child);
			std::cout << "],";
		}
		node = node->next;
	}
}

/**
 * @brief 
 * 0: not in order
 * 1: in order
 * 2: inconclusive
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int compare(Node *a, Node *b) {
	while (a != nullptr && b != nullptr) {
		if (a->val == -1 && b->val == -1) {
			int comparison = compare(a->child, b->child);
			if (comparison == 0 || comparison == 1) {
				return comparison;
			}
		}
		else if (a->val == -1) {
			Node *n = new Node;
			n->child = new Node;
			n->child->val = b->val;
			n->child->parent = n;
			int comparison = compare(a, n);
			free(n->child);
			free(n);
			if (comparison == 0 || comparison == 1) {
				return comparison;
			}
		}
		else if (b->val == -1) {
			Node *n = new Node;
			n->child = new Node;
			n->child->val = a->val;
			n->child->parent = n;
			int comparison = compare(n, b);
			free(n->child);
			free(n);
			if (comparison == 0 || comparison == 1) {
				return comparison;
			}
		}
		else {
			if (a->val < b->val) {
				return 1;
			}
			else if (a->val > b->val) {
				return 0;
			}
		}
		a = a->next;
		b = b->next;
	}

	if (a == nullptr && b == nullptr) {
		return 2;
	}
	else if (a == nullptr) {
		return 1;
	}
	else {
		return 0;
	}
}

bool comparison_wrapper(Node* a, Node* b) {
	int comparison = compare(a, b);
	return comparison > 0;
}

int main(int argc, char **argv) {
	if (argc < 2)
	{
		std::cerr << "no filename given" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::vector<Node*> nodes;

	file_utils::process_lines(argv[1], [&](auto line) {
		std::stack<char> token_stack;
		std::stack<Node*> node_stack;
		for (int i=0; i<line.length(); i++) {
			char c = line[i];
			if (c == ']') {
				std::string curr_num;
				Node *child_node = nullptr;
				while (1) {
					char top = token_stack.top();
					token_stack.pop();
					if (top == ',' || top == '[') {
						Node *element = new Node;
						if (curr_num == "n") {
							element->child = node_stack.top();
							node_stack.pop();
							element->child->parent = element;
						}
						else if (curr_num.length() != 0) {
							element->val = string_utils::convert_string<int>(curr_num);
						}
						if (child_node != nullptr) {
							element->next = child_node;
							child_node->previous = element;
						}
						child_node = element;
						curr_num = "";
						if (top == '[') {
							break;
						}
					}
					else {
						curr_num.insert(0, 1, top);
					}
				}
				node_stack.push(child_node);
				token_stack.push('n');
			}
			else {
				token_stack.push(c);
			}
		}

		if (!node_stack.empty()) {
			nodes.push_back(node_stack.top());
		}
	});

	int sum = 0;

	for (int i=0; i<nodes.size()-1; i+=2) {
		if (compare(nodes[i], nodes[i+1]) == 1) {
			sum += (i/2)+1;
		}
	}

	std::cout << sum << std::endl;

	Node *p1 = new Node;
	p1->child = new Node;
	p1->child->parent = p1;
	p1->child->val = 2;

	Node *p2 = new Node;
	p2->child = new Node;
	p2->child->parent = p2;
	p2->child->val = 6;

	nodes.push_back(p1);
	nodes.push_back(p2);

	std::sort(nodes.begin(), nodes.end(), comparison_wrapper);

	int i1 = 0;
	int i2 = 0;

	for (int i=0; i<nodes.size(); i++) {
		if (nodes[i] == p1) {
			i1 = i+1;
		}
		else if (nodes[i] == p2) {
			i2 = i+1;
		}
	}

	std::cout << i1*i2 << std::endl;
	
	return 0;
}
