
//      project:      hyperspace explorer
//      module:       
//      contains:     
//      compile with: make all
//	author:	      helge preuss (scout@hyperspace-travel.de)
//	license:      GPL (see License.txt)

#include <vector>
#include <iomanip>
#include <qapplication.h>
#include <qstringlist.h>
#include <qstring.h>
#include <qdir.h>
#include "4DView.H"

QStringList rcdirs;	//  why tf did i make that global again? damn, i really should write comments immediately after writing the code</rant>

using std::cout;
using std::cerr;
using std::endl;
using std::setprecision;

using std::pair;
using std::map;
using std::vector;

/*******************************************************************************
 * yeah, big deal...
 */
void help (QString progname) {
  cout << "Usage:" << endl
       << progname.toStdString() << " [--rcdir dir]" << endl
       << progname.toStdString() << " [-h | --help]" << endl
       << "Consult the online help for more info!" << endl;
}


/*******************************************************************************
 *  writes a HTML table row of the benchmark results given as parameter to cout
 *  @param results 	run_times[dim][run_no.]
 */
void evaluate_benchmark (vector<vector<double> > results) {
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


/*******************************************************************************
 *  writes a HTML table of the benchmark results given as parameter to cout
 *  this is really more an exercise in convoluted STL containers than real
 *  functionality :-)
 *  @param results_by_style 	a map: "display_style" => run_times[dim][run_no.]
 */
void evaluate_benchmark (map<const char *, vector<vector<double> > > results_by_style) {

  cout << "<table>\n";
  
  map<const char *, vector<vector<double> > >::iterator it;

  for (it = results_by_style.begin (); it != results_by_style.end (); ++it) {
    const char *style = (*it).first;
    vector<vector<double> > results = (*it).second;

    cout << "  <tr><td colspan='" << results[0].size ()+1 <<"' align='center'>"
	 << style << "</td></tr>\n";
    evaluate_benchmark (results);
  }

  cout << "</table>\n";
  
}


/*******************************************************************************
 *  writes HTML tables, ordered by object, of the benchmark results given as
 *  parameter to cout
 *  this is really more an exercise in convoluted STL containers than real
 *  functionality :-)
 *  @param results_by_object 	a map: "object" => "display_style" => run_times[dim][run_no.]
 */
void evaluate_benchmark (map<const char *, map<const char *, vector<vector<double> > > > results_by_object) {
  /*  for_each (results_by_object.begin (),
                results_by_object.end (),
		evaluate_benchmark<(map<const char *, vector<vector<double> > > > (...)
  */
  map<const char *, map<const char *, vector<vector<double> > > >::iterator it;

  for (it = results_by_object.begin (); it != results_by_object.end (); ++it) {
    const char *object = (*it).first;
    map<const char *, vector<vector<double> > > results = (*it).second;

    cout << "<b>"<<object<<"</b>";
    evaluate_benchmark (results);
  }
}


/*******************************************************************************
 *  runs rotation in four and three dimensions on a C4DView in a set display
 *  style, timing the runs
 *  @param view 	the C4Dview with the object already selected
 *  @param num_runs 	number of times to run the rotation
 *  @param num_steps 	number of steps for a full rotation (360 degrees)
 *  @param step 	increment per step in degrees. hardcoded to 1.0 in
 *			benchmark (const unsigned) below.
 *  @return		a vector[]: run_times[2][] for 3- and 4D
 */
vector<vector<double> > run_benchmarks (C4DView & view,
					const unsigned num_runs,
					const unsigned num_steps,
					const double step) {
  vector <vector<double> > results (2);
  
  results[0] = vector<double> (num_runs);
  results[1] = vector<double> (num_runs);
  for (unsigned i = 0; i < num_runs; i++) {
    cerr << " " << i+1 << " / " << num_runs << "  \r";
    results[0][i] = view.Benchmark3D (num_steps, step, step, step, true);   
    results[1][i] = view.Benchmark4D (num_steps, step, step, step, true);   
  }
  
  return results;
}	


/*******************************************************************************
 *  runs rotation in four and three dimensions on a C4DView in solid and
 *  wireframe, with and without 4D depth cue
 *  times the runs and evaluates the times by style and object
 *  this is really more an exercise in convoluted STL containers than real
 *  functionality :-)
 *  @param view 	the C4Dview with the object already selected
 *  @param num_runs 	number of times to run the rotation
 *  @param num_steps 	number of steps for a full rotation (360 degrees)
 *  @param step 	increment per step in degrees. hardcoded to 1.0 in
 *			benchmark (const unsigned) below.
 *  @return		a map: "display style" => run_times[]
 */
map<const char *, vector<vector<double> > > benchmarks_by_style (C4DView & view,
								 const unsigned num_runs,
								 const unsigned num_steps,
								 const double step) {
  map<const char *, vector<vector<double> > > results_by_style;

  view.Wireframe ();
  results_by_style.insert (
			   pair<const char *, vector<vector<double> > > (
									 "Wireframe",
									 run_benchmarks (view, num_runs, num_steps, step)));
  view.HyperFog ();
  results_by_style.insert (
			   pair<const char *, vector<vector<double> > > (
									 "Wireframe + 4D Depth Cue",
									 run_benchmarks (view, num_runs, num_steps, step)));
  view.Wireframe ();
  view.HyperFog ();
  results_by_style.insert (
			   pair<const char *, vector<vector<double> > > (
									 "Solid",
									 run_benchmarks (view, num_runs, num_steps, step)));
  view.HyperFog ();
  results_by_style.insert (
			   pair<const char *, vector<vector<double> > > (
									 "Solid + 4D Depth Cue",
									 run_benchmarks (view, num_runs, num_steps, step)));
  return results_by_style;
}


/*******************************************************************************
 *  runs rotation in four and three dimensions for hypercube and hyperpyramid
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

    map < const char *, map<const char *, vector<vector<double> > > > results_by_object;

    view.ObjectHypercube ();

    map<const char *, vector<vector<double> > > results_by_style = benchmarks_by_style (view, num_runs, num_steps, step);
    results_by_object.insert (pair<const char *, map<const char *, vector<vector<double> > > > (
												  "Hypercube",
												  benchmarks_by_style (view, num_runs, num_steps, step)));

    view.ObjectHyperpyramid ();

    results_by_style = benchmarks_by_style (view, num_runs, num_steps, step);
    results_by_object.insert (pair<const char *, map<const char *, vector<vector<double> > > > (
												  "Hyperpyramid",
												  benchmarks_by_style (view, num_runs, num_steps, step)));

    
    evaluate_benchmark (results_by_object);
  }
  
  exit (0);
}


/*******************************************************************************
 *  parses commandline
 *  choices for args:
 *		      --rcdir <resource_directory>
 *		      --benchmark [number_of_runs]
 *  @param argc 	number of arguments
 *  @param argv 	array of arguments
 */
void parse (int argc, char *argv[]) {
  for (int i = 0; i < argc; i++) {
    if (QString (argv[i]) == QString ("--rcdir"))
      if (i+1 < argc) rcdirs.append (QString (argv[i+1]));
    if (QString (argv[i]) == QString ("--help") ||
	QString (argv[i]) == QString ("-h")) {
      help (argv[0]);
      exit (0);
    }
    if (QString (argv[i]) == QString ("--benchmark")) {
      if (i+1 < argc) benchmark (QString (argv[i+1]).toUInt ());
      else benchmark (10);
    }
  }
}


/*******************************************************************************
 *  initialize and run HyperspaceExplorer
 *  @param argc 	number of arguments
 *  @param argv 	array of arguments
 *  @return 		exit status
 */
int main (int argc, char *argv[]) {
  QApplication app (argc, argv);

  QString rcdir (".HyperspaceExplorer");
  //  if default rc directory does not yet exist, create it
  if (!QDir::home ().exists (rcdir))
    QDir::home ().mkdir (rcdir);
  //  if Vector module for linking custom functions does not exist, copy it
  if (!QDir::home ().exists (rcdir+"/plugins"))
    QDir::home ().mkdir (rcdir+"/plugins");
  if (!QDir::home ().exists (rcdir+"/plugins/Vector.o")) {
#   if 0    
      cerr << (qApp->applicationDirPath ()+"/Vector.o").ascii () << " "
                                                   << (rcdir+"/plugins/Vector.o").ascii () << " "
                                                   << symlink ((qApp->applicationDirPath ()+"/Vector.o").ascii (),
                                                   (QDir::home ().absPath ()+"/"+rcdir+"/plugins/Vector.o").ascii () ) << " "
	 << strerror (errno) << endl
                                                   << qApp->applicationDirPath ()+"/Vector.H "
                                                   << symlink ((qApp->applicationDirPath ()+"/Vector.H").ascii (),
                                                   (QDir::home ().absPath ()+"/"+rcdir+"/plugins/Vector.H").ascii () ) << " "
	 << strerror (errno) << endl;
#   else
                                                   symlink ((qApp->applicationDirPath ()+"/Vector.o").ascii (),
                                                   (QDir::home ().absPath ()+"/"+rcdir+"/Vector/Vector.o").ascii () );
                                           symlink ((qApp->applicationDirPath ()+"/Vector.H").ascii (),
                                                   (QDir::home ().absPath ()+"/"+rcdir+"/plugins/Vector.H").ascii () );
#   endif    
  }  
  rcdirs.append (QDir::home ().absPath ()+"/"+rcdir);
  
  parse (argc, argv);

  rcdirs.append (".");

  C4DView view;
  app.setMainWidget (&view);

  int ret = app.exec ();
  return ret;
}
