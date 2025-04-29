#!/bin/sh

DIR="folly"

REGEXP_keywords='\b(alignas|alignof|and|and_eq|asm|atomic_cancel|atomic_commit|atomic_noexcept|auto|bitand|bitor|bool|break|case|catch|char|char8_t|char16_t|char32_t|class|compl|concept|const|consteval|constexpr|constinit|const_cast|continue|contract_assert|co_await|co_return|co_yield|decltype|default|delete|do|double|dynamic_cast|else|enum|explicit|export|extern|false|float|for|friend|goto|if|inline|int|long|mutable|namespace|new|noexcept|not|not_eq|nullptr|operator|or|or_eq|private|protected|public|reflexpr|register|reinterpret_cast|requires|return|short|signed|sizeof|static|static_assert|static_cast|struct|switch|synchronized|template|this|thread_local|throw|true|try|typedef|typeid|typename|union|unsigned|using|virtual|void|volatile|wchar_t|while|xor|xor_eq)\b'
REGEXP_identifiers="\b[_a-zA-Z][_a-zA-Z0-9]*\b"
REGEXP_integer_literal="[^.-]\b(0[bB][01]+('[01]+)*[uUlLzZ]*|0[xX][0-9a-fA-F]+('[0-9a-fA-F]+)*[uUlLzZ]*|0[0-7]+('[0-7]+)*[uUlLzZ]*|[1-9][0-9]*('[0-9]+)*[uUlLzZ]*|0('[0]+)*[uUlLzZ]*)\b[^.-]"
REGEXP_decimal_literal="\b[1-9][0-9]*('[0-9]+)*[uUlLzZ]*\b"
REGEXP_oct_literal="\b(0[0-7]+('[0-7]+)*[uUlLzZ]*)\b"
REGEXP_hex_literal="\b(0[xX][0-9a-fA-F]+('[0-9a-fA-F]+)*[uUlLzZ]*\.?[0-9pP]*)\b"
REGEXP_floating_literal="[-+]?\b(([0-9]+\.[0-9]*|[0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?[fFlL]?)|(0[xX][0-9a-fA-F]*\.[0-9a-fA-F]+([pP][-+]?[0-9]+)?[fFlL]?)\b"
REGEXP_string_literal='(L|u8|u|U)?R?\"([^"\\]*(\\.[^"\\]*)*)?\"'
REGEXP_character_literal="^int "
REGEXP_user_defined_literals="^int "
REGEXP_prep="\s*#\s*(include|define|if|endif|else|elif|pragma|undef|error|warning)[^'\n]*"
REGEXP_comparison_operators="^int "
REGEXP_assignment_operators="^int "
REGEXP_member_access_operators="^int "
REGEXP_comments="//\s*.*|/\*[^*]*\*+(?:[^/*][^*]*\*+)*/"
#REGEXP_comments="//.*"


#for f in `find $DIR -name "*.cpp"`; do
  #  echo "*** File $f"
 #   grep -o -E $REGEXP_keywords $f
#done


    grep -o -E $REGEXP_comments 1.cpp
