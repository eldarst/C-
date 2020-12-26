#include <iostream>
#include <numeric>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Rational{
public:
    Rational(){
        num = 0;
        den = 1;
    }
    Rational(int numerator , int denominator){
        if(denominator == 0){
            cout << "Invalid argument" << endl;
            throw exception();
        }
        int nod = gcd(numerator, denominator);
        if(numerator != 0) {
            if ((numerator > 0 && denominator > 0) || (numerator < 0 && denominator < 0)) {
                numerator /= nod;
                denominator /= nod;
                num = abs(numerator);
                den = abs(denominator);
            } else if ((numerator > 0 && denominator < 0) || (numerator < 0 && denominator > 0)) {
                numerator /= nod;
                denominator /= nod;
                num = -abs(numerator);
                den = abs(denominator);

            }
        }
        else{
            num = 0;
            den = 1;
        }
    }

    int Numerator() const {
        return num;
    }
    int Denominator() const {
        return den;
    }
private:
    int den;
    int num;
};


bool operator== (const Rational& lhs, const Rational& rhs){
    if(lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator())
        return true;
    else
        return false;
}


Rational operator +(const Rational& lhs, const Rational& rhs){
    if(lhs.Numerator() == 0)
        return rhs;
    else if(rhs.Numerator() == 0)
        return lhs;
    else{
        int od = lcm(lhs.Denominator(), rhs.Denominator());
        int left = lhs.Numerator() * (od/lhs.Denominator());
        int right = rhs.Numerator() * (od/rhs.Denominator());

        return Rational(left + right, od);}
}


Rational operator -(const Rational& lhs, const Rational& rhs){
    if(lhs.Numerator() == 0)
        return Rational(-rhs.Numerator(), -rhs.Denominator());
    else if(rhs.Numerator() == 0)
        return lhs;
    else{
        int od = lcm(lhs.Denominator(), rhs.Denominator());
        int left = lhs.Numerator() * (od/lhs.Denominator());
        int right = rhs.Numerator() * (od/rhs.Denominator());

        return Rational(left - right, od);}
}


Rational operator *(const Rational& lhs, const Rational& rhs){
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}


Rational operator /(const Rational& lhs, const Rational&rhs)
{
    if(rhs.Numerator() == 0){
        cout << "Division by zero" << endl;
        throw exception();
    }
    return Rational(lhs.Numerator() * rhs.Denominator(), lhs.Denominator() * rhs.Numerator());
}
bool EnsureNextSymbol(istream& stream){
    if(stream.peek() == '/') {
        stream.ignore(1);
        return true;
    }

    else
        return false;
}

istream& operator >>(istream& stream, Rational& ratio){
    if(stream) {
        int ln, rn;
        if(!(stream >> ln)){
            return stream;
        }
        if(!EnsureNextSymbol(stream)){
            return stream;
        }
        if(!(stream >> rn)){
            return stream;
        }
        ratio = Rational(ln, rn);
    }
    return stream;
}
ostream& operator <<( ostream& stream, const Rational& ratio){
    stream << ratio.Numerator() << "/" << ratio.Denominator() ;
    return stream;
}

bool operator< (const Rational& lhs, const Rational& rhs) {
    double lhn = lhs.Numerator();
    double lhd = lhs.Denominator();
    double rhn = rhs.Numerator();
    double rhd = rhs.Denominator();
    bool k = lhn/lhd < rhn/rhd;
    return k;
}
Rational ReadCalculation(stringstream& stream){
    Rational lhs, rhs;
    if(!(stream >> lhs)) {
        cout << "Invalid argument" << endl;
        throw exception();
    }
    string operation;
    stream.ignore(1);
    stream >> operation;
    stream.ignore(1);
    if(!(stream >> rhs)) {
        cout << "Invalid argument" << endl;
        throw exception();
    }
    Rational result;
    if(operation == "*")
        result = lhs * rhs;
    else if( operation == "/")
        result = lhs / rhs;
    else if(operation == "+")
        result = lhs + rhs;
    else if(operation == "-")
        result = lhs - rhs;
    else
        throw runtime_error("Invalid operation");
    return result;

}
int main() {
    string line;
    getline(cin, line);
        try{
            stringstream s(line);
            Rational r =ReadCalculation(s);
            cout << r << endl;
            }
        catch (exception& ex) {
        }


    return 0;
}
