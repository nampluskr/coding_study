#if 0
// Chapter 2. Builder
// 2.5 Groovy-style Builder

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Tag {
    string name;
    string text;
    vector<Tag> children;
    vector<pair<string, string>> attributes;

    friend ostream& operator<<(ostream& os, const Tag& tag) {
        os << "<" << tag.name;
        for (const auto& att : tag.attributes)
            os << " " << att.first << "=\"" << att.second << "\"";
        if (tag.children.size() == 0 && tag.text.length() == 0) {
            os << "/>" << endl;
        }
        else {
            os << ">" << endl;
            if (tag.text.length())
                os << tag.text << endl;
            for (const auto& child : tag.children)
                os << child;
            os << "</" << tag.name << ">" << endl;
        }
        return os;
    }

protected:
    Tag(const string& name, const string& text)
        : name{ name }, text{ text } {}
    Tag(const string& name, const vector<Tag>& children)
        : name{ name }, children{ children } {}
};

struct Paragraph : Tag {
    explicit Paragraph(const string& text) : Tag("p", text) {}
    Paragraph(initializer_list<Tag> children) : Tag("p", children) {}
};

struct Image : Tag {
    explicit Image(const string& url) : Tag("img", "") {
        attributes.push_back({ "src", url });
    }
};

int main()
{
    cout << Paragraph{ Image("http://pokemon.com/pikachu.png") } << endl;
    return 0;
}
#endif