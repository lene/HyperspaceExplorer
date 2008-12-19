#!/bin/bash

# generate a distribution for hyperspace explorer and do everything that is
# needed to publish it on sourceforge, with as little user interaction as
# possible

BASEDIR="${HOME}/workspace"
PROJECTDIR="HyperspaceExplorer"
FILENAME="HyperspaceExplorer"
EXECUTABLE="HyperspaceExplorer"
PROJECTNAME="hyperspace-expl"
USERNAME="metaldog"

set +xv

# processes arguments to the script
function parse_commandline() {
    edit=0
    generate=0
    check=0
    upload=0
    document=0
    branch=0

    while [ $# != 0 ]; do
        case "$1" in
            --edit|-e)      edit=1;;
            --generate|-g)  generate=1;;
            --check|-c)     check=1;;
            --upload|-u)    upload=1;;
            --document|-d)  document=1;;
            --branch|-b)    branch=1;;
            --version|-v)   VERSION=$2;
                            shift;;
            -* | *)         print_help; exit 1 ;;

        esac
        shift
    done
    if [ -z "$VERSION" ]; then
        print_help
        exit 1
    fi
}

function print_help() {
    echo $(basename $0) --version\|-v \<VERSION\>
    echo "          [--edit\|-e]"
    echo "          [--generate\|-g]"
    echo "          [--check\|-c]"
    echo "          [--upload\|-u]"
    echo "          [--document\|-d]"
    echo "          [--branch\|-b]"
    echo "The --version parameter is mandatory."
    echo "If no step for deployment is specified, all will be executed."
}

# things that must be done manually
function edit() {
    echo
    echo 'check release notes and changelog!'
    echo
    echo 'hit ENTER to continue'
    read YES

    ver=$(grep -n 'PROJECT_NUMBER' Doxyfile | grep \= | cut -d '=' -f 2)
    if [ $ver != $VERSION ]; then
        echo
        echo "change PROJECT_NUMBER in Doxyfile to ${VERSION}!"
        echo
        grep -n PROJECT_NUMBER Doxyfile | grep \=
        echo
        echo 'hit ENTER to continue'
        read YES
    fi

    ver=$(grep -n 'VERSION[ *]=' src/src.pro | cut -d '=' -f 2)
    if [ $ver != $VERSION ]; then
        echo
        echo "update VERSION in src.pro to ${VERSION}!"
        echo
        grep -n 'VERSION[ *]=' src/src.pro
        echo
        echo 'hit ENTER to continue'
        read YES
    fi

    echo
    echo 'make sure CONFIG in src/src.pro is set to release (and not debug). ie.:'
    echo '    CONFIG -= debug'
    echo '    CONFIG += release qt warn_on uic'
    echo
    echo 'hit ENTER to continue'
    read YES

    echo
    echo 'make sure you have set the startup object to a new one'
    echo
    echo 'hit ENTER to continue'
    read YES
}

# generate distribution package
function generate() {
    # File and directory names which should NOT be included in the archive
    EXCLUDE=".svn tmp testing archive plugins"

    # File and directory names which SHOULD be included in the archive must be
    # listed as argument to the tar command below

    for exclude in ${EXCLUDE}; do
        EXCLUDE_CLAUSE="${EXCLUDE_CLAUSE} --exclude=${exclude}"
    done

    cd ${BASEDIR}/${PROJECTDIR}
    test -f Makefile && make clean
    find . -name \*~ | xargs rm -f
    find . -name Makefile | xargs rm -f
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
        make -j2 && \
        sudo make install && \
        ./${EXECUTABLE} || exit 1
}

# upload distribution and publish it on SF
function upload() {
    rsync --progress \
        ${BASEDIR}/${PROJECTDIR}/${FILENAME}-${VERSION}.tar.bz2 \
        ${USERNAME}@frs.sourceforge.net:uploads/

    echo
    echo '*********************************************************************'
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
    DOCDIR="devel/html"

    cd ${BASEDIR}/${PROJECTDIR}

    wget -N -P devel ${TAGFILE}
    find ${DOCDIR}/html  -maxdepth 1 -type f \! -type l | \
        xargs rm
    yes q | \
        doxygen 2> /dev/null
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


parse_commandline $@

LINES=$(find . -name *.[CH] -exec cpp -fpreprocessed "{}" \; 2> /dev/null | \
        grep -v ^$ | \
        grep -v ^# | \
        wc -l)
echo $LINES lines of code

if [ $edit -eq 1 -o $generate -eq 1 -o $check -eq 1 -o $upload -eq 1 \
        -o $document -eq 1 -o $branch -eq 1 ]; then
    test $edit -eq 1 && edit
    test $generate -eq 1 && generate
    test $check -eq 1 && check
    test $upload -eq 1 && upload
    test $document -eq 1 && document
    test $branch -eq 1 && branch
else
    edit && \
        generate && \
        check && \
        upload && \
        document && \
        branch
fi
