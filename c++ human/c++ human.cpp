// midterm2time.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
class Person {
private:
    string name;
    int age;
public:
    friend ostream& operator<<(ostream& os, Person& human) {
        os << "Name: " << human.name << " age: " << human.age;
    }
    Person& operator+=(int age) {
        this->age += age;
        return *this;
    }
    Person& operator+=(const Person& rhs) {
        age += rhs.age;
        return *this;
    }
    explicit operator bool() const {
        if (age > 18) {
            return true;
        }
        return false;
    }
    Person(string name, int age) : name(name), age(age) {}
    Person(const Person& rhs) {
        name = rhs.name;
        age = rhs.age;
    }
    virtual ~Person() {}
    Person& operator=(const Person& rhs) {
        if (this != &rhs) {
            name = rhs.name;
            age = rhs.age;
        }
        return *this;
    }
    string getName() const { return name; }
    int getAge() const { return age; }
    virtual void say() { cout << "I am a person" << endl; }
    Person& operator++() {
        age++;
        return *this;
    }
    Person operator++(int) {
        Person temp = *this;
        age++;
        return temp;
    }
};

class Adult;

class General :public Person {
private:
    vector<Person*> army;
public:
    General(const General& gen) : Person(gen) {
        army = gen.army;
    }
    Person& operator[] (size_t access) {
        return *army[access];
    }
    Person operator[](size_t access) const {
        return *army[access];
    }
    General(const string name, int age) : Person(name, age) {}
    void say() { cout << "I AM A GENERAL!" << endl; }
    bool hire(Person& person) {
        if (person.getAge() < 18) {
            cout << "You are not old enough!" << endl;
            return false;
        }
        cout << "Welcome recruit " << person.getName() << "! " << endl;
        army.push_back(&person);
        return true;
    }
};

class Child : public Person {
private:
    Adult* parent;
public:
    Child(const Child& child) : Person(child) {
        parent = child.parent;
    }
    ~Child() {}
    Child& operator==(const Child& rhs) {
        if (this != &rhs) {
            this->Person::operator=(rhs);
            parent = rhs.parent;
        }
        return *this;
    }
    explicit operator bool() const {
        if (this->getAge() >= 18) {
            return false;
        }
        return true;
    }
    ~Child() {}
    Child(const string name, int age) : Person(name, age), parent(nullptr) {}
    void setParent(Adult* parent) {
        this->parent = parent;
    }
    void say() {
        cout << "I am a child" << endl;
    }
};

class Adult : public Person {
private:
    vector<Child*> children;
public:
    explicit operator bool() const {
        if (this->getAge() >= 18) {
            return true;
        }
        return false;
    }
    ~Adult() {
        for (Child* c : children) {
            delete c;
            c = nullptr;
        }
        children.clear();
    }
    Adult(string name, int age) : Person(name, age) {}
    void say() { cout << "Adult" << endl; }
    void birth(const string name, int age) {
        Child* c = new Child(name, age);
        c->setParent(this);
        children.push_back(c);
    }
    void adopt(Child& child) {
        children.push_back(&child);
    }
};

bool operator==(const Person& lhs, const Person& rhs) {
    if ((lhs.getName() == rhs.getName()) && (lhs.getAge() == rhs.getAge())) {
        return true;
    }
    return false;
}

Person operator+(const Person& lhs, const Person& rhs) {
    Person temp = lhs;
    return temp += rhs;
}
int main() {
    ifstream ifs("text.txt");
    if (!ifs) {
        cerr << "No text file.";
    }
    vector<Person*> people;
    Child boy("boy", 18);
    Adult parent("parent", 202);
    parent.birth("baby", 1);
}