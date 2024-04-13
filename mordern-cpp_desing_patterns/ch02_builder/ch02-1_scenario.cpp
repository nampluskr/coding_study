#if 0
// Chapter 2. Builder
// 2.1 Scenario

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

int main()
{
    if (1) {
        printf("*** Simple implementation:\n");
        string words[] = { "hello", "world" };
        ostringstream oss;
        oss << "<ul>" << endl;
        for (auto w : words)
            oss << "  <li>" << w << "</li>" << endl;
        oss << "</ul>" << endl;
        printf(oss.str().c_str());
    }
    printf("\n");

    if (1) {
        printf("***OOP implementation:\n");
        string words[] = { "hello", "world" };
        HtmlElement list{"ul", ""};
        for (auto w : words)
            list.elements.emplace_back(HtmlElement{"li", w});
        printf(list.str().c_str());
    }

    return 0;
}
#endif