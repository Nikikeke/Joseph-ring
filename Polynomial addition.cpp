#include <iostream>  
#include <vector>  
#include <algorithm>  
#include <functional>  
#include <utility>  
#include <sstream>  

void getTwoPolynomial(std::vector<std::pair<int, int> > &lhs,
	std::vector<std::pair<int, int> > &rhs)
{
	int coefficient, power;
	std::string strBuf;
	std::stringstream ss;

	std::getline(std::cin, strBuf);
	ss.str(strBuf);
	while (!ss.eof())
	{
		ss >> coefficient >> power;
		if (0 > power)
		{
			break;
		}

		lhs.push_back(std::make_pair(coefficient, power));
	}

	std::getline(std::cin, strBuf);
	ss.str("");
	ss.clear();
	ss.str(strBuf);
	while (!ss.eof())
	{
		ss >> coefficient >> power;
		if (0 > power)
		{
			break;
		}

		rhs.push_back(std::make_pair(coefficient, power));
	}
}

struct descend_order : public std::unary_function<std::pair<int, int>,
	bool>
{
	result_type operator()(const argument_type &lhs, const argument_type &rhs)
	{
		return lhs.second > rhs.second;
	}
};

void compute(std::vector<std::pair<int, int> > &ret,
	std::vector<std::pair<int, int> > &lhs,
	std::vector<std::pair<int, int> > &rhs)
{  
	std::sort(lhs.begin(), lhs.end(), descend_order());
	std::sort(rhs.begin(), rhs.end(), descend_order());

	std::pair<int, int> tmp;
	std::vector<std::pair<int, int> >::iterator next;
	std::vector<std::pair<int, int> >::iterator itl = lhs.begin();
	std::vector<std::pair<int, int> >::iterator itr = rhs.begin();
	while (lhs.end() != itl && rhs.end() != itr)
	{
		if (itl->second > itr->second)
		{
			tmp = *itl;
			next = itl;
			++next;

			while (lhs.end() != next && next->second == tmp.second)
			{
				tmp.first += next->first;
				++next;
			}
			itl = next;
		}
		else if (itl->second < itr->second)
		{
			tmp = *itr;
			next = itr;
			++next;

			while (rhs.end() != next && next->second == tmp.second)
			{
				tmp.first += next->first;
				++next;
			}
			itr = next;
		}
		else
		{
			tmp.second = itl->second;
			tmp.first = itl->first + itr->first;
			next = itl;
			++next;

			while (lhs.end() != next && next->second == tmp.second)
			{
				tmp.first += next->first;
				++next;
			}
			itl = next;

			next = itr;
			++next;
   
			while (rhs.end() != next && next->second == tmp.second)
			{
				tmp.first += next->first;
				++next;
			}
			itr = next;
		}

		if (0 == tmp.first)
		{
			continue;
		}
		ret.push_back(tmp);
	}

	while (lhs.end() != itl)
	{
		tmp = *itl;
		next = itl;
		++next;
		// check the power of the next item is the same   
		while (lhs.end() != next && next->second == tmp.second)
		{
			tmp.first += next->first;
			++next;
		}
		itl = next;

		if (0 != tmp.first)
		{
			ret.push_back(tmp);
		}
	}

	while (rhs.end() != itr)
	{
		tmp = *itr;
		next = itr;
		++next;
  
		while (rhs.end() != next && next->second == tmp.second)
		{
			tmp.first += next->first;
			++next;
		}
		itr = next;

		if (0 != tmp.first)
		{
			ret.push_back(tmp);
		}
	}
}

void print(std::vector<std::pair<int, int> > &ret)
{
	std::vector<std::pair<int, int> >::iterator it;

	for (it = ret.begin(); it != ret.end(); ++it)
	{
		std::cout << "[ " << it->first << ' ' << it->second << " ] ";
	}

	std::cout << '\n';
}

int main(void)
{
	int n;
	std::vector<std::pair<int, int> > lhs;
	std::vector<std::pair<int, int> > rhs;
	std::vector<std::pair<int, int> > ret;

	std::cin >> n;
	std::cin.ignore(2, '\n');
	lhs.reserve(50);
	rhs.reserve(50);
	ret.reserve(50);

	while (0 < n)
	{
		getTwoPolynomial(lhs, rhs);
		compute(ret, lhs, rhs);
		print(ret);

		--n;
		lhs.clear();
		rhs.clear();
		ret.clear();
	}

	return 0;
}