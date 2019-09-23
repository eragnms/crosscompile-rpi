# For debugging run:
# ./configure CFLAGS="-ggdb3 -O0" CXXFLAGS="-ggdb3 -O0" LDFLAGS="-ggdb3
# otherwise just run:
# ./configure
# Version numbering scheme, see
# https://packaging.python.org/distributing/#choosing-a-versioning-scheme
# 1.2.0.dev1  # Development release
# 1.2.0.a1     # Alpha Release
# 1.2.0.b1     # Beta Release
# 1.2.0.rc1    # Release Candidate
# 1.2.0       # Final Release
# 1.2.0.post1 # Post Release
# 1.2.0.<anything>.s1 # Special of <anything>
AC_INIT([crosscompile], [0.0.1.dev1], [mats@mcnab.se])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CXX
AC_PROG_LIBTOOL
AC_SUBST(LIBTOOL_DEPS)
AC_LTDL_DLLIB
AC_CONFIG_FILES([
			Makefile
            src/Makefile
            ])

# https://stackoverflow.com/questions/11898782/how-to-conditionally-compile-in-a-autotools-project?rq=1
# https://medium.com/@au42/the-useful-raspberrypi-cross-compile-guide-ea56054de187

AC_ARG_ENABLE([rpi],
[  --enable-rpi    Build for Raspberry Pi],
[case "${enableval}" in
yes) rpi=true ;;
no)  rpi=false ;;
*) AC_MSG_ERROR([bad value ${enableval} for --enable-rpi]) ;;
esac],[rpi=false])
AM_CONDITIONAL([RPI], [test x$rpi = xtrue])
AS_IF([test x$rpi = xtrue], [
            PWD="/home/mats/projects"
            TOOLCHAIN_HOST="arm-linux-gnueabihf"
            TOOLCHAIN_PATH="${PWD}/rpi-tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/bin"
            CPP="${TOOLCHAIN_PATH}/${TOOLCHAIN_HOST}-cpp"
            CC="${TOOLCHAIN_PATH}/${TOOLCHAIN_HOST}-gcc"
            CXX="${TOOLCHAIN_PATH}/${TOOLCHAIN_HOST}-g++"
            LD="${TOOLCHAIN_PATH}/${TOOLCHAIN_HOST}-ld"
            AS="${TOOLCHAIN_PATH}/${TOOLCHAIN_HOST}-as"
            AR="${TOOLCHAIN_PATH}/${TOOLCHAIN_HOST}-ar"
            RANLIB="${TOOLCHAIN_PATH}/${TOOLCHAIN_HOST}-ranlib"
            SYSROOT="${PWD}/rpi-tools/arm-bcm2708/arm-rpi-4.9.3-linux-gnueabihf/arm-linux-gnueabihf/sysroot"
])

CXXFLAGS="$CXXFLAGS \
-std=c++11 \
-pthread \
-Wall \
-Werror \
-Wextra \
-Wredundant-decls \
-Wcast-align \
-Wmissing-declarations \
-Wmissing-include-dirs \
-Winvalid-pch \
-Wredundant-decls \
-Wformat=2 \
-Wmissing-format-attribute \
-Wno-format-nonliteral \
-fvisibility=default \
-lstdc++ \
-larmadillo"

#-lSoapySDR \
#-lLimeSuite \

AS_IF([test x$rpi = xtrue], [
            CFLAGS+="--sysroot=${SYSROOT}"
            CPPFLAGS+="--sysroot=${SYSROOT}"
            CXXFLAGS+="--sysroot=${SYSROOT}"
            CONFIG_OPTS=()
            CONFIG_OPTS+=("CFLAGS=${CFLAGS}")
            CONFIG_OPTS+=("CPPFLAGS=${CPPFLAGS}") CONFIG_OPTS+=("CXXFLAGS=${CXXFLAGS}")
            CONFIG_OPTS+=("LDFLAGS=${LDFLAGS}") CONFIG_OPTS+=("PKG_CONFIG_DIR=")
            CONFIG_OPTS+=("--host=${TOOLCHAIN_HOST}")
            CONFIG_OPTS+=("CPP=${CPP}")
            CONFIG_OPTS+=("CC=${CC}")
            CONFIG_OPTS+=("CXX=${CXX}")
            CONFIG_OPTS+=("LD=${LD}")
            CONFIG_OPTS+=("AS=${AS}")
            CONFIG_OPTS+=("AR=${AR}")
            CONFIG_OPTS+=("RANLIB=${RANLIB}")
            BUILD_PREFIX="${PWD}/tmp"
            CONFIG_OPTS+=("--prefix=${BUILD_PREFIX}")
            CONFIG_OPTS+=("PKG_CONFIG_DIR=")
            CONFIG_OPTS+=("PKG_CONFIG_LIBDIR=${SYSROOT}/usr/lib/arm-linux-gnueabihf/pkgconfig:${SYSROOT}/usr/share/pkgconfig")
            CONFIG_OPTS+=("PKG_CONFIG_SYSROOT=${SYSROOT}")
            CONFIG_OPTS+=("PKG_CONFIG_PATH=${BUILD_PREFIX}/lib/pkgconfig")
])

AC_OUTPUT
