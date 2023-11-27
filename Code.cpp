// https://www.hackerrank.com/contests/apl-lab-03/challenges/big-integer-operations/problem

#include<bits/stdc++.h>

using namespace std;

const int N = 200;

class Integer {

public:
    vector<int> v;
    string numString;
    int sign = 1;
    vector<int> mag;

    void integerBuildHelper() {
        v = vector<int>(200);
        int i = 0;
        if(numString[0] == '-') {
            sign = -1;
            i++;
        }

        int j = 0;

        for(int k = numString.size() - 1; k >= i; k--) {
            v[j++] = numString[k] - '0';
        }
        reverse(v.begin(), v.end());
        getSignPart();
    }

    
    Integer() {

    }
    Integer(string num) {
        numString = num;
        
        integerBuildHelper();
        
    }

    // return the magnitude of the integer in string format
    string getIntPart() {
        string s = ""; 
        int firstZero = true;
        for(int i = 0; i < (int)v.size(); i++) {
            if(v[i] != 0) {
                firstZero = false;
                s += (v[i] + '0');
            } else if(!firstZero) {
                s += (v[i] + '0');
            }
        }
        if(s == "") s += "0";
        return s;
    }

    int numLength() {
        return getIntPart().size();
    }

    // returns the updated sign 
    int getSignPart() {
        string i = getIntPart();
        if(i == "0") {
            sign = 1;
        }
        return sign;
    }

    // vector<int> getMag() {
    //     string s = getIntPart();
    //     vector<int> ans;
    //     int firstZero = true;
    //     for(int i = 0; i < s.size(); i++) {
    //         if(s[i] != "0") {
    //             ans.push_back(s[i] - '0');
    //             firstZero = false;
    //         } else {
    //             ans.push_back(s[i] - '0');
    //         }
    //     }
    //     return (mag = s);

    // }
 
    // returns the intger in string format
    string getInt() {
        string s;
        if(getSignPart() == -1) {
            s += "-";
        } 
        s += getIntPart();
        return s;
    }

    string addHelper(string s1, string s2) {
        
        reverse(s1.begin(), s1.end());
        reverse(s2.begin(), s2.end());
        
        int _n1 = s1.size();
        int _n2 = s2.size();
        
        int _carry = 0;
        string ans;

        for(int _i = 0; _i < max(_n1, _n2); _i++) {
            int _temp = _carry;
            if(_i < _n1) {
                _temp += (s1[_i] - '0');
            } 
            if(_i < _n2) {
                _temp += (s2[_i] - '0');
            }
            _carry = _temp / 10;
            ans += to_string(_temp%10)[0];
        }
        if(_carry) {
            ans += "1";
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

    string subHelper(string s1, string s2) {
        reverse(s1.begin(), s1.end());
        reverse(s2.begin(), s2.end());

        int _n1 = s1.size();
        int _n2 = s2.size();
        int _carry = 0;
        string ans = "";
        
        for(int i = 0; i < _n2; i++) {
            int currSub = 0;
            currSub = (s1[i] - '0') - (s2[i] - '0') - _carry;
               
            if(currSub < 0) {
                currSub += 10;
                _carry = 1;
            } else {
                _carry = 0;
            }
            ans += (currSub + '0');
        }
            
        for(int i = _n2; i < _n1; i++) {
            int currSub = 0;
            currSub = (s1[i] - '0') - _carry;
               
            if(currSub < 0) {
                currSub += 10;
                _carry = 1;
            } else {
                _carry = 0;
            }
            ans += (currSub + '0');
        }
        
        reverse(ans.begin(), ans.end());
        string str;
        bool firstZero = true;
        
        for(int i = 0; i < (int)ans.size(); i++) {
            if(ans[i] != '0') {
                str += ans[i];
                firstZero = false;
            } else if(!firstZero) {
                str += ans[i];
            }
        }
        return str;
    }

    bool checkSmall(string s1, string s2) {
        if(s1.size() < s2.size())
            return true;
        else if(s1.size() > s2.size())
            return false;
        else {
            return (s1 < s2);
        }
    }

    bool operator==(Integer& num) {
        int _n1 = numLength();
        int _n2 = num.numLength();

        if(_n1 != _n2 || getSignPart() != num.getSignPart()) return false;
        return (getIntPart() == num.getIntPart());
    }

    bool operator!=(Integer& num) {
        return !(*this == num);
    }

    bool operator<(Integer& num) {
        int _n1 = numLength();
        int _n2 = num.numLength();

        if(getSignPart() == -1 && num.getSignPart() == 1) return true;
        else if(getSignPart() == 1 && num.getSignPart() == -1) return false;
        else {
            if(getSignPart() < 0) {
                if(_n1 == _n2) {
                    return (getIntPart() > num.getIntPart());
                } else {
                    if(_n1 > _n2) return true;
                    else return false;
                }
            } else {
                if(_n1 == _n2) {
                    return (getIntPart() < num.getIntPart());
                } else {
                    if(_n1 > _n2) {
                        return false;
                    } else {
                        return true;
                    }
                }
            }
        }
    }

    bool operator<=(Integer& num) {
        return (*this < num || *this == num);
    }

    bool operator>(Integer& num) {
        return !(*this <= num);
    }

    bool operator>=(Integer& num) {
        return (*this == num || *this > num);
    }

    Integer operator+(Integer& num) {
        string ans;
        if(getSignPart() == num.getSignPart()) {
            if(getSignPart() == -1) {
                ans += "-";
            }
            ans += addHelper(getIntPart(), num.getIntPart());
        } else {
            if(checkSmall(getIntPart(), num.getIntPart())) {
                if(num.getSignPart() == -1) {
                    ans += "-";
                }
                ans += subHelper(num.getIntPart(), getIntPart());
            } else {
                if(getSignPart() == -1) {
                    ans += "-";
                }
                ans += subHelper(getIntPart(), num.getIntPart());
            }
        }
        Integer result;
        result.numString = ans;
        result.integerBuildHelper();
        return result;
    }

    Integer operator-(Integer& num) {
        num.sign *= -1;
        return (*this+num);
    }

    string multiply(string num1, string num2) {
        vector<int>pos(num1.size() + num2.size());
        for(int i = num1.size() - 1; i >= 0; i--){
            for(int j = num2.size() - 1; j >= 0; j--){
                int sum = (num1[i] - '0') * (num2[j] - '0') + pos[i + j + 1];
                pos[i + j + 1] = sum % 10;
                pos[i + j] += sum / 10;
            }
        }
        string res = "";
        for(auto x: pos) if(!(res == "" && x == 0)) res.push_back(x + '0');
        return res == "" ? "0" : res;
    }

    Integer operator*(Integer& num) {
        int t_sign = (getSignPart()*num.getSignPart());
        string ans = multiply(getIntPart(), num.getIntPart());
        if(t_sign == -1) {
            ans = "-" + ans;
        }
        Integer result;
        result.numString = ans;
        result.integerBuildHelper();
        return result;
    }

    Integer div(Integer dividend, Integer divisor) {
        
        Integer one;
        one.numString = "1";
        one.integerBuildHelper();
        Integer quotient;
        quotient.numString = "0";
        quotient.integerBuildHelper();
        
        while(dividend >= divisor) {
            dividend = dividend - divisor;
            divisor.sign = 1;
            quotient = quotient + one;
        }
        return quotient;
    }

    Integer mod(Integer dividend, Integer divisor) {
        Integer t = div(dividend, divisor);
        Integer d = t*divisor;
        Integer rem = dividend - d;
        return rem;
    }

    Integer operator/(Integer& num) {
        
        Integer result;
        //cout << "result " << result << endl;
        Integer ten;
        ten.numString = "10";
        ten.integerBuildHelper();
        //cout << "ten " << ten << endl;

        int t_sign = getSignPart()*num.getSignPart();

        sign = 1;
        num.sign = 1;
        num.getSignPart();

        string num1 = getIntPart();
        string num2 = num.getIntPart();

        int index = 0;

        Integer dividend;
        dividend.numString.append(1,(num1[index]));
        dividend.integerBuildHelper();
        
        //cout << "dividend " << dividend <<  endl;
        
        while(dividend < num) {
            dividend = dividend*ten;
            Integer next;
            next.numString.append(1, (num1[++index]));
            next.integerBuildHelper();
            dividend = dividend + next;
        }
        
        //cout << "dividend " << dividend << endl;

        while((int)num1.size() > index) {
            Integer ans = div(dividend, num);
            //cout << "ans " << ans << endl;
            result.numString = result.numString + ans.numString;
            result.integerBuildHelper();
            ans = mod(dividend, num);
            ans = ans*ten;
            Integer next;
            next.numString.append(1, (num1[++index]));
            next.integerBuildHelper();
            ans = ans + next;
            dividend = ans;
            // cout << "dividend " << dividend << endl;
            // cout << "result " << result << endl;
        }
        
        result.sign = t_sign;
        result.getSignPart();

        if(result.numLength()) {
            result.numString = "0";
            result.getSignPart();
        }
        return result;
    }

    Integer operator%(Integer& num) {
        int t_sign = sign;
        num.sign = 1;
        sign = 1;
        Integer t = *this / num;
        Integer d = t*num;
        Integer rem = *this - d;
        rem.sign = t_sign;
        return rem;
    }

    Integer operator+=(Integer& num) {
        *this = *this + num;
        return *this;
    }

    Integer operator-=(Integer& num) {
        *this = *this - num;
        return *this;
    }

    Integer operator*=(Integer& num) {
        *this = *this * num;
        return *this;
    }

    Integer operator/=(Integer& num) {
        *this = *this/num;
        return *this;
    }

    Integer operator%=(Integer& num) {
        *this = *this % num;
        return *this;
    }

    friend std::ostream& operator<<(ostream& out, Integer& n);
    friend std::istream& operator>>(istream& in, Integer& n);
};

std::ostream& operator<<(ostream& out, Integer& n) {  
    return (out << n.getInt());
}

std::istream& operator>>(istream& in, Integer& n) {
    return (in >> n.numString);
}

int main() {
    string s;

    while(true) {
        cin >> s; 
        
        if(s == "+") {
            Integer a, b, c;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            c = a + b;
            cout << c;
        }
        
        else if(s == "-"){
            Integer a, b, c;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            c = a - b;
            cout << c;
        }
        
        else if(s == "*") {
            Integer a, b, c;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            c = a * b;
            cout << c;
        }
        
        else if(s == "/") {
            Integer a, b, c;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            c = a / b;
            cout << c;
        }
        
        else if(s == "%") {
            Integer a, b, c;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            c = a % b;
            cout << c;
        } 
            
        else if(s == "+=") {
            Integer a, b, c;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            a += b;
            cout << a;
        } 
            
        else if(s == "-=") {
            Integer a, b, c;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            a -= b;
            cout << a;
        } 
            
        else if(s == "*=") {
            Integer a, b, c;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            a *= b;
            cout << a;
        } 
            
        else if(s == "/=") {
            Integer a, b, c;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            a /= b;
            cout << a;
        } 
            
        else if(s == "%=") {
            Integer a, b, c;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            a %= b;
            cout << a;
        } 
            
        else if(s == "<") {
            Integer a, b;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            bool ans = (a < b);
            if(ans) cout << "true";
            else cout << "false";
        } 
            
        else if(s == "<=") {
            Integer a, b;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            bool ans = (a <= b);
            if(ans) cout << "true";
            else cout << "false";
        } 
            
        else if(s == ">") {
            Integer a, b;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            bool ans = (a > b);
            if(ans) cout << "true";
            else cout << "false";
        } 
            
        else if(s == ">=") {
            Integer a, b;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            bool ans = (a >= b);
            if(ans) cout << "true";
            else cout << "false";
        } 
        
        else if(s == "==") {
            Integer a, b;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            bool ans = (a == b);
            if(ans) cout << "true";
            else cout << "false";
        } 
            
        else if(s == "!=") {
            Integer a, b;
            cin >> a >> b;
            a.integerBuildHelper();
            b.integerBuildHelper();
            bool ans = (a != b);
            if(ans) cout << "true";
            else cout << "false";
        } 
            
        else if(s == "end"){
            break;
        }
        cout << endl;
    }
    
    return 0;
}

