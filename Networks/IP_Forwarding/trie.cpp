# include <bits/stdc++.h>
#include "trie.h"
using namespace std;

trie::trie()
{
	root= new node;
};

void trie::insert_ip(string netAddress, int subnetlength)
{
	node* temp= root;
	for(int i=0;i<subnetlength;i++)
	{
		if(netAddress[i] == '0')
		{
			if(temp->Zero == NULL)
				temp->Zero = new node;//if not present already, then only create a new node
			temp = temp->Zero;
			}
			else 
			{
				if(temp->One == NULL)
					temp->One = new node;//if not present already, then only create a new node
				temp = temp->One;
			}
	}
	temp-> is_prefix = true;
};

int trie::find_ip(string ip_find)
{
	node* temp = root;
	int level_found = -1;
	int i=0;
	for(i=0;i<32;i++)
	{
		if(temp -> is_prefix == true)
		{
			level_found = i;
		}
		if(ip_find[i] == '0')
		{
			if( temp-> Zero == NULL)
				break;//signifies this prefix is not there
			else temp = temp -> Zero;
		}
		else
		{
			if( temp-> One == NULL)
				break;//signifies this prefix is not there
			else temp= temp -> One;
		}
	}
	if(temp -> is_prefix == true && i == 32)
	{
		level_found = 32;
	}
	return level_found;
};
