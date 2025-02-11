#!/bin/sh

DIR="folly"

REGEXP="include|main|define|case|if|for|while|return|using|catch|try|true|false|else|throw"
REGEXP_keyword="^int "
REGEXP_identifiers="^int "
REGEXP_Integer_literal="^int "
REGEXP_decimal_literal="^int "
REGEXP_oct_literal="^int "
REGEXP_hex_literal="^int "
REGEXP_floating_literal="^int "
REGEXP_string_literal="^int "
REGEXP_character_literal="^int "
REGEXP_user_defined_literals="^int "
REGEXP_prep="^int "
REGEXP_comparison_operators="^int "
REGEXP_assignment_operators="^int "
REGEXP_member_access_operators="^int "
REGEXP_comments="^int "


for f in `find $DIR -name "*.cpp"`; do
    echo "*** File $f"
    grep -E $REGEXP $f
done
