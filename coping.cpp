#include <iostream>
#include <sstream>
#include <random>
using namespace std;

random_device dev;
mt19937 rng(dev());
uniform_int_distribution<std::mt19937::result_type> dist(1,1000000);

class Item {
public:
    Item() {
        stringstream s;
        s << dist(rng);
        id_ = s.str();
        cout << "Constructor of " << id_ << endl;
    }
    Item(const Item& c) {
        cout << "Copy constructor: " << id_ << " <- " << c.GetID() << endl;
        id_ = "Copy of " + c.GetID();
    }
    Item(Item&& c) {
        cout << "Move constructor: " << id_ << " <- " << c.GetID() << endl;
        swap(id_, c.GetID());
    }
    ~Item() {
        cout << "Destructor of " << id_ << endl;
    }
    const string& GetID() const { return id_; }
    string& GetID() { return id_; }

private:
    string id_;
};

void f_no_copy(const Item& c) {
    cout << "f_no_copy(" << c.GetID() << ")" << endl;
}

void f_should_copy(const Item c) {
    cout << "f_should_copy(" << c.GetID() << ")" << endl;
}

void f_should_move(Item&& c) {
    Item m(move(c));
    cout << "f_should_move(" << m.GetID() << ")" << endl;
}

void f_nested(const Item& c) {
    cout << "f_nested(" << c.GetID() << ")" << endl;
    f_no_copy(c);
    f_should_copy(c);
}

void f_nested_move(Item&& c) {
    cout << "f_nested_move(" << c.GetID() << ")" << endl;
    f_no_copy(c);
    f_should_move(move(c));
}

int main(int argc, char** argv)
{
    cout << "Coping test" << endl;

    Item c;
    f_nested(c);
    f_nested_move(move(c));

    return 0;
}