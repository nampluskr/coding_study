#if 0
// Chapter 2. Builder
// 2.4 Communicating Intent

#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct HtmlBuilder;

struct HtmlElement {
    string name;
    string text;
    vector<HtmlElement> elements;
    const size_t indent_size = 2;
    friend HtmlBuilder;

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

    static HtmlBuilder build(const string& root_name);

protected:
    HtmlElement() {}
    HtmlElement(const string& name, const string& text)
        : name(name), text(text) {}
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

    operator HtmlElement() const { return root; }   // since C++11
    HtmlElement get() const { return root; }
};

HtmlBuilder HtmlElement::build(const string& root_name) {
    return HtmlBuilder(root_name);
}

int main()
{
    if (1) {
        printf("*** Communicating Intent (static builder):\n");
        HtmlBuilder builder = HtmlElement::build("ul")
            .add_child("li", "hello")
            .add_child("li", "world");
        printf(builder.str().c_str());
    }

    printf("\n");
    if (1) {
        printf("*** Communicating Intent (Move Constructor):\n");
        HtmlElement element = HtmlElement::build("ul")
            .add_child("li", "hello")
            .add_child("li", "world");
        printf(element.str().c_str());
    }

    printf("\n");
    if (1) {
        printf("*** Communicating Intent (get method):\n");
        HtmlElement element = HtmlElement::build("ul")
            .add_child("li", "hello")
            .add_child("li", "world")
            .get();
        printf(element.str().c_str());
    }

    return 0;
}
#endif