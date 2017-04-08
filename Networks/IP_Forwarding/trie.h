#include <bits/stdc++.h>
using namespace std;

class trie
{
public:
	struct node
	{
		node* Zero ;
		node* One ;
		bool is_prefix;

		node()
		{
			Zero = NULL;
			One = NULL;
			is_prefix = false;
		}
	};
	node* root;

	trie();
	void insert_ip(string netAddress, int subnetlength);
	int find_ip(string ip_find);

};