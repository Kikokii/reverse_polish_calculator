#include <cstring>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

class table
{
  private:
    vector<double> num;
    vector<string> name;

  public:
    void setnumber(double n, string key)
    {
        for (size_t i = 0; i < name.size(); i++)
        {
            if (name[i] == key)
            {
                num[i] = n;
                string tempname = name[i];
                double tempnum = num[i];
                for (size_t j = i + 1; j < name.size(); j ++) {
                    name[j - 1] = name[j];
                    num[j - 1] = num[j];
                }
                name.back() = tempname;
                num.back() = tempnum;

                return;
            }
        }
        num.push_back(n);
        name.push_back(key);
    }

    optional<double> getnumber(string key)
    {
        for (size_t i = 0; i < name.size(); i++)
        {
            if (name[i] == key)
            {
                return num[i];
            }
        }
        return nullopt;
    }

    std::tuple<string, double> getentry(size_t index) const
    {
        return tuple(name[index], num[index]);
    }

    size_t getnumberofentries() const { return name.size(); }
};

int main()
{
    std::string line;
    vector<double> number;
    table variables;

    while (cout << "   ", getline(cin, line))
    {
        std::stringstream line_input(line);
        std::string next_token;
        if (!(line_input >> next_token))
            continue;
        if (next_token == "let")
        {
            line_input >> next_token;
            string key = next_token;
            line_input >> next_token;
            std::stringstream token(next_token);
            double n;
            token >> n;
            variables.setnumber(n, key);
        }
        else if (next_token == "show")
        {
            size_t size = variables.getnumberofentries();

            for (size_t i = size - std::min(size_t(10), size); i < size; i++)
            {
                auto [a, b] = variables.getentry(i);
                cout << a << " " << b << endl;
            }
        }
        else
        {
            do
            {
                if (isalpha(next_token[0]))
                {
                    auto x = variables.getnumber(next_token);
                    if (x)
                    {
                        number.push_back(x.value());
                    }
                    else
                    {
                        cout << next_token << " is not defined" << endl;
                        break;
                    }
                }
                else if (next_token != "+" && next_token != "-" &&
                         next_token != "*" && next_token != "/")
                {
                    std::stringstream token(next_token);
                    double n;
                    token >> n;
                    number.push_back(n);
                }
                else
                {
                    if (number.size() < 2)
                    {
                        cout << "Too few operands" << endl;
                        break;
                    }
                    double x = number.back();
                    number.pop_back();
                    double y = number.back();
                    number.pop_back();
                    double z;
                    if (next_token == "+")
                    {
                        z = x + y;
                    }
                    if (next_token == "-")
                    {
                        z = y - x;
                    }
                    if (next_token == "*")
                    {
                        z = x * y;
                    }
                    if (next_token == "/")
                    {
                        z = y / x;
                    }
                    number.push_back(z);
                }
            } while (line_input >> next_token);

            if (number.size() > 1)
            {
                cout << "Too many operands" << endl;
                break;
            }
            else
            {
                cout << number.back() << endl;
                variables.setnumber(number.back(), "ans");
                number.pop_back();
            }
        }
    }
}
