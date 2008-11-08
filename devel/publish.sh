#!/bin/bash

# generate a distribution for hyperspace explorer and do everything that is
# needed to publish it on sourceforge, with as little user interaction as
# possible

VERSION=${1:-"0.6.2"}
BASEDIR="${HOME}/workspace"
PROJECTDIR="HyperspaceExplorer"
FILENAME="HyperspaceExplorer"
EXECUTABLE="HyperspaceExplorer"
PROJECTNAME="hyperspace-expl"
USERNAME="metaldog"

set -xv

# things that must be done manually

echo
echo 'check release notes and changelog!'
echo
echo 'hit ENTER to continue'
read YES

echo
echo 'edit version number in Doxyfile!'
echo
echo 'hit ENTER to continue'
read YES

echo
echo 'update VERSION in src.pro!'
echo
echo 'hit ENTER to continue'
read YES

echo
echo 'make sure CONFIG is set to release (and not debug). ie.:'
echo '    CONFIG -= debug'
echo '    CONFIG += release qt warn_on uic'
echo
echo 'hit ENTER to continue'
read YES

# generate distribution package
function generate() {
    EXCLUDE=".svn tmp testing archive plugins"
    INCLUDE="src,AUTHORS,COPYING,ChangeLog,Doxyfile,HyperspaceExplorer.pro,INSTALL,License.txt,README,*.4d"

    for exclude in ${EXCLUDE}; do
        EXCLUDE_CLAUSE="${EXCLUDE_CLAUSE} --exclude=${exclude}"
    done

    cd ${BASEDIR}/${PROJECTDIR}
    make clean
    find . -name \*~ | xargs rm
    find . -name Makefile | xargs rm
    cd ${BASEDIR}
    tar ${EXCLUDE_CLAUSE} \
        --create --bzip2 --file ${PROJECTDIR}/${FILENAME}-${VERSION}.tar.bz2 \
        ${PROJECTDIR}/{src,AUTHORS,COPYING,ChangeLog,Doxyfile,HyperspaceExplorer.pro,INSTALL,License.txt,README,*.4d}
}

# check distribution package
function check() {
    mkdir -p ${HOME}/tmp && \
        cd ${HOME}/tmp && \
        rm -rf * .??* && \
        tar jxf ${BASEDIR}/${PROJECTDIR}/${FILENAME}-${VERSION}.tar.bz2 && \
        cd ${PROJECTDIR} && \
        qmake && \
        make -j4 && \
        sudo make install && \
        ./${EXECUTABLE} || exit 1
}

# upload distribution and publish it on SF
function upload() {
    rsync --progress \
        ${BASEDIR}/${PROJECTDIR}/${FILENAME}-${VERSION}.tar.bz2 \
        ${USERNAME}@frs.sourceforge.net:uploads/

    echo
    echo '*************************************************************************'
    echo
    echo 'now generate the release!'
    echo
    echo 'https://sourceforge.net/project/admin/editpackages.php?group_id=34073'
    echo
    echo 'hit ENTER to continue'
    read YES

    mv ${BASEDIR}/${PROJECTDIR}/${FILENAME}-${VERSION}.tar.bz2 \
        ${BASEDIR}/${PROJECTDIR}/archive
}

# generate and upload documentation; remove obsolete documentation files and add new ones
function document() {
    TAGFILE="http://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/libstdc++.tag"
    DOCDIR=""

    cd ${BASEDIR}/${PROJECTDIR}

    wget -N -P devel ${TAGFILE}
    find ${DOCDIR}/html  -maxdepth 1 -type f \! -type l | xargs rm
    yes q | doxygen 2> /dev/null
    svn up ${DOCDIR} 2>&1 | grep Restored | cut -d ' ' -f 2- | xargs svn del
    svn st ${DOCDIR}/html | grep ^? | cut -c 2- | xargs svn add
    svn commit -m "auto-generated documentation"
    rsync -rL --delete-after --exclude=.svn ${DOCDIR}/html/ \
        ${USERNAME},${PROJECTNAME}@web.sourceforge.net:htdocs
}

# create a branch in subversion
function branch() {
    SVNBASE="https://hyperspace-expl.svn.sourceforge.net/svnroot/${PROJECTNAME}"

    svn copy \
        ${SVNBASE}/trunk/all \
        ${SVNBASE}/tags/release-${VERSION}
}

generate
check
upload
document
branch