<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="page">
    <name>index</name>
    <title>HyperspaceExplorer</title>
    <filename>index</filename>
    <docanchor file="index">intro</docanchor>
  </compound>
  <compound kind="group">
    <name>FunctionGroup</name>
    <title>Functions and objects</title>
    <filename>group__FunctionGroup.html</filename>
    <subgroup>RealGroup</subgroup>
    <subgroup>ObjectGroup</subgroup>
    <subgroup>SurfaceGroup</subgroup>
    <class kind="class">ComplexFunction</class>
    <class kind="class">CustomFunctionBase</class>
    <class kind="class">Function</class>
    <class kind="class">Object</class>
    <class kind="class">SteinerFunction</class>
    <class kind="class">Surface</class>
  </compound>
  <compound kind="group">
    <name>RealGroup</name>
    <title>Functions R^3 -&gt; R</title>
    <filename>group__RealGroup.html</filename>
    <subgroup>PolarGroup</subgroup>
    <class kind="class">CustomFunction</class>
    <class kind="class">RealBase</class>
    <class kind="class">RealFunction</class>
    <class kind="class">Hypersphere</class>
    <class kind="class">Torus2</class>
    <class kind="class">Fr3r</class>
    <class kind="class">GravitationPotential</class>
    <class kind="class">Fr3rSin</class>
    <class kind="class">Fr3rExp</class>
  </compound>
  <compound kind="group">
    <name>PolarGroup</name>
    <title>Polar functions R^3 -&gt; R</title>
    <filename>group__PolarGroup.html</filename>
    <class kind="class">CustomPolarFunction</class>
    <class kind="class">Torus1</class>
    <class kind="class">Polar</class>
    <class kind="class">PolarSin</class>
    <class kind="class">PolarSin2</class>
    <class kind="class">PolarR</class>
  </compound>
  <compound kind="group">
    <name>ObjectGroup</name>
    <title>Arbitrary four-dimensional objects, described by their surfaces</title>
    <filename>group__ObjectGroup.html</filename>
    <class kind="class">Hypercube</class>
    <class kind="class">Sponge</class>
    <class kind="class">Pyramid</class>
    <class kind="class">Gasket</class>
  </compound>
  <compound kind="group">
    <name>SurfaceGroup</name>
    <title>Functions R^2 -&gt; R^4, describing surfaces in four-space</title>
    <filename>group__SurfaceGroup.html</filename>
    <subgroup>ComplexGroup</subgroup>
    <class kind="class">CustomSurface</class>
    <class kind="class">SurfaceBase</class>
    <class kind="class">Surface1</class>
    <class kind="class">Horizon</class>
    <class kind="class">Torus3</class>
  </compound>
  <compound kind="group">
    <name>ComplexGroup</name>
    <title>Functions C -&gt; C</title>
    <filename>group__ComplexGroup.html</filename>
    <class kind="class">z2</class>
    <class kind="class">z3</class>
    <class kind="class">zA</class>
    <class kind="class">ez</class>
    <class kind="class">emz2</class>
    <class kind="class">zm1</class>
    <class kind="class">zm2</class>
    <class kind="class">sqrtz</class>
    <class kind="class">lnz</class>
    <class kind="class">sinz</class>
    <class kind="class">cosz</class>
    <class kind="class">sinhz</class>
    <class kind="class">coshz</class>
    <class kind="class">tanz</class>
    <class kind="class">Polynomial</class>
    <class kind="class">CustomComplexFunction</class>
  </compound>
  <compound kind="group">
    <name>FunctorGroup</name>
    <title>Function objects</title>
    <filename>group__FunctorGroup.html</filename>
    <class kind="class">Loki::Functor</class>
  </compound>
  <compound kind="group">
    <name>SingletonGroup</name>
    <title>Singleton</title>
    <filename>group__SingletonGroup.html</filename>
    <subgroup>CreationGroup</subgroup>
    <subgroup>LifetimeGroup</subgroup>
    <class kind="class">Loki::SingletonHolder</class>
    <class kind="class">Loki::Singleton</class>
  </compound>
  <compound kind="group">
    <name>CreationGroup</name>
    <title>Creation policies</title>
    <filename>group__CreationGroup.html</filename>
    <class kind="struct">Loki::CreateUsingNew</class>
    <class kind="struct">Loki::CreateUsing</class>
    <class kind="struct">Loki::CreateUsingMalloc</class>
    <class kind="struct">Loki::CreateStatic</class>
  </compound>
  <compound kind="group">
    <name>LifetimeGroup</name>
    <title>Lifetime policies</title>
    <filename>group__LifetimeGroup.html</filename>
    <subgroup>LongevityLifetimeGroup</subgroup>
    <class kind="struct">Loki::DefaultLifetime</class>
    <class kind="struct">Loki::PhoenixSingleton</class>
    <class kind="struct">Loki::DeletableSingleton</class>
    <class kind="struct">Loki::SingletonWithLongevity</class>
    <class kind="struct">Loki::NoDestroy</class>
    <class kind="class">Loki::FollowIntoDeath</class>
    <member kind="function">
      <type>void</type>
      <name>SetLongevity</name>
      <anchorfile>group__LifetimeGroup.html</anchorfile>
      <anchor>g82d4520d213b3b9ef2090f5e237874cf</anchor>
      <arglist>(T *pDynObject, unsigned int longevity, Destroyer d)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>LongevityLifetimeGroup</name>
    <title>LongevityLifetime</title>
    <filename>group__LongevityLifetimeGroup.html</filename>
    <namespace>LongevityLifetime</namespace>
    <class kind="struct">Loki::LongevityLifetime::SingletonFixedLongevity</class>
    <class kind="struct">Loki::LongevityLifetime::DieLast</class>
    <class kind="struct">Loki::LongevityLifetime::DieDirectlyBeforeLast</class>
    <class kind="struct">Loki::LongevityLifetime::DieFirst</class>
  </compound>
  <compound kind="group">
    <name>SmallObjectGroup</name>
    <title>Small objects</title>
    <filename>group__SmallObjectGroup.html</filename>
    <subgroup>SmallObjectGroupInternal</subgroup>
    <class kind="struct">Loki::LongevityLifetime::DieAsSmallObjectParent</class>
    <class kind="struct">Loki::LongevityLifetime::DieAsSmallObjectChild</class>
    <class kind="class">Loki::SmallObjectBase</class>
    <class kind="class">Loki::SmallObject</class>
    <class kind="class">Loki::SmallValueObject</class>
  </compound>
  <compound kind="group">
    <name>SmallObjectGroupInternal</name>
    <title>Internals</title>
    <filename>group__SmallObjectGroupInternal.html</filename>
    <class kind="class">Loki::SmallObjAllocator</class>
    <class kind="class">Loki::AllocatorSingleton</class>
  </compound>
  <compound kind="group">
    <name>ThreadingGroup</name>
    <title>Threading</title>
    <filename>group__ThreadingGroup.html</filename>
    <class kind="class">Loki::Mutex</class>
    <class kind="class">Loki::SingleThreaded</class>
  </compound>
  <compound kind="group">
    <name>VecMathTest</name>
    <title>Vector and Matrix algebra optimized, in test state</title>
    <filename>group__VecMathTest.html</filename>
    <class kind="struct">VecMath::NotYetImplementedException</class>
    <class kind="class">VecMath::Matrix</class>
  </compound>
  <compound kind="group">
    <name>UIGroup</name>
    <title>User Interface</title>
    <filename>group__UIGroup.html</filename>
    <subgroup>UIHelpers</subgroup>
    <class kind="class">C4DView</class>
    <class kind="class">AnimationDialogImpl</class>
    <class kind="class">ComplexDialogImpl</class>
    <class kind="class">FunctionDialogImpl</class>
    <class kind="class">GLObject</class>
    <class kind="class">Menu4D</class>
    <class kind="class">PluginCreator</class>
    <class kind="class">PolarDialogImpl</class>
    <class kind="class">SurfaceDialogImpl</class>
    <class kind="class">ValuesDialogImpl</class>
    <class kind="class">XQGLWidget</class>
  </compound>
  <compound kind="group">
    <name>UIHelpers</name>
    <title>Helper classes for User Interface classes</title>
    <filename>group__UIHelpers.html</filename>
    <class kind="class">RealFunctionFactory</class>
    <class kind="class">SurfaceFactory</class>
    <class kind="class">C4DView::TemplatedRealFunctionFactory</class>
    <class kind="class">C4DView::TemplatedSurfaceFactory</class>
    <class kind="class">C4DView::CustomFunctionSlot</class>
    <class kind="class">FunctionSlotHelper</class>
    <class kind="class">SurfaceSlotHelper</class>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>createCustomFunction</name>
      <anchorfile>group__UIHelpers.html</anchorfile>
      <anchor>gb4150e26778debfb3de8214203578a41</anchor>
      <arglist>(C4DView *view)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual RealFunction *</type>
      <name>createFunction</name>
      <anchorfile>group__UIHelpers.html</anchorfile>
      <anchor>ged16c50d49e40a85f81e1c3f8a98e916</anchor>
      <arglist>(C4DView *)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>VecMath</name>
    <title>Vector and Matrix algebra</title>
    <filename>group__VecMath.html</filename>
    <class kind="class">VecMath::Matrix</class>
    <class kind="class">VecMath::Vector</class>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>gef433144f359a8cda43c2290871425b3</anchor>
      <arglist>(std::ostream &amp;o, const Vector&lt; D, N &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D &gt;</type>
      <name>cross</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g42f840301b4c197f9e58290655ad7f73</anchor>
      <arglist>(const Vector&lt; D &gt; &amp;, const Vector&lt; D &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D &gt;</type>
      <name>cross</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g84360f66f3dcffe78961def5353844f3</anchor>
      <arglist>(const Vector&lt; D &gt; &amp;, const Vector&lt; D &gt; &amp;, const Vector&lt; D &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; 3, N &gt;</type>
      <name>vcross</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g5f42c95ec973af0eae139718319fc9dd</anchor>
      <arglist>(Vector&lt; 3, N &gt; a, Vector&lt; 3, N &gt; b)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; 4, N &gt;</type>
      <name>vcross</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g73fe56ecc2d2897eb3f5c1b723536e11</anchor>
      <arglist>(Vector&lt; 4, N &gt; a, Vector&lt; 4, N &gt; b, Vector&lt; 4, N &gt; c)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>vnormalize</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g4b99a05522c09599748899e794bc65e9</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;x)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>AnimationDialogImpl</name>
    <filename>classAnimationDialogImpl.html</filename>
    <member kind="function">
      <type></type>
      <name>AnimationDialogImpl</name>
      <anchorfile>classAnimationDialogImpl.html</anchorfile>
      <anchor>23097e15ef85fd3616b804b7de14db7d</anchor>
      <arglist>(QWidget *parent=0, Qt::WFlags f=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~AnimationDialogImpl</name>
      <anchorfile>classAnimationDialogImpl.html</anchorfile>
      <anchor>4c9b789036a6bdd3946ef740d51af1e8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>getFrames</name>
      <anchorfile>classAnimationDialogImpl.html</anchorfile>
      <anchor>fe27f8e4964bfb47b1077dbe3d6c01a1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getDir</name>
      <anchorfile>classAnimationDialogImpl.html</anchorfile>
      <anchor>103a707a4a171815281250c32a5a017f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getPrefix</name>
      <anchorfile>classAnimationDialogImpl.html</anchorfile>
      <anchor>f296b830191f9b9b64a75fa1f79ce315</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>openFileDialog</name>
      <anchorfile>classAnimationDialogImpl.html</anchorfile>
      <anchor>9a53610a48693af3702d7c5febd65a47</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>C4DView</name>
    <filename>classC4DView.html</filename>
    <base>XQGLWidget</base>
    <member kind="slot">
      <type>void</type>
      <name>Wireframe</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>a85ee69ee9d08b67f7c80a808899250d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>Coordinates</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>b1879724a1a60391e50df4b28e788637</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>HyperFog</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6ec69c264ef0fbc942ad10681e143c4f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>Light</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>85b0abd47c0ba580eeade18a29f7e659</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>Colors</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e7d270b5c291f26895ca051ca6162480</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>Fog</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>4a37060ea7489e65b44f85b558e134e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>Transparent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>5f904b3e57ae685e36ec2dbd59bb27fa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>Shade</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>0710f796e1d311cd309ea6901a0c6130</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>Benchmark</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f3d208f4c7ac90df63b87c2bb0e845c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>RenderToImages</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>85e1779319ecc80e3b98473cbf3a9faa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>ObjectHypercube</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>bc3a4f6e3276734aa70e0853f0df6022</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>ObjectHyperpyramid</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>951f672d7d323bb799c1ab18d412e1d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>ObjectHypersponge</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>395baf447937415a0f3366c4d1c529ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>ObjectGasket</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>2b8270b08a2a62faa7381adcd83715af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>customFunction</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f530ff0aca68b1e08e154a40608c11b3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>customPolarFunction</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f20dba04d475059869fa8f663fca0ac7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>customSurface</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c22a486c7bd7231ed278452281190f03</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>customComplexFunction</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6a39870f461647dd0dacc0d3f683ba56</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>C4DView</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>1d7079e8957ce7e685531a3f9062c468</anchor>
      <arglist>(QWidget *=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~C4DView</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>7d2fd637746d3f3148c904abfcb19806</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setWireframe</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>50cd0bdd8d4df8eb716691b7cb873de3</anchor>
      <arglist>(bool wire)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getColors</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>11d1dc167954200076be2356f842f326</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getShade</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>b7c711c8e896b9e7be780f5ebb765295</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getFog</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>5ac61e899d29f964da5f01c5f619343c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getLight</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>92be44cfa82ced5b0a4adcfaeb89dfc3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getTransparent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d68aa80ea300193b700aeb001cf4e8bc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getDisplayCoordinates</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>75ddb2c5f106d81db18300d316d86972</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getRenderToPixmap</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>dc4f19f4c1433bbb8bea6c37177adefe</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>getDisplayPolygons</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>68bbe4bf27aba718c97b3f456cf656e6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Benchmark3D</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8a01e49be6af9cab84880a176b7c42ae</anchor>
      <arglist>(int, double, double, double, bool=true)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>Benchmark4D</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>60f45904ff9b227fdf426b5960fa4130</anchor>
      <arglist>(int, double, double, double, bool=true)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>OnTimer</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>2c45a3e0625e7ee0567630203bbb0360</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>AnimationSettings</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c781d4f8f3a11fd65fc0c41921460b59</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>ApplyChanges</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>2b2301dc9f09593ece4bf58a742dd0b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Transform</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6850e75dd5a38a4ffc5d0a1f7bcb953d</anchor>
      <arglist>(double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw, double Tx, double Ty, double Tz, double Tw)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Transform</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>16d5190870a166c65a20c59368ca0f2f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Project</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>b9ec4da2c4a27a95302759968c3b9d90</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Draw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>87493fb1f2d39371ddfd024f72676738</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>PreRedraw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>638fd2fe648c1fcd8f9a3ac03ac8f6b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Redraw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8d3fbc1fbe82b40046652bca8bde9605</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>RenderScene</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e0e7e693f0c2ba5afeaea265c8c21895</anchor>
      <arglist>(unsigned Frame)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>OnPaint</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e8db20fdfebe8d979f90ff303305a79d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>InitCross</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>04a35de24dbf03d029afc5d0be93ec11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetupDepthCue</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f46da1a68ffbcc00eddc03df078fe150</anchor>
      <arglist>(bool)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>DrawCoordinates</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>37a8191d956104629a6182ba86755cd1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>StartAnimation</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>715dbd8c1e15f6d118853e1789d081e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>StopAnimation</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>45b036ac24d2404ad7bd69139a49b2d8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>RandomAnimation</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f33c8cf03fcfc94d4c64f9f4454b0339</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>QPixmap</type>
      <name>makePixmap</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>99a55bb5dd4ba5f78e31506c55425987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>writeFrame</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>54cf3b6bbb8bf1eed47afc6da5fcebe2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>checkAnglesForOverflow</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>0b8d96f3304d94af1bac8854c908842f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>UpdateStatus</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d37702c9ecc5cbf124df84d0263734b9</anchor>
      <arglist>(QString=&quot;&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>AssignValues</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e38186ceacf6c4e6b13de7bee6cd8bda</anchor>
      <arglist>(const std::auto_ptr&lt; Function &gt; &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double</type>
      <name>Size</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>15c8ca4d71f5b5e5b07a959601820f83</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>mouseMoveEvent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>1b5e87b494b99e3705c64e924480f4ef</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>mousePressEvent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>93fd8d7586928e6cd1b0c7131bff84b2</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>mouseReleaseEvent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>00949bc8cb7215be6ff50e947d6f576f</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>mouseDoubleClickEvent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6dc432e565b97c2aa6f2273bbe4135c7</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>paintEvent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>5ff6e70d47395827f5ef14793253c8d0</anchor>
      <arglist>(QPaintEvent *)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>resizeEvent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>5f79a84b79c832319a46af95192ad180</anchor>
      <arglist>(QResizeEvent *)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeGL</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>3c797ad72f10f9d43d720a45cd60509a</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::auto_ptr&lt; Function &gt;</type>
      <name>F</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>eb29ac45dbb361327d3a896d6cfeb3dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Tx</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>db5cfd77a40b633ec673817596bee941</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Ty</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>35d5730f883860881c08fd92fb1c45f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Tz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>85279ff6a911120f4a639e978aee28a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Tw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>220596e2ea0808fd2649bf5e15665c70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Rxy</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f616f6f928911482a1289a7b7383e9d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Rxz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>1de4e8cf82971be49b90642ed1b1ce8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Rxw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>ff9f5d182cdc045e3d4fd4caee8b2d78</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Ryz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>25e68533955f4aeaff3a2598a0e0d22c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Ryw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8f3ca9b51d740fc803f909faa91e05e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Rzw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>df17c0f3427a04cfb4ba26f5975ab8c2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>GLdouble</type>
      <name>m_rotX</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f4c3a85eec507687a6c8582d72d35f8f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>GLdouble</type>
      <name>m_rotY</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e039bceeeedfb04fe7c499a6b3b6b6f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>GLdouble</type>
      <name>m_rotZ</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>46e61c4e6edb2d937edc786a164fd5c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>GLdouble</type>
      <name>m_transX</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8c1ed22d36c0d09d267ac7acf5c62177</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>GLdouble</type>
      <name>m_transY</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>cadab1413fbe0090c2977cbde134cdd1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>GLdouble</type>
      <name>m_camZ</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e1dce655f46f29f97e103657bb32ed92</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>CamW</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>96287a5656d85fbf043ca2115ba032dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>ScrW</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>3a259a45ebe409bbcbc40194434680ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>AntiAlias</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>1091fdf89eeefab1571c162a2d930d0e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>DisplayPolygons</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>abe62566f12f502ce84c70315a5a09fb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>Lighting</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>350c7f9a53d4da61b995ac46775636ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>DepthCue3D</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>7cffa336571a0dbe61187ba872198828</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>DepthCue4D</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e4c78c156b6ffb23361ac3ebfb2071f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>DisplayCoordinates</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>cb7e608271d4ef0047ba421b650e0772</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>RenderToPixmap</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6b2f78bc553d6d393bb94e33f01d17f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QString</type>
      <name>animationDirectory</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>7cb6cee77811f65a77cb0c97bac8203e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QString</type>
      <name>animationPrefix</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e766d45e783ed357a35cb3482b1a4cc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>animationMaxFrames</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>099120e62f40d3ba958361c736d5b127</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>const unsigned</type>
      <name>animation_fps</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>dc3741dcb91695bf84c2f921a0d1ca2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>GLint</type>
      <name>ObjectList</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>a98a366c65ed9c65156d47d09244e08d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>GLint</type>
      <name>CoordinateCross</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>0447c7f6581eb8f83ce1a7b6a254a34a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>Animated</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c93c8aafdb0ea0c423778c488659e5d9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>TakingSpinValues</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>459c2b9c088667794ee7439f3ec871ae</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>animationFrame</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>11d5c808eca03f51b584e3914be7e3c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>CurrentlyRendering</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>17f63d856f35e4b651ab7462122f0ea2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QPoint</type>
      <name>m_LeftDownPos</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>1207eda2b7efe382f85ed4574a0f635d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QPoint</type>
      <name>m_MidDownPos</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>32d7f659a68895fbc3353c23c65f5d41</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QPoint</type>
      <name>m_RightDownPos</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d6eef90e25422bfcfc1663309ed595a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QTimer *</type>
      <name>AnimationTimer</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>545e55ae07939317721b12a6da92eb86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QTimer *</type>
      <name>AnimateRandomTimer</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>ceae252bed8926ed258fdbe764a7ecf2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ValuesDialogImpl *</type>
      <name>Values</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>01680cf201e442d0568e5880496d74d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dxy</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>eccde127fe4cea16d334b1e68e14e0a1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dxz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6deb7cbfe0ad56bc162a90f1cadd3333</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dxw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>eb93c8f93ba6b011dd4694d78d4940e2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dyz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>802dc6d624a69f8f8c65a99b4b676e48</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dyw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>11c7bfdf817cf329783fd4fc9bcfe932</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dzw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>813e9410b0d5655609b3da15ca471446</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dx</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d016759aaf2d5bb311bc8e80ed9b337b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dy</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>4c723750173470484a107461148e0960</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>7f09fb0903ba5a2fb70d51b7274cabf0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; std::vector&lt; VecMath::Vector&lt; 4 &gt; &gt; &gt;</type>
      <name>Cross</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>3a944bfbcae2c13b0fcac503d62a60fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; std::vector&lt; VecMath::Vector&lt; 4 &gt; &gt; &gt;</type>
      <name>CrossTrans</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>0eba9d6ac6f7fe31287fd728ef61266c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; std::vector&lt; VecMath::Vector&lt; 3 &gt; &gt; &gt;</type>
      <name>CrossScr</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>4b450c11b94a6dc190fd7b0e8bdb64c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Menu4D *</type>
      <name>menu</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>9311d9bc1abd37efb55eca7ecbcf964b</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>CustomFunctionSlot&lt; CustomFunction &gt;</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e47dce0b05c5aa8b8166aef6df650108</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>CustomFunctionSlot&lt; CustomPolarFunction &gt;</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6da5c089645fd25577a1e32f4db77d06</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>CustomFunctionSlot&lt; CustomComplexFunction &gt;</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>a8678e6fee93da8081f6a9011a1d41cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>CustomFunctionSlot&lt; CustomSurface &gt;</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>fe3d7015a7bf22b3cf3a7ad178630e2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>FunctionSlotHelper</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>36046b63ea701d901a03695f98246e78</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="protected">
      <type>friend class</type>
      <name>SurfaceSlotHelper</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>ac8480f38ed88a738dd93173e300cd97</anchor>
      <arglist></arglist>
    </member>
    <class kind="class">C4DView::CustomFunctionSlot</class>
    <class kind="class">C4DView::TemplatedRealFunctionFactory</class>
    <class kind="class">C4DView::TemplatedSurfaceFactory</class>
  </compound>
  <compound kind="class">
    <name>C4DView::CustomFunctionSlot</name>
    <filename>classC4DView_1_1CustomFunctionSlot.html</filename>
    <templarg>function</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>createCustomFunction</name>
      <anchorfile>group__UIHelpers.html</anchorfile>
      <anchor>gb4150e26778debfb3de8214203578a41</anchor>
      <arglist>(C4DView *view)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>createCustomSurface</name>
      <anchorfile>classC4DView_1_1CustomFunctionSlot.html</anchorfile>
      <anchor>2eaaaf653f2d1bbfe3a2b416f33e4b08</anchor>
      <arglist>(C4DView *view)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>C4DView::TemplatedRealFunctionFactory</name>
    <filename>classC4DView_1_1TemplatedRealFunctionFactory.html</filename>
    <templarg>function</templarg>
    <base>RealFunctionFactory</base>
    <member kind="function" virtualness="virtual">
      <type>virtual RealFunction *</type>
      <name>createFunction</name>
      <anchorfile>group__UIHelpers.html</anchorfile>
      <anchor>ged16c50d49e40a85f81e1c3f8a98e916</anchor>
      <arglist>(C4DView *)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>C4DView::TemplatedSurfaceFactory</name>
    <filename>classC4DView_1_1TemplatedSurfaceFactory.html</filename>
    <templarg>function</templarg>
    <base>SurfaceFactory</base>
    <member kind="function" virtualness="virtual">
      <type>virtual Surface *</type>
      <name>createSurface</name>
      <anchorfile>classC4DView_1_1TemplatedSurfaceFactory.html</anchorfile>
      <anchor>00cfc1d3d1125e22c38325610d10b457</anchor>
      <arglist>(C4DView *)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Color</name>
    <filename>classColor.html</filename>
    <member kind="function">
      <type></type>
      <name>Color</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>565126164d4a96f3b109829391702c7c</anchor>
      <arglist>(float, float, float, float=0.)</arglist>
    </member>
    <member kind="function">
      <type>float &amp;</type>
      <name>r</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>9023bb1107a89197950986157c4ef9de</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>float &amp;</type>
      <name>g</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>4b63eac9efcfc3f626f10f43f4f13391</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>float &amp;</type>
      <name>b</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>48ea644ea0e8f943f5049a1fae966c55</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>float &amp;</type>
      <name>a</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>3ef2ea6a92faf2a560e359cfa75a3597</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator float *</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>b64d37c2436bee884af85d80d5cae572</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Color</type>
      <name>operator*=</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>96290badbfa2d5aa740bbea07ee5bdc0</anchor>
      <arglist>(float)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setComponentLowerLimit</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>6c25bc30b1d2dbd3210d1964fae53742</anchor>
      <arglist>(float)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setComponentUpperLimit</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>90b94d65cd470c2ac979825c0c1b2c20</anchor>
      <arglist>(float)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>float</type>
      <name>RGBA</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>945779bc9577f258cff038ed98b1b6e2</anchor>
      <arglist>[4]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ComplexDialogImpl</name>
    <filename>classComplexDialogImpl.html</filename>
    <base>PluginCreator</base>
    <member kind="slot" virtualness="virtual">
      <type>virtual bool</type>
      <name>checkValidity</name>
      <anchorfile>classComplexDialogImpl.html</anchorfile>
      <anchor>8c0f8801288912c8374cd69441cff5db</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual bool</type>
      <name>loadFunction</name>
      <anchorfile>classComplexDialogImpl.html</anchorfile>
      <anchor>3a58825ce6e3bd308916f9ca888dd91a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ComplexDialogImpl</name>
      <anchorfile>classComplexDialogImpl.html</anchorfile>
      <anchor>4ff709ebd98f53e5da1b862113eb3d66</anchor>
      <arglist>(QWidget *parent=0, Qt::WFlags f=0)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>functionPresent</name>
      <anchorfile>classComplexDialogImpl.html</anchorfile>
      <anchor>e7174b5975f212e06c53bb4f8cf965f8</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>writeSource</name>
      <anchorfile>classComplexDialogImpl.html</anchorfile>
      <anchor>26ac6a4d95b30d9741d18ed6e02a245a</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ComplexFunction</name>
    <filename>classComplexFunction.html</filename>
    <base>Surface</base>
    <member kind="function">
      <type></type>
      <name>ComplexFunction</name>
      <anchorfile>classComplexFunction.html</anchorfile>
      <anchor>1ca44717ee72b524ce3e7afd8d358ca0</anchor>
      <arglist>(const QString &amp;name, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~ComplexFunction</name>
      <anchorfile>classComplexFunction.html</anchorfile>
      <anchor>c61debf37f95ee22901d7c086ec098f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classComplexFunction.html</anchorfile>
      <anchor>644b064a32d83344be095b2375cb1e90</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="function">
      <type>typedef std::complex&lt; double &gt;</type>
      <name>function_type</name>
      <anchorfile>classComplexFunction.html</anchorfile>
      <anchor>1b8acddb789e35834c412b16743d1cb9</anchor>
      <arglist>(std::complex&lt; double &gt;)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>f</name>
      <anchorfile>classComplexFunction.html</anchorfile>
      <anchor>234485506b16d03867c20e8e8d7e0b21</anchor>
      <arglist>(double, double)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Initialize</name>
      <anchorfile>classComplexFunction.html</anchorfile>
      <anchor>a978ff4b165e029bb82ba33dce35e4e3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classComplexFunction.html</anchorfile>
      <anchor>2e32c8694d416d318bd81ce004f44086</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>coshz</name>
    <filename>classcoshz.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>coshz</name>
      <anchorfile>classcoshz.html</anchorfile>
      <anchor>0460b05f1d89b00e63e932f7a1dac1cf</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classcoshz.html</anchorfile>
      <anchor>47afebca43426823d6396f93649acf29</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classcoshz.html</anchorfile>
      <anchor>fa65daf802d43d894d545c6fa28d3c25</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>cosz</name>
    <filename>classcosz.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>cosz</name>
      <anchorfile>classcosz.html</anchorfile>
      <anchor>51b502bea027c0d691f0e093db0d3e2a</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classcosz.html</anchorfile>
      <anchor>e6b035b5222d74ef9abe20b99a94e827</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classcosz.html</anchorfile>
      <anchor>558a3b254b3dbf8834a581e37fd0ea8f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>CustomComplexFunction</name>
    <filename>classCustomComplexFunction.html</filename>
    <base>ComplexFunction</base>
    <base>CustomFunctionBase&lt; ComplexFunction::function_type &gt;</base>
    <member kind="function">
      <type></type>
      <name>CustomComplexFunction</name>
      <anchorfile>classCustomComplexFunction.html</anchorfile>
      <anchor>5d1101707ec8a50c97620c85ce279f24</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CustomComplexFunction</name>
      <anchorfile>classCustomComplexFunction.html</anchorfile>
      <anchor>ea0f69a39d81d3c4ae1da0bd7d550b5c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>ComplexFunction::function_type</type>
      <name>g</name>
      <anchorfile>classCustomComplexFunction.html</anchorfile>
      <anchor>c5e94e402bf81b2324ade8e60f9d56a3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>CustomFunction</name>
    <filename>classCustomFunction.html</filename>
    <base>RealFunction</base>
    <base>CustomFunctionBase&lt; RealFunction::raw_function_type &gt;</base>
    <member kind="function">
      <type></type>
      <name>CustomFunction</name>
      <anchorfile>classCustomFunction.html</anchorfile>
      <anchor>6b507d733c2fb3595e00df9c1a575cb3</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, bool final=true)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CustomFunction</name>
      <anchorfile>classCustomFunction.html</anchorfile>
      <anchor>fe42408508c689532dd7b73576210751</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>f</name>
      <anchorfile>classCustomFunction.html</anchorfile>
      <anchor>8091263336df8fc584788756a811c9e5</anchor>
      <arglist>(double, double, double)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>CustomFunctionBase</name>
    <filename>classCustomFunctionBase.html</filename>
    <templarg>function_type</templarg>
    <member kind="function">
      <type>QString</type>
      <name>symbolic</name>
      <anchorfile>classCustomFunctionBase.html</anchorfile>
      <anchor>3060ebeee0e5430aaac08cd2d2031ca7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>isValid</name>
      <anchorfile>classCustomFunctionBase.html</anchorfile>
      <anchor>65eb2e36fd445edeeaaee56b1f352343</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>loadFunction</name>
      <anchorfile>classCustomFunctionBase.html</anchorfile>
      <anchor>d2e4b7516d73ab9ebeb9a33c6708f6b8</anchor>
      <arglist>(const QString &amp;, QString=&quot;f&quot;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setValid</name>
      <anchorfile>classCustomFunctionBase.html</anchorfile>
      <anchor>5bfbc3ddb6bf716ec25672e903cca40e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setInvalid</name>
      <anchorfile>classCustomFunctionBase.html</anchorfile>
      <anchor>deba6cb6f2a94795aac27f22783193b1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>function_type *</type>
      <name>func</name>
      <anchorfile>classCustomFunctionBase.html</anchorfile>
      <anchor>e1c85b8492b3259da76fb076d2de9c41</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>void *</type>
      <name>handle</name>
      <anchorfile>classCustomFunctionBase.html</anchorfile>
      <anchor>80f923985c3463bddc2e57ff41887d86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>valid</name>
      <anchorfile>classCustomFunctionBase.html</anchorfile>
      <anchor>0a8f0d22381cd68f9229024bf75971e3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>CustomPolarFunction</name>
    <filename>classCustomPolarFunction.html</filename>
    <base>CustomFunction</base>
    <member kind="function">
      <type></type>
      <name>CustomPolarFunction</name>
      <anchorfile>classCustomPolarFunction.html</anchorfile>
      <anchor>4da5bf879492f3baa2dc472fcfd5b70c</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CustomPolarFunction</name>
      <anchorfile>classCustomPolarFunction.html</anchorfile>
      <anchor>dd055521ce33d0e4e420e52e9e133c78</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>f</name>
      <anchorfile>classCustomPolarFunction.html</anchorfile>
      <anchor>5e5e847b7a80c3df3b9c893494257cbc</anchor>
      <arglist>(double, double, double)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>CustomSurface</name>
    <filename>classCustomSurface.html</filename>
    <base>Surface</base>
    <base>CustomFunctionBase&lt; Surface::raw_function_type &gt;</base>
    <member kind="function">
      <type></type>
      <name>CustomSurface</name>
      <anchorfile>classCustomSurface.html</anchorfile>
      <anchor>72af48595fc53ce17862cd05fb1fae22</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~CustomSurface</name>
      <anchorfile>classCustomSurface.html</anchorfile>
      <anchor>09a78eacb67d05a4e4854301f0505212</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual Surface::function_type</type>
      <name>f</name>
      <anchorfile>classCustomSurface.html</anchorfile>
      <anchor>1d54a8a914cc1d2133dda2d72235eac7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>emz2</name>
    <filename>classemz2.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>emz2</name>
      <anchorfile>classemz2.html</anchorfile>
      <anchor>9754439ceb4812a1688a34dddaf62451</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, double _alpha=1)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classemz2.html</anchorfile>
      <anchor>32a37152a8c5006fb61b10e3bc23125d</anchor>
      <arglist>(double _a=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classemz2.html</anchorfile>
      <anchor>65b0faaa192623a7b348388c728b4fad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>alpha</name>
      <anchorfile>classemz2.html</anchorfile>
      <anchor>01515f10d97c4aa3ac9ba1b2543280d5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ez</name>
    <filename>classez.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>ez</name>
      <anchorfile>classez.html</anchorfile>
      <anchor>d063385199577c6d317c40e5d773bdc5</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, double _alpha=2)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classez.html</anchorfile>
      <anchor>c405c6888cb741bb61d8baec5a9fafda</anchor>
      <arglist>(double _a=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classez.html</anchorfile>
      <anchor>9518db66e4e846eda5895791c9417fa4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>alpha</name>
      <anchorfile>classez.html</anchorfile>
      <anchor>b206b0560b82b129f183e0efa1f48840</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Fr3r</name>
    <filename>classFr3r.html</filename>
    <base>RealFunction</base>
    <member kind="function">
      <type></type>
      <name>Fr3r</name>
      <anchorfile>classFr3r.html</anchorfile>
      <anchor>438c26c506e5fda0242a16ba517a4e5e</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classFr3r.html</anchorfile>
      <anchor>4dfb0ba6640f894d2e08d062ec98cadb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Radius</name>
      <anchorfile>classFr3r.html</anchorfile>
      <anchor>105b69177647b3a246002885c3834da3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Fr3rExp</name>
    <filename>classFr3rExp.html</filename>
    <base>RealFunction</base>
    <member kind="function">
      <type></type>
      <name>Fr3rExp</name>
      <anchorfile>classFr3rExp.html</anchorfile>
      <anchor>2711de0e8315031811dc0c7c95f80786</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classFr3rExp.html</anchorfile>
      <anchor>455382fbe0bf6c17e607ae106a4d94ac</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Fr3rSin</name>
    <filename>classFr3rSin.html</filename>
    <base>RealFunction</base>
    <member kind="function">
      <type></type>
      <name>Fr3rSin</name>
      <anchorfile>classFr3rSin.html</anchorfile>
      <anchor>c26b6a297516602648707d867cd6b4bf</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classFr3rSin.html</anchorfile>
      <anchor>3f1f72ff9d484144c49bdbed4658bb6a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Function</name>
    <filename>classFunction.html</filename>
    <member kind="typedef">
      <type>std::vector&lt; float &gt;</type>
      <name>floatvec1D</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>8bb7d4dbd11f9ca7b8d1e2411e9a02e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; floatvec1D &gt;</type>
      <name>floatvec2D</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>4c15e6200b99c8e333e0fc1859822b2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; floatvec2D &gt;</type>
      <name>floatvec3D</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>9c3a1e1ebb63069140bedf690fe2cae8</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecMath::Vector&lt; 3 &gt; &gt;</type>
      <name>vec3vec1D</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>b4b38b599eb124967f4665e2d56afb64</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; vec3vec1D &gt;</type>
      <name>vec3vec2D</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>9f46be8d00fa46a28bbd9165074510bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; vec3vec2D &gt;</type>
      <name>vec3vec3D</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>f3fbebbb4cb0151aeea503738ad6fd2f</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; VecMath::Vector&lt; 4 &gt; &gt;</type>
      <name>vec4vec1D</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>67b6c27b652c41b419602713cd4d72b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; vec4vec1D &gt;</type>
      <name>vec4vec2D</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>0c807fd0b7c98ca9c5052c15b3c817a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; vec4vec2D &gt;</type>
      <name>vec4vec3D</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>fbc77cb3e6c8ca2c59225db92f5e420c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>e206568fd4fd4c885e3ccff76345c4e6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Function</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>860c512c6fde48ab92d69033ca48c0d7</anchor>
      <arglist>(const QString &amp;name, double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Transform</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>ba589b8ff84f92035c7b74bef6e9c1fc</anchor>
      <arglist>(double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw, double Tx, double Ty, double Tz, double Tw)=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Transform</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>42e2e15e46dc3c126a924ad7701ef69f</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Project</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>929005804b69da40687124c28d9116e2</anchor>
      <arglist>(double ScrW, double CamW, bool DepthCue4D)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Draw</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>77acd0c0e0414c96bfe56b6a4f5929d6</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>ReInit</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>6a8c47a1286ef289e53bb3a2cef07bb5</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>d718e144e4dadb18eeb5eebcc46ac3f5</anchor>
      <arglist>(double _a=0, double _b=0, double _c=0, double _d=0)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getFunctionName</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>d9d5798104590fa83ac7c43502a4ed72</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>getNumParameters</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>d18b0ec9865d28b35579cb3d908ef202</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::vector&lt; QString &gt;</type>
      <name>getParameterNames</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>55e3c5ac36b0597f9332287502fe07f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>getParameterName</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>0a05df01c1ec8b0aa9a23a3551da3d53</anchor>
      <arglist>(unsigned i)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>operator()</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>68cf5a6e74a4f6a96893079ace0dc228</anchor>
      <arglist>(double, double, double)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual vec4vec1D</type>
      <name>df</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>7e1d08b78b48b4be45772cec73b926ac</anchor>
      <arglist>(double, double, double)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>Initialize</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>2da5ea0209b3253e285fe4d56f10d0bb</anchor>
      <arglist>(void)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual unsigned long</type>
      <name>MemRequired</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>d6a10b999b0d561d36a473d461c62311</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>tmin</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>6fbe081f6df6800e076075f5ab4b964f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>tmax</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>f135b0723892c79a2d0191f00e4ca8f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dt</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>a97d770719415f7023f04ada90a03576</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>umin</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>c071319d6c2ef873f73f88fe952e3fa1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>umax</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>07225eeeb1060365dd8675f4ebdc8332</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>du</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>be75c0330aee2be564da236c2ad6af89</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>vmin</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>6636c1379de44f6087a135e6a47a1173</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>vmax</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>977fa459e3fb608ed60fb1b6446b6d07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dv</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>0816edec47aa531c04a233208a0bb44b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>tsteps</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>99b0bf62c51a77b25e0a1141a740dde6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>usteps</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>eec8fc2cf02bb1ddab2c333af7b0e720</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>vsteps</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>4dafffb2325a48316f08c70c34e1b0f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>VecMath::Vector&lt; 4 &gt;</type>
      <name>F</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>3805b737129fe652314bf2603c9b7855</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>NumVertices</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>e2fe5f64785bde405df1c0c7d69bbc46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QString</type>
      <name>functionName</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>e7491b1f17c6929f8716f07bfa5f2b46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; QString &gt;</type>
      <name>parameterNames</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>b51bc4eb3a16cd5073803509fc5a242e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FunctionDialogImpl</name>
    <filename>classFunctionDialogImpl.html</filename>
    <base>PluginCreator</base>
    <member kind="slot" virtualness="virtual">
      <type>virtual bool</type>
      <name>checkValidity</name>
      <anchorfile>classFunctionDialogImpl.html</anchorfile>
      <anchor>bab23d215be4015efddc7a173f55d65f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual bool</type>
      <name>loadFunction</name>
      <anchorfile>classFunctionDialogImpl.html</anchorfile>
      <anchor>b1716ee7d7cfd63874b8f3db029db031</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FunctionDialogImpl</name>
      <anchorfile>classFunctionDialogImpl.html</anchorfile>
      <anchor>f1a24630efd60292e3a473d9ca447fa7</anchor>
      <arglist>(QWidget *parent=0, Qt::WFlags f=0)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>functionPresent</name>
      <anchorfile>classFunctionDialogImpl.html</anchorfile>
      <anchor>5c1cadd3333c5e6008b54298cce46696</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>writeSource</name>
      <anchorfile>classFunctionDialogImpl.html</anchorfile>
      <anchor>42b371226c6719adae49e8cb7eb457b1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FunctionSlotHelper</name>
    <filename>classFunctionSlotHelper.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>slot</name>
      <anchorfile>classFunctionSlotHelper.html</anchorfile>
      <anchor>faed6163af28f8aec9713bc41db04764</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FunctionSlotHelper</name>
      <anchorfile>classFunctionSlotHelper.html</anchorfile>
      <anchor>9b1187ecca8c85f4ab35ca29d3eeb32e</anchor>
      <arglist>(C4DView *_view, RealFunctionFactory *ff)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~FunctionSlotHelper</name>
      <anchorfile>classFunctionSlotHelper.html</anchorfile>
      <anchor>333781450ab084e3e900e591b60ed7fd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>C4DView *</type>
      <name>view</name>
      <anchorfile>classFunctionSlotHelper.html</anchorfile>
      <anchor>48b327d3202aabe535e4f4ab6ae6e5d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>RealFunctionFactory *</type>
      <name>functionFactory</name>
      <anchorfile>classFunctionSlotHelper.html</anchorfile>
      <anchor>293309d6079d4a20edec924a3e61522c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Gasket</name>
    <filename>classGasket.html</filename>
    <base>Pyramid</base>
    <member kind="function">
      <type></type>
      <name>Gasket</name>
      <anchorfile>classGasket.html</anchorfile>
      <anchor>02cf79a8236f67c60e616d6016ca32b2</anchor>
      <arglist>(unsigned level=1, double rad=1, VecMath::Vector&lt; 4 &gt; Center=VecMath::Vector&lt; 4 &gt;(0., 0., 0., 0.))</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Transform</name>
      <anchorfile>classGasket.html</anchorfile>
      <anchor>1621e2fd3bbdfa08d856267d0946daf4</anchor>
      <arglist>(double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw, double Tx, double Ty, double Tz, double Tw)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Project</name>
      <anchorfile>classGasket.html</anchorfile>
      <anchor>cd9211ebec49fe02e9794526afc41194</anchor>
      <arglist>(double ScrW, double CamW, bool DepthCue4D)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Draw</name>
      <anchorfile>classGasket.html</anchorfile>
      <anchor>86e0a72afdfc932b81e6ced27ed3b130</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classGasket.html</anchorfile>
      <anchor>3cf2053ec1ffa7afc2c65973a5f3afbe</anchor>
      <arglist>(double _a=0, double _b=0, double=0, double=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ReInit</name>
      <anchorfile>classGasket.html</anchorfile>
      <anchor>d4ff88db24102c117decfc8d4309489a</anchor>
      <arglist>(double, double, double, double, double, double, double, double, double)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>Initialize</name>
      <anchorfile>classGasket.html</anchorfile>
      <anchor>1c1d1a1c6508a13532efd9b4618781e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual unsigned long</type>
      <name>MemRequired</name>
      <anchorfile>classGasket.html</anchorfile>
      <anchor>e65a8be228108ab1997e0cc80504aa56</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>Level</name>
      <anchorfile>classGasket.html</anchorfile>
      <anchor>3cf0e9d9a6fb5df3116d6fe6089eec31</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; Pyramid * &gt;</type>
      <name>List</name>
      <anchorfile>classGasket.html</anchorfile>
      <anchor>f47356230807f00e9ae520f107bb5974</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>rad</name>
      <anchorfile>classGasket.html</anchorfile>
      <anchor>d63c710092bb2a22974fb8103a2198d0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>VecMath::Vector&lt; 4 &gt;</type>
      <name>center</name>
      <anchorfile>classGasket.html</anchorfile>
      <anchor>5c02d5d0075c6b4fbff9d7f636e7f249</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Global</name>
    <filename>classGlobal.html</filename>
    <member kind="function">
      <type>QAction *</type>
      <name>getQuitAction</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>c05adbe8fdcd63247b2022a848312146</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>QMainWindow *</type>
      <name>getMainWindow</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>68e498c6d171a579289613b5d780db1f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>GetGLList</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>1ee9e9244bd1fe16b13f252ecc952872</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setColor</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>fc415ad35cd5f1150223adc110af2abb</anchor>
      <arglist>(const Color &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setColor</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>cd24574b306c815486b2b41bd5c58f91</anchor>
      <arglist>(float r, float g, float b, float a=1.0)</arglist>
    </member>
    <member kind="function">
      <type>Color &amp;</type>
      <name>BackgroundColor</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>d2cda1b62aafc1e37319de079b51db1f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setBackground</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>d51a21fbe6a770154d8a16d0e5a06072</anchor>
      <arglist>(const Color &amp;rgba)</arglist>
    </member>
    <member kind="function">
      <type>Color &amp;</type>
      <name>FogColor</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>de13b8a6c462f1d8f0180bbaa4960008</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFogColor</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>1ae62128f23c890ebca8d6d0f7075f5c</anchor>
      <arglist>(const Color &amp;rgba)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>atod</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>46d4d63fb67924db3e1bcf093a917a3f</anchor>
      <arglist>(QString)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>itoa</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>41cee4049871dc14b3f7101e40734c16</anchor>
      <arglist>(int x)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>ftoa</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>2854bac3d8ea35166049a1a07028ed43</anchor>
      <arglist>(double x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>CheckGLErrors</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>28cb8515629b9395ed5e2c00a8c1be7b</anchor>
      <arglist>(const char *op=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>glVertex</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>897ad69b2f273e4379c4dba53983ef25</anchor>
      <arglist>(VecMath::Vector&lt; 3 &gt; &amp;V)</arglist>
    </member>
    <member kind="function">
      <type>VecMath::Vector&lt; 3 &gt;</type>
      <name>vnormalize</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>3787cef8ea672abfa0f8beaf3738c698</anchor>
      <arglist>(double xx, double yy, double zz)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static unsigned long</type>
      <name>getMaxMemory</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>028fc2484b8b9ccb9cf857a77076b637</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Color &amp;</type>
      <name>white</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>c512ceb809cd9a6b401900318d4bbc62</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static Color &amp;</type>
      <name>grey50</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>2d8afc1687681fc168bb468000fb9326</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>QStringList</type>
      <name>rcdirs</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>bcddc926a59c03ecfcca578f5829be8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const double</type>
      <name>SR3</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>db311d7f438bfa1f40f030b56e813578</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static bool</type>
      <name>check_memory</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>53d14f4c4fa1472251cb87181a021291</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static unsigned long</type>
      <name>check_proc_meminfo</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>ee41dfa8c3f54721609d57c58ae702d8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const double</type>
      <name>ambientColorModifier</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>d4539a71509e1ef13b4f46a55012e27f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const double</type>
      <name>specularColorModifier</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>a95e8a76247e0677dda04db724c1e322</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const double</type>
      <name>specularColorMinimum</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>79e85452303b5f18b408fe0467bf25ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const double</type>
      <name>ALPHA</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>a8a55e4a11eb8df8f7b3ec312626b48d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const double</type>
      <name>SHININESS</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>1f0c53a55b080e48ea48f1b405d09790</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMainWindow *</type>
      <name>mainWindow</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>80cba6b0d930d4f38f01be9a03012b3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QAction *</type>
      <name>quitAction</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>85c2751599c677efee668f61fc86e09d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static Color</type>
      <name>background</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>2f8f0a44741d3e331a41f0cb7cef5782</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static Color</type>
      <name>fog_color</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>8a4a15ef7b6327aaafec97ba55635e74</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static Color</type>
      <name>White</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>c057e73b4628f9010a2580ccf21244d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static Color</type>
      <name>Grey50</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>ca5d167ac2b151c95be44e3e07bd8c58</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static unsigned long</type>
      <name>MaximumMemory</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>9ce07a3f47f79473e32f67eca456f79b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GLObject</name>
    <filename>classGLObject.html</filename>
    <member kind="function">
      <type></type>
      <name>GLObject</name>
      <anchorfile>classGLObject.html</anchorfile>
      <anchor>8b1b7ee78b7d0ea198a53ed044b3c4c4</anchor>
      <arglist>(GLuint objlist=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>GLObject</name>
      <anchorfile>classGLObject.html</anchorfile>
      <anchor>157fbefc3010f38d4bc22b5a41ca2298</anchor>
      <arglist>(unsigned elements, GLuint objlist,...)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned</type>
      <name>Draw</name>
      <anchorfile>classGLObject.html</anchorfile>
      <anchor>f5ff7b7c9928a618f1ada4c597054764</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>classGLObject.html</anchorfile>
      <anchor>98fdb66cc6be8438515db60d51a77b53</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; GLuint &gt;</type>
      <name>List</name>
      <anchorfile>classGLObject.html</anchorfile>
      <anchor>a142f6b830b6df84750d7d9cdfec29b3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GravitationPotential</name>
    <filename>classGravitationPotential.html</filename>
    <base>RealFunction</base>
    <member kind="function">
      <type></type>
      <name>GravitationPotential</name>
      <anchorfile>classGravitationPotential.html</anchorfile>
      <anchor>1087fe7d0272f927001e19fba7636f06</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, double _M=1, double _R=0.25)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classGravitationPotential.html</anchorfile>
      <anchor>3316dc8a0507e88642ad113d7941b6f4</anchor>
      <arglist>(double _a=0, double _b=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classGravitationPotential.html</anchorfile>
      <anchor>51bd59d7e700290c8b366f5b5f9abb20</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>M</name>
      <anchorfile>classGravitationPotential.html</anchorfile>
      <anchor>40e2a829e43c48b1b910b8fa68626c09</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>R</name>
      <anchorfile>classGravitationPotential.html</anchorfile>
      <anchor>de477d7a596d6b7e6786430c9392c39d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>HelpWindow</name>
    <filename>classHelpWindow.html</filename>
    <member kind="function">
      <type></type>
      <name>HelpWindow</name>
      <anchorfile>classHelpWindow.html</anchorfile>
      <anchor>d29d3d424ef273e7466711b490468621</anchor>
      <arglist>(const QString &amp;home_, const QString &amp;path=&quot;&quot;, QWidget *parent=0)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QTextBrowser *</type>
      <name>browser</name>
      <anchorfile>classHelpWindow.html</anchorfile>
      <anchor>4c1d4af3f94fc4770fc47464dce1c360</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Horizon</name>
    <filename>classHorizon.html</filename>
    <base>Surface</base>
    <member kind="function">
      <type></type>
      <name>Horizon</name>
      <anchorfile>classHorizon.html</anchorfile>
      <anchor>87fb6007c4b29aecdd664efa56ae9647</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classHorizon.html</anchorfile>
      <anchor>0c491c1d64aea3eb792222bdb77fa152</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classHorizon.html</anchorfile>
      <anchor>579fa87ed4a96626c0a68238aa23e081</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Hypercube</name>
    <filename>classHypercube.html</filename>
    <base>Object</base>
    <member kind="function">
      <type></type>
      <name>Hypercube</name>
      <anchorfile>classHypercube.html</anchorfile>
      <anchor>36892251a5c462aa676217f162b65ffd</anchor>
      <arglist>(double _a, const VecMath::Vector&lt; 4 &gt; &amp;_Center=VecMath::Vector&lt; 4 &gt;(0., 0., 0., 0.))</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classHypercube.html</anchorfile>
      <anchor>290688b04edc2e4f651cd9ca4da861b6</anchor>
      <arglist>(double _a=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>description</name>
      <anchorfile>classHypercube.html</anchorfile>
      <anchor>e078bd2bfb18a8aa22f166cafce4a421</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>Initialize</name>
      <anchorfile>classHypercube.html</anchorfile>
      <anchor>790d87e55f2b01d1b339df6f05852ffd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>DeclareSquare</name>
      <anchorfile>classHypercube.html</anchorfile>
      <anchor>0c9fb7fe129ae7e5e2834fd0ea861e8d</anchor>
      <arglist>(unsigned, unsigned, unsigned, unsigned, unsigned)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>a</name>
      <anchorfile>classHypercube.html</anchorfile>
      <anchor>732e1022d95319bb996c87b2913f8c08</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>VecMath::Vector&lt; 4 &gt;</type>
      <name>center</name>
      <anchorfile>classHypercube.html</anchorfile>
      <anchor>3615b176fba06ffbbf9ef8dd0b8c04c5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Hypersphere</name>
    <filename>classHypersphere.html</filename>
    <base>RealFunction</base>
    <member kind="function">
      <type></type>
      <name>Hypersphere</name>
      <anchorfile>classHypersphere.html</anchorfile>
      <anchor>d03be78c012ccd6339a0d37633522635</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, double _rad=1)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classHypersphere.html</anchorfile>
      <anchor>8eeb401282ab3269d40537b68cb2b3d3</anchor>
      <arglist>(double _a=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classHypersphere.html</anchorfile>
      <anchor>8b641f61bdb8dff6d4d99e5eb40ea70b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>normal</name>
      <anchorfile>classHypersphere.html</anchorfile>
      <anchor>9bf34a96391538b27d1c693a4c455e39</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Radius</name>
      <anchorfile>classHypersphere.html</anchorfile>
      <anchor>05716ee24d8d877c9c93783038e7e21d</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>lnz</name>
    <filename>classlnz.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>lnz</name>
      <anchorfile>classlnz.html</anchorfile>
      <anchor>9c702619b9141f558e89172afcef3af3</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classlnz.html</anchorfile>
      <anchor>a57a9788bb8dad639fbcae4ebdb1bde7</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classlnz.html</anchorfile>
      <anchor>cbfd3ae9c24d00d9f832c6b5c47e6d6e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Log</name>
    <filename>classLog.html</filename>
    <member kind="function">
      <type>void</type>
      <name>log</name>
      <anchorfile>classLog.html</anchorfile>
      <anchor>f966932995045e1463770d3523c953ee</anchor>
      <arglist>(std::string)</arglist>
    </member>
    <member kind="function">
      <type>Log &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classLog.html</anchorfile>
      <anchor>4ad2a2bb579c6547bbf929175c83370a</anchor>
      <arglist>(const std::string &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Log &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classLog.html</anchorfile>
      <anchor>759be4a65a5f0e4bb4a8f87572719626</anchor>
      <arglist>(long x)</arglist>
    </member>
    <member kind="function">
      <type>Log &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classLog.html</anchorfile>
      <anchor>b6b9880bbdfcb0524d15bd80ac86e70b</anchor>
      <arglist>(unsigned long x)</arglist>
    </member>
    <member kind="function">
      <type>Log &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classLog.html</anchorfile>
      <anchor>62f89b754758fd5abab1a0c5aba8d4e0</anchor>
      <arglist>(double x)</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>Log</name>
      <anchorfile>classLog.html</anchorfile>
      <anchor>f6071a60aa52b6c1b511f99b4bc1b8fe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>Log</name>
      <anchorfile>classLog.html</anchorfile>
      <anchor>60fc11c5c263c4bfad3f9561a4881a13</anchor>
      <arglist>(const Log &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>Log &amp;</type>
      <name>operator=</name>
      <anchorfile>classLog.html</anchorfile>
      <anchor>692828ab7538c3ac8219d1ce3f904ca6</anchor>
      <arglist>(const Log &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>~Log</name>
      <anchorfile>classLog.html</anchorfile>
      <anchor>0fbfda88fbee5027c89f6eb121059360</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="friend">
      <type>friend class</type>
      <name>Loki::CreateUsingNew&lt; Log &gt;</name>
      <anchorfile>classLog.html</anchorfile>
      <anchor>88787a52fc4a5f408f5ee37c8abc4a7e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>LSystem</name>
    <filename>classLSystem.html</filename>
    <member kind="function">
      <type></type>
      <name>LSystem</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>5e9506c4c5b6a661a45e5e0ab5ae7abd</anchor>
      <arglist>(unsigned=2)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>LSystem</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>752e2f2cc7821661d7f01b984eb17629</anchor>
      <arglist>(string, map&lt; string, string &gt;, unsigned=2)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>level</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>d31901fbaadda93ba54b6616501024e4</anchor>
      <arglist>(unsigned n)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>level</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>eba71210aa4455cd0658453b49a19120</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>axiom</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>68cb58ba0e7e74a60dd7d9db75baaea1</anchor>
      <arglist>(string a)</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>axiom</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>afe2941e51024f24df00c6fdfbd79b40</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>set_rule</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>a4d26823f3029d8a6feeb3d5a0793735</anchor>
      <arglist>(string key, string rule)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>rules</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>d0914b4eb626d193b118179e2cd93f93</anchor>
      <arglist>(map&lt; string, string &gt; rules)</arglist>
    </member>
    <member kind="function">
      <type>map&lt; string, string &gt;</type>
      <name>rules</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>14cee192160e045064a85145a3dec298</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>angle</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>74930bf8dcedafd8150f604c82723c76</anchor>
      <arglist>(double angle)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>angle</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>84ba9c3e789b4059fb7f5eb20e5bae44</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>8f3fdd2089827f45f12633dc7fcb336c</anchor>
      <arglist>(string key, string object)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>object</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>5193766b33c3896fc864b79722d01d55</anchor>
      <arglist>(map&lt; string, string &gt; object)</arglist>
    </member>
    <member kind="function">
      <type>map&lt; string, string &gt;</type>
      <name>object</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>709769d2bf43c08a58d156563ff3df9f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>string</type>
      <name>object</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>58f544fc6e925abda7cae01903186d95</anchor>
      <arglist>(string key)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual string</type>
      <name>Expand</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>2b1f8ad1a06677a5a32119a437746eb5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual string</type>
      <name>POV_Source</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>3f7800a7435085b89d1715ad73d025a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Draw</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>5e32baa8c46e3b35c1eca57d15f1a8ae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>string</type>
      <name>POV_Header</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>7711fc15f6dc35bdcb69ff11e177fe37</anchor>
      <arglist>(const string &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>string</type>
      <name>POV_Footer</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>c9b5f9ca84de775ca02251cce44108de</anchor>
      <arglist>(const Vector &amp;, const Vector &amp;)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual string</type>
      <name>POV_Atom</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>a572e29ca30f92a91652b1947717bd14</anchor>
      <arglist>(const string &amp;, const string &amp;)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual string</type>
      <name>Expand</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>2f394b1c71d1964f43945d00929d983b</anchor>
      <arglist>(string, unsigned)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>string</type>
      <name>m_axiom</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>8b8778d9be5a920e7028ad3c12e6dc9c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>map&lt; string, string &gt;</type>
      <name>m_rules</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>b1fc7b2fcb91725ea9f0e2892ba5f1ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>m_level</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>8f58d68ec8058a4ac0225ac25ae9d2e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>m_scale</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>2f9bf40ac831c28a30911a2847c4d505</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>m_angle</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>7de31319414e8c9356d980b1303b7c50</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>map&lt; string, string &gt;</type>
      <name>m_object</name>
      <anchorfile>classLSystem.html</anchorfile>
      <anchor>0e614253fe936672a956289b3f5101be</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Menu4D</name>
    <filename>classMenu4D.html</filename>
    <member kind="typedef">
      <type>std::map&lt; QString, QAction * &gt;</type>
      <name>ActionMapType</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>9d77617fa92b20610b2c7af71ce9c307</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::map&lt; QMenu *, ActionMapType &gt;</type>
      <name>MenuMapType</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>16034ce8d7c8bb3433b6fb5830261a9f</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Menu4D</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>88472d5698340a5090f39f4467edf2cf</anchor>
      <arglist>(C4DView *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>updateFunctionMenu</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>aa3fef467995d3701b1aa54e50dd1e39</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="function">
      <type>QAction *&amp;</type>
      <name>getAction</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>7792476cf4ac47f81252d69cbf7ca52c</anchor>
      <arglist>(const QString &amp;key)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addToMenuBar</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>e01f65904e1cb5810ae760cb99565dda</anchor>
      <arglist>(QMenuBar *menuBar)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QAction *</type>
      <name>insertAction</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>722cc6d2d4fca574510d5b6f5b7b6449</anchor>
      <arglist>(QMenu *, const QString &amp;, const char *, bool=true)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QAction *</type>
      <name>insertAction</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>2841caf1740ea9885f9e6376e099eddd</anchor>
      <arglist>(QMenu *, const QString &amp;, RealFunctionFactory *, bool=true)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QAction *</type>
      <name>insertAction</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>20552c6d6735d3cf30fb577b424618c7</anchor>
      <arglist>(QMenu *, const QString &amp;, SurfaceFactory *, bool=true)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QAction *</type>
      <name>insertAction</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>72069f68676ba2bb0cbe3379342d259d</anchor>
      <arglist>(QMenu *_menu, const Function *function, const char *slot, bool checkable=true)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>C4DView *</type>
      <name>parent</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>3dbb3295e8653ea4836f7a6e003f2f7b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>functions</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>3bd1be593925c5b107bd690c002194e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>appear</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>ba12a7b1e1ee68cc3d4a274e1b70e2a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>animation</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>cf9c72674031073314bbe07db0541ad5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>help</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>cabcba935440b751f5fcf38bc3e093f3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>fr3r</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>37866501a2d40412d9173bd4817d952a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>objects</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>27445c54b995f2e17be6ca7e61c5fc5a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>surfaces</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>eb2e62145fcf5c64211360b3d7cc67ad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>fcc</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>dcfef3e466a387a964b6bb361b0187e1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>MenuMapType</type>
      <name>menuMap</name>
      <anchorfile>classMenu4D.html</anchorfile>
      <anchor>0f1ae22ea522ece59d48ec5bcda0ba96</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Object</name>
    <filename>classObject.html</filename>
    <base>Function</base>
    <member kind="typedef">
      <type>std::vector&lt; unsigned &gt;</type>
      <name>uintvec1D</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>6b75a43f15ef4d901ad0c6820bb8b3e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>std::vector&lt; uintvec1D &gt;</type>
      <name>uintvec2D</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>ee0fb4b1bde4a789bbe7382cbb82a9cb</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Object</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>88590464e2e1cb975f59ddb47f4f09b7</anchor>
      <arglist>(const QString &amp;, unsigned, unsigned)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ReInit</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>cb280cacb700070c0cccd0bf35225102</anchor>
      <arglist>(double, double, double, double, double, double, double, double, double)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Transform</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>325a0b66e653f67de1d26c35022cdaa5</anchor>
      <arglist>(double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw, double Tx, double Ty, double Tz, double Tw)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Project</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>8404a4e0b7cddabbb14797c755c3daa8</anchor>
      <arglist>(double ScrW, double CamW, bool DepthCue4D)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Draw</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>3afa1b9af32b78d81b5de0836c511aeb</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>operator()</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>3dfa9443e4d4b71f1a12827bab2d90f5</anchor>
      <arglist>(double, double, double)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>f</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>c78eebfcc84080ef2e811e9da0c3621e</anchor>
      <arglist>(double, double, double)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>NumVertices</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>89cc867189fc1262c9b696f9b489ea18</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>NumSurfaces</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>48f7312dce9f320206095c17eb235bd9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vec4vec1D</type>
      <name>X</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>97547b332fe3f47276e035dc770600df</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vec4vec1D</type>
      <name>Xtrans</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>ef07f5a71e1d1bb0cd05b0386f438d6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vec3vec1D</type>
      <name>Xscr</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>c6f586998024548c7ac2cfdb5c2e4921</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>floatvec1D</type>
      <name>R</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>61ff801a10427bf1b8a8fb5ec9f9937d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>floatvec1D</type>
      <name>G</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>770462e34d7856993a31aca7bcc71f94</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>floatvec1D</type>
      <name>B</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>3a5f711ad4ef87bb9a2c2c78199899d6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>uintvec2D</type>
      <name>Surface</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>febafa6727a1d46aaf384fba88f31c1a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PluginCreator</name>
    <filename>classPluginCreator.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~PluginCreator</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>2b7db1dca02da60b9e8fa6b26042fb02</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>libraryName</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>4b0c4aa6bb17649c888f720f96741c6d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>loadFunction</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>934c4708ba3cf6054982d9b0b67e29d2</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual bool</type>
      <name>functionPresent</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>72d965933b305fe25e9e27b9ab88fbb6</anchor>
      <arglist>(const QString &amp;)=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>writeSource</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>a951c5e85ecfdc22750cb5485c9d5b9e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>loadFunction</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>d03c07d5b51939b87483122fbb2edbcf</anchor>
      <arglist>(const QString &amp;, QDialog *)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>checkValidity</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>ffb2921b42c0adceb0611b594d9c692b</anchor>
      <arglist>(const QString &amp;, const QString &amp;, QDialog *)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>compile</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>1c6920f6a1d27a1473fcabc18195eb5b</anchor>
      <arglist>(QString)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>bool</type>
      <name>link</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>9f7766eedfa75857a52c2f07d6831bad</anchor>
      <arglist>(QString)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QString</type>
      <name>LibraryName</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>6084c2eae2022898d503bae9cac97617</anchor>
      <arglist></arglist>
    </member>
    <class kind="class">PluginCreator::LoadFunctionHelper</class>
  </compound>
  <compound kind="class">
    <name>PluginCreator::LoadFunctionHelper</name>
    <filename>classPluginCreator_1_1LoadFunctionHelper.html</filename>
    <templarg>F</templarg>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>functionPresent</name>
      <anchorfile>classPluginCreator_1_1LoadFunctionHelper.html</anchorfile>
      <anchor>daa553cc712de9359f011e289acbc299</anchor>
      <arglist>(const QString &amp;, QDialog *)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Polar</name>
    <filename>classPolar.html</filename>
    <base>RealFunction</base>
    <member kind="function">
      <type></type>
      <name>Polar</name>
      <anchorfile>classPolar.html</anchorfile>
      <anchor>1915fdb6145030005485f323bbf111fb</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classPolar.html</anchorfile>
      <anchor>3166e315e6b0e4b706a8a0fe87d2157c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PolarDialogImpl</name>
    <filename>classPolarDialogImpl.html</filename>
    <base>PluginCreator</base>
    <member kind="slot" virtualness="virtual">
      <type>virtual bool</type>
      <name>checkValidity</name>
      <anchorfile>classPolarDialogImpl.html</anchorfile>
      <anchor>cf9f33255a1bd65a1b70475d5fc4f1a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual bool</type>
      <name>loadFunction</name>
      <anchorfile>classPolarDialogImpl.html</anchorfile>
      <anchor>e3a5c9fcd53a63338439b8ffbca02673</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>PolarDialogImpl</name>
      <anchorfile>classPolarDialogImpl.html</anchorfile>
      <anchor>32ef3773ec9a225a0d8760b187d65788</anchor>
      <arglist>(QWidget *parent=0, Qt::WFlags f=0)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>functionPresent</name>
      <anchorfile>classPolarDialogImpl.html</anchorfile>
      <anchor>6c55103e9be8f4068223c07934bcdcc0</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>writeSource</name>
      <anchorfile>classPolarDialogImpl.html</anchorfile>
      <anchor>d4bf86e4ca4285e16dc37d95252315f6</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PolarR</name>
    <filename>classPolarR.html</filename>
    <base>RealFunction</base>
    <member kind="function">
      <type></type>
      <name>PolarR</name>
      <anchorfile>classPolarR.html</anchorfile>
      <anchor>2a3c7f1387bcb12cbd110aba70531209</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, double _phase=2)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classPolarR.html</anchorfile>
      <anchor>6a1d202b518c5698b76a7f66cab741c6</anchor>
      <arglist>(double _a=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classPolarR.html</anchorfile>
      <anchor>459afefce858d473e97188ffbd68d4ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Phase</name>
      <anchorfile>classPolarR.html</anchorfile>
      <anchor>51df4cea866fc51a0d5a6301ace1cb36</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PolarSin</name>
    <filename>classPolarSin.html</filename>
    <base>RealFunction</base>
    <member kind="function">
      <type></type>
      <name>PolarSin</name>
      <anchorfile>classPolarSin.html</anchorfile>
      <anchor>740d752f6b10f835495760fdf62aa930</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, double _phase=2)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classPolarSin.html</anchorfile>
      <anchor>3f4c61294de768ab57351a62a3096f09</anchor>
      <arglist>(double _a=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classPolarSin.html</anchorfile>
      <anchor>a251c15750227005569e44a4ba26fce8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>Phase</name>
      <anchorfile>classPolarSin.html</anchorfile>
      <anchor>555d7c189e46b68d0d42648ff9462b36</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>PolarSin2</name>
    <filename>classPolarSin2.html</filename>
    <base>RealFunction</base>
    <member kind="function">
      <type></type>
      <name>PolarSin2</name>
      <anchorfile>classPolarSin2.html</anchorfile>
      <anchor>5595a98e7c1b2862702760b284998c95</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classPolarSin2.html</anchorfile>
      <anchor>e02ab268122d4685189e9d0e640c093b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Polynomial</name>
    <filename>classPolynomial.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>Polynomial</name>
      <anchorfile>classPolynomial.html</anchorfile>
      <anchor>5d2e89aac78d8d59d93abbc42d65fc0f</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, double _a1, double _a2, double _a3, double _a4)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classPolynomial.html</anchorfile>
      <anchor>43641b71a87fc4335feae113271358e5</anchor>
      <arglist>(double _a=0, double _b=0, double _c=0, double _d=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classPolynomial.html</anchorfile>
      <anchor>d77ec1bc3e000fc8d3443f5513f58c6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>a</name>
      <anchorfile>classPolynomial.html</anchorfile>
      <anchor>742c72cf37506507b1c2fa6d997bf509</anchor>
      <arglist>[5]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Pyramid</name>
    <filename>classPyramid.html</filename>
    <base>Object</base>
    <member kind="function">
      <type></type>
      <name>Pyramid</name>
      <anchorfile>classPyramid.html</anchorfile>
      <anchor>cddc2af9239e33dc248a3ebcb8c7bfd5</anchor>
      <arglist>(double _a, const VecMath::Vector&lt; 4 &gt; &amp;_Center=VecMath::Vector&lt; 4 &gt;(0., 0., 0., 0.))</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classPyramid.html</anchorfile>
      <anchor>c5b649d5cb7fd2637751385ba3d63af0</anchor>
      <arglist>(double _a=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>Initialize</name>
      <anchorfile>classPyramid.html</anchorfile>
      <anchor>dc837fa34b2f484a0c28da7210677db9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>DeclareTriangle</name>
      <anchorfile>classPyramid.html</anchorfile>
      <anchor>9867ed04145e00009d85352f1b15727a</anchor>
      <arglist>(unsigned, unsigned, unsigned, unsigned)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>VecMath::Vector&lt; 4 &gt;</type>
      <name>center</name>
      <anchorfile>classPyramid.html</anchorfile>
      <anchor>e70d929b9b9e9eaac5a1ed6cb8e22578</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>a</name>
      <anchorfile>classPyramid.html</anchorfile>
      <anchor>6f9e737d979568956e870d7d7605fb97</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealBase</name>
    <filename>classRealBase.html</filename>
    <base>Function</base>
    <member kind="function">
      <type>typedef VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>function_type</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>e33f099d1ff8b841d0f3961bbdd74618</anchor>
      <arglist>(double, double, double)</arglist>
    </member>
    <member kind="function">
      <type>typedef VecMath::Vector&lt; 4 &gt;</type>
      <name>raw_function_type</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>5b57016405717bea79950aee2dc02255</anchor>
      <arglist>(double, double, double)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RealBase</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>53b370431bb413146c845c2269a2a73c</anchor>
      <arglist>(const QString &amp;name, double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>f</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>c2cd018b4108455a6daa23d78b2064a6</anchor>
      <arglist>(double, double, double)=0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>operator()</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>8f529fd1c84d703a9ca7e8d43a16a5fd</anchor>
      <arglist>(double t, double u, double v)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealFunction</name>
    <filename>classRealFunction.html</filename>
    <base>RealBase</base>
    <member kind="function">
      <type></type>
      <name>RealFunction</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>198dec897172567a0fb6c110a2afbe22</anchor>
      <arglist>(const QString &amp;name, double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Transform</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>ab400a3b8c445044007307fa295f1c89</anchor>
      <arglist>(double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw, double Tx, double Ty, double Tz, double Tw)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Project</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>184141451489cdd8373a47acc9ec673e</anchor>
      <arglist>(double ScrW, double CamW, bool DepthCue4D)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Draw</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>640817dd87a840f3698e4a931f0e7fc8</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ReInit</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>cd8338dd5e99de2034682e7b7891219d</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>normal</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>fc801388deaab9bb3783ae470891a2d8</anchor>
      <arglist>(double t, double u, double v)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>DrawPlane</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>45794e4c47942b87f76535062cc23423</anchor>
      <arglist>(unsigned)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>DrawStrip</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>dbafbb0c90473d0b4c3dbc5c3dfdd75a</anchor>
      <arglist>(unsigned, unsigned)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>DrawCube</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>891f30e71e090f4c8cfb0362d1c40cd3</anchor>
      <arglist>(unsigned, unsigned, unsigned)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>Initialize</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>37c91ed60f82198f48dfab887dd743c3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>InitMem</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>1905c4297b0f6b4f91a3b24b55b62eea</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vec4vec3D</type>
      <name>X</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>950ebb62a55990cd42ce6ee48aaa9810</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vec4vec3D</type>
      <name>Xtrans</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>ed466bcba4e1959d68c4932513612e19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vec3vec3D</type>
      <name>Xscr</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>2b4805a60e748aee992f62ac7c9bd4df</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>floatvec3D</type>
      <name>R</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>cde2075b97cf67ceeefcfa3148bc707e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>floatvec3D</type>
      <name>G</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>99af055c93f9e7563adfa625fd667724</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>floatvec3D</type>
      <name>B</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>fadc909693e918fe4453cfebbcb638a6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealFunctionFactory</name>
    <filename>classRealFunctionFactory.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual RealFunction *</type>
      <name>createFunction</name>
      <anchorfile>classRealFunctionFactory.html</anchorfile>
      <anchor>75d8ebcb47210fd0ca8a472955e8405b</anchor>
      <arglist>(C4DView *)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sinhz</name>
    <filename>classsinhz.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>sinhz</name>
      <anchorfile>classsinhz.html</anchorfile>
      <anchor>eb81cbd41b41768558e63b9bba02b559</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classsinhz.html</anchorfile>
      <anchor>23f8dfe02e6123b17b059da2b9606a1f</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classsinhz.html</anchorfile>
      <anchor>998410f8948ed3f9bb21bab2626da913</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sinz</name>
    <filename>classsinz.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>sinz</name>
      <anchorfile>classsinz.html</anchorfile>
      <anchor>106c003cf91f0aae52e54ea050aa85ac</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classsinz.html</anchorfile>
      <anchor>78d0f7de6ddae7080ef0e01917e336a7</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classsinz.html</anchorfile>
      <anchor>fb261d6d8d9c9b5a910b7e896be312b3</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Sponge</name>
    <filename>classSponge.html</filename>
    <base>Hypercube</base>
    <member kind="function">
      <type></type>
      <name>Sponge</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>0d524e4eea3e514891726a0e46784f32</anchor>
      <arglist>(unsigned _level=1, int _distance=1, double _rad=1, VecMath::Vector&lt; 4 &gt; _center=VecMath::Vector&lt; 4 &gt;(0., 0., 0., 0.))</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>~Sponge</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>7f86fac04936c5486a16a187f32e0e5b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Transform</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>00961c9a2034c8edac7697568e2f6cc8</anchor>
      <arglist>(double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw, double Tx, double Ty, double Tz, double Tw)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Project</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>ee14d45eb035e31bf23efe2c45245e6a</anchor>
      <arglist>(double ScrW, double CamW, bool DepthCue4D)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Draw</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>673da787a17189eafade24bf21e82f70</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>36471176a1ee0aef443094278469f6a6</anchor>
      <arglist>(double _a=0, double _b=0, double _c=0, double=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ReInit</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>e4ee07a364e503076552de10d5006260</anchor>
      <arglist>(double, double, double, double, double, double, double, double, double)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>description</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>7821a0eec75f0d4c75c6e9c1a4ea0d5c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>Initialize</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>b552ce65169a2b44bc93e86dbba76a25</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual unsigned long</type>
      <name>MemRequired</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>31290427d5599a4ea65e24b23427eeef</anchor>
      <arglist>(unsigned)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>Level</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>9bbf04ed220e35a64d987d972c9baf07</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>std::vector&lt; Hypercube * &gt;</type>
      <name>List</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>599e21656433097f9e7f2ac143a1dc7a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>distance</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>5b0880e7ae3dfa67598961e9e4cc075d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>rad</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>309b53bbc078d739edd0eb31e127b1fa</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>VecMath::Vector&lt; 4 &gt;</type>
      <name>center</name>
      <anchorfile>classSponge.html</anchorfile>
      <anchor>5a57edfbaa6e238e19e16b4e88c10dee</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>sqrtz</name>
    <filename>classsqrtz.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>sqrtz</name>
      <anchorfile>classsqrtz.html</anchorfile>
      <anchor>e5f774457375311636cf8790720312b8</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classsqrtz.html</anchorfile>
      <anchor>9269ac280bb7a05fdb62f4f266ccb21f</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classsqrtz.html</anchorfile>
      <anchor>21554d23ad7feca1dc057c1ce37b49ac</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SteinerFunction</name>
    <filename>classSteinerFunction.html</filename>
    <base>Function</base>
    <member kind="function">
      <type></type>
      <name>SteinerFunction</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>f75c1e1d04c4f1de11270e76989bd5e0</anchor>
      <arglist>(double _umin, double _umax, double _ustep, double _vmin, double _vmax, double _vstep, double _a=2.)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Draw</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>f8d09643c2cedc9b6bfd308415fdd248</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>Vector &amp;</type>
      <name>f</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>c281ae5f18e2375b792710c3ccda7acc</anchor>
      <arglist>(double, double)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double **</type>
      <name>df</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>347a06fc2f4e0b34f5ced88a0f934b55</anchor>
      <arglist>(double, double)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>a</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>ef043dfe1e1798290f3745ddac512240</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>umin</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>a9926ddc4cde4aecccdc19cfc5801fc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>umax</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>f1e55a6bbdad3b19a981e9f3e8c4772f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>du</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>fbd1a8e0e4376c491c5e811adb4d5a41</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>vmin</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>a05d2007e03fd3669ff1be419ed537bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>vmax</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>c4583620d0b428836d217db5ca0789fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dv</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>89e75493dbbf5d12a6f87afc6263e0b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>Vector</type>
      <name>F</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>4071a5fbd4d419f5f728b050fe9a1a17</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Surface</name>
    <filename>classSurface.html</filename>
    <base>SurfaceBase</base>
    <member kind="function">
      <type></type>
      <name>Surface</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>8fc57f2a15292135c00545c9d224ec68</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Surface</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>14f5dccdc28a9fc9d72fbabc24b42d60</anchor>
      <arglist>(const QString &amp;name, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Transform</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>98f6a79d334e61068031f15ebef90458</anchor>
      <arglist>(double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw, double Tx, double Ty, double Tz, double Tw)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Transform</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>ce4dec89d0480aa9c59b5d0bc578131e</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Project</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>15e6f13147e522e15ddda573201926b1</anchor>
      <arglist>(double ScrW, double CamW, bool DepthCue4D)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Draw</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>926508366b1255fa6ae5cbd5d400174a</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>ReInit</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>a6b958d909ace5cfc2347cb8082d3fdb</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>580a0a8dc84fdc53152e20a41c576735</anchor>
      <arglist>(double _a=0, double _b=0, double _c=0, double _d=0)</arglist>
    </member>
    <member kind="function">
      <type>vec4vec2D</type>
      <name>Data</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>94d03f3097e1478093dd3a286f987562</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual vec4vec1D</type>
      <name>df</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>dc25dc3cc52c171fbd4ef38cb96a516a</anchor>
      <arglist>(double, double)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Initialize</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>e140ab69205e1a6a73459b9e22cda019</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>InitMem</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>f77d456ed7b5d495f4a54978ab5f4acc</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual unsigned long</type>
      <name>MemRequired</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>185472961fe456f587c160c2cc6e8545</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>DrawPlane</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>c892c3621a13bb30418c5b2d73763ea2</anchor>
      <arglist>(unsigned)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>DrawStrip</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>4b6eecac144cb1d0650d711727ecb540</anchor>
      <arglist>(unsigned)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>normal</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>19a24f801227ea542d749f94cb3fa44d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>umin</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>d0c58ea4eaaa5a1b616f7630e10b9b5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>umax</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>e69a5129b7739178c131550ff5738021</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>du</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>c939cc8c38972d3f6310e85bd57970a8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>vmin</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>7caf2e83204ffdec4b01a056c69a9d60</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>vmax</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>c58ed3059e0d9e6bbb8a0665ee57f4a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>dv</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>a3a7fbf7f6f5c16bfe79b08324ea8ada</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>usteps</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>107f2d371027fc0b935086a23bb0f5bf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>vsteps</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>13e7593db4e6be501947add27c679d99</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>unsigned</type>
      <name>NumVertices</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>2cf4c28a257ce73719c4280d4d6bcbf6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>VecMath::Vector&lt; 4 &gt;</type>
      <name>F</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>80d92e7d5fb9aaeff5b557b41b02978f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vec4vec2D</type>
      <name>X</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>d6ea34c0e91689a28144fc4959f3acc1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vec4vec2D</type>
      <name>Xtrans</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>958a812babb443ccda9b2ba1dda19b9a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>vec3vec2D</type>
      <name>Xscr</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>0d4e87cf750c15554d39725baca6896e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>floatvec2D</type>
      <name>R</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>edae59b363aec7bc66a7e4ba1d6b2328</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>floatvec2D</type>
      <name>G</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>a4e58afa2b994b4a48e83b94f3fc7db7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>floatvec2D</type>
      <name>B</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>5820231eed7444889a2f82f6ee4ccc4b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Surface1</name>
    <filename>classSurface1.html</filename>
    <base>Surface</base>
    <member kind="function">
      <type></type>
      <name>Surface1</name>
      <anchorfile>classSurface1.html</anchorfile>
      <anchor>86c0983ef9c5c527244d2bac298c9210</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classSurface1.html</anchorfile>
      <anchor>6eb55c84c5e9bdc7eeaa2b3931254639</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classSurface1.html</anchorfile>
      <anchor>cc2a2a6e0c8a13269315cb2ffac50579</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SurfaceBase</name>
    <filename>classSurfaceBase.html</filename>
    <base>Function</base>
    <member kind="function">
      <type>typedef VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>function_type</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>02cf6fe2a88f04b0a81430b9050622f7</anchor>
      <arglist>(double, double)</arglist>
    </member>
    <member kind="function">
      <type>typedef VecMath::Vector&lt; 4 &gt;</type>
      <name>raw_function_type</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>d2203f76756ba3478e3a73dc215fc06a</anchor>
      <arglist>(double, double)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SurfaceBase</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>e51173a2ee46a56ccbb02bf9a26ff87f</anchor>
      <arglist>(const QString &amp;name, double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>f</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>ba6ce6327e509663e484560f849d03f1</anchor>
      <arglist>(double, double)=0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>operator()</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>279eefbc9e2d3733eeae5dee35a62f0b</anchor>
      <arglist>(double u, double v, double=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SurfaceDialogImpl</name>
    <filename>classSurfaceDialogImpl.html</filename>
    <base>PluginCreator</base>
    <member kind="slot" virtualness="virtual">
      <type>virtual bool</type>
      <name>checkValidity</name>
      <anchorfile>classSurfaceDialogImpl.html</anchorfile>
      <anchor>c550d0adc24a6184822c8f0949f2dde8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual bool</type>
      <name>loadFunction</name>
      <anchorfile>classSurfaceDialogImpl.html</anchorfile>
      <anchor>ad946f3182546f50ee84ae134d1196f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SurfaceDialogImpl</name>
      <anchorfile>classSurfaceDialogImpl.html</anchorfile>
      <anchor>65e1b1a5403b060c4fc10c657643491c</anchor>
      <arglist>(QWidget *parent=0, Qt::WFlags f=0)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual bool</type>
      <name>functionPresent</name>
      <anchorfile>classSurfaceDialogImpl.html</anchorfile>
      <anchor>157da54702f3a3731db11480a83d5b93</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>writeSource</name>
      <anchorfile>classSurfaceDialogImpl.html</anchorfile>
      <anchor>ec4e55afe7dafd34504f91dfd6718814</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SurfaceFactory</name>
    <filename>classSurfaceFactory.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual Surface *</type>
      <name>createSurface</name>
      <anchorfile>classSurfaceFactory.html</anchorfile>
      <anchor>0b854424fb13bc295186e06cd03a1f8f</anchor>
      <arglist>(C4DView *)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SurfaceSlotHelper</name>
    <filename>classSurfaceSlotHelper.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>slot</name>
      <anchorfile>classSurfaceSlotHelper.html</anchorfile>
      <anchor>8713bbb96e6f3d213a0b8f4b99cf6cf5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>SurfaceSlotHelper</name>
      <anchorfile>classSurfaceSlotHelper.html</anchorfile>
      <anchor>9f9f70d53c7ad3abbc86d5120417acb2</anchor>
      <arglist>(C4DView *_view, SurfaceFactory *sf)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~SurfaceSlotHelper</name>
      <anchorfile>classSurfaceSlotHelper.html</anchorfile>
      <anchor>74c11f8948ce53da826ad0a35cbcb9bc</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>C4DView *</type>
      <name>view</name>
      <anchorfile>classSurfaceSlotHelper.html</anchorfile>
      <anchor>173ab760460eac61eb2b6d85aef49bf4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>SurfaceFactory *</type>
      <name>surfaceFactory</name>
      <anchorfile>classSurfaceSlotHelper.html</anchorfile>
      <anchor>91041f0179161a909376440ad38635b9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>tanz</name>
    <filename>classtanz.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>tanz</name>
      <anchorfile>classtanz.html</anchorfile>
      <anchor>6b98b0fc0a80f4bbf6d84fbff92a74fd</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classtanz.html</anchorfile>
      <anchor>3f97b2d036e9fec0bb9aa915f336c6ef</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classtanz.html</anchorfile>
      <anchor>7714095e8de036ba2026c6f520fbb839</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Torus1</name>
    <filename>classTorus1.html</filename>
    <base>RealFunction</base>
    <member kind="function">
      <type></type>
      <name>Torus1</name>
      <anchorfile>classTorus1.html</anchorfile>
      <anchor>35f93c2495b645c03b5eb1133b1eb040</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, double _R=2, double _r=1, double _rho=0.5)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classTorus1.html</anchorfile>
      <anchor>016c592bbb7e0220cb00f1dc2c4a726c</anchor>
      <arglist>(double _a=0, double _b=0, double _c=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classTorus1.html</anchorfile>
      <anchor>5eed4631d608d7892264aab65eed15dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>R</name>
      <anchorfile>classTorus1.html</anchorfile>
      <anchor>d8c010a1e3bcc7b43ca15ddb9deb32ff</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>r</name>
      <anchorfile>classTorus1.html</anchorfile>
      <anchor>b6b7e9f00c1e5a75ece9da15c83ef5c3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>rho</name>
      <anchorfile>classTorus1.html</anchorfile>
      <anchor>5d55d3759dd9c227ecc7b5385ee5410b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Torus2</name>
    <filename>classTorus2.html</filename>
    <base>RealFunction</base>
    <member kind="function">
      <type></type>
      <name>Torus2</name>
      <anchorfile>classTorus2.html</anchorfile>
      <anchor>89902faec35a16ac5bd27e37fd9ca47c</anchor>
      <arglist>(double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, double _R=1, double _r=0.5)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classTorus2.html</anchorfile>
      <anchor>ef07d5df812d4ce4ec7f86555bcf4817</anchor>
      <arglist>(double _a=0, double _b=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classTorus2.html</anchorfile>
      <anchor>3c9380712b296d5605dd88fcc8c9b7bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>R</name>
      <anchorfile>classTorus2.html</anchorfile>
      <anchor>0eecd76d70d73b373d489997a5e39fba</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>r</name>
      <anchorfile>classTorus2.html</anchorfile>
      <anchor>ea0b57ed552559bdf03487bd087c3c11</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Torus3</name>
    <filename>classTorus3.html</filename>
    <base>Surface</base>
    <member kind="function">
      <type></type>
      <name>Torus3</name>
      <anchorfile>classTorus3.html</anchorfile>
      <anchor>4109e686fa418cf2b0831d23bf58fa78</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classTorus3.html</anchorfile>
      <anchor>3973f9361c1de567826e5501ad37ebab</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classTorus3.html</anchorfile>
      <anchor>4b7e1986731243f42ba630be199a3327</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ValuesDialogImpl</name>
    <filename>classValuesDialogImpl.html</filename>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>accept</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>3d7dbd6e96bd194671fd6ff1740a16a9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>DisplayValues</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>813bff12de96b2ffcfd72da1a497acae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>CheckNumeric</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>d1fcea057f865946f480f25df3a0fe3d</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>aText</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>55bfdfcb9ab4eaad8164ba3319424d2c</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>bText</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>5811e7e153c970c9364b2602688e27b8</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>cText</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>79c641944fb103e0bf45fa6d4276a39c</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>dText</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>9c419dfd967d87ccc939eb9f6b079d02</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>ApplyChanges</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>ca584b2129ab9a092f92d43648bea46b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ValuesDialogImpl</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>da76fef88c056d9145243be54f61a53a</anchor>
      <arglist>(QWidget *parent=0, Qt::WFlags f=0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>tmin</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>cf44326524cdb808f3b83f3d6ccd6ce3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>tmax</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>9deedc0fea0cc09bbe3e261917e23bac</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>tsteps</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>ff5cf3e627d9325f3bfc55222b8dca18</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>dt</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>39541b9109d58b7c3cf6975e881fac59</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>umin</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>c70c7cd9e4ad3296163740fd9808b01f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>umax</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>6b9f29acb0cacffc9eb66d9abb40fc01</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>usteps</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>2ca21cd2065d4d160fe67484162e27fe</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>du</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>ecdf74cad782692b3d25c3e46061b04e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>vmin</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>7024993179ff61a802ac315e8ef54358</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>vmax</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>5c31b70b5b42c1199305c30955f70eed</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>vsteps</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>051de95fdff4fb77ef19cf71e39487af</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>dv</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>331647a85da7776a9d850a6b656b5419</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>a</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>ab1a0c657bdccc10a0b7b47afe655d2b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>b</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>fa0af8f6641a8e853148ec6500213372</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>c</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>8c737755a4710cea2f63643ec49d1443</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>d</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>e2188628d68fa2e33eb32aae5f41e859</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>Function</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>e66d0eedcd271ecabc6b1f42cca91471</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>FunctionName</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>6397f0835fee52c667e9ee8e0604ad8a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFunction</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>4421918403808ad24e1e2dba0698cca0</anchor>
      <arglist>(const QString &amp;f)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>InsertFunction</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>67a38cbc0b628577a8d9ee08c5c077c4</anchor>
      <arglist>(const QString &amp;FuncName, int index=-1)</arglist>
    </member>
    <member kind="slot" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>AlignValues</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>677dc70ed3fc8b4709fd4667656d7ffc</anchor>
      <arglist>(int)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>XQGLWidget</name>
    <filename>classXQGLWidget.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>ViewPos</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>29ceaff4a9ff944d7fa1c3497809dd82</anchor>
      <arglist>(double, double, double)</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>ViewPos</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>be130b7049320b1633bda409b9db9d64</anchor>
      <arglist>(double)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>XQGLWidget</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>85f432f8fe5454ab47b7c1fda0039323</anchor>
      <arglist>(QWidget *=0)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetDrawObject</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>5e63c325977c7f2af7edb7fbb00060f0</anchor>
      <arglist>(GLObject *obj)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>SetDrawObject</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>4452667e1e8cc368816bfbddcbee5c36</anchor>
      <arglist>(GLuint list)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBackgroundColor</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>33a2e41222b9255e2b13cc64d0f34f9f</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;RGBA)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetBackgroundColor</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>c0b6d0e8d75a9038c59f83db71be9921</anchor>
      <arglist>(float R, float G, float B, float A)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>Rotate</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>d24cd45a87ed97e8842c84d7ff67a4f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>Help</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>b2326fa68fe06bb430ed7ce747d2e046</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>SetAlpha</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>1ce4e8bb8be33cec6b537f22383dc7cb</anchor>
      <arglist>(int)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>Left</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>fec2ac2281d670b359fb9477427709a3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>Right</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>0f547eeeeb537d450ad98ef997a3c8a2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>Up</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>5fe1a661d1487779dedcb81c8df20566</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>Down</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>2a468256f058a20bd1a38175ee07c9c6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>SLeft</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>edec7e3837fad859c9fedb47612c95f6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>SRight</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>365d407818722fc180f415deb6706acd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>SUp</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>8aedcf9f26e9490e5b43a05316da141a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>SDown</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>5f805b208465835abb6578ea2b8a9d8e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>CALeft</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>be015a7eea04c322413d36199f5761f3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>CARight</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>9de89c2937e6b374f54bcb030092f8f8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>CAUp</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>719193b6534d457413cf4ac56a9c6cf9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>CADown</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>16d007066fed2d61795438e00c212365</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>Plus</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>fba8e87397fe66b7cd19d45fc591ee00</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>Minus</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>d738f17bb35e7236a962986f75bb2d22</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>A</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>1407ff3bb6d52f180e3152268c170841</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>about</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>be958ac396d977eb7279a6347d303f89</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>aboutQt</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>5a905b642d68c9a70ad33575a155f895</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>initializeGL</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>69e77b7b2dc97790205c1887cd7d80ae</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>paintGL</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>38eb82afe576b7445c9720dc3cba6843</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>resizeGL</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>1f1d84bed197953b9d339ab0495ffd20</anchor>
      <arglist>(int, int)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>Draw</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>2e642031dfb59ebd190d167d74ae41f3</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mousePressEvent</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>44578829e915827cd9b457cd6037431b</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mouseReleaseEvent</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>8e7b9cd64b6647e710945579e7ec467e</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>mouseMoveEvent</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>b9689a6101acf007eca185b691d26510</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>SetupDepthCue</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>ffa30cf0c781bdd1d13e4a4feb7c53a6</anchor>
      <arglist>(float, float)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>InitLight</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>26ff1c69c2921fcd7dbda3ba2e9cc146</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>InitShade</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>57af4a40809575753d59245131ca9f28</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>InitFog</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>3ef91e9a4c73281099e352cd58f6d1e0</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>InitTransparence</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>fe7d67b5d34a14ae183c1ddef927d80a</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>GLObject *</type>
      <name>DrawObject</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>1efb2a9a604bdf843349a7562ae77ee2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>R</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>fc36dd30e32e73098dbefa9fb8d4fe7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>psi</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>c07a6942200319cd46f5f71b82237784</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>theta</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>d9731d1c9aa6017dfe1e6ea650ba835e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>phi</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>121637b147c4189bf840f38a79c44fa2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>VecMath::Vector&lt; 4 &gt;</type>
      <name>Background</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>71a090364e22d0d0f14bcce96f81174b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>GLfloat</type>
      <name>Alpha</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>52ba14c60ea42ef0173bb81fe206c23a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>light</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>1f905c62b66052daf0a5f0b68b8ec1fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>fog</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>1c3762dcb8959c73ad460449b527fbb3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>transparent</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>6e3aa1e5ed950e2cddd2677ae9bc4d29</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>shade</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>222d2d3ba9382f2910dcc5238e2b38c4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>bool</type>
      <name>colors</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>7de1b140bed3eed70cb6fd8fb56c7757</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>xpressed</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>1a226ba73abe0b7aa26df15e5331b236</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>int</type>
      <name>ypressed</name>
      <anchorfile>classXQGLWidget.html</anchorfile>
      <anchor>f07392faf7f6b9ad26db0fcfa4410aea</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>z2</name>
    <filename>classz2.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>z2</name>
      <anchorfile>classz2.html</anchorfile>
      <anchor>a3275d3d9e8e6b8a1da4139fd6757de9</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classz2.html</anchorfile>
      <anchor>2a7166cbbd02118399d350ee2dab9b01</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classz2.html</anchorfile>
      <anchor>877021ae4fd62890e7729049ff36980a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>z3</name>
    <filename>classz3.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>z3</name>
      <anchorfile>classz3.html</anchorfile>
      <anchor>a7f33bef3cdf16605c20fbc90bfa8ffa</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classz3.html</anchorfile>
      <anchor>d32ed22dc9e9f0410f5ea160aa1466ae</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classz3.html</anchorfile>
      <anchor>9dfc3491ac6e1112bfbd6af3185213f8</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>zA</name>
    <filename>classzA.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>zA</name>
      <anchorfile>classzA.html</anchorfile>
      <anchor>6f23706274665115f7dc2713f41ffe5e</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, double _alpha=2)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classzA.html</anchorfile>
      <anchor>d45d697ba6f97919da150077abe2f208</anchor>
      <arglist>(double _a=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classzA.html</anchorfile>
      <anchor>5576b7c32870c9b5204415db7120d8e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>double</type>
      <name>alpha</name>
      <anchorfile>classzA.html</anchorfile>
      <anchor>d2e4bc060816cd29d6018f9203fda83f</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>zm1</name>
    <filename>classzm1.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>zm1</name>
      <anchorfile>classzm1.html</anchorfile>
      <anchor>6a2e26646a2207503e4689f070578e9a</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classzm1.html</anchorfile>
      <anchor>843b570cf08a730cd6afd85419158aed</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classzm1.html</anchorfile>
      <anchor>bef9e2f243806657da1426b3406d03c4</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>zm2</name>
    <filename>classzm2.html</filename>
    <base>ComplexFunction</base>
    <member kind="function">
      <type></type>
      <name>zm2</name>
      <anchorfile>classzm2.html</anchorfile>
      <anchor>fafc50cc03bab616113d7b7e16efc427</anchor>
      <arglist>(double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>SetParameters</name>
      <anchorfile>classzm2.html</anchorfile>
      <anchor>34e714557e70c728999946bebac7a415</anchor>
      <arglist>(double=0, double=0, double=0, double=0)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classzm2.html</anchorfile>
      <anchor>2f8c6138a1bae28aff2eb6c515dbbe34</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="namespace">
    <name>Loki</name>
    <filename>namespaceLoki.html</filename>
    <class kind="class">Loki::EmptyType</class>
    <class kind="class">Loki::FunctorImpl&lt; R, NullType &gt;</class>
    <class kind="class">Loki::FunctorImpl&lt; R, Seq&lt; P1 &gt; &gt;</class>
    <class kind="class">Loki::FunctorImpl&lt; R, Seq&lt; P1, P2 &gt; &gt;</class>
    <class kind="class">Loki::FunctorImpl&lt; R, Seq&lt; P1, P2, P3 &gt; &gt;</class>
    <class kind="class">Loki::FunctorImpl&lt; R, Seq&lt; P1, P2, P3, P4 &gt; &gt;</class>
    <class kind="class">Loki::FunctorImpl&lt; R, LOKI_TYPELIST_1(P1)&gt;</class>
    <class kind="class">Loki::FunctorImpl&lt; R, LOKI_TYPELIST_2(P1, P2)&gt;</class>
    <class kind="class">Loki::FunctorImpl&lt; R, LOKI_TYPELIST_3(P1, P2, P3)&gt;</class>
    <class kind="class">Loki::FunctorImpl&lt; R, LOKI_TYPELIST_4(P1, P2, P3, P4)&gt;</class>
    <class kind="class">Loki::FunctorHandler</class>
    <class kind="class">Loki::MemFunHandler</class>
    <class kind="class">Loki::Functor</class>
    <class kind="class">Loki::NullType</class>
    <class kind="struct">Loki::Seq</class>
    <class kind="struct">Loki::Seq&lt;&gt;</class>
    <class kind="struct">Loki::CreateUsingNew</class>
    <class kind="struct">Loki::CreateUsing</class>
    <class kind="struct">Loki::CreateUsingMalloc</class>
    <class kind="struct">Loki::CreateStatic</class>
    <class kind="struct">Loki::DefaultLifetime</class>
    <class kind="struct">Loki::PhoenixSingleton</class>
    <class kind="struct">Loki::DeletableSingleton</class>
    <class kind="struct">Loki::SingletonWithLongevity</class>
    <class kind="struct">Loki::NoDestroy</class>
    <class kind="class">Loki::FollowIntoDeath</class>
    <class kind="class">Loki::SingletonHolder</class>
    <class kind="class">Loki::Singleton</class>
    <class kind="class">Loki::SmallObjAllocator</class>
    <class kind="class">Loki::AllocatorSingleton</class>
    <class kind="class">Loki::SmallObjectBase</class>
    <class kind="class">Loki::SmallObject</class>
    <class kind="class">Loki::SmallValueObject</class>
    <class kind="class">Loki::Mutex</class>
    <class kind="class">Loki::SingleThreaded</class>
    <class kind="struct">Loki::Typelist</class>
    <class kind="struct">Loki::Int2Type</class>
    <class kind="struct">Loki::Type2Type</class>
    <class kind="struct">Loki::Select</class>
    <class kind="struct">Loki::Select&lt; false, T, U &gt;</class>
    <class kind="struct">Loki::IsSameType</class>
    <class kind="struct">Loki::IsSameType&lt; T, T &gt;</class>
    <class kind="struct">Loki::Conversion</class>
    <class kind="struct">Loki::Conversion&lt; T, T &gt;</class>
    <class kind="struct">Loki::Conversion&lt; void, T &gt;</class>
    <class kind="struct">Loki::Conversion&lt; T, void &gt;</class>
    <class kind="struct">Loki::Conversion&lt; void, void &gt;</class>
    <class kind="struct">Loki::SuperSubclass</class>
    <class kind="struct">Loki::SuperSubclass&lt; void, void &gt;</class>
    <class kind="struct">Loki::SuperSubclass&lt; void, U &gt;</class>
    <class kind="struct">Loki::SuperSubclass&lt; T, void &gt;</class>
    <class kind="struct">Loki::SuperSubclassStrict</class>
    <class kind="struct">Loki::SuperSubclassStrict&lt; void, void &gt;</class>
    <class kind="struct">Loki::SuperSubclassStrict&lt; void, U &gt;</class>
    <class kind="struct">Loki::SuperSubclassStrict&lt; T, void &gt;</class>
    <class kind="struct">Loki::IsCustomUnsignedInt</class>
    <class kind="struct">Loki::IsCustomSignedInt</class>
    <class kind="struct">Loki::IsCustomFloat</class>
    <class kind="class">Loki::TypeTraits</class>
    <member kind="typedef">
      <type>void(LOKI_C_CALLING_CONVENTION_QUALIFIER *</type>
      <name>atexit_pfn_t</name>
      <anchorfile>namespaceLoki.html</anchorfile>
      <anchor>ee0a364633a62467e474b1f4c6f019de</anchor>
      <arglist>)()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>namespaceLoki.html</anchorfile>
      <anchor>f3edcfef5331945667c3719de05e9020</anchor>
      <arglist>(const EmptyType &amp;, const EmptyType &amp;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>namespaceLoki.html</anchorfile>
      <anchor>d91ee07d8b5f298cdca793871da9bac0</anchor>
      <arglist>(const EmptyType &amp;, const EmptyType &amp;)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&gt;</name>
      <anchorfile>namespaceLoki.html</anchorfile>
      <anchor>a21c33cdc3448e1dc4c7c657e78dc11f</anchor>
      <arglist>(const EmptyType &amp;, const EmptyType &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLongevity</name>
      <anchorfile>group__LifetimeGroup.html</anchorfile>
      <anchor>g82d4520d213b3b9ef2090f5e237874cf</anchor>
      <arglist>(T *pDynObject, unsigned int longevity, Destroyer d)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>SetLongevity</name>
      <anchorfile>namespaceLoki.html</anchorfile>
      <anchor>c0616590b1ce8fe3853105359358aa28</anchor>
      <arglist>(T *pDynObject, unsigned int longevity, typename Private::Deleter&lt; T &gt;::Type d=Private::Deleter&lt; T &gt;::Delete)</arglist>
    </member>
    <member kind="function">
      <type>unsigned int</type>
      <name>GetLongevity</name>
      <anchorfile>namespaceLoki.html</anchorfile>
      <anchor>bd6a1e278e749117c26908963320b02e</anchor>
      <arglist>(AllocatorSingleton&lt; T, C, M, O, L, X &gt; *)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loki::FunctorImpl&lt; R, LOKI_TYPELIST_3(P1, P2, P3)&gt;</name>
    <filename>classLoki_1_1FunctorImpl_3_01R_00_01LOKI__TYPELIST__3_07P1_00_01P2_00_01P3_08_4.html</filename>
    <templarg>R</templarg>
    <templarg>P1</templarg>
    <templarg>P2</templarg>
    <templarg>P3</templarg>
    <member kind="typedef">
      <type>R</type>
      <name>ResultType</name>
      <anchorfile>classLoki_1_1FunctorImpl_3_01R_00_01LOKI__TYPELIST__3_07P1_00_01P2_00_01P3_08_4.html</anchorfile>
      <anchor>ae95a7793da0be1b86f813be1d442444</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TypeTraits&lt; P1 &gt;::ParameterType</type>
      <name>Parm1</name>
      <anchorfile>classLoki_1_1FunctorImpl_3_01R_00_01LOKI__TYPELIST__3_07P1_00_01P2_00_01P3_08_4.html</anchorfile>
      <anchor>619b77590d987a1ae9232a2daa98731c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TypeTraits&lt; P2 &gt;::ParameterType</type>
      <name>Parm2</name>
      <anchorfile>classLoki_1_1FunctorImpl_3_01R_00_01LOKI__TYPELIST__3_07P1_00_01P2_00_01P3_08_4.html</anchorfile>
      <anchor>bf594ab530d797cfd005ab48d68e5438</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TypeTraits&lt; P3 &gt;::ParameterType</type>
      <name>Parm3</name>
      <anchorfile>classLoki_1_1FunctorImpl_3_01R_00_01LOKI__TYPELIST__3_07P1_00_01P2_00_01P3_08_4.html</anchorfile>
      <anchor>0c9c9ab888ad281a15ebc479e3ae786c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual R</type>
      <name>operator()</name>
      <anchorfile>classLoki_1_1FunctorImpl_3_01R_00_01LOKI__TYPELIST__3_07P1_00_01P2_00_01P3_08_4.html</anchorfile>
      <anchor>b93de7958170a07374eafe12d6779afa</anchor>
      <arglist>(Parm1, Parm2, Parm3)=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loki::Functor</name>
    <filename>classLoki_1_1Functor.html</filename>
    <templarg>R</templarg>
    <templarg>TList</templarg>
    <member kind="typedef">
      <type>FunctorImpl&lt; R, TList &gt;</type>
      <name>Impl</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>d341453f89024ff16e357fb21cdb4f29</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>R</type>
      <name>ResultType</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>b2f11ff96aad714a5fc401dc113a003c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>TList</type>
      <name>ParmList</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>ac8084a42cea9f23a40f5ef53ac7764c</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Impl::Parm1</type>
      <name>Parm1</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>9dae1e44e930972899658821958b2335</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Impl::Parm2</type>
      <name>Parm2</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>81e5b75f9f2cb833a32a343c48488daa</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Impl::Parm3</type>
      <name>Parm3</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>945d941687237f791877c0dcf0417004</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Impl::Parm4</type>
      <name>Parm4</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>73b70c2b3ab613bc3540b30acac77532</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Impl *(std::auto_ptr&lt; Impl &gt;::*</type>
      <name>unspecified_bool_type</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>38b6b2a43947cfe159ea8a8fa5504aba</anchor>
      <arglist>)() const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Functor</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>097fca42190e38db73e8cce943577d91</anchor>
      <arglist>(const Functor &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Functor</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>0dbdad76ec7c9131bff649010ec2707c</anchor>
      <arglist>(std::auto_ptr&lt; Impl &gt; spImpl)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Functor</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>3cd7ffad8b78b77b47fcce2df3cde334</anchor>
      <arglist>(Fun fun)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Functor</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>f431de46b5d3f1adcbe9777e52cff066</anchor>
      <arglist>(const PtrObj &amp;p, MemFn memFn)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator unspecified_bool_type</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>42a593864d4dbfbcab90169097e0a5de</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Functor &amp;</type>
      <name>operator=</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>30993b4c884e67ad4076a9726dd8a1a3</anchor>
      <arglist>(const Functor &amp;rhs)</arglist>
    </member>
    <member kind="function">
      <type>ResultType</type>
      <name>operator()</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>1471990a21ace9cc8aa4b5b357ce9d1b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>ResultType</type>
      <name>operator()</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>a79230b45a24c56a908c33f6acb89218</anchor>
      <arglist>(Parm1 p1) const </arglist>
    </member>
    <member kind="function">
      <type>ResultType</type>
      <name>operator()</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>59faa938f355967f3c81f8cb34604f20</anchor>
      <arglist>(Parm1 p1, Parm2 p2) const </arglist>
    </member>
    <member kind="function">
      <type>ResultType</type>
      <name>operator()</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>1bc35fb315d2e76dadc292887ec80733</anchor>
      <arglist>(Parm1 p1, Parm2 p2, Parm3 p3) const </arglist>
    </member>
    <member kind="function">
      <type>ResultType</type>
      <name>operator()</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>74e74c9be1519f0ccae9b6b07831c487</anchor>
      <arglist>(Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4) const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::auto_ptr&lt; Impl &gt;</type>
      <name>spImpl_</name>
      <anchorfile>classLoki_1_1Functor.html</anchorfile>
      <anchor>6297c5a0088da68bc714b847f7cc5d5e</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Loki::CreateUsingNew</name>
    <filename>structLoki_1_1CreateUsingNew.html</filename>
    <templarg>T</templarg>
    <member kind="function" static="yes">
      <type>static T *</type>
      <name>Create</name>
      <anchorfile>structLoki_1_1CreateUsingNew.html</anchorfile>
      <anchor>31964d318aadd16f17c48743fcd50cdf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Destroy</name>
      <anchorfile>structLoki_1_1CreateUsingNew.html</anchorfile>
      <anchor>4188b322ea06b90120d9ebc81e88216f</anchor>
      <arglist>(T *p)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T *</type>
      <name>Create</name>
      <anchorfile>structLoki_1_1CreateUsingNew.html</anchorfile>
      <anchor>31964d318aadd16f17c48743fcd50cdf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Destroy</name>
      <anchorfile>structLoki_1_1CreateUsingNew.html</anchorfile>
      <anchor>4188b322ea06b90120d9ebc81e88216f</anchor>
      <arglist>(T *p)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Loki::CreateUsing</name>
    <filename>structLoki_1_1CreateUsing.html</filename>
    <templarg>Alloc</templarg>
    <class kind="struct">Loki::CreateUsing::Allocator</class>
  </compound>
  <compound kind="struct">
    <name>Loki::CreateUsingMalloc</name>
    <filename>structLoki_1_1CreateUsingMalloc.html</filename>
    <templarg>T</templarg>
    <member kind="function" static="yes">
      <type>static T *</type>
      <name>Create</name>
      <anchorfile>structLoki_1_1CreateUsingMalloc.html</anchorfile>
      <anchor>55bf1f773f835e3b56bf7f51e17f03f6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Destroy</name>
      <anchorfile>structLoki_1_1CreateUsingMalloc.html</anchorfile>
      <anchor>ffb9968bbfb43c4199a538f95bc2d2fc</anchor>
      <arglist>(T *p)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T *</type>
      <name>Create</name>
      <anchorfile>structLoki_1_1CreateUsingMalloc.html</anchorfile>
      <anchor>55bf1f773f835e3b56bf7f51e17f03f6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Destroy</name>
      <anchorfile>structLoki_1_1CreateUsingMalloc.html</anchorfile>
      <anchor>ffb9968bbfb43c4199a538f95bc2d2fc</anchor>
      <arglist>(T *p)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Loki::CreateStatic</name>
    <filename>structLoki_1_1CreateStatic.html</filename>
    <templarg>T</templarg>
    <member kind="function" static="yes">
      <type>static T *</type>
      <name>Create</name>
      <anchorfile>structLoki_1_1CreateStatic.html</anchorfile>
      <anchor>e6e4d0e1496c78a0ac48f196cf0bad07</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Destroy</name>
      <anchorfile>structLoki_1_1CreateStatic.html</anchorfile>
      <anchor>3566e40a9f08d7756c50a31f5b0f148f</anchor>
      <arglist>(T *p)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T *</type>
      <name>Create</name>
      <anchorfile>structLoki_1_1CreateStatic.html</anchorfile>
      <anchor>e6e4d0e1496c78a0ac48f196cf0bad07</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>Destroy</name>
      <anchorfile>structLoki_1_1CreateStatic.html</anchorfile>
      <anchor>3566e40a9f08d7756c50a31f5b0f148f</anchor>
      <arglist>(T *p)</arglist>
    </member>
    <class kind="union">Loki::CreateStatic::MaxAlign</class>
  </compound>
  <compound kind="struct">
    <name>Loki::DefaultLifetime</name>
    <filename>structLoki_1_1DefaultLifetime.html</filename>
    <templarg>T</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ScheduleDestruction</name>
      <anchorfile>structLoki_1_1DefaultLifetime.html</anchorfile>
      <anchor>e368711b2fc33401c04cad59dbb78419</anchor>
      <arglist>(T *, atexit_pfn_t pFun)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>OnDeadReference</name>
      <anchorfile>structLoki_1_1DefaultLifetime.html</anchorfile>
      <anchor>c259e7d796d544c1bc3721b00ad2c86c</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Loki::PhoenixSingleton</name>
    <filename>classLoki_1_1PhoenixSingleton.html</filename>
    <templarg>T</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ScheduleDestruction</name>
      <anchorfile>classLoki_1_1PhoenixSingleton.html</anchorfile>
      <anchor>dca8841655ea2d2d39494f1773e1baa3</anchor>
      <arglist>(T *, atexit_pfn_t pFun)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>OnDeadReference</name>
      <anchorfile>classLoki_1_1PhoenixSingleton.html</anchorfile>
      <anchor>bd026bc7d753b645317c5aa9d62ed895</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static bool</type>
      <name>destroyedOnce_</name>
      <anchorfile>classLoki_1_1PhoenixSingleton.html</anchorfile>
      <anchor>794c0451e122c6fa550adfb28ee7e1f7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Loki::DeletableSingleton</name>
    <filename>classLoki_1_1DeletableSingleton.html</filename>
    <templarg>T</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ScheduleDestruction</name>
      <anchorfile>classLoki_1_1DeletableSingleton.html</anchorfile>
      <anchor>cdb434705832a8dec514cf4a56954cf0</anchor>
      <arglist>(T *, atexit_pfn_t pFun)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>OnDeadReference</name>
      <anchorfile>classLoki_1_1DeletableSingleton.html</anchorfile>
      <anchor>c18984dfcb610ee1979cee691e163d9f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>GracefulDelete</name>
      <anchorfile>classLoki_1_1DeletableSingleton.html</anchorfile>
      <anchor>626c2dc57146f1aea6bf911682f8e3e9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" static="yes">
      <type>static void</type>
      <name>atexitCallback</name>
      <anchorfile>classLoki_1_1DeletableSingleton.html</anchorfile>
      <anchor>d6a37ac24c1f199967c4908ffdd6f729</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static atexit_pfn_t</type>
      <name>deleter</name>
      <anchorfile>classLoki_1_1DeletableSingleton.html</anchorfile>
      <anchor>0d2bcad67762e4cc88e926386bfab002</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static bool</type>
      <name>isDead</name>
      <anchorfile>classLoki_1_1DeletableSingleton.html</anchorfile>
      <anchor>62fc02272ad280316f3e6fb27272994a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static bool</type>
      <name>needCallback</name>
      <anchorfile>classLoki_1_1DeletableSingleton.html</anchorfile>
      <anchor>5cec2ed562f3292accfa9468c37ea052</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Loki::SingletonWithLongevity</name>
    <filename>classLoki_1_1SingletonWithLongevity.html</filename>
    <templarg>T</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ScheduleDestruction</name>
      <anchorfile>classLoki_1_1SingletonWithLongevity.html</anchorfile>
      <anchor>46c377297e8770861cf5592f1681bdb0</anchor>
      <arglist>(T *pObj, atexit_pfn_t pFun)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>OnDeadReference</name>
      <anchorfile>classLoki_1_1SingletonWithLongevity.html</anchorfile>
      <anchor>a16692d939cc7ca18ea0dc34ea637ea8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Loki::NoDestroy</name>
    <filename>structLoki_1_1NoDestroy.html</filename>
    <templarg>T</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ScheduleDestruction</name>
      <anchorfile>structLoki_1_1NoDestroy.html</anchorfile>
      <anchor>6c62dfcf936280a3951caba23c4312ca</anchor>
      <arglist>(T *, atexit_pfn_t)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>OnDeadReference</name>
      <anchorfile>structLoki_1_1NoDestroy.html</anchorfile>
      <anchor>247f32f3f188838a244cce638af380f7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loki::FollowIntoDeath</name>
    <filename>classLoki_1_1FollowIntoDeath.html</filename>
    <class kind="struct">Loki::FollowIntoDeath::AfterMaster</class>
    <class kind="class">Loki::FollowIntoDeath::Followers</class>
    <class kind="struct">Loki::FollowIntoDeath::With</class>
  </compound>
  <compound kind="struct">
    <name>Loki::FollowIntoDeath::AfterMaster</name>
    <filename>structLoki_1_1FollowIntoDeath_1_1AfterMaster.html</filename>
    <templarg>Master</templarg>
    <class kind="struct">Loki::FollowIntoDeath::AfterMaster::IsDestroyed</class>
  </compound>
  <compound kind="struct">
    <name>Loki::FollowIntoDeath::AfterMaster::IsDestroyed</name>
    <filename>structLoki_1_1FollowIntoDeath_1_1AfterMaster_1_1IsDestroyed.html</filename>
    <templarg>F</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ScheduleDestruction</name>
      <anchorfile>structLoki_1_1FollowIntoDeath_1_1AfterMaster_1_1IsDestroyed.html</anchorfile>
      <anchor>00bdcb0018e0a678018f9e767caf1d31</anchor>
      <arglist>(F *, atexit_pfn_t pFun)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>OnDeadReference</name>
      <anchorfile>structLoki_1_1FollowIntoDeath_1_1AfterMaster_1_1IsDestroyed.html</anchorfile>
      <anchor>9a2d4a4fa70972a93c4f54f4533e1ad7</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Loki::FollowIntoDeath::With</name>
    <filename>structLoki_1_1FollowIntoDeath_1_1With.html</filename>
    <templarg>Lifetime</templarg>
    <class kind="struct">Loki::FollowIntoDeath::With::AsMasterLifetime</class>
  </compound>
  <compound kind="struct">
    <name>Loki::FollowIntoDeath::With::AsMasterLifetime</name>
    <filename>structLoki_1_1FollowIntoDeath_1_1With_1_1AsMasterLifetime.html</filename>
    <templarg>Master</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ScheduleDestruction</name>
      <anchorfile>structLoki_1_1FollowIntoDeath_1_1With_1_1AsMasterLifetime.html</anchorfile>
      <anchor>ab8622a6b436f51a721b48acf622c800</anchor>
      <arglist>(Master *pObj, atexit_pfn_t pFun)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>OnDeadReference</name>
      <anchorfile>structLoki_1_1FollowIntoDeath_1_1With_1_1AsMasterLifetime.html</anchorfile>
      <anchor>7a6d01c07aeb094a9870bf18bc4f49a8</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loki::SingletonHolder</name>
    <filename>classLoki_1_1SingletonHolder.html</filename>
    <templarg>T</templarg>
    <templarg>CreationPolicy</templarg>
    <templarg>LifetimePolicy</templarg>
    <templarg>ThreadingModel</templarg>
    <templarg>MutexPolicy</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>ObjectType</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>90400cb32897f9942958bece12165136</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>T</type>
      <name>ObjectType</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>90400cb32897f9942958bece12165136</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T &amp;</type>
      <name>Instance</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>52a113a9dc9aa53a5ab777c573f9fa28</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T &amp;</type>
      <name>Instance</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>eef8c30eaf5336c25bf0c6ff7b64b68e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>ThreadingModel&lt; T *, MutexPolicy &gt;::VolatileType</type>
      <name>PtrInstanceType</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>bdc75f6c6bd8e68d4e8f90db5aaafc4b</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>T *</type>
      <name>PtrInstanceType</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>338c3d48e13d1ca6ef0bc652b2e695f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>MakeInstance</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>d944c37d85028f4046d4e1f78f133710</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void LOKI_C_CALLING_CONVENTION_QUALIFIER</type>
      <name>DestroySingleton</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>fa306d4e67df281b85b0c932cf5186c6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>MakeInstance</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>6770e9272efc0a341def45b37bee5d41</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" static="yes">
      <type>static void</type>
      <name>DestroySingleton</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>37255d34c4d081d9b0468f42c09f0d83</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static PtrInstanceType</type>
      <name>pInstance_</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>3aaa564fefd318e66188c5f5c61f3fa0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static bool</type>
      <name>destroyed_</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>feb17951ea9358a3f6dbbf3a9ad32d0a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loki::Singleton</name>
    <filename>classLoki_1_1Singleton.html</filename>
    <templarg>T</templarg>
    <member kind="function" static="yes">
      <type>static T &amp;</type>
      <name>Instance</name>
      <anchorfile>classLoki_1_1Singleton.html</anchorfile>
      <anchor>b338e9495ecd5ba5ae62110b0f683656</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T &amp;</type>
      <name>Instance</name>
      <anchorfile>classLoki_1_1Singleton.html</anchorfile>
      <anchor>b338e9495ecd5ba5ae62110b0f683656</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loki::SmallObjAllocator</name>
    <filename>classLoki_1_1SmallObjAllocator.html</filename>
    <member kind="function">
      <type>void *</type>
      <name>Allocate</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>589fe436ba59e4bce90ea7e337d77b8a</anchor>
      <arglist>(std::size_t size, bool doThrow)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Deallocate</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>2b669733cfa9dd157603d13d979f8c1c</anchor>
      <arglist>(void *p, std::size_t size)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Deallocate</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>50406896d75a2591d4bd7dc53325e3d6</anchor>
      <arglist>(void *p)</arglist>
    </member>
    <member kind="function">
      <type>std::size_t</type>
      <name>GetMaxObjectSize</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>e49e9de3fd7b2fd93676cc1d63299b0d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>std::size_t</type>
      <name>GetAlignment</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>b1c8a2a3d7e9368ab59422ddd082105c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>TrimExcessMemory</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>6b635664b20a6984303dabde86c8ac83</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>IsCorrupt</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>2b7fbd5bf5fc56e45754abd2497ad18f</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>SmallObjAllocator</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>3d40b34b1a2d08a6bb9d9fa22ab5ce24</anchor>
      <arglist>(std::size_t pageSize, std::size_t maxObjectSize, std::size_t objectAlignSize)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>~SmallObjAllocator</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>0c861c4605844ee30dbe2a4f533fe2ae</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>SmallObjAllocator</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>830e547e97d0b14da81aff6f3e9657d4</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>SmallObjAllocator</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>91bf9724f641e616b87ccbc232daa395</anchor>
      <arglist>(const SmallObjAllocator &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>SmallObjAllocator &amp;</type>
      <name>operator=</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>90704c9383f3c1e11ce1be826148cbf2</anchor>
      <arglist>(const SmallObjAllocator &amp;)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Loki::FixedAllocator *</type>
      <name>pool_</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>fd9e9b0d3727cefd809acd5f62e4af5e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const std::size_t</type>
      <name>maxSmallObjectSize_</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>19e31f0bac9adbc17c3f782210a25ac8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const std::size_t</type>
      <name>objectAlignSize_</name>
      <anchorfile>classLoki_1_1SmallObjAllocator.html</anchorfile>
      <anchor>48ce64f65471acd76fc5dfca7dd050d6</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loki::AllocatorSingleton</name>
    <filename>classLoki_1_1AllocatorSingleton.html</filename>
    <templarg>ThreadingModel</templarg>
    <templarg>chunkSize</templarg>
    <templarg>maxSmallObjectSize</templarg>
    <templarg>objectAlignSize</templarg>
    <templarg>LifetimePolicy</templarg>
    <templarg>MutexPolicy</templarg>
    <base>Loki::SmallObjAllocator</base>
    <member kind="typedef">
      <type>AllocatorSingleton&lt; ThreadingModel, chunkSize, maxSmallObjectSize, objectAlignSize, LifetimePolicy &gt;</type>
      <name>MyAllocator</name>
      <anchorfile>classLoki_1_1AllocatorSingleton.html</anchorfile>
      <anchor>47fa2a9f8348fc8ce749221f7bfa7245</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>ThreadingModel&lt; MyAllocator, MutexPolicy &gt;</type>
      <name>MyThreadingModel</name>
      <anchorfile>classLoki_1_1AllocatorSingleton.html</anchorfile>
      <anchor>c9fde708e2ee0bf990c3eaa34422ca25</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>Loki::SingletonHolder&lt; MyAllocator, Loki::CreateStatic, LifetimePolicy, ThreadingModel &gt;</type>
      <name>MyAllocatorSingleton</name>
      <anchorfile>classLoki_1_1AllocatorSingleton.html</anchorfile>
      <anchor>74b23f8327ce4f3d795aa20240deb99e</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>AllocatorSingleton</name>
      <anchorfile>classLoki_1_1AllocatorSingleton.html</anchorfile>
      <anchor>c1ce92a825643f114d555fea170e2a99</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~AllocatorSingleton</name>
      <anchorfile>classLoki_1_1AllocatorSingleton.html</anchorfile>
      <anchor>f4248c104f7c04f4dbef16543083be53</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static AllocatorSingleton &amp;</type>
      <name>Instance</name>
      <anchorfile>classLoki_1_1AllocatorSingleton.html</anchorfile>
      <anchor>0de7839b1e888e11ff44bc50b78ca7d7</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ClearExtraMemory</name>
      <anchorfile>classLoki_1_1AllocatorSingleton.html</anchorfile>
      <anchor>082b4ba1c6574c5bed916c55ecf46e82</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>IsCorrupted</name>
      <anchorfile>classLoki_1_1AllocatorSingleton.html</anchorfile>
      <anchor>033978d127f16d2da0fd79d31ee75713</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>AllocatorSingleton</name>
      <anchorfile>classLoki_1_1AllocatorSingleton.html</anchorfile>
      <anchor>cf05bdb2a6b611616b7aa733e6a88f76</anchor>
      <arglist>(const AllocatorSingleton &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>AllocatorSingleton &amp;</type>
      <name>operator=</name>
      <anchorfile>classLoki_1_1AllocatorSingleton.html</anchorfile>
      <anchor>86e9962a29f762a587c5c4f257e43cf8</anchor>
      <arglist>(const AllocatorSingleton &amp;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loki::SmallObjectBase</name>
    <filename>classLoki_1_1SmallObjectBase.html</filename>
    <templarg>ThreadingModel</templarg>
    <templarg>chunkSize</templarg>
    <templarg>maxSmallObjectSize</templarg>
    <templarg>objectAlignSize</templarg>
    <templarg>LifetimePolicy</templarg>
    <templarg>MutexPolicy</templarg>
    <member kind="typedef">
      <type>AllocatorSingleton&lt; ThreadingModel, chunkSize, maxSmallObjectSize, objectAlignSize, LifetimePolicy &gt;</type>
      <name>ObjAllocatorSingleton</name>
      <anchorfile>classLoki_1_1SmallObjectBase.html</anchorfile>
      <anchor>d07df1c9ec9c41580e07e32eddcda82d</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void *</type>
      <name>operator new</name>
      <anchorfile>classLoki_1_1SmallObjectBase.html</anchorfile>
      <anchor>39f9c8d5b17c09bece34c8a400981970</anchor>
      <arglist>(std::size_t size)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void *</type>
      <name>operator new</name>
      <anchorfile>classLoki_1_1SmallObjectBase.html</anchorfile>
      <anchor>d212efa68b48292bf8fd2dd158b49400</anchor>
      <arglist>(std::size_t size, const std::nothrow_t &amp;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void *</type>
      <name>operator new</name>
      <anchorfile>classLoki_1_1SmallObjectBase.html</anchorfile>
      <anchor>dbbe1bde0960a38502af0940004d942f</anchor>
      <arglist>(std::size_t size, void *place)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>operator delete</name>
      <anchorfile>classLoki_1_1SmallObjectBase.html</anchorfile>
      <anchor>698e8b9ebac9df8c03e557c842a59bc5</anchor>
      <arglist>(void *p, std::size_t size)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>operator delete</name>
      <anchorfile>classLoki_1_1SmallObjectBase.html</anchorfile>
      <anchor>b835d84fa8bc1ed3a558dc2e7a7e39ec</anchor>
      <arglist>(void *p, const std::nothrow_t &amp;)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>operator delete</name>
      <anchorfile>classLoki_1_1SmallObjectBase.html</anchorfile>
      <anchor>e2da17da13c6c6a0d7e33c9df9eb27f2</anchor>
      <arglist>(void *p, void *place)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type></type>
      <name>SmallObjectBase</name>
      <anchorfile>classLoki_1_1SmallObjectBase.html</anchorfile>
      <anchor>d1c3a013df6cd2d95908003e006e1515</anchor>
      <arglist>(const SmallObjectBase &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>SmallObjectBase &amp;</type>
      <name>operator=</name>
      <anchorfile>classLoki_1_1SmallObjectBase.html</anchorfile>
      <anchor>6e872e4f97b5572c294dc0162cbcccf6</anchor>
      <arglist>(const SmallObjectBase &amp;)</arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>ThreadingModel&lt; ObjAllocatorSingleton, MutexPolicy &gt;</type>
      <name>MyThreadingModel</name>
      <anchorfile>classLoki_1_1SmallObjectBase.html</anchorfile>
      <anchor>90ac89e260a3b8f0427e8535289925dc</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>ObjAllocatorSingleton::MyAllocatorSingleton</type>
      <name>MyAllocatorSingleton</name>
      <anchorfile>classLoki_1_1SmallObjectBase.html</anchorfile>
      <anchor>68898e5adb4be4d8b2527519b220e656</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loki::SmallObject</name>
    <filename>classLoki_1_1SmallObject.html</filename>
    <templarg>ThreadingModel</templarg>
    <templarg>chunkSize</templarg>
    <templarg>maxSmallObjectSize</templarg>
    <templarg>objectAlignSize</templarg>
    <templarg>LifetimePolicy</templarg>
    <templarg>MutexPolicy</templarg>
    <base>Loki::SmallObjectBase</base>
    <member kind="function" protection="private">
      <type></type>
      <name>SmallObject</name>
      <anchorfile>classLoki_1_1SmallObject.html</anchorfile>
      <anchor>96e2281173a793f24c6c63b9c47213c8</anchor>
      <arglist>(const SmallObject &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>SmallObject &amp;</type>
      <name>operator=</name>
      <anchorfile>classLoki_1_1SmallObject.html</anchorfile>
      <anchor>b44804989134885b0e9625280c88f3c8</anchor>
      <arglist>(const SmallObject &amp;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loki::SmallValueObject</name>
    <filename>classLoki_1_1SmallValueObject.html</filename>
    <templarg>ThreadingModel</templarg>
    <templarg>chunkSize</templarg>
    <templarg>maxSmallObjectSize</templarg>
    <templarg>objectAlignSize</templarg>
    <templarg>LifetimePolicy</templarg>
    <templarg>MutexPolicy</templarg>
    <base>Loki::SmallObjectBase</base>
    <member kind="function" protection="protected">
      <type></type>
      <name>SmallValueObject</name>
      <anchorfile>classLoki_1_1SmallValueObject.html</anchorfile>
      <anchor>e446be83fd90d9369b557a90b2d6f4e5</anchor>
      <arglist>(const SmallValueObject &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>SmallValueObject &amp;</type>
      <name>operator=</name>
      <anchorfile>classLoki_1_1SmallValueObject.html</anchorfile>
      <anchor>9cca2d34447dd4ebc4a885cb04f113e4</anchor>
      <arglist>(const SmallValueObject &amp;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loki::Mutex</name>
    <filename>classLoki_1_1Mutex.html</filename>
    <member kind="function">
      <type>void</type>
      <name>Lock</name>
      <anchorfile>classLoki_1_1Mutex.html</anchorfile>
      <anchor>190a1d0d81f1a623d4b10c2ef49246df</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Unlock</name>
      <anchorfile>classLoki_1_1Mutex.html</anchorfile>
      <anchor>3a6f6671b80b8554af2491c29bf724cd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>Mutex</name>
      <anchorfile>classLoki_1_1Mutex.html</anchorfile>
      <anchor>ad80f4b44baebf4b4ae9d8f0d8a84441</anchor>
      <arglist>(const Mutex &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>Mutex &amp;</type>
      <name>operator=</name>
      <anchorfile>classLoki_1_1Mutex.html</anchorfile>
      <anchor>3a89e0fa0a02d47c9a5b66b7759fd2fd</anchor>
      <arglist>(const Mutex &amp;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Loki::SingleThreaded</name>
    <filename>classLoki_1_1SingleThreaded.html</filename>
    <templarg>Host</templarg>
    <templarg>MutexPolicy</templarg>
    <member kind="typedef">
      <type>Host</type>
      <name>VolatileType</name>
      <anchorfile>classLoki_1_1SingleThreaded.html</anchorfile>
      <anchor>3fef4723aad84781feda8f50d6751796</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef">
      <type>int</type>
      <name>IntType</name>
      <anchorfile>classLoki_1_1SingleThreaded.html</anchorfile>
      <anchor>277b17f61aa3c5a8f4ff4de9fea0132b</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static IntType</type>
      <name>AtomicAdd</name>
      <anchorfile>classLoki_1_1SingleThreaded.html</anchorfile>
      <anchor>bc5edd309278f9824020099c1c355414</anchor>
      <arglist>(volatile IntType &amp;lval, IntType val)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static IntType</type>
      <name>AtomicSubtract</name>
      <anchorfile>classLoki_1_1SingleThreaded.html</anchorfile>
      <anchor>7f7f55dab1422a52b8b5c21d90c05b03</anchor>
      <arglist>(volatile IntType &amp;lval, IntType val)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static IntType</type>
      <name>AtomicMultiply</name>
      <anchorfile>classLoki_1_1SingleThreaded.html</anchorfile>
      <anchor>d8540343e6df5fe0f15f0cb2897402ab</anchor>
      <arglist>(volatile IntType &amp;lval, IntType val)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static IntType</type>
      <name>AtomicDivide</name>
      <anchorfile>classLoki_1_1SingleThreaded.html</anchorfile>
      <anchor>4b93e9d3eb987772117b8a7e66fe426e</anchor>
      <arglist>(volatile IntType &amp;lval, IntType val)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static IntType</type>
      <name>AtomicIncrement</name>
      <anchorfile>classLoki_1_1SingleThreaded.html</anchorfile>
      <anchor>98929acf64576693c065c1d9560bd40b</anchor>
      <arglist>(volatile IntType &amp;lval)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static IntType</type>
      <name>AtomicDecrement</name>
      <anchorfile>classLoki_1_1SingleThreaded.html</anchorfile>
      <anchor>ef003bc717978b34a62cdc35b6465924</anchor>
      <arglist>(volatile IntType &amp;lval)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>AtomicAssign</name>
      <anchorfile>classLoki_1_1SingleThreaded.html</anchorfile>
      <anchor>e402f02eefbc022d0da89ae125cca513</anchor>
      <arglist>(volatile IntType &amp;lval, IntType val)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>AtomicAssign</name>
      <anchorfile>classLoki_1_1SingleThreaded.html</anchorfile>
      <anchor>f120eb3c0bb68384d1072b26026a1aec</anchor>
      <arglist>(IntType &amp;lval, volatile IntType &amp;val)</arglist>
    </member>
    <class kind="struct">Loki::SingleThreaded::Lock</class>
  </compound>
  <compound kind="struct">
    <name>Loki::SingleThreaded::Lock</name>
    <filename>structLoki_1_1SingleThreaded_1_1Lock.html</filename>
    <member kind="function">
      <type></type>
      <name>Lock</name>
      <anchorfile>structLoki_1_1SingleThreaded_1_1Lock.html</anchorfile>
      <anchor>4500e2b46f013628ab24de6cb3a4de4e</anchor>
      <arglist>(const SingleThreaded &amp;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Lock</name>
      <anchorfile>structLoki_1_1SingleThreaded_1_1Lock.html</anchorfile>
      <anchor>e2ac78676358c1a5d4bb3f51443af592</anchor>
      <arglist>(const SingleThreaded *)</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Loki::LongevityLifetime::SingletonFixedLongevity</name>
    <filename>classLoki_1_1LongevityLifetime_1_1SingletonFixedLongevity.html</filename>
    <templarg>Longevity</templarg>
    <templarg>T</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>ScheduleDestruction</name>
      <anchorfile>classLoki_1_1LongevityLifetime_1_1SingletonFixedLongevity.html</anchorfile>
      <anchor>1d2485084acb6833205c603131c4ede2</anchor>
      <arglist>(T *pObj, atexit_pfn_t pFun)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>OnDeadReference</name>
      <anchorfile>classLoki_1_1LongevityLifetime_1_1SingletonFixedLongevity.html</anchorfile>
      <anchor>7469345a20917d5cb1b5312e77af71e2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>Loki::LongevityLifetime::DieLast</name>
    <filename>structLoki_1_1LongevityLifetime_1_1DieLast.html</filename>
    <templarg>T</templarg>
    <base>Loki::LongevityLifetime::SingletonFixedLongevity</base>
  </compound>
  <compound kind="struct">
    <name>Loki::LongevityLifetime::DieDirectlyBeforeLast</name>
    <filename>structLoki_1_1LongevityLifetime_1_1DieDirectlyBeforeLast.html</filename>
    <templarg>T</templarg>
    <base>Loki::LongevityLifetime::SingletonFixedLongevity</base>
  </compound>
  <compound kind="struct">
    <name>Loki::LongevityLifetime::DieFirst</name>
    <filename>structLoki_1_1LongevityLifetime_1_1DieFirst.html</filename>
    <templarg>T</templarg>
    <base>SingletonFixedLongevity&lt; 0, T &gt;</base>
  </compound>
  <compound kind="struct">
    <name>Loki::LongevityLifetime::DieAsSmallObjectParent</name>
    <filename>structLoki_1_1LongevityLifetime_1_1DieAsSmallObjectParent.html</filename>
    <templarg>T</templarg>
    <base>Loki::LongevityLifetime::DieLast</base>
  </compound>
  <compound kind="struct">
    <name>Loki::LongevityLifetime::DieAsSmallObjectChild</name>
    <filename>structLoki_1_1LongevityLifetime_1_1DieAsSmallObjectChild.html</filename>
    <templarg>T</templarg>
    <base>Loki::LongevityLifetime::DieDirectlyBeforeLast</base>
  </compound>
  <compound kind="namespace">
    <name>LongevityLifetime</name>
    <filename>namespaceLongevityLifetime.html</filename>
  </compound>
  <compound kind="class">
    <name>VecMath::Matrix</name>
    <filename>classVecMath_1_1Matrix.html</filename>
    <templarg>D</templarg>
    <templarg>N</templarg>
    <member kind="function">
      <type></type>
      <name>Matrix</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>afaeb5312b577fa2bb48e9605e76afd5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Matrix</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>fa3dcfdb384b9d3ad844578451401bc2</anchor>
      <arglist>(N, N, N, N, N, N)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Matrix</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>110bedf8a53847d2985f57bdb897afe1</anchor>
      <arglist>(unsigned, unsigned, N)</arglist>
    </member>
    <member kind="function">
      <type>N &amp;</type>
      <name>operator()</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>23a74a530edd9ae5e54d7b792f7b0d40</anchor>
      <arglist>(unsigned i, unsigned j)</arglist>
    </member>
    <member kind="function">
      <type>Matrix&lt; D, N &gt;</type>
      <name>operator*</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>b560a8ea5f4708be9b5d4164d07ccbb4</anchor>
      <arglist>(const Matrix&lt; D, N &gt; &amp;) const </arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator*</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>c9bb6064bbab4c97f65dbb89b25358a1</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Matrix&lt; D, N &gt;</type>
      <name>operator-</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>73eff5fdc698d339122b800dc1eeb3aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>Print</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>f6ef681da5373b7f1214fca37b0dfa7d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Matrix</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>110bedf8a53847d2985f57bdb897afe1</anchor>
      <arglist>(unsigned, unsigned, N)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Matrix</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>2cbaca136bfebfeadb1646b49a1ef28c</anchor>
      <arglist>(bool random)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Matrix</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>79e43f201d199747ad5bfb7e5c90ee60</anchor>
      <arglist>(const N a[D][D])</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Matrix</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>2fcfc3d24f171f0b785568e31246c9b5</anchor>
      <arglist>(const N *a)</arglist>
    </member>
    <member kind="function">
      <type>N</type>
      <name>operator()</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>99cf82a7c1bd1af4d1b50927f64aed65</anchor>
      <arglist>(unsigned i, unsigned j) const </arglist>
    </member>
    <member kind="function">
      <type>N &amp;</type>
      <name>operator()</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>10a5a2dc0327ce50af18806a39e2faa0</anchor>
      <arglist>(unsigned i, unsigned j)</arglist>
    </member>
    <member kind="function">
      <type>Matrix&lt; D, N &gt;</type>
      <name>operator*</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>1f6faf9525beb1bebe0e631db8d409e9</anchor>
      <arglist>(const Matrix&lt; D, N &gt; &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>Matrix&lt; D, N &gt;</type>
      <name>operator*=</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>8107ec5c6964bd5715ded0de8a500f26</anchor>
      <arglist>(const Matrix&lt; D, N &gt; &amp;other)</arglist>
    </member>
    <member kind="function">
      <type>VecMath::Vector&lt; D, N &gt;</type>
      <name>operator*</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>955315c730d0acf6bc1c44b4dd4351a8</anchor>
      <arglist>(const VecMath::Vector&lt; D, N &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>print</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>ca1a9a5285708e821b35db56226a1f77</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>N</type>
      <name>det</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>ad3219dd37882f712a68af0f6ce115be</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Matrix&lt; D-1, N &gt;</type>
      <name>matrix_minor</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>ebb8b54532f1ad66cef37ea7aba3548a</anchor>
      <arglist>(unsigned i, unsigned j)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>N</type>
      <name>M</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>b05a96df5ab732804b596f5e34d3216b</anchor>
      <arglist>[D][D]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>N</type>
      <name>data_</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>2a642afb497fa4ca0adb485f0e492ee5</anchor>
      <arglist>[D][D]</arglist>
    </member>
    <class kind="struct">VecMath::Matrix::ConstructLoop</class>
    <class kind="struct">VecMath::Matrix::ConstructLoop&lt; D_, 0, 0 &gt;</class>
    <class kind="struct">VecMath::Matrix::ConstructLoop&lt; D_, 0, j &gt;</class>
    <class kind="struct">VecMath::Matrix::ConstructLoop&lt; D_, i, 0 &gt;</class>
    <class kind="struct">VecMath::Matrix::CopyLoop</class>
    <class kind="struct">VecMath::Matrix::CopyLoop&lt; 0, 0, D_ &gt;</class>
    <class kind="struct">VecMath::Matrix::CopyLoop&lt; 0, j, D_ &gt;</class>
    <class kind="struct">VecMath::Matrix::CopyLoop&lt; i, 0, D_ &gt;</class>
    <class kind="struct">VecMath::Matrix::Multiply</class>
    <class kind="struct">VecMath::Matrix::MultiplyColLoop</class>
    <class kind="struct">VecMath::Matrix::MultiplyColLoop&lt; i, 0, D_ &gt;</class>
    <class kind="struct">VecMath::Matrix::MultiplyInnerLoop</class>
    <class kind="struct">VecMath::Matrix::MultiplyInnerLoop&lt; i, j, 0, D_ &gt;</class>
    <class kind="struct">VecMath::Matrix::MultiplyRowLoop</class>
    <class kind="struct">VecMath::Matrix::MultiplyRowLoop&lt; 0, D_ &gt;</class>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::ConstructLoop</name>
    <filename>structVecMath_1_1Matrix_1_1ConstructLoop.html</filename>
    <templarg>D_</templarg>
    <templarg>i</templarg>
    <templarg>j</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>row_loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1ConstructLoop.html</anchorfile>
      <anchor>d4c98ae6c9ced7303b9f4cbebf70ad24</anchor>
      <arglist>(N a[D][D])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>col_loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1ConstructLoop.html</anchorfile>
      <anchor>020261e53088f417772d8482366e8947</anchor>
      <arglist>(N a[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::ConstructLoop&lt; D_, 0, 0 &gt;</name>
    <filename>structVecMath_1_1Matrix_1_1ConstructLoop_3_01D___00_010_00_010_01_4.html</filename>
    <templarg>D_</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>row_loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1ConstructLoop_3_01D___00_010_00_010_01_4.html</anchorfile>
      <anchor>bd76d08952638eac75de3605cf3572b6</anchor>
      <arglist>(N a[D][D])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>col_loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1ConstructLoop_3_01D___00_010_00_010_01_4.html</anchorfile>
      <anchor>3466f03ab3f1f55834edf05b18e2943d</anchor>
      <arglist>(N a[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::ConstructLoop&lt; D_, 0, j &gt;</name>
    <filename>structVecMath_1_1Matrix_1_1ConstructLoop_3_01D___00_010_00_01j_01_4.html</filename>
    <templarg>D_</templarg>
    <templarg>j</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>row_loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1ConstructLoop_3_01D___00_010_00_01j_01_4.html</anchorfile>
      <anchor>ba08387b85702d80f41a5b8d1a38c884</anchor>
      <arglist>(N a[D][D])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>col_loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1ConstructLoop_3_01D___00_010_00_01j_01_4.html</anchorfile>
      <anchor>323e0e6e628e770885d889db9a551e38</anchor>
      <arglist>(N a[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::ConstructLoop&lt; D_, i, 0 &gt;</name>
    <filename>structVecMath_1_1Matrix_1_1ConstructLoop_3_01D___00_01i_00_010_01_4.html</filename>
    <templarg>D_</templarg>
    <templarg>i</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>row_loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1ConstructLoop_3_01D___00_01i_00_010_01_4.html</anchorfile>
      <anchor>039d3ed367d85985a26743123d7f13bf</anchor>
      <arglist>(N a[D][D])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>col_loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1ConstructLoop_3_01D___00_01i_00_010_01_4.html</anchorfile>
      <anchor>ba0a249190fb1eb275da61b4349842da</anchor>
      <arglist>(N a[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::CopyLoop</name>
    <filename>structVecMath_1_1Matrix_1_1CopyLoop.html</filename>
    <templarg>i</templarg>
    <templarg>j</templarg>
    <templarg>D_</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>copy_row</name>
      <anchorfile>structVecMath_1_1Matrix_1_1CopyLoop.html</anchorfile>
      <anchor>4ebad8452bedb2841bcb0e93e297c969</anchor>
      <arglist>(N from[D][D], N to[D][D])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>copy_col</name>
      <anchorfile>structVecMath_1_1Matrix_1_1CopyLoop.html</anchorfile>
      <anchor>ab95906a2a48848c46ca443631a64eb8</anchor>
      <arglist>(N from[D][D], N to[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::CopyLoop&lt; 0, 0, D_ &gt;</name>
    <filename>structVecMath_1_1Matrix_1_1CopyLoop_3_010_00_010_00_01D___01_4.html</filename>
    <templarg>D_</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>copy_col</name>
      <anchorfile>structVecMath_1_1Matrix_1_1CopyLoop_3_010_00_010_00_01D___01_4.html</anchorfile>
      <anchor>2dffd4befd8412f64cc9a0513f4a91fe</anchor>
      <arglist>(N from[D][D], N to[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::CopyLoop&lt; 0, j, D_ &gt;</name>
    <filename>structVecMath_1_1Matrix_1_1CopyLoop_3_010_00_01j_00_01D___01_4.html</filename>
    <templarg>j</templarg>
    <templarg>D_</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>copy_row</name>
      <anchorfile>structVecMath_1_1Matrix_1_1CopyLoop_3_010_00_01j_00_01D___01_4.html</anchorfile>
      <anchor>73761d9c54126f2cb5396d8e5c9d856e</anchor>
      <arglist>(N from[D][D], N to[D][D])</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>copy_col</name>
      <anchorfile>structVecMath_1_1Matrix_1_1CopyLoop_3_010_00_01j_00_01D___01_4.html</anchorfile>
      <anchor>2600c76a7b627452ec28a319ed8e0fac</anchor>
      <arglist>(N from[D][D], N to[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::CopyLoop&lt; i, 0, D_ &gt;</name>
    <filename>structVecMath_1_1Matrix_1_1CopyLoop_3_01i_00_010_00_01D___01_4.html</filename>
    <templarg>i</templarg>
    <templarg>D_</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>copy_col</name>
      <anchorfile>structVecMath_1_1Matrix_1_1CopyLoop_3_01i_00_010_00_01D___01_4.html</anchorfile>
      <anchor>ff13ee39bf63e475428398b3349a5d16</anchor>
      <arglist>(N from[D][D], N to[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::Multiply</name>
    <filename>structVecMath_1_1Matrix_1_1Multiply.html</filename>
    <templarg>D_</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>multiply</name>
      <anchorfile>structVecMath_1_1Matrix_1_1Multiply.html</anchorfile>
      <anchor>697bbffbef972c93d87062c3b667638f</anchor>
      <arglist>(const N a[D][D], const N b[D][D], N c[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::MultiplyColLoop</name>
    <filename>structVecMath_1_1Matrix_1_1MultiplyColLoop.html</filename>
    <templarg>i</templarg>
    <templarg>j</templarg>
    <templarg>D_</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1MultiplyColLoop.html</anchorfile>
      <anchor>a0134d77ce1f36e25890f591584cbf0f</anchor>
      <arglist>(const N a[D][D], const N b[D][D], N c[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::MultiplyColLoop&lt; i, 0, D_ &gt;</name>
    <filename>structVecMath_1_1Matrix_1_1MultiplyColLoop_3_01i_00_010_00_01D___01_4.html</filename>
    <templarg>i</templarg>
    <templarg>D_</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1MultiplyColLoop_3_01i_00_010_00_01D___01_4.html</anchorfile>
      <anchor>a1d031f96f4438be2dc1f3d8cadd8e20</anchor>
      <arglist>(const N a[D][D], const N b[D][D], N c[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::MultiplyInnerLoop</name>
    <filename>structVecMath_1_1Matrix_1_1MultiplyInnerLoop.html</filename>
    <templarg>i</templarg>
    <templarg>j</templarg>
    <templarg>k</templarg>
    <templarg>D_</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1MultiplyInnerLoop.html</anchorfile>
      <anchor>5308531d8b81c0510cbd57f0c19fb905</anchor>
      <arglist>(const N a[D][D], const N b[D][D], N c[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::MultiplyInnerLoop&lt; i, j, 0, D_ &gt;</name>
    <filename>structVecMath_1_1Matrix_1_1MultiplyInnerLoop_3_01i_00_01j_00_010_00_01D___01_4.html</filename>
    <templarg>i</templarg>
    <templarg>j</templarg>
    <templarg>D_</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1MultiplyInnerLoop_3_01i_00_01j_00_010_00_01D___01_4.html</anchorfile>
      <anchor>16407b02898e8cb8eadff7e86be709cc</anchor>
      <arglist>(const N a[D][D], const N b[D][D], N c[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::MultiplyRowLoop</name>
    <filename>structVecMath_1_1Matrix_1_1MultiplyRowLoop.html</filename>
    <templarg>i</templarg>
    <templarg>D_</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1MultiplyRowLoop.html</anchorfile>
      <anchor>ea4947bfe7d8c1782df64827f8c73770</anchor>
      <arglist>(const N a[D][D], const N b[D][D], N c[D][D])</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::Matrix::MultiplyRowLoop&lt; 0, D_ &gt;</name>
    <filename>structVecMath_1_1Matrix_1_1MultiplyRowLoop_3_010_00_01D___01_4.html</filename>
    <templarg>D_</templarg>
    <member kind="function" static="yes">
      <type>static void</type>
      <name>loop</name>
      <anchorfile>structVecMath_1_1Matrix_1_1MultiplyRowLoop_3_010_00_01D___01_4.html</anchorfile>
      <anchor>2bead12deb0461d3ce7873ece233dd71</anchor>
      <arglist>(const N a[D][D], const N b[D][D], N c[D][D])</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VecMath::Vector</name>
    <filename>classVecMath_1_1Vector.html</filename>
    <templarg>D</templarg>
    <templarg>N</templarg>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>7ce10a3281bba5657868f7817ff06379</anchor>
      <arglist>(N,...)</arglist>
    </member>
    <member kind="function">
      <type>N &amp;</type>
      <name>operator[]</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>65b86dd66378dba300f0026a3eb02a95</anchor>
      <arglist>(unsigned i)</arglist>
    </member>
    <member kind="function">
      <type>N</type>
      <name>operator[]</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>495b90c06c0eff975cdf37e70fbd06f8</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt; &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>17f70aae366128f7148096ade6b81ee0</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt; &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>7d51f7d32747367552f54a11c2fb8c49</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt; &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>aee09ef5f2ec33845899979f21de76f6</anchor>
      <arglist>(const N &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator-</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>f6686d68f8e7073c89ff57bca8a16b24</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator+</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>c0a5d6a6275a36d6cf01ae0ca93862dd</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator-</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>84934a5d1548fc800a8524be2e3c090f</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator*</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>df9a50f7a2cf5b360405ce05a49ad42f</anchor>
      <arglist>(const N &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>N</type>
      <name>operator*</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>482500d5c8d51f1a1fb45452947c365e</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;X) const </arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator/</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>99cded84739f77be3d691c65dc8b4439</anchor>
      <arglist>(const N &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>N</type>
      <name>sqnorm</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>c60183f68f2d8a6473c64c2e753cd053</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>N *</type>
      <name>data</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>540cec1fb9483d9cad8ea9356525d867</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>63640f08c7793bf37aedf32e552499dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>517fef66b018fabab9e91f32ee99e1cc</anchor>
      <arglist>(N,...)</arglist>
    </member>
    <member kind="function">
      <type>N &amp;</type>
      <name>operator[]</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>a59a2deeac095d34c178eafb8ef86857</anchor>
      <arglist>(unsigned i)</arglist>
    </member>
    <member kind="function">
      <type>N</type>
      <name>operator[]</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>db52104e1fab7ee35c43a9ac21c063ae</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt; &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>b651408fbe63a848fdeca1eda8812727</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt; &amp;</type>
      <name>operator-=</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>9952aec037b375082078d802eefe4a28</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt; &amp;</type>
      <name>operator*=</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>880e685179a418f5e79da715d1e436a6</anchor>
      <arglist>(const N &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator-</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>769cab9bb70e99ffc34fc6a264e09fc1</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator+</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>38ca2040a445c58b752e285ba98cf52f</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator-</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>4815043540a8862c67db0266e1b71d16</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;Y)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator*</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>5e2a60f1a088d7da9108a73f110b0ef8</anchor>
      <arglist>(const N &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>N</type>
      <name>operator*</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>88cd95d3d5e5cb2acb15c046f30832a6</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;X) const </arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator/</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>5e1b66a2713adfb230f3baa9417e3c88</anchor>
      <arglist>(const N &amp;s)</arglist>
    </member>
    <member kind="function">
      <type>N</type>
      <name>sqnorm</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>1ac5b53c857112a28de561ee4c80e6d3</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>N *</type>
      <name>data</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>540cec1fb9483d9cad8ea9356525d867</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static unsigned</type>
      <name>dimension</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>9d4348338bf90f69f8d3979a34fd2e7c</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static unsigned</type>
      <name>dimension</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>cfdfd007cda74ebada548887e5bbb016</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>N</type>
      <name>x</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>5fc498893a35a23282dbfd6fb7784ad9</anchor>
      <arglist>[D]</arglist>
    </member>
  </compound>
</tagfile>
