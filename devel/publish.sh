#!/bin/bash

# generate a distribution for hyperspace explorer and do everything that is
# needed to publish it on sourceforge, with as little user interaction as
# possible

VERSION="X.Y.Z"
BASEDIR="~/workspace"

# things that must be done manually

echo 'check release notes and changelog!'
echo 'hit ENTER to continue'
read YES

echo 'update VERSION in src.pro!'
echo 'hit ENTER to continue'
read YES

echo 'make sure CONFIG is set to release (and not debug). ie.:'
echo '    CONFIG -= debug'
echo '    CONFIG += release qt warn_on uic'
echo 'hit ENTER to continue'
read YES

# generate distribution package

cd ${BASEDIR}/HyperspaceExplorer
make clean
find . -name \*~ | xargs rm
cd ${BASEDIR}
tar --exclude=.svn --exclude=tmp --exclude=testing --exclude=archive --exclude=plugins \
    --create --bzip2 --file HyperspaceExplorer/HyperspaceExplorer-${VERSION}.tar.bz2 \
    HyperspaceExplorer/src HyperspaceExplorer/*.4d HyperspaceExplorer/HyperspaceExplorer.pro \
    HyperspaceExplorer/AUTHORS HyperspaceExplorer/COPYING HyperspaceExplorer/ChangeLog \
    HyperspaceExplorer/Doxyfile HyperspaceExplorer/HyperspaceExplorer.pro \
    HyperspaceExplorer/INSTALL HyperspaceExplorer/License.txt HyperspaceExplorer/README


# check distribution package

mkdir -p ~/tmp; cd ~/tmp; rm -rf * .??*
tar jxf ${BASEDIR}/HyperspaceExplorer/HyperspaceExplorer-${VERSION}.tar.bz2
cd HyperspaceExplorer; qmake && make -j4 && sudo make install
./HyperspaceExplorer


# upload distriution and publish it on SF

rsync ${BASEDIR}/HyperspaceExplorer/HyperspaceExplorer-${VERSION}.tar.bz2 \
    metaldog@frs.sourceforge.net:uploads/

echo 'now generate the release!'
echo 'https://sourceforge.net/project/admin/editpackages.php?group_id=34073'
echo 'hit ENTER to continue'
read YES

mv ${BASEDIR}/HyperspaceExplorer/HyperspaceExplorer-${VERSION}.tar.bz2 \
    ${BASEDIR}/HyperspaceExplorer/archive

# generate and upload documentation; remove obsolete documentation files and add new ones

echo 'edit version number in Doxyfile!'
echo 'hit ENTER to continue'
read YES

cd ${BASEDIR}/HyperspaceExplorer

wget -N -P devel http://gcc.gnu.org/onlinedocs/libstdc++/latest-doxygen/libstdc++.tag
find devel/html/html  -maxdepth 1 -type f \! -type l | xargs rm
yes q | doxygen 2> /dev/null
svn up devel/html/ 2>&1 | grep Restored | cut -d ' ' -f 2- | xargs svn del
svn st devel/html/html | grep ^? | cut -c 2- | xargs svn add
svn commit -m "auto-generated documentation"
rsync -rL --delete-after --exclude=.svn devel/html/html/ \
  metaldog,hyperspace-expl@web.sourceforge.net:htdocs


# create a branch in subversion

svn copy \
    https://hyperspace-expl.svn.sourceforge.net/svnroot/hyperspace-expl/trunk/all \
    https://hyperspace-expl.svn.sourceforge.net/svnroot/hyperspace-expl/tags/release-${VERSION}
