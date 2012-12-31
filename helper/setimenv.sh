#!/bin/sh
#

kdelibexecdir=$(kde4-config --install libexec)

if [ -z "${kdelibexecdir}" ]; then
    return 0
fi

eval $(${kdelibexecdir}/imenvloader)

unset GTK_IM_MODULE
if [ -n "${_GTK_IM_MODULE_LIBRARY}" ]; then
    for name in ${_GTK_IM_MODULE_LIBRARY}
    do
        if "${kdelibexecdir}/gtkimmoduledetector" "${name}"; then
            export GTK_IM_MODULE="${_GTK_IM_MODULE}"
            break
        fi
    done

    if [ -z "${GTK_IM_MODULE}" ]; then
        export GTK_IM_MODULE=xim
    fi
fi

unset QT_IM_MODULE
if [ -n "${_QT_IM_MODULE_LIBRARY}" ]; then
    for name in ${_QT_IM_MODULE_LIBRARY}
    do
        if "${kdelibexecdir}/qtimmoduledetector" "${name}"; then
            export QT_IM_MODULE="${_QT_IM_MODULE}"
            break
        fi
    done

    if [ -z "${QT_IM_MODULE}" ]; then
        export QT_IM_MODULE=xim
    fi
fi

unset XMODIFIERS
if [ -n "${_XMODIFIERS}" ]; then
    export XMODIFIERS="@im=${_XMODIFIERS}"
else
    unset XMODIFIERS
fi

unset _XMODIFIERS
unset _GTK_IM_MODULE
unset _GTK_IM_MODULE_LIBRARY
unset _QT_IM_MODULE
unset _QT_IM_MODULE_LIBRARY
