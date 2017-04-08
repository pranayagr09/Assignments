#include <bits/stdc++.h>
#include "trie.h"
using namespace std;

trie routeTable;
int main()
{
	string s;
	getline(cin,s);
	getline(cin,s);

	while(s != "default")
	{
		istringstream iss(s);
		int ip_add_part;//signifies ip address parts
		int netmask_part;
		char dot;
		string ip;
		for(int i=0;i<3;i++)
		{
			iss>>ip_add_part;
			ip += bitset<8>(ip_add_part).to_string();
			iss>>dot;
		}
		iss>>ip_add_part;
		ip += bitset<8>(ip_add_part).to_string();//ip string in binary

		int subnetLength = 0;//signifies no. of 1's in subnet mask
		int i=0;
		for(;i<3;i++)
		{
			iss>>netmask_part;
			iss>>dot;
			if(netmask_part == 255)
				subnetLength += 8;
			else 
			{
				string t = bitset<8>(netmask_part).to_string();
				for(int j=0;j<8 && t[j] != '0';j++)
					subnetLength++;
				break;
			}
		}
		iss>>netmask_part;
		if(i == 3)
		{
			string t = bitset<8>(netmask_part).to_string();
			for(int j=0;j<8 && t[j] != '0';j++)
				subnetLength++;
		}
		routeTable.insert_ip(ip,subnetLength);
		getline(cin,s);
	}

	getline(cin,s);
	istringstream iss(s);
	int test_ips;//no. of queries
	iss>>test_ips;
	getline(cin,s);
	for(int i=0;i<test_ips;i++)
	{
		istringstream iss(s);
		int test_ip_part;
		char dot;
		string ip;
		for(int j=0;j<3;j++)
		{
			iss>>test_ip_part;
			cout<<test_ip_part;
			ip += bitset<8>(test_ip_part).to_string();
			iss>>dot;
			cout<<dot;
		}
		iss>>test_ip_part;
		cout<<test_ip_part<<" ";
		ip += bitset<8>(test_ip_part).to_string();
		getline(cin,s);
		if(routeTable.find_ip(ip) == -1)
			cout<<"default"<<endl;
		else 
		{
		//for network address
			int len = routeTable.find_ip(ip);
			string ip_net_add = ip.substr(0, len);
			for( int j = len;j<=32;j++)
				ip_net_add += '0';
			string temp;
			temp = ip_net_add[0];
			for(int i=1;i<=24;i++)
			{
				if(i % 8 == 0)
				{
					cout<<bitset<8>(temp).to_ulong()<<".";
					temp= ip_net_add[i];
				}
				else temp += ip_net_add[i];
			}
			for(int i=25;i<32;i++)
				temp +=  ip_net_add[i];
			cout<<bitset<8>(temp).to_ulong()<<" ";

		//for subnet masks
			int counter=0;
			int netmaskPart[4]= {0};
			while(len/8>=1)
			{
				netmaskPart[counter]=255;
				counter++;
				len -= 8;
			}
			if(counter != 4)
			{
				string leftover = "";
				for(int i=0;i<len;i++)
					leftover += '1';
				for(int i=len;i<8;i++)
					leftover += '0';
				netmaskPart[counter] = bitset<8>(leftover).to_ulong();
			}
			for(int i=0;i<3;i++)
				cout<<netmaskPart[i]<<".";
			cout<<netmaskPart[3]<<endl;
		}
	}
}