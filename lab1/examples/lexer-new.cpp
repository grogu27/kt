#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iterator>
#include <regex>
#include <sstream>
#include <string>

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Usage: lexer FILE\n";
        std::exit(1);
    }
    std::ifstream ifs;
    ifs.open(argv[1], std::ifstream::in);

    std::regex regexp("include|main|define|case|if|for|while|return|using|catch|try|true|false|else|throw");
    //std::regex regexp("\b(alignas|alignof|and|and_eq|asm|atomic_cancel|atomic_commit|atomic_noexcept|auto|bitand|bitor|bool|break|case|catch|char|char8_t|char16_t|char32_t|class|compl|concept|const|consteval|constexpr|constinit|const_cast|continue|contract_assert|co_await|co_return|co_yield|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|reflexpr|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|synchronized|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq)\b");
    //std::regex regexp("\b[_a-zA-Z][_a-zA-Z0-9]*\b");
    //std::regex regexp("[^.-]\b(0[bB][01]+('[01]+)*[uUlLzZ]*|0[xX][0-9a-fA-F]+('[0-9a-fA-F]+)*[uUlLzZ]*|0[0-7]+('[0-7]+)*[uUlLzZ]*|[1-9][0-9]*('[0-9]+)*[uUlLzZ]*|0('[0]+)*[uUlLzZ]*)\b[^.-]");
    //std::regex regexp("\b[1-9][0-9]*('[0-9]+)*[uUlLzZ]*\b");
    //std::regex regexp("\b(0[0-7]+('[0-7]+)*[uUlLzZ]*)\b");
    //std::regex regexp("\b(0[xX][0-9a-fA-F]+('[0-9a-fA-F]+)*[uUlLzZ]*\.?[0-9pP]*)\b");
    //std::regex regexp("[-+]?\b(([0-9]+\.[0-9]*|[0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?[fFlL]?)|(0[xX][0-9a-fA-F]*\.[0-9a-fA-F]+([pP][-+]?[0-9]+)?[fFlL]?)\b");
    //std::regex regexp3('(L|u8|u|U)?R?\"([^"\\]*(\\.[^"\\]*)*)?\');
    //std::regex regexp("\s*#\s*(include|define|if|endif|else|elif|pragma|undef|error|warning)[^'\n]*");
    //std::regex regexp"//\s*.*|/\*[^*]*\*+(?:[^/*][^*]*\*+)*/");
    std::string str;
    while(std::getline(ifs, str)) {
        auto lexeme_begin = std::sregex_iterator(str.begin(), str.end(), regexp);
        auto lexeme_end = std::sregex_iterator();
        int nlexemes = std::distance(lexeme_begin, lexeme_end);
        if (nlexemes > 0) {
            std::cout << "Found " << std::distance(lexeme_begin, lexeme_end) << " lexemes\n";
            for (std::sregex_iterator i = lexeme_begin; i != lexeme_end; ++i) {
                std::smatch match = *i;
                std::cout << "-- lexeme: " << match.str() << "\n";
            }
        }
    }
    ifs.close();

    return 0;
}
