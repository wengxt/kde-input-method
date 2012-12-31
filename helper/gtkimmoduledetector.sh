#!/bin/sh

test_command() {
    type "$1" >/dev/null 2>&1
}

test_immodules()
{
    GTK_QUERY_IMMODULES=$1

    if ! test_command "${GTK_QUERY_IMMODULES}"; then
        if test_command "${GTK_QUERY_IMMODULES}-64"; then
            GTK_QUERY_IMMODULES="${GTK_QUERY_IMMODULES}-64"
        elif test_command "${GTK_QUERY_IMMODULES}-32"; then
            GTK_QUERY_IMMODULES="${GTK_QUERY_IMMODULES}-32"
        else
            GTK_QUERY_IMMODULES=
        fi
    fi

    if [ -z "${GTK_QUERY_IMMODULES}" ]; then
        return 0
    fi

    "${GTK_QUERY_IMMODULES}" | grep -q "$2"
}

test_immodules gtk-query-immodules-3.0 "$1" || return 1
test_immodules gtk-query-immodules-2.0 "$1" || return 1
