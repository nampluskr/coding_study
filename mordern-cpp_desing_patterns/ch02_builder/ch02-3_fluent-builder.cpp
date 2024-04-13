#if 0
// Chapter 2. Builder
// 2.3 Fluent Builder

#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct HtmlElement {
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;

    HtmlElement() {}
    HtmlElement(const string& name, const string& text)
        : name(name), text(text) {}

    string str(int indent = 0) const {
        ostringstream oss;
        string i(indent_size * indent, ' ');
        oss << i << "<" << name << ">" << endl;
        if (text.size() > 0)
            oss << string(indent_size * (indent + 1), ' ') << text << endl;

        for (const auto& e : elements)
            oss << e.str(indent + 1);

        oss << i << "</" << name << ">" << endl;
        return oss.str();
    }
};

struct HtmlBuilder {
    HtmlElement root;

    HtmlBuilder(string root_name) { root.name = root_name; }

    HtmlBuilder& add_child(string child_name, string child_text) {
        HtmlElement e{ child_name, child_text };
        root.elements.emplace_back(e);
        return *this;
    }
    HtmlBuilder* add_child2(string child_name, string child_text) {
        HtmlElement e{ child_name, child_text };
        root.elements.emplace_back(e);
        return this;
    }
    string str() { return root.str(); }
};

int main()
{
    if (1) {
        printf("*** Fluent Builder (Reference):\n");
        HtmlBuilder builder{ "ul" };
        builder.add_child("li", "hello").add_child("li", "world");
        printf(builder.str().c_str());
    }
    printf("\n");

    if (1) {
        printf("*** Fluent Builder (Pointer):\n");
        HtmlBuilder* builder = new HtmlBuilder("ul");
        builder->add_child2("li", "hello")->add_child2("li", "world");
        printf(builder->str().c_str());

        delete builder;
    }

    return 0;
}
#endif