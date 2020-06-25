#include <cstring>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class table
{
  private:
    vector<double> num;
    vector<string> name;

  public:
    void setnumber(double n, string key) {}
    optional<double> getnumber(string key) {}
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
        if ( next_token == "let")
        {
            line_input >> next_token;
            string key = next_token;
            line_input >> next_token;
            std::stringstream token(next_token);
            double n;
            token >> n;
            variables.setnumber(n, key);
        }
        else
        {

            do
            {

                if (next_token != "+" && next_token != "-" &&
                    next_token != "*" && next_token != "/")
                {
                    std::stringstream token(next_token);
                    double n;
                    token >> n;
                    number.push_back(n);
                }

                else if (isalpha(next_token[0]))
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
                else
                {
                    if (number.size() < 2)
                    {
                        cout << "Too few operands" << endl;
                        break;
                    }
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
