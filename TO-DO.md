- get back to full-featured state with current compiler
  - check all commented lines to see what they were good for (//, /*, #if 0)
  - squash all warnings
  - reenable --benchmark
    - and make it run from gitlab CI
- LSystems
- implement multithreaded transformations:
  - add menu entry to switch transformation method
    - make Appearance menu submenu of new Settings menu
  - multithreaded transformations for Composites
  - use Thrust library for CUDA transform
- fix crash when switching desktop and back ("... is not a GL list")
- make rotations on Composites behave correctly
- ensure commitDraw() is only called once, after all vertices are added - do
  something with scope
  - use a GL view that takes advantage of this optimization
- refactor test suites for all Displayables to use as much common code as
  possible
- Matrix should have late binding so different algorithms for multiplication can
  be selected
  - test how much of a performance hit polymorphic Matrix multiplication is
  - move all creations of Matrix objects to a factory
  - replace operator notation with explicit function calls ;-(
- make the output function of Matrix, Vector, Rotation, NestedVector and whatnot
  conform to same interface
- combine vertex array with Realm to have a single class for surfaces without 
  interdependence
- continue with "torations" - or generalize rotations so they can take 
  displacement as a parameter
- separate the UI::View functions out of C4DView and make the rest a controller 
  class
  - change Displayable::Draw() to take a shared_ptr<View> instead of a raw
    pointer

