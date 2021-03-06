/*
Hyperspace Explorer - visualizing higher-dimensional geometry
Copyright (C) 2010  Lene Preuss <lene.preuss@gmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

/** \mainpage HyperspaceExplorer
 *
 *  \section intro Introduction
 *
 *  Hyperspace Explorer is a program that lets you visualize four-dimensional
 *  objects and mathematical functions.
 *
 *  Just as you can define objects in three-dimensional space, you can define
 *  objects with four dimensions. And just as three-dimensional objects can be
 *  projected onto a plane, four-dimensional objects can be projected into
 *  three-space.
 *
 *  This program uses this approach to acquaint you with a couple of
 *  four-dimensional objects. Four-dimensional objects are projected to three
 *  dimensions, and then displayed on the computer monitor (after a further
 *  projection to two dimensions).
 *
 *  Every object thus is viewed from a viewpoint in four dimensions, as well as
 *  a viewpoint in three dimensions. That leaves freedom for plenty of viewing
 *  transformations. You can translate and rotate what is displayed in three and
 *  four dimensions, to get a better feeling for the objects and for four-space
 *  manipulations.
 *
 *  This web site displays the API documentation generated by the
 *  <a href="http://www.doxygen.org">doxygen</a> documentation generation tool.
 *  For the project's home page, including downloads, visit
 *  http://sourceforge.net/projects/hyperspace-expl . For help on using the
 *  program, see the \ref userdoc.
 *
 *  \page userdoc User Documentation
 *
 *  The following is the online documentation that is built into Hyperspace
 *  Explorer. It contains everything that is to know about Hyperspace Explorer
 *  from the user's point of view.
 *
 *  \htmlinclude doc/Hyperspace_Explorer_Help.html
 *
 *  \page links Links To Pages About Higher-dimensional Geometry
 *
 *  <a href="http://www.hyperspace-travel.de/">Hyperspace Travel Guide</a>\n
 *  My personal page explaining the math behind the projection of four
 *  dimensional objects to 3D. Also, a tiny zoo of four dimensional objects.
 *  It is quite badly maintained, I'm afraid.
 *
 *  <a href="http://members.aol.com/Polycell/uniform.html">Uniform Polytopes in
 *  Four Dimensions</a>\n
 *  George Olshevsky's catalog of polytopes, the four dimensional analogues to
 *  polyhedra in three-space. Contains many interesting objects and some 3D
 *  polyhedra too.
 *
 *  <a href="http://members.shaw.ca/quadibloc/math/fdiint.htm">The Fourth
 *  Dimension</a>\n
 *  A page by John Savard which tries to make some polytopes imaginable, most
 *  notably the 120-cell. IMHO, it succeeds quite well at that attempt.
 *
 *  <a href="http://eusebeia.dyndns.org/4d/geom.html">4D Geometric Objects</a>\n
 *  A catalog of four dimensional object with an emphasis on rotopes. The same
 *  site also hosts a little <a href="http://eusebeia.dyndns.org/4d/4dfaq.html">
 *  4D FAQ</a> and a HOWTO on <a href="http://eusebeia.dyndns.org/4d/vis/vis.html">
 *  Visualization fo four-dimensional geometry</a>.
 *
 *  <a href="http://tetraspace.alkaline.org/phpBB3/index.php">Fourth Dimension:
 *  Tetraspace</a>\n
 *  A forum, created by Garrett Jones, dedicated to the discussion of four
 *  dimensional space. The posts usually have high quality, you can learn a lot
 *  here. The page also hosts an <a href="http://tetraspace.alkaline.org/">
 *  Introduction to "The Fourth Dimension"</a> and the <a
 *  href="http://teamikaria.com/wiki/Main_Page">Higher Dimensions Database</a>.
 *
 *  <a href="http://www.polytope.net/hedrondude/polychora.htm">Uniform Polychora
 *  </a>\n
 *  This is a site by Jonathan Bowers, cataloguing polychora. I haven't had time
 *  to check it out yet, but it enjoys a good reputation.
 */

#include <vector>
#include <iomanip>

#include <QApplication>
#include <QMainWindow>
#include <QStringList>
#include <QString>
#include <QDir>

#include "4DView.h"
#include "Menu4D.h"
#include "Globals.h"
#include "Parser.h"
#include "Transformation/TransformationFactory.h"

using std::cout;
using std::cerr;
using std::endl;
using std::setprecision;

using std::pair;
using std::map;
using std::vector;

/** yeah, big deal... */
void help (QString progname) {
  cout << "Usage:" << endl
       << progname.toStdString() << " [--rcdir dir]" << endl
       << QString(progname.size(), ' ').toStdString()
       << " [--script scriptfile]" << endl
       << QString(progname.size(), ' ').toStdString()
       << " [--benchmark [number_of_runs]]" << endl
       << QString(progname.size(), ' ').toStdString()
       << " [--transformation single|multi]" << endl
       << QString(progname.size(), ' ').toStdString()
       << " [-h | --help]" << endl
       << "Consult the online help for more info!" << endl;
}

typedef vector<vector<double> > double2D;
typedef map<const char *, double2D> double2Dmap;
typedef pair<const char *, double2D> double2DmapPair;

/** writes a HTML table row of the benchmark results given as parameter to cout
 *  @param results 	run_times[dim][run_no.]                               */
void evaluate_benchmark (double2D results) {
  for (unsigned i = 0; i < 2; i++) {
    cout << "  <tr><td>" << i+3 << "D" << "</td>";
    double avg = 0, sqdev = 0;
    for (unsigned j = 0; j < results[i].size (); j++) {
      avg += results[i][j];
    }
    avg /= results[i].size ();

    for (unsigned j = 0; j < results[i].size (); j++) {
      sqdev += (results[i][j]-avg)*(results[i][j]-avg);
    }
    sqdev = sqrt (sqdev/results[i].size ());

    cout << setprecision (3) << "<td>" << avg  << "s 	&plusmn;" << sqdev << "s</td>";
    cout << "</tr>" << endl;
  }

}

/** writes a HTML table of the benchmark results given as parameter to cout
 *  this is really more an exercise in convoluted STL containers than real
 *  functionality :-)
 *  @param results_by_style 	a map: "display_style" => run_times[dim][run_no.]
 */
void evaluate_benchmark (double2Dmap results_by_style) {

  cout << "<table>\n";

  double2Dmap::iterator it;

  for (it = results_by_style.begin (); it != results_by_style.end (); ++it) {
    const char *style = (*it).first;
    vector<vector<double> > results = (*it).second;

    cout << "  <tr><td colspan='" << results[0].size ()+1 <<"' align='center'>"
	 << style << "</td></tr>\n";
    evaluate_benchmark (results);
  }

  cout << "</table>\n";

}


/** writes HTML tables, ordered by object, of the benchmark results given as
 *  parameter to cout
 *  this is really more an exercise in convoluted STL containers than real
 *  functionality :-)
 *  @param results_by_object 	a map: "object" => "display_style" => run_times[dim][run_no.]
 */
void evaluate_benchmark (map<const char *, double2Dmap> results_by_object) {
  map<const char *, double2Dmap>::iterator it;

  for (it = results_by_object.begin (); it != results_by_object.end (); ++it) {
    const char *object = (*it).first;
    double2Dmap results = (*it).second;

    cout << "<b>"<<object<<"</b>";
    evaluate_benchmark (results);
  }
}


/** runs rotation in four and three dimensions on a C4DView in a set display
 *  style, timing the runs
 *  @param view 	the C4Dview with the object already selected
 *  @param num_runs 	number of times to run the rotation
 *  @param num_steps 	number of steps for a full rotation (360 degrees)
 *  @param step 	increment per step in degrees. hardcoded to 1.0 in
 *			benchmark (const unsigned) below.
 *  @return             a vector[]: run_times[2][] for 3- and 4D              */
double2D run_benchmarks (C4DView & view,
			const unsigned num_runs,
			const unsigned num_steps,
			const double step) {
  double2D results (2);

  results[0] = vector<double> (num_runs);
  results[1] = vector<double> (num_runs);
  for (unsigned i = 0; i < num_runs; i++) {
    cerr << " " << i+1 << " / " << num_runs << "  \r";
    results[0][i] = view.Benchmark3D (num_steps, step, step, step, true);
    results[1][i] = view.Benchmark4D (num_steps, step, step, step, true);
  }

  return results;
}


/** runs rotation in four and three dimensions on a C4DView in solid and
 *  wireframe, with and without 4D depth cue
 *  times the runs and evaluates the times by style and object
 *  this is really more an exercise in convoluted STL containers than real
 *  functionality :-)
 *  @param view 	the C4Dview with the object already selected
 *  @param num_runs 	number of times to run the rotation
 *  @param num_steps 	number of steps for a full rotation (360 degrees)
 *  @param step 	increment per step in degrees. hardcoded to 1.0 in
 *			benchmark (const unsigned) below.
 *  @return             a map: "display style" => run_times[]                 */
double2Dmap benchmarks_by_style (C4DView & view, const unsigned num_runs,
                                 const unsigned num_steps, const double step) {
    double2Dmap results_by_style;

    view.setSolid(false);
    results_by_style.insert (
        double2DmapPair (
            "Wireframe",
            run_benchmarks (view, num_runs, num_steps, step)));
    view.setHyperfog(true);
    results_by_style.insert (
        double2DmapPair (
            "Wireframe + 4D Depth Cue",
            run_benchmarks (view, num_runs, num_steps, step)));
    view.setSolid(true);
    view.setHyperfog(false);
    results_by_style.insert (
        double2DmapPair (
            "Solid",
            run_benchmarks (view, num_runs, num_steps, step)));
    view.setHyperfog(true);
    results_by_style.insert (
        double2DmapPair (
            "Solid + 4D Depth Cue",
            run_benchmarks (view, num_runs, num_steps, step)));
    return results_by_style;
}

#if 0
/** runs rotation in four and three dimensions for hypercube and hyperpyramid
 *  for num_runs
 *  times the runs and evaluates the times by style and object
 *  this is really more an exercise in convoluted STL containers than real
 *  functionality :-)
 *  @param num_runs 	number of runs
 */
void benchmark (const unsigned num_runs = 10) {
    unsigned num_steps = 360;
    double step = 1.;

    C4DView view;

    {
#if 0
        map < const char *, double2Dmap> results_by_object;

        view.ObjectHypercube ();
        cerr << "Hypercube\n";

        double2Dmap results_by_style = benchmarks_by_style (view, num_runs, num_steps, step);
        results_by_object.insert (
            pair<const char *, double2Dmap> ("Hypercube",
                benchmarks_by_style (view, num_runs, num_steps, step)));

        view.ObjectHyperpyramid ();
        cerr << "Hyperpyramid\n";

        results_by_style = benchmarks_by_style (view, num_runs, num_steps, step);
        results_by_object.insert (
            pair<const char *, double2Dmap> ("Hyperpyramid",
                benchmarks_by_style (view, num_runs, num_steps, step)));

        view.ObjectHypersponge();
        cerr << "Hypersponge\n";

        results_by_style = benchmarks_by_style (view, num_runs, num_steps, step);
        results_by_object.insert (
            pair<const char *, double2Dmap> ("Hypersponge",
                benchmarks_by_style (view, num_runs, num_steps, step)));

        evaluate_benchmark (results_by_object);
#endif
    }

  exit (0);
}
#endif

/** parses commandline
 *  choices for args:
 *              --rcdir <resource_directory>
 *              --script <script_file>
 *              --benchmark [number_of_runs]
 *              --transformation single|multi
 *  @param argc number of arguments
 *  @param argv array of arguments                                            */
void parse (int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        if (QString (argv[i]) == QString ("--rcdir")) {
            if (i+1 < argc)
                Globals::Instance().rcdirs().append (QString (argv[i+1]));
        }
        if (QString (argv[i]) == QString ("--script")) {
            if (i+1 < argc) {
                Script::Parser parser(argv[i+1]);
                C4DView view;

                Globals::Instance().getMainWindow()->setCentralWidget(&view);
                Globals::Instance().getMainWindow()->resize(580,600);

                Globals::Instance().getMainWindow()->show();

                parser.setView(&view);

                parser.execute();

                exit(0);
            }
        }
        if (QString (argv[i]) == QString ("--help") ||
	    QString (argv[i]) == QString ("-h")) {
            help (argv[0]);
            exit (0);
        }
        if (QString (argv[i]) == QString ("--benchmark")) {
            
#if 0
            if (i+1 < argc) benchmark (QString (argv[i+1]).toUInt ());
            else benchmark (10);
#else
            cout << "--benchmark is temporarily out of order" << endl;
#endif
            exit(0);
        }
        if (QString (argv[i]) == QString ("--transformation")) {
            if (i+1 < argc) {
                ++i;
                if (QString (argv[i]) == QString ("single")) {
                    TransformationFactory::setTransformationMethod(TransformationFactory::Singlethreaded);
                } else if (QString (argv[i]) == QString ("multi")) {
                    TransformationFactory::setTransformationMethod(TransformationFactory::Multithreaded);
                } else {
                    help(argv[0]);
                }
            } else {
                help(argv[0]);
            }

        }

    }
}

/** add the default entries to the path to look for rc files (and plugins,
 *  and documentation): $HOME/.HyperspaceExplorer and
 *  $PREFIX/share/HyperspaceExplorer (where PREFIX is /usr/local per default  */
void setRCFilePath() {
    QString rcdir (".HyperspaceExplorer");
    //  if default rc directory does not yet exist, create it
    if (!QDir::home().exists(rcdir))
        QDir::home().mkdir(rcdir);
    //  if Vector module for linking custom functions does not exist, copy it
    if (!QDir::home().exists(rcdir+"/plugins"))
        QDir::home().mkdir(rcdir+"/plugins");
    if (!QDir::home().exists(rcdir+"/plugins/Vector.H")) {
        QFile::link((qApp->applicationDirPath()+"/Vector.H").toLatin1(),
                  (QDir::home().absolutePath()+"/"+rcdir+"/plugins/Vector.H").toLatin1());
    }
    Globals::Instance().rcdirs().append (QDir::home ().absolutePath ()+"/"+rcdir);

    QString prefix(make_str(PREFIX));
    Globals::Instance().rcdirs().append(prefix+"/share/HyperspaceExplorer");
}

/** 
 *  Sets the method used to transform Vertices. The method can be overridden 
 *  with the command line parameter \code --transformation single|multi \endcode
 */
void setTransformationMethod() {
    if (Util::isMultithreadedSensible()) {
        TransformationFactory::setTransformationMethod(TransformationFactory::Multithreaded);
    } else {
        TransformationFactory::setTransformationMethod(TransformationFactory::Singlethreaded);
    }
}

/** initialize and run HyperspaceExplorer
 *  @param argc number of arguments
 *  @param argv array of arguments
 *  @return     exit status                                                   */
int main (int argc, char *argv[]) {

    int ret = 1;

    try {
        QApplication app (argc, argv);

        setRCFilePath();
        
        setTransformationMethod();

        parse (argc, argv);

        //  okay to set . last in rc file path? shouldn't it be first?
        Globals::Instance().rcdirs().append (".");

        C4DView view;
        Globals::Instance().getMainWindow()->setCentralWidget(&view);
        Globals::Instance().getMainWindow()->resize(580,600);

        Globals::Instance().getMainWindow()->show();

        ret = app.exec ();
    } catch (std::logic_error &e) {
        std::cerr << "\n\n"
            "The programmer of this software has done something wrong.\n"
            "You can drop her a message: <lene.preuss@gmail.com>\n"
            "or use the bug tracker for Hyperspace Explorer at:\n"
            "https://sourceforge.net/tracker2/?func=add&group_id=34073&atid=410707\n"
            "Please add the following message to the bug report: \n"
                << e.what() << "\n\n"
            "The program will abort now.\n";
        abort();
    }
    return ret;
}
