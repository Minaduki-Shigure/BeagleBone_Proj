#!/bin/sh

set -e

PACKAGE=mplayer
svnurl=svn://svn.mplayerhq.hu/mplayer
VER_SUFFIX=""

CWD_DIR=${PWD}
GOS_DIR=${CWD_DIR}/get-orig-source

DEB_SOURCE=$(dpkg-parsechangelog 2>/dev/null | sed -n 's/^Source: //p')
DEB_VERSION=$(dpkg-parsechangelog 2>/dev/null | sed -n 's/^Version: //p')
UPSTREAM_VERSION=$(echo ${DEB_VERSION} | sed -r 's/[^:]+://; s/-[^-]+$$//;s/\+dfsg[0-9]*$//;s/\+repack[0-9]*$//')
SVN_VERSION=$(echo ${UPSTREAM_VERSION} | sed -nr 's/^[0-9.:-~]+\+svn([0-9]+)$$/\1/p')

if [ "${DEB_SOURCE}" != "${PACKAGE}" ]; then
    echo 'Please run this script from the sources root directory.'
    exit 1
fi

if [ -z ${SVN_VERSION} ] && [ -z "${UPSTREAM_VERSION}" ]; then
    echo 'Please update the latest entry in the changelog to show a valid version.'
    exit 2
elif [ -z ${SVN_VERSION} ]; then
    svnurl="${svnurl}/tags/MPlayer-${UPSTREAM_VERSION}"
else
    svnurl="-r ${SVN_VERSION} ${svnurl}/trunk"
fi

rm -rf ${GOS_DIR}
mkdir ${GOS_DIR} && cd ${GOS_DIR}

# Download mplayer
svn checkout --config-option config:miscellany:use-commit-times=yes ${svnurl} ${DEB_SOURCE}-${UPSTREAM_VERSION}
cd ${GOS_DIR}/${DEB_SOURCE}-${UPSTREAM_VERSION}
if [ ! -e VERSION ]; then
    echo ${UPSTREAM_VERSION} > VERSION
    touch -h -d "$(svn propget --revprop -r ${SVN_VERSION} svn:date)" VERSION
fi

# Setting times...
cd ${GOS_DIR}/${DEB_SOURCE}-${UPSTREAM_VERSION}
for F in $(find -type l); do touch -h -r "$(readlink -e $F)" "$F"; done

# Clean-up...
cd ${GOS_DIR}/${DEB_SOURCE}-${UPSTREAM_VERSION}
rm -f .gitignore
find . -depth -type d -name ".svn" -exec rm -rf '{}' \;

# Packing...
cd ${GOS_DIR}
find -L ${DEB_SOURCE}-${UPSTREAM_VERSION} -xdev -type f -print | LC_ALL=C sort \
| XZ_OPT="-6v" tar -caf "${CWD_DIR}/${DEB_SOURCE}_${UPSTREAM_VERSION}${VER_SUFFIX}.orig.tar.xz" -T- --owner=root --group=root --mode=a+rX

cd ${CWD_DIR} && rm -rf ${GOS_DIR}
