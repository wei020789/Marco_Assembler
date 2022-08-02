#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

ifstream file;
vector<string> DEFTAB, ARGTAB, OUTPUT, tmp, rec;
vector < pair<string, pair<int, int>>> NAMETAB;
string lab, op, val, s;
int line = -1, nti, dti;
bool expanding = false;
size_t pos;

void split(string, string);
void GETLINE();
void PROCESSLINE();
void DEFINE();
void EXPAND();

void split(string str, string delimiter)
{
	tmp.clear();
	while ((pos = str.find(delimiter)) != string::npos)
	{
		tmp.push_back(str.substr(0, pos));
		str = str.substr(pos + 1);
	}
	tmp.push_back(str);
	if (tmp.size() < 3)
		tmp.push_back("");
}
void GETLINE()
{
	if (expanding)
	{
		s = DEFTAB[dti];
		for (int i = 0; i < ARGTAB.size(); i++)
		{
			pos = s.find("?" + to_string(i));
			if (pos != string::npos)
			{
				s.replace(pos, 1 + to_string(i).size(), ARGTAB[i]);
				break;
			}
		}
		if (dti - 1 == NAMETAB[nti].second.first)
			s.insert(0, lab);
	}
	else
	{
		while (getline(file, s) && (s[0] == '.' || s == ""));
		split(s, "\t");
		lab = tmp[0];
		op = tmp[1];
		val = tmp[2];
	}
}
void PROCESSLINE()
{
	bool found = false;
	for (int i = 0; i < NAMETAB.size(); i++)
	{
		if (op == NAMETAB[i].first)
		{
			found = true;
			op.clear();
			nti = i;
		}
	}
	if (found)
	{
		EXPAND();
	}
	else if (op == "MACRO")
	{
		DEFINE();
	}
	else
		OUTPUT.push_back(s);
}
void DEFINE()
{
	int level = 1;

	rec.clear();
	line++;
	NAMETAB.push_back(make_pair(lab, make_pair(line, line)));
	DEFTAB.push_back(lab + "\t" + val);

	split(val, ",");
	for (int i = 0; i < tmp.size(); i++)
	{
		rec.push_back(tmp[i]);
	}
	while (level > 0)
	{
		line++;
		GETLINE();
		for (int i = 0; i < rec.size(); i++)
		{
			pos = s.find(rec[i]);
			if (pos != string::npos)
			{
				s.replace(pos, rec[i].size(), "?" + to_string(i));
			}
		}
		DEFTAB.push_back(s);
		if (op == "MARCO") level++;
		if (op == "MEND") level--;
	}
	NAMETAB.back().second.second = line;
}
void EXPAND()
{
	expanding = true;

	OUTPUT.push_back("." + s);
	ARGTAB.clear();
	split(val, ",");
	for (int i = 0; i < tmp.size(); i++)
		ARGTAB.push_back(tmp[i]);

	for (dti = NAMETAB[nti].second.first + 1; dti < NAMETAB[nti].second.second; dti++)
	{
		GETLINE();
		PROCESSLINE();
	}

	expanding = false;
}