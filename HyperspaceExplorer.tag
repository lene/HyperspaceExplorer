<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="page">
    <name>index</name>
    <title>HyperspaceExplorer</title>
    <filename>index</filename>
    <docanchor file="index">intro</docanchor>
  </compound>
  <compound kind="group">
    <name>Coloring</name>
    <title>Functionality for defining color schemes</title>
    <filename>group__Coloring.html</filename>
    <class kind="class">Color</class>
    <class kind="class">ColorManager</class>
    <class kind="class">xyz2RGBColorManager</class>
    <class kind="class">monochromeColorManager</class>
    <class kind="class">ColorManagerManager</class>
  </compound>
  <compound kind="group">
    <name>FunctionGroup</name>
    <title>Functions and objects</title>
    <filename>group__FunctionGroup.html</filename>
    <subgroup>RealGroup</subgroup>
    <subgroup>ObjectGroup</subgroup>
    <subgroup>SurfaceGroup</subgroup>
    <subgroup>FunctionParameterGroup</subgroup>
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
    <name>FunctionParameterGroup</name>
    <title>FunctionParameterGroup</title>
    <filename>group__FunctionParameterGroup.html</filename>
    <class kind="class">FunctionParameterValueBase</class>
    <class kind="class">FunctionParameterValue</class>
    <class kind="class">FunctionParameter</class>
    <class kind="class">ParameterFac</class>
    <class kind="class">ParameterMap</class>
    <member kind="typedef">
      <type>Loki::SingletonHolder&lt; ParameterFac &gt;</type>
      <name>ParameterFactory</name>
      <anchorfile>group__FunctionParameterGroup.html</anchorfile>
      <anchor>g292f843041b81e669c6ad1799c62c898</anchor>
      <arglist></arglist>
    </member>
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
    <name>UIGroup</name>
    <title>User Interface</title>
    <filename>group__UIGroup.html</filename>
    <subgroup>Coloring</subgroup>
    <subgroup>UIHelpers</subgroup>
    <class kind="class">C4DView</class>
    <class kind="class">AnimationDialogImpl</class>
    <class kind="class">ComplexDialogImpl</class>
    <class kind="class">FunctionDialogImpl</class>
    <class kind="class">C4DView::Menu4D</class>
    <class kind="class">PluginCreator</class>
    <class kind="class">PolarDialogImpl</class>
    <class kind="class">SurfaceDialogImpl</class>
    <class kind="class">Ui_ValuesDialog</class>
    <class kind="class">ValuesDialogImpl</class>
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
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual RealFunction *</type>
      <name>doCreateFunction</name>
      <anchorfile>group__UIHelpers.html</anchorfile>
      <anchor>g7d01311aa80799bb82b77d0313f7bdf5</anchor>
      <arglist>(C4DView *)</arglist>
    </member>
  </compound>
  <compound kind="group">
    <name>VecMath</name>
    <title>Vector and Matrix algebra</title>
    <filename>group__VecMath.html</filename>
    <class kind="class">VecMath::Matrix</class>
    <class kind="struct">VecMath::NumAxes</class>
    <class kind="class">VecMath::RotationAxes</class>
    <class kind="class">VecMath::Rotation</class>
    <class kind="class">VecMath::Vector</class>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g66177497b2b0c964a01d7be1087cdf17</anchor>
      <arglist>(std::ostream &amp;o, const Rotation&lt; D, N &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>std::istringstream &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g481900ade75f6885f522982564e1f702</anchor>
      <arglist>(std::istringstream &amp;in, Rotation&lt; D, N &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>gef433144f359a8cda43c2290871425b3</anchor>
      <arglist>(std::ostream &amp;o, const Vector&lt; D, N &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>std::istringstream &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g32efe5289273edf4fcd804d59be355b8</anchor>
      <arglist>(std::istringstream &amp;in, Vector&lt; D, N &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D &gt;</type>
      <name>cross</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g65ec0cbac29ab530c63be146545c5532</anchor>
      <arglist>(const Vector&lt; D &gt; &amp;, const Vector&lt; D &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D &gt;</type>
      <name>cross</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g7025733deb7fc498f87ffdf8ceb93fab</anchor>
      <arglist>(const Vector&lt; D &gt; &amp;, const Vector&lt; D &gt; &amp;, const Vector&lt; D &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; 3, N &gt;</type>
      <name>vcross</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>gebb474b1869607dba1cd231e786a169d</anchor>
      <arglist>(Vector&lt; 3, N &gt; a, Vector&lt; 3, N &gt; b)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; 4, N &gt;</type>
      <name>vcross</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>gbdc5bc1e998587a215aff0c5a1a7b95d</anchor>
      <arglist>(Vector&lt; 4, N &gt; a, Vector&lt; 4, N &gt; b, Vector&lt; 4, N &gt; c)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>vnormalize</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g646679fba90010325c01c937abfb4ea4</anchor>
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
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>ObjectHypercube</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>bc3a4f6e3276734aa70e0853f0df6022</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>ObjectHyperpyramid</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>951f672d7d323bb799c1ab18d412e1d7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
      <name>ObjectHypersponge</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>395baf447937415a0f3366c4d1c529ee</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" virtualness="virtual">
      <type>virtual void</type>
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
      <type>bool &amp;</type>
      <name>getColors</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d9687bb0368033af4e97f2c4571156d9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool &amp;</type>
      <name>getShade</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>89dd3e07ddd664711df895975a3d4bcd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool &amp;</type>
      <name>getFog</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>dabc3be452e44e3101ad2f9f4cee5e4c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool &amp;</type>
      <name>getLight</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c83101f5d137e9357245e863a2df7d3e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool &amp;</type>
      <name>getTransparent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>5ad3a5d84454cb614b14748d772013b4</anchor>
      <arglist>()</arglist>
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
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>applyTransform</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>85b4bbf559894040c81d08b8657a1d55</anchor>
      <arglist>(const VecMath::Rotation&lt; 4 &gt; &amp;R, const VecMath::Vector&lt; 4 &gt; &amp;T)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>animate</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>ba68449fe84c206cbd20926378797611</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setImgDir</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>7921fd7bb829954c2307ff71daebdd89</anchor>
      <arglist>(const std::string &amp;s)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setImgPrefix</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>ad0b04453c9ba092780d8e22ae36ba8c</anchor>
      <arglist>(const std::string &amp;s)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setSize</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>2c5dae3094d155b16f374dad68c07407</anchor>
      <arglist>(unsigned w, unsigned h)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setColors</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>128fc82da387471fbd9c88fe35263e8f</anchor>
      <arglist>(bool)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setShading</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>7b529adaf92650371f5b6e81dbf4792b</anchor>
      <arglist>(bool)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setTransparence</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>262d0aa0188edc2b262160959ce7d965</anchor>
      <arglist>(bool)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setFog</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>556e03bfff4b2f369a86edb47f3e4b84</anchor>
      <arglist>(bool)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setHyperfog</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>b8007107aba8c57dd39063be93ca8f96</anchor>
      <arglist>(bool)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setCoordinates</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>eb4ec12aada637e796110fe8172d12ff</anchor>
      <arglist>(bool)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setFunction</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>1cb1c0e65ff3650457256f4f8192b70e</anchor>
      <arglist>(Function *_f)</arglist>
    </member>
    <member kind="slot" protection="private">
      <type>void</type>
      <name>OnTimer</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>2c45a3e0625e7ee0567630203bbb0360</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="private">
      <type>void</type>
      <name>AnimationSettings</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c781d4f8f3a11fd65fc0c41921460b59</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>ApplyChanges</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>7cdc25eeb13d2f7904348f51ac68b63b</anchor>
      <arglist>(const ParameterMap &amp;)</arglist>
    </member>
    <member kind="slot" protection="private">
      <type>void</type>
      <name>Help</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>aefd85a2c570d47d9d82b1861d73b631</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="private">
      <type>void</type>
      <name>about</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>5043ee7707435f83b4a3891a9145452b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="private">
      <type>void</type>
      <name>aboutQt</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>1a27f7faf0214a769ebd09bd033432e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>Transform</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8a51cc06ede29308384576f277a67e19</anchor>
      <arglist>(const VecMath::Rotation&lt; 4 &gt; &amp;R, const VecMath::Vector&lt; 4 &gt; &amp;T)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>Transform</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>16d5190870a166c65a20c59368ca0f2f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>Project</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>b9ec4da2c4a27a95302759968c3b9d90</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>PreRedraw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>638fd2fe648c1fcd8f9a3ac03ac8f6b4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>Redraw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8d3fbc1fbe82b40046652bca8bde9605</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>RenderScene</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e0e7e693f0c2ba5afeaea265c8c21895</anchor>
      <arglist>(unsigned Frame)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>OnPaint</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e8db20fdfebe8d979f90ff303305a79d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>InitCross</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>04a35de24dbf03d029afc5d0be93ec11</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SetupDepthCue</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f46da1a68ffbcc00eddc03df078fe150</anchor>
      <arglist>(bool)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>DrawCoordinates</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>37a8191d956104629a6182ba86755cd1</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>StartAnimation</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>715dbd8c1e15f6d118853e1789d081e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>StopAnimation</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>45b036ac24d2404ad7bd69139a49b2d8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>RandomAnimation</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f33c8cf03fcfc94d4c64f9f4454b0339</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QPixmap</type>
      <name>makePixmap</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>99a55bb5dd4ba5f78e31506c55425987</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>writeFrame</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>54cf3b6bbb8bf1eed47afc6da5fcebe2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>checkAnglesForOverflow</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>0b8d96f3304d94af1bac8854c908842f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>UpdateStatus</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d37702c9ecc5cbf124df84d0263734b9</anchor>
      <arglist>(QString=&quot;&quot;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>AssignValues</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e38186ceacf6c4e6b13de7bee6cd8bda</anchor>
      <arglist>(const std::auto_ptr&lt; Function &gt; &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>Size</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>15c8ca4d71f5b5e5b07a959601820f83</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>mouseMoveEvent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>1b5e87b494b99e3705c64e924480f4ef</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>mousePressEvent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>93fd8d7586928e6cd1b0c7131bff84b2</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>mouseReleaseEvent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>00949bc8cb7215be6ff50e947d6f576f</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>mouseDoubleClickEvent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6dc432e565b97c2aa6f2273bbe4135c7</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>paintEvent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>5ff6e70d47395827f5ef14793253c8d0</anchor>
      <arglist>(QPaintEvent *)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>resizeEvent</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>5f79a84b79c832319a46af95192ad180</anchor>
      <arglist>(QResizeEvent *)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>initializeGL</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>3c797ad72f10f9d43d720a45cd60509a</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>resizeGL</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>ac3d22c30bf8b042077fb31fec2c367b</anchor>
      <arglist>(int, int)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setF</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d14af93d68b1ee2ad229076c1380079c</anchor>
      <arglist>(Function *_f)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>const std::auto_ptr&lt; Function &gt; &amp;</type>
      <name>F</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c45dda1281a8b4d8b729d451ffb5b869</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setT</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>0298fb79b894d5f9fe0c2918718fab7c</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;_t)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>const VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>T</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>5cbbef88488967558c45e960a667d822</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>addT</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>b035f874475d1ad203c17f349c041857</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;_dT)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setR</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>848ab529f41e858c486e63937f03034a</anchor>
      <arglist>(const VecMath::Rotation&lt; 4 &gt; &amp;_r)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>const VecMath::Rotation&lt; 4 &gt; &amp;</type>
      <name>R</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>94ebd881a91d0b608f4b69598ff0714f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>addR</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>1bb7c7a2df076405aadfb092e198475c</anchor>
      <arglist>(const VecMath::Rotation&lt; 4 &gt; &amp;_dR)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setdR3</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>daff8b8bdcacbd89f8cc48972a46acd3</anchor>
      <arglist>(const VecMath::Rotation&lt; 3 &gt; &amp;_dr)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>const VecMath::Rotation&lt; 3 &gt; &amp;</type>
      <name>dR3</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>4338767ea07e6fc2ed80f981525bbe54</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>adddR3</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>b3dee71322f74b46d42cbb2a7fdb60ce</anchor>
      <arglist>(const VecMath::Rotation&lt; 3 &gt; &amp;_ddr)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>setdR</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c827f1ccf2d9044f2585d8fff918b2a5</anchor>
      <arglist>(const VecMath::Rotation&lt; 4 &gt; &amp;_dr)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>const VecMath::Rotation&lt; 4 &gt; &amp;</type>
      <name>dR</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>0291884b93abb31f5aa310c10701e9c3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>adddR</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>a0f793fd49810409fc5f6f7906f2dc53</anchor>
      <arglist>(const VecMath::Rotation&lt; 4 &gt; &amp;_ddR)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_rot</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>36180772cadbb1517885c1a366aca25c</anchor>
      <arglist>(const VecMath::Rotation&lt; 3, GLdouble &gt; &amp;_r)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>const VecMath::Rotation&lt; 3, GLdouble &gt; &amp;</type>
      <name>m_rot</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>45846d7481660ac879e933d8395cf49f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>addm_rot</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>b7654a2bad6deeb87868385f3bd9c89d</anchor>
      <arglist>(const VecMath::Rotation&lt; 3, GLdouble &gt; &amp;_dmr)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_trans</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>3c8461856c1f84ed95d6f4994c69ede3</anchor>
      <arglist>(const VecMath::Vector&lt; 3, GLdouble &gt; &amp;_t)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>const VecMath::Vector&lt; 3, GLdouble &gt; &amp;</type>
      <name>m_trans</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>72ca1b3ddd5fd4dcfc1cb592d6e5c97a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>addm_trans</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>a69265d16f26ed97574de62b0a9780db</anchor>
      <arglist>(const VecMath::Vector&lt; 3, GLdouble &gt; &amp;_dmt)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setCamW</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>2e8a0ea9818d7ac4abcbd36a5f21e816</anchor>
      <arglist>(const double &amp;_cw)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>CamW</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6d87c315db886123bc697933917ce9e2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setScrW</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d4a1a6b6545c751a0e23751bff494a76</anchor>
      <arglist>(const double &amp;_sw)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>ScrW</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8afccb3859458c1f70004151ef6dff80</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setAntiAlias</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>1a313ff59f394c1260a25b2abb416add</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>AntiAlias</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>730ab9721faffb6f27132249b0dc934f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setDisplayPolygons</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f4f7dc0f9089488e57e8ab1e2a47563a</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>DisplayPolygons</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>a916a6e9d67827899cbdb5aca3757344</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setLighting</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>0224f59d0473ac8193ee6b9e42752975</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>Lighting</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>1857368e9b829c49eeb39725b5b1bd06</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setDepthCue3D</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>45f6f0d7acfcbd20597ad574797f3b56</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>DepthCue3D</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d72b329338b14cd8cd7054bd9ab6ada4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setDepthCue4D</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>4fd14d4fbbf502adf21df13c59755187</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>DepthCue4D</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>199f6bd254cc7d2bb94bc3db5fcb768e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setDisplayCoordinates</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>700df16a6a80ee40845a71ef5abe6fb2</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>DisplayCoordinates</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>0633e33f22c9442a3da080da44c95256</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setRenderToPixmap</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e907d355acbcedd3d7050afd96ed5856</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>RenderToPixmap</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>bc2d5684906652fb0b13eec75de4780b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>distance</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>41727b00738e4af7b6b746fea8230425</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setanimationDirectory</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>95739fa0b53519e4b65e6858ae7c3679</anchor>
      <arglist>(const QString &amp;b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>const QString &amp;</type>
      <name>animationDirectory</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>9608e7dd765186a37471947b934f1910</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setanimationPrefix</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8f4f98e6f315d5ed757255e9db4043e9</anchor>
      <arglist>(const QString &amp;b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>const QString &amp;</type>
      <name>animationPrefix</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>ac6d91436671898ec36765904b422b47</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setanimationFrame</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>3a857a46088bc6168ddf234eda7a3fee</anchor>
      <arglist>(unsigned b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>unsigned</type>
      <name>animationFrame</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d98270d5bafd502d5556fc1d914f5657</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setanimationMaxFrames</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>ae1eee4761e0c45ad051290289db4ff4</anchor>
      <arglist>(unsigned b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>unsigned</type>
      <name>animationMaxFrames</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>9e2861e1a13684c208a0c944108def4f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>const unsigned</type>
      <name>animation_fps</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>0199c1874cd38dde53cd85d7959d2d7f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setObjectList</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6a91ef85500b929ad9403d62cc75118e</anchor>
      <arglist>(GLint b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>GLint</type>
      <name>ObjectList</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>646e0b61e1634dacf043d20692cb33cc</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setCoordinateCross</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>ddbd7468a38ac997ba7c1741bf59a235</anchor>
      <arglist>(GLint b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>GLint</type>
      <name>CoordinateCross</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>890b368e6451af1fef597099e7399757</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setAnimated</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8f3f8549b263336dd3fe0f8a19a810e9</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>Animated</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8f09d1be7f8e3a1d8e3059cf88c5d70a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setCurrentlyRendering</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>a0ba46f4a9bdc839a90e7893156a5777</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>CurrentlyRendering</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>7abb14706e24ad8161e334879ff2c931</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setAnimationTimer</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>dd6cab0aeee3b4d28ce7077608deac9f</anchor>
      <arglist>(QTimer *b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QTimer *</type>
      <name>AnimationTimer</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>ff68ae28fb8a03868f9729df70617ffd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setAnimateRandomTimer</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>098ea4993752703e4a50a987e2e1ebde</anchor>
      <arglist>(QTimer *b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QTimer *</type>
      <name>AnimateRandomTimer</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>21fc24f013ccfbf7e5e703e60eca73ae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setValues</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>7d1b1ba0142b57801c7ee5a378a89774</anchor>
      <arglist>(ValuesDialogImpl *b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ValuesDialogImpl *</type>
      <name>Values</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>580c9d5495ed83d2d2fd6a1c771cd79a</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setMenu</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>1c93c4e74f2244fc902a32470607723a</anchor>
      <arglist>(Menu4D *b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>Menu4D *</type>
      <name>Menu</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>9fd23354578b01a6f5bb392cafea4344</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setMouseHandler</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>5fddc6a3ce9440d06dae3e8fad7e9e11</anchor>
      <arglist>(MouseHandler4D *m)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>MouseHandler4D *</type>
      <name>MouseHandler</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e33037a83f46215a8092b3c7151f421e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>SetupDepthCue</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d306f57ab4a1565454abbf7856a88a92</anchor>
      <arglist>(float, float)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>InitLight</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>03b3ed76ada1847e4b75e19de8c7e6cb</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>InitShade</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>31f530de55047a78f7f29958a4ece8a9</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>InitFog</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8e209837b51cb976674e81e6359f930d</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>InitTransparence</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>3c423447f2090b7e3e2c791f54244b02</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::auto_ptr&lt; C4DView::Impl &gt;</type>
      <name>pImpl</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>df5d54d0759ca64fc1056441f4b8b682</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; std::vector&lt; VecMath::Vector&lt; 4 &gt; &gt; &gt;</type>
      <name>Cross</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>3a944bfbcae2c13b0fcac503d62a60fe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; std::vector&lt; VecMath::Vector&lt; 4 &gt; &gt; &gt;</type>
      <name>CrossTrans</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>0eba9d6ac6f7fe31287fd728ef61266c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; std::vector&lt; VecMath::Vector&lt; 3 &gt; &gt; &gt;</type>
      <name>CrossScr</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>4b450c11b94a6dc190fd7b0e8bdb64c1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static GLfloat</type>
      <name>LightPos</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c2d8375d0e5fd3438d7806e5eadb6740</anchor>
      <arglist>[4]</arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>CustomFunctionSlot&lt; CustomFunction &gt;</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e47dce0b05c5aa8b8166aef6df650108</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>CustomFunctionSlot&lt; CustomPolarFunction &gt;</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6da5c089645fd25577a1e32f4db77d06</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>CustomFunctionSlot&lt; CustomComplexFunction &gt;</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>a8678e6fee93da8081f6a9011a1d41cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>CustomFunctionSlot&lt; CustomSurface &gt;</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>fe3d7015a7bf22b3cf3a7ad178630e2c</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>FunctionSlotHelper</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>36046b63ea701d901a03695f98246e78</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend" protection="private">
      <type>friend class</type>
      <name>SurfaceSlotHelper</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>ac8480f38ed88a738dd93173e300cd97</anchor>
      <arglist></arglist>
    </member>
    <class kind="class">C4DView::CustomFunctionSlot</class>
    <class kind="struct">C4DView::Impl</class>
    <class kind="class">C4DView::Menu4D</class>
    <class kind="class">C4DView::MouseHandler4D</class>
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
  <compound kind="struct">
    <name>C4DView::Impl</name>
    <filename>structC4DView_1_1Impl.html</filename>
    <member kind="function">
      <type></type>
      <name>Impl</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>091b6b4b5cd8c7896982cb25b0a51c8f</anchor>
      <arglist>(C4DView *parent)</arglist>
    </member>
    <member kind="variable">
      <type>Color</type>
      <name>Background</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>5a9e528b32c5c03f9cdb7529209a82bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::auto_ptr&lt; Function &gt;</type>
      <name>F</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>2b72ba34a0717cf86dd585028a8d4467</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VecMath::Vector&lt; 4 &gt;</type>
      <name>T</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>8ea4aaea895e1b93730183ce2358061e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VecMath::Rotation&lt; 4 &gt;</type>
      <name>R</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>e5ed1dd715209a6895176c4eb473e36f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VecMath::Rotation&lt; 4 &gt;</type>
      <name>dR</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>2335e837e02cd34554561045678b97b7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VecMath::Rotation&lt; 3, GLdouble &gt;</type>
      <name>m_rot</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>e1c0c06ea8688b13f4b0f42efe6e6b6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VecMath::Rotation&lt; 3, GLdouble &gt;</type>
      <name>dR3</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>4f7e166bec3acdf48961d6ca88408eaf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>VecMath::Vector&lt; 3, GLdouble &gt;</type>
      <name>m_trans</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>4a633c4d2ecbbe0fd8167831145bc42a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>CamW</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>192ba7de2db741f965b51203813ca165</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>ScrW</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>a5df6de272ca1c28d980d3ec9c46dbe5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>AntiAlias</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>a87cecbe7c47c8002f8d889c08945a04</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>DisplayPolygons</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>604ef3378d1d05fd3f87b73807a406ec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>Lighting</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>d17b279aa2f35bbdac91d616979a2fa8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>DepthCue3D</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>b8b0e1d5cc782c906c2e90fc57bf80d3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>DepthCue4D</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>eb1ae6c570224ebaede2a86653967bb7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>light</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>62c68a4cea1d88c46720b042420b84f7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>fog</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>415610beba91dc18c72783dfe3e59f35</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>transparent</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>f6801bb89643098b7ecbe44005b2df64</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>shade</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>57121e41390e2b4802cc2147e122c57f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>colors</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>acc63caf8fdd48b6c36a276a1e45da97</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>distance</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>b2b9ba9496df929ed64279da8d75ce82</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>DisplayCoordinates</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>57f39f03817730e9c45af09f8f0aef7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>RenderToPixmap</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>2c232c1a3138aa52a4ff1b3c8825eef8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QString</type>
      <name>animationDirectory</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>c3d45bf0171fe1fe3813689ffab77365</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QString</type>
      <name>animationPrefix</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>2406494efc801231c36d4c2248b09afe</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>animationFrame</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>bfbc503157adcc2e33c149c07cdb59ed</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>unsigned</type>
      <name>animationMaxFrames</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>33cb657cbba5dec230aa1e8c108af905</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const unsigned</type>
      <name>animation_fps</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>f631fff9f5b4874c5fccf00c7cc19deb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>GLint</type>
      <name>ObjectList</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>bc62e63236ebc41bc0cdb1856b701424</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>GLint</type>
      <name>CoordinateCross</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>dbe47e782fce1bed15f4719090a7302a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>Animated</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>503ce545ecd653b4e7bd9cd3ddee7dc0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>CurrentlyRendering</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>bc804963c638f50c21b36fc80b2218ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QTimer *</type>
      <name>AnimationTimer</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>bb8ef7e728ae5c058d60ed7487193e88</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QTimer *</type>
      <name>AnimateRandomTimer</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>47bcadad22a088fad759c3fb2418ebc8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>ValuesDialogImpl *</type>
      <name>Values</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>e1b669a3fcb19b2cb652fd0e33061602</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>Menu4D *</type>
      <name>menu</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>89a7c96b95f1aed9fc92460b5f159607</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>MouseHandler4D *</type>
      <name>mouseHandler</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>2459988a99bd31873a4c590e01195e19</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>C4DView::Menu4D</name>
    <filename>classC4DView_1_1Menu4D.html</filename>
    <member kind="function">
      <type></type>
      <name>Menu4D</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>1c8271d3064b6fb41f2a86934edf282a</anchor>
      <arglist>(C4DView *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>updateFunctionMenu</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>825a245cf67d222bf15c26e5cc7a70b9</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="function">
      <type>QAction *&amp;</type>
      <name>getAction</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>2dfc9833855fee3fb25d13456f47bc26</anchor>
      <arglist>(const QString &amp;key)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>addToMenuBar</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>7ffe2f1f4d1f407ef16fca9c023d4e26</anchor>
      <arglist>(QMenuBar *menuBar)</arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>std::map&lt; QString, QAction * &gt;</type>
      <name>ActionMapType</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>bb1778aa54f8b2e0663538868e82ff42</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>std::map&lt; QMenu *, ActionMapType &gt;</type>
      <name>MenuMapType</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>4ef420e40c8512de94c4386dd5437a44</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type>QAction *</type>
      <name>insertAction</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>80890e8721371e24c7039ce6598c5655</anchor>
      <arglist>(QMenu *, const QString &amp;, const char *, bool=true)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QAction *</type>
      <name>insertAction</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>12dab543031d2ebfe7420cfe9d0f21ea</anchor>
      <arglist>(QMenu *, const QString &amp;, RealFunctionFactory *, bool=true)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QAction *</type>
      <name>insertAction</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>bde326bf07a4e0b4c666c20f7bb251f2</anchor>
      <arglist>(QMenu *, const QString &amp;, SurfaceFactory *, bool=true)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>C4DView *</type>
      <name>parent</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>234a8e699bb4ddbf3a531009edac7da8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>functions</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>59dc7c822d693882212ad96f7b1dd2f9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>appear</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>754ce3faa0df6ab0107910a877d53c7c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>animation</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>104f923fca1653c1eb7566ce6ead6ea2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>help</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>6638bcc697359a93455eaf081b4718c6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>fr3r</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>7712db1a12d9b3c76dcbae852e357192</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>objects</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>32e06740a2ed447362e009d58e73d807</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>surfaces</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>2b35d3f7abd2f2a77adc8ccde8acc800</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QMenu *</type>
      <name>fcc</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>b24910c9ddbee13e10ce20f8b02be99d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>MenuMapType</type>
      <name>menuMap</name>
      <anchorfile>classC4DView_1_1Menu4D.html</anchorfile>
      <anchor>c2dd48d93e7df06a4f9725e02a1789ee</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>C4DView::MouseHandler4D</name>
    <filename>classC4DView_1_1MouseHandler4D.html</filename>
    <member kind="function">
      <type></type>
      <name>MouseHandler4D</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>b4790b3863d7d7a148236a6ae4ac91fc</anchor>
      <arglist>(C4DView *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mouseMoveEvent</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>a81a97ec93c32f1acaa142706b3b6814</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mousePressEvent</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>3fd72e434043c95051a38c2dbfccab7a</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mouseReleaseEvent</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>9e5ab5cea257501da2f87c3f13140029</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mouseDoubleClickEvent</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>681ee2ee24d1528a92b6ec0ff4dad9c2</anchor>
      <arglist>(QMouseEvent *)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_LeftDownPos</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>92d1a9fd22803c865cf152191606b43e</anchor>
      <arglist>(QPoint b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QPoint</type>
      <name>LeftDownPos</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>4a49dbaa91cad131251db04800ae3abd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_MidDownPos</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>909181777e8fc6db6c75712debfebb7f</anchor>
      <arglist>(QPoint b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QPoint</type>
      <name>MidDownPos</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>a2558a7d9a20a5d58db50ea1bcd5cc21</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_RightDownPos</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>a4f667972a1db23cccac9aed209f1bc7</anchor>
      <arglist>(QPoint b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QPoint</type>
      <name>RightDownPos</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>57f9f2674114a147356973a597b3fb81</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setTakingSpinValues</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>494cf8d0f71605be3ea5a4578ce53df5</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>TakingSpinValues</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>4c95b09d3ea40d76c2e47dc08e0998b4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>C4DView *</type>
      <name>parent</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>4b4ff1cbc3a9e85f1fd5f6daaef574ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QPoint</type>
      <name>m_LeftDownPos</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>7daa8d9f9a43f9d014dd2c3db2c1e4e6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QPoint</type>
      <name>m_MidDownPos</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>2eb10db3ada376e9cfcf8154f7191df5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QPoint</type>
      <name>m_RightDownPos</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>b199e14588f77831dedb7433ed64a074</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>bool</type>
      <name>m_TakingSpinValues</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>2200d230bd663feca709116bd4180eda</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>C4DView::TemplatedRealFunctionFactory</name>
    <filename>classC4DView_1_1TemplatedRealFunctionFactory.html</filename>
    <templarg>function</templarg>
    <base>RealFunctionFactory</base>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual RealFunction *</type>
      <name>doCreateFunction</name>
      <anchorfile>group__UIHelpers.html</anchorfile>
      <anchor>g7d01311aa80799bb82b77d0313f7bdf5</anchor>
      <arglist>(C4DView *)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>C4DView::TemplatedSurfaceFactory</name>
    <filename>classC4DView_1_1TemplatedSurfaceFactory.html</filename>
    <templarg>function</templarg>
    <base>SurfaceFactory</base>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual Surface *</type>
      <name>doCreateSurface</name>
      <anchorfile>classC4DView_1_1TemplatedSurfaceFactory.html</anchorfile>
      <anchor>e10b2482a01aacfb004d30d30cc0695b</anchor>
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
      <anchor>38a084160d7c811e71fbace3ce612806</anchor>
      <arglist>(float, float, float, float=1.)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Color</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>46c431895589d4687b45de7dc88b31bf</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;)</arglist>
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
      <type>Color</type>
      <name>operator*=</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>34ada2ca4d7d1fa7ac9b6b10dc0c4455</anchor>
      <arglist>(const Color &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Color</type>
      <name>operator*</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>2ee47ea7f9fe38c19108842e9b076ec8</anchor>
      <arglist>(float)</arglist>
    </member>
    <member kind="function">
      <type>Color</type>
      <name>operator*</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>3f50eab1d8d56ff11dd52cd4c575bd5c</anchor>
      <arglist>(const Color &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Color</type>
      <name>operator+=</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>7f623d09256dacb4996006382238f787</anchor>
      <arglist>(float)</arglist>
    </member>
    <member kind="function">
      <type>Color</type>
      <name>operator+</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>b4e82d8b087e2bdd8407351c3e3e02bb</anchor>
      <arglist>(float)</arglist>
    </member>
    <member kind="function">
      <type>Color</type>
      <name>operator+=</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>ddd202a7c9833daa6bd4ea441635dfff</anchor>
      <arglist>(const Color &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Color</type>
      <name>operator+</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>6ba5a4109c6afe40b45efc7107a9fb76</anchor>
      <arglist>(const Color &amp;)</arglist>
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
    <member kind="function">
      <type></type>
      <name>operator std::string</name>
      <anchorfile>classColor.html</anchorfile>
      <anchor>003d14e1c63981ad66238fe3d30bef7b</anchor>
      <arglist>() const </arglist>
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
    <name>ColorManager</name>
    <filename>classColorManager.html</filename>
    <member kind="function">
      <type></type>
      <name>ColorManager</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>3f622f9db654bc2899ba7e045d4b119d</anchor>
      <arglist>(const Function *_f)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setFunction</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>bb1652a9ccbced5d9bc7bda29ba6f0de</anchor>
      <arglist>(const Function *_f)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>calibrateColor</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>90923216a204fddbbf3936bb4d4f00d3</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;x, const Color &amp;col=Color())=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRGB</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>033c23a659bdba5b1897c80b7848a32f</anchor>
      <arglist>(const Color &amp;rgb)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setColor</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>57bdd15e796f3e54754e90152c05970a</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual Color</type>
      <name>getColor</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>2aeae9e387ffc3e9c74a0e17064bdce3</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;x)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>depthCueColor</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>332d02ab6a78c2c45caf8494046737b8</anchor>
      <arglist>(double wmax, double wmin, double w, const VecMath::Vector&lt; 4 &gt; &amp;x)=0</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>getContents</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>ad1a7b0968629130c33bce1d6e95028c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>std::vector&lt; Color &gt;</type>
      <name>colorvec1D</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>655a8539f21e4ccc3252fcaeb50416e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>std::vector&lt; colorvec1D &gt;</type>
      <name>colorvec2D</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>8c2eb598d222e229ca9b7d737c76aa68</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>std::vector&lt; colorvec2D &gt;</type>
      <name>colorvec3D</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>17cd311dedbbad7a800f327d5d0fc4a6</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>std::vector&lt; colorvec3D &gt;</type>
      <name>colorvec4D</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>4c7e1d50f80ad5ec9213ff6924821648</anchor>
      <arglist></arglist>
    </member>
    <member kind="typedef" protection="protected">
      <type>std::map&lt; VecMath::Vector&lt; 4 &gt;, Color &gt;</type>
      <name>colormap</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>e092ace0146c74427af31cb4ad0f0221</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double</type>
      <name>getoffset4Ddepthcue</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>208ab4fdd39c6fb598450bc597068263</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>const Function *</type>
      <name>f</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>e9121833c447573323407f2261732dc6</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>ambientColorModifier</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>0514d78a7b4503dc6938fe64e3badde0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>specularColorModifier</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>37e2146273d34e3133e6c43261106983</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>specularColorMinimum</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>01495ef2165ec65a7b1024ea7263f60d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>SHININESS</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>28a882d32d0279c35e2488548c0d827d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>ALPHA</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>338f8765ad29889ad1960158ddd4f833</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>offset4Ddepthcue</name>
      <anchorfile>classColorManager.html</anchorfile>
      <anchor>7ab03319a99e2984440ffd021a24cd5c</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ColorManagerManager</name>
    <filename>classColorManagerManager.html</filename>
    <member kind="function">
      <type>void</type>
      <name>setColorManager</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>77b2777fcd462fbf18791ca024cb4189</anchor>
      <arglist>(ColorManager *cm)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFunction</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>40c9e0ab4f9e0053e4b35583e27760de</anchor>
      <arglist>(Function *_f)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calibrateColor</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>eacae9f535f4bbe3a25f089b92c29d62</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;x, const Color &amp;_col=Color())</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setColor</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>633b88b251a718a4eb50375c7be3cbe6</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>depthCueColor</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>2a2d545b1c230e93f050385a1d3a77e6</anchor>
      <arglist>(double wmax, double wmin, double w, const VecMath::Vector&lt; 4 &gt; &amp;x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setRGB</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>6653aa733813159326436cbf365a0ad3</anchor>
      <arglist>(const Color &amp;_col)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>getContents</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>74f49fd0d9acb2485c61087fe079c63c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>ColorManagerManager</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>f98780a1f32bfd674ac45b9b8d6a5e57</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>ColorManagerManager</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>6bd01582a26740422a215bd2786c01c9</anchor>
      <arglist>(const ColorManagerManager &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>ColorManagerManager &amp;</type>
      <name>operator=</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>0ef73a2088f4ff56881d6705a2b2a118</anchor>
      <arglist>(const ColorManagerManager &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>~ColorManagerManager</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>65dc9c0778830a4cf4f5648976f0fe15</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::auto_ptr&lt; ColorManager &gt;</type>
      <name>colorManager</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>22f19f71797fdefae20c009744794381</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend class</type>
      <name>Loki::CreateUsingNew&lt; ColorManagerManager &gt;</name>
      <anchorfile>classColorManagerManager.html</anchorfile>
      <anchor>e46f47ae0dbb8ea18c47f4694c6eadc5</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ComplexDialogImpl</name>
    <filename>classComplexDialogImpl.html</filename>
    <base>PluginCreator</base>
    <member kind="function">
      <type></type>
      <name>ComplexDialogImpl</name>
      <anchorfile>classComplexDialogImpl.html</anchorfile>
      <anchor>4ff709ebd98f53e5da1b862113eb3d66</anchor>
      <arglist>(QWidget *parent=0, Qt::WFlags f=0)</arglist>
    </member>
    <member kind="slot" protection="private" virtualness="virtual">
      <type>virtual bool</type>
      <name>checkValidity</name>
      <anchorfile>classComplexDialogImpl.html</anchorfile>
      <anchor>8c0f8801288912c8374cd69441cff5db</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="private" virtualness="virtual">
      <type>virtual bool</type>
      <name>loadFunction</name>
      <anchorfile>classComplexDialogImpl.html</anchorfile>
      <anchor>3a58825ce6e3bd308916f9ca888dd91a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual bool</type>
      <name>functionPresent</name>
      <anchorfile>classComplexDialogImpl.html</anchorfile>
      <anchor>e7174b5975f212e06c53bb4f8cf965f8</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
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
      <anchor>a9df814735ac9e619569c48a5ab620dd</anchor>
      <arglist>(const QString &amp;name)</arglist>
    </member>
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
    <member kind="variable" protection="protected">
      <type>virtual RealFunction::function_type</type>
      <name>f</name>
      <anchorfile>classCustomFunction.html</anchorfile>
      <anchor>dd9350656e4c9499cdc52dc80543c9b0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>CustomFunctionBase</name>
    <filename>classCustomFunctionBase.html</filename>
    <templarg>function_type</templarg>
    <member kind="function">
      <type></type>
      <name>~CustomFunctionBase</name>
      <anchorfile>classCustomFunctionBase.html</anchorfile>
      <anchor>cb395c323a02392fb2dfb46fac141f0d</anchor>
      <arglist>()</arglist>
    </member>
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
    <member kind="variable" protection="private">
      <type>void *</type>
      <name>handle</name>
      <anchorfile>classCustomFunctionBase.html</anchorfile>
      <anchor>80f923985c3463bddc2e57ff41887d86</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
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
    <member kind="variable" protection="protected">
      <type>virtual RealFunction::function_type</type>
      <name>f</name>
      <anchorfile>classCustomPolarFunction.html</anchorfile>
      <anchor>bb24915afd71420db0befdfa164a1116</anchor>
      <arglist></arglist>
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
      <anchor>410a42e6418b05bd7afe28a5cd93d116</anchor>
      <arglist>(const ParameterMap &amp;parms)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classemz2.html</anchorfile>
      <anchor>65b0faaa192623a7b348388c728b4fad</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
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
      <anchor>fdb78abe0d9431731a523bb25f1b0de8</anchor>
      <arglist>(const ParameterMap &amp;parms)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classez.html</anchorfile>
      <anchor>9518db66e4e846eda5895791c9417fa4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
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
      <anchor>54faa047f6af1918e88f662cb5e9bd4b</anchor>
      <arglist>(const QString &amp;name, ParameterMap _parms=ParameterMap())</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>Transform</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>0a3dff00a3f82504d75f52aa4b77b676</anchor>
      <arglist>(const VecMath::Rotation&lt; 4 &gt; &amp;R, const VecMath::Vector&lt; 4 &gt; &amp;T)=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>Transform</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>1a5bdfce53f7d21a73842e19868e39de</anchor>
      <arglist>()</arglist>
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
      <anchor>3182062a98f1212d2b402b80d515444a</anchor>
      <arglist>(const ParameterMap &amp;)</arglist>
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
      <type>ParameterMap</type>
      <name>getParameters</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>44cfbb753b145fd88812b8ff749df406</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>FunctionParameter *</type>
      <name>getParameter</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>2ccf820f7363613448529ff4b8e0d89a</anchor>
      <arglist>(QString name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setParameter</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>5fdd859f7deb0f6efa36f0b22111b19d</anchor>
      <arglist>(const ParameterMap &amp;parms, T &amp;parm, const std::string &amp;key)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual const unsigned</type>
      <name>getDefinitionSpaceDimensions</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>ad8af4396ed5a8034b627cb54bf2cab2</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>operator()</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>68cf5a6e74a4f6a96893079ace0dc228</anchor>
      <arglist>(double, double, double)=0</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setVertex</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>07cc99ac6516462fbbce9aa5347ef975</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;X, VecMath::Vector&lt; 3 &gt; &amp;Xscr)</arglist>
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
    <member kind="function" protection="protected">
      <type>void</type>
      <name>declareParameter</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>a490e914a7cd65862ba7956fd558553e</anchor>
      <arglist>(const std::string &amp;, const T &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>declareParameter</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>9db0bcb6b9a829d4b64ade2666e3702f</anchor>
      <arglist>(const std::string &amp;, const T &amp;, const T &amp;)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>addVertices</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>dab9c5dfed7cfe3840ec9a28d2248327</anchor>
      <arglist>(unsigned num)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setfunctionName</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>575a3d4270fb0aa9ec4e4b433ae5bffc</anchor>
      <arglist>(const QString &amp;_name)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>insertParameter</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>04cb73563ed4bb916fe52c94b3d25a5c</anchor>
      <arglist>(const std::pair&lt; std::string, FunctionParameter * &gt; &amp;value)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>VecMath::Vector&lt; 4 &gt;</type>
      <name>F</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>3805b737129fe652314bf2603c9b7855</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned</type>
      <name>NumVertices</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>e2fe5f64785bde405df1c0c7d69bbc46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>QString</type>
      <name>functionName</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>e7491b1f17c6929f8716f07bfa5f2b46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ParameterMap</type>
      <name>parameters</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>df8416ce9302cb8d9fa27400cdaa7c3c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; std::string &gt;</type>
      <name>parameterNames</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>b312b39486784bb4ce427aec71b4722b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FunctionDialogImpl</name>
    <filename>classFunctionDialogImpl.html</filename>
    <base>PluginCreator</base>
    <member kind="function">
      <type></type>
      <name>FunctionDialogImpl</name>
      <anchorfile>classFunctionDialogImpl.html</anchorfile>
      <anchor>f1a24630efd60292e3a473d9ca447fa7</anchor>
      <arglist>(QWidget *parent=0, Qt::WFlags f=0)</arglist>
    </member>
    <member kind="slot" protection="private" virtualness="virtual">
      <type>virtual bool</type>
      <name>checkValidity</name>
      <anchorfile>classFunctionDialogImpl.html</anchorfile>
      <anchor>bab23d215be4015efddc7a173f55d65f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="private" virtualness="virtual">
      <type>virtual bool</type>
      <name>loadFunction</name>
      <anchorfile>classFunctionDialogImpl.html</anchorfile>
      <anchor>b1716ee7d7cfd63874b8f3db029db031</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual bool</type>
      <name>functionPresent</name>
      <anchorfile>classFunctionDialogImpl.html</anchorfile>
      <anchor>5c1cadd3333c5e6008b54298cce46696</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual void</type>
      <name>writeSource</name>
      <anchorfile>classFunctionDialogImpl.html</anchorfile>
      <anchor>42b371226c6719adae49e8cb7eb457b1</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FunctionFactory</name>
    <filename>classFunctionFactory.html</filename>
    <member kind="typedef">
      <type>Function *(*</type>
      <name>CreateFunctionCallback</name>
      <anchorfile>classFunctionFactory.html</anchorfile>
      <anchor>db679d773ab93bd016901031161934e4</anchor>
      <arglist>)()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>registerFunction</name>
      <anchorfile>classFunctionFactory.html</anchorfile>
      <anchor>140b292b1cb6dc9188805051a15bd14d</anchor>
      <arglist>(const std::string &amp;name, CreateFunctionCallback creator)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>unregisterFunction</name>
      <anchorfile>classFunctionFactory.html</anchorfile>
      <anchor>ef97cd2b9091900bc16cef6120114bf0</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="function">
      <type>Function *</type>
      <name>createFunction</name>
      <anchorfile>classFunctionFactory.html</anchorfile>
      <anchor>8eff61335844e102bdc76c710edd9be3</anchor>
      <arglist>(const std::string &amp;name)</arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>std::map&lt; std::string, CreateFunctionCallback &gt;</type>
      <name>CallbackMap</name>
      <anchorfile>classFunctionFactory.html</anchorfile>
      <anchor>cfd7d788dd0f22fea0f5af32ac130906</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>FunctionFactory</name>
      <anchorfile>classFunctionFactory.html</anchorfile>
      <anchor>3818fde88f978bdea66627e32b1bf4e0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>FunctionFactory</name>
      <anchorfile>classFunctionFactory.html</anchorfile>
      <anchor>aebcf7551bbe096d858f8a3825b6365d</anchor>
      <arglist>(const FunctionFactory &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>FunctionFactory &amp;</type>
      <name>operator=</name>
      <anchorfile>classFunctionFactory.html</anchorfile>
      <anchor>25a34048bb8b8e770c227328bbfa7190</anchor>
      <arglist>(const FunctionFactory &amp;)</arglist>
    </member>
    <member kind="function" protection="private">
      <type></type>
      <name>~FunctionFactory</name>
      <anchorfile>classFunctionFactory.html</anchorfile>
      <anchor>3e08c967981ee4809ffd5826d7d363c2</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>CallbackMap</type>
      <name>callbacks</name>
      <anchorfile>classFunctionFactory.html</anchorfile>
      <anchor>00d37d70c75ea68159277c4e9e299e23</anchor>
      <arglist></arglist>
    </member>
    <member kind="friend">
      <type>friend class</type>
      <name>Loki::CreateUsingNew&lt; FunctionFactory &gt;</name>
      <anchorfile>classFunctionFactory.html</anchorfile>
      <anchor>11ab13c8e070ad69bdd838ad3e9b721b</anchor>
      <arglist></arglist>
    </member>
    <class kind="class">FunctionFactory::BadFunctionException</class>
  </compound>
  <compound kind="class">
    <name>FunctionFactory::BadFunctionException</name>
    <filename>classFunctionFactory_1_1BadFunctionException.html</filename>
    <member kind="function">
      <type></type>
      <name>BadFunctionException</name>
      <anchorfile>classFunctionFactory_1_1BadFunctionException.html</anchorfile>
      <anchor>53907a4e0d6723c0228b3acd49d6789b</anchor>
      <arglist>(const std::string &amp;what)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FunctionParameter</name>
    <filename>classFunctionParameter.html</filename>
    <member kind="function">
      <type></type>
      <name>FunctionParameter</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>5a594bf8e0c0eedf04a2001d71927b86</anchor>
      <arglist>(const std::string &amp;_name, const std::string &amp;_description=&quot;&quot;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator double</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>899785f4cc806d047f4bcaa3e09c9a70</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator unsigned</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>4ceb73af54431e1baef2141349bf473d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator int</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>d0b204425a20d60acb7e05544b9f0799</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator std::string</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>888c39115a43604729e2a0bc3b3f08ec</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>getName</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>00da045a716f0605b5e3661dd9a41723</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setName</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>3641551ca2bba3cc2517d2f756c92689</anchor>
      <arglist>(const std::string &amp;_name)</arglist>
    </member>
    <member kind="function">
      <type>const std::string &amp;</type>
      <name>getDescription</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>030890057652213aa956bc0056f9bcae</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDescription</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>8854ef6b6c7e6940df332aebbaaef317</anchor>
      <arglist>(const std::string &amp;_description)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>d8923ccb1a2c9c86eadf7fd41b06d21b</anchor>
      <arglist>(FunctionParameterValue&lt; T &gt; *_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>65442a43fe7b3b230f51a99537e2a5f8</anchor>
      <arglist>(std::string _value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setDefaultValue</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>d3f0a76d63c6e62533ce95dd19ea6996</anchor>
      <arglist>(FunctionParameterValue&lt; T &gt; *_defaultValue)</arglist>
    </member>
    <member kind="function">
      <type>FunctionParameterValueBase *</type>
      <name>value</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>f79a567326e46dba8dfb1d7e96b152a5</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>FunctionParameterValueBase *</type>
      <name>defaultValue</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>e7e4eb69dc6802a52c8ccff5631a753d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Impl *</type>
      <name>pImpl</name>
      <anchorfile>classFunctionParameter.html</anchorfile>
      <anchor>76673a7d1646b068d9cf6a93601a1bff</anchor>
      <arglist></arglist>
    </member>
    <class kind="struct">FunctionParameter::Impl</class>
  </compound>
  <compound kind="struct">
    <name>FunctionParameter::Impl</name>
    <filename>structFunctionParameter_1_1Impl.html</filename>
    <member kind="function">
      <type></type>
      <name>Impl</name>
      <anchorfile>structFunctionParameter_1_1Impl.html</anchorfile>
      <anchor>7c50f0c1650f1731930b6159397f6aa0</anchor>
      <arglist>(const std::string &amp;_name, const std::string &amp;_description=&quot;&quot;)</arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>name</name>
      <anchorfile>structFunctionParameter_1_1Impl.html</anchorfile>
      <anchor>16b840c8106f594b01b12f4ee5f31c28</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::string</type>
      <name>description</name>
      <anchorfile>structFunctionParameter_1_1Impl.html</anchorfile>
      <anchor>92c0153e6275128b35743d48a956aa8c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::auto_ptr&lt; FunctionParameterValueBase &gt;</type>
      <name>value</name>
      <anchorfile>structFunctionParameter_1_1Impl.html</anchorfile>
      <anchor>fb4e9b091ed1d8133deb2a8a8451b429</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::auto_ptr&lt; FunctionParameterValueBase &gt;</type>
      <name>defaultValue</name>
      <anchorfile>structFunctionParameter_1_1Impl.html</anchorfile>
      <anchor>cfd926358184dfb5919a6c4a05100fbf</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FunctionParameterValue</name>
    <filename>classFunctionParameterValue.html</filename>
    <templarg>T</templarg>
    <base>FunctionParameterValueBase</base>
    <member kind="function">
      <type></type>
      <name>FunctionParameterValue</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>c54221790a847e86d1488242b646185e</anchor>
      <arglist>(const T &amp;_value)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setValue</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>c01e6de990697e9adf4f70302f51238c</anchor>
      <arglist>(const char *)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>operator double</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>cbf55f79789e12f6e6b78d6b9b6c7770</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>operator unsigned</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>075a19bd2e0c9d5b7ea388d415518cde</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>operator int</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>81409bf82f1e0344d1b60bb4561bad86</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual</type>
      <name>operator std::string</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>0dab8de459b02b353da7d8ec27fdf26c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>toString</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>3b678c97c0bd27b6c8589557ed6fef9f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FunctionParameterValue</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>e2194bc5225cee3551e72421889647b6</anchor>
      <arglist>(const double &amp;_value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FunctionParameterValue</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>009a90fe4349e0220e13b19ed401f7b9</anchor>
      <arglist>(const unsigned &amp;_value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FunctionParameterValue</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>cf4b754e19b5ac2deffccc852a8d1167</anchor>
      <arglist>(const int &amp;_value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FunctionParameterValue</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>685050400a470cdafcb7526dc72adaa6</anchor>
      <arglist>(const std::string &amp;_value)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator double</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>7dc6b36c669eea417f0189f9d1688061</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator unsigned</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>c8468855aebc08fb9002c29e58502d07</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator int</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>8b1d234e217e551ebd59f18d858afd5a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator std::string</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>96f986d27ac2f8abb4435c76edd7eaa3</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>dda12921a11499d00bd1d83c2ae5b9e4</anchor>
      <arglist>(const char *_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>fa656786c3651c14d646a1fcc1936835</anchor>
      <arglist>(const char *_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>164f4d976977d3d3b82f8cddd166230f</anchor>
      <arglist>(const char *_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setValue</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>0eb475fb7d67702357eb7c533adcb198</anchor>
      <arglist>(const char *_value)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>T</type>
      <name>value</name>
      <anchorfile>classFunctionParameterValue.html</anchorfile>
      <anchor>3591cc9a71f9279f11df23e075d02904</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FunctionParameterValueBase</name>
    <filename>classFunctionParameterValueBase.html</filename>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setValue</name>
      <anchorfile>classFunctionParameterValueBase.html</anchorfile>
      <anchor>926882a10c75d392d8384757d8910e68</anchor>
      <arglist>(const double &amp;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setValue</name>
      <anchorfile>classFunctionParameterValueBase.html</anchorfile>
      <anchor>c4df9f2381511249aaeeb458c4673875</anchor>
      <arglist>(const unsigned &amp;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setValue</name>
      <anchorfile>classFunctionParameterValueBase.html</anchorfile>
      <anchor>939fac5936cdc57c88e771b0de3d0c89</anchor>
      <arglist>(const int &amp;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setValue</name>
      <anchorfile>classFunctionParameterValueBase.html</anchorfile>
      <anchor>29950ca43cb1200a2197b2bca217aeaa</anchor>
      <arglist>(const std::string &amp;)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>setValue</name>
      <anchorfile>classFunctionParameterValueBase.html</anchorfile>
      <anchor>4897962d597cbdb6e464a6fe2db57182</anchor>
      <arglist>(const char *)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual</type>
      <name>operator double</name>
      <anchorfile>classFunctionParameterValueBase.html</anchorfile>
      <anchor>3b3022bc134779596c38ac8f4afa9884</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual</type>
      <name>operator unsigned</name>
      <anchorfile>classFunctionParameterValueBase.html</anchorfile>
      <anchor>1cf25f1b6bc62a4a81042a5d00aa7057</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual</type>
      <name>operator int</name>
      <anchorfile>classFunctionParameterValueBase.html</anchorfile>
      <anchor>8863252ecd7d0b17c81fb3e78453029b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual</type>
      <name>operator std::string</name>
      <anchorfile>classFunctionParameterValueBase.html</anchorfile>
      <anchor>23b42bb6bca92628fbdb0a184938352b</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual std::string</type>
      <name>toString</name>
      <anchorfile>classFunctionParameterValueBase.html</anchorfile>
      <anchor>e6671c4b7548b72f3a68248e35201e7f</anchor>
      <arglist>()=0</arglist>
    </member>
    <class kind="struct">FunctionParameterValueBase::WrongParameterTypeException</class>
  </compound>
  <compound kind="struct">
    <name>FunctionParameterValueBase::WrongParameterTypeException</name>
    <filename>structFunctionParameterValueBase_1_1WrongParameterTypeException.html</filename>
    <member kind="function">
      <type></type>
      <name>WrongParameterTypeException</name>
      <anchorfile>structFunctionParameterValueBase_1_1WrongParameterTypeException.html</anchorfile>
      <anchor>7eedebff6e87b232a010ff9de9f4c291</anchor>
      <arglist>(const std::string &amp;_class, const std::string &amp;_function, const std::string &amp;_type)</arglist>
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
      <anchor>57a1b430a1f1a4a0956ac983a134ac6b</anchor>
      <arglist>(const VecMath::Rotation&lt; 4 &gt; &amp;R, const VecMath::Vector&lt; 4 &gt; &amp;T)</arglist>
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
      <anchor>cddb72bd882ada85324313792fedfe3e</anchor>
      <arglist>(const ParameterMap &amp;parms)</arglist>
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
      <type>double</type>
      <name>atod</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>8b65c68f5a6c98885f25be5e96274b64</anchor>
      <arglist>(const std::string &amp;)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>atoi</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>9699f5a415c29ec1055b218077a53515</anchor>
      <arglist>(const std::string &amp;)</arglist>
    </member>
    <member kind="function">
      <type>unsigned</type>
      <name>atou</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>ae47a7f3539bb7925a5bf7cb8e84dec8</anchor>
      <arglist>(const std::string &amp;)</arglist>
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
    <member kind="function" static="yes">
      <type>static bool</type>
      <name>checkMemory</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>5f0781e03ce9b82997ed08cf25e67b25</anchor>
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
    <member kind="function" protection="private" static="yes">
      <type>static unsigned long</type>
      <name>check_proc_meminfo</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>ee41dfa8c3f54721609d57c58ae702d8</anchor>
      <arglist>()</arglist>
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
      <type>static bool</type>
      <name>check_memory</name>
      <anchorfile>classGlobal.html</anchorfile>
      <anchor>53d14f4c4fa1472251cb87181a021291</anchor>
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
      <anchor>111c5a6f5a4794afc529c25fd0633d5a</anchor>
      <arglist>(const ParameterMap &amp;parms)</arglist>
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
      <anchor>e405a9eaf0b835a4546aecbb48e938f5</anchor>
      <arglist>(const ParameterMap &amp;parms)</arglist>
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
      <anchor>40aaf3955e02904625d8f12d044d9ba0</anchor>
      <arglist>(const ParameterMap &amp;)</arglist>
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
      <anchor>dded3526b14b62d865242bd3075928a7</anchor>
      <arglist>(const VecMath::Vector&lt; D &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Log &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>classLog.html</anchorfile>
      <anchor>02912c0c708f37fdc42a8c9109c9a1fe</anchor>
      <arglist>(const VecMath::Rotation&lt; D &gt; &amp;)</arglist>
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
    <name>monochromeColorManager</name>
    <filename>classmonochromeColorManager.html</filename>
    <base>ColorManager</base>
    <member kind="function">
      <type></type>
      <name>monochromeColorManager</name>
      <anchorfile>classmonochromeColorManager.html</anchorfile>
      <anchor>5f0910e88338221cbb34d1b297be169b</anchor>
      <arglist>(Function *_f)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calibrateColor</name>
      <anchorfile>classmonochromeColorManager.html</anchorfile>
      <anchor>cbd6eb12fe0079c69c69e8f0786dba64</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;, const Color &amp;=Color())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Color</type>
      <name>getColor</name>
      <anchorfile>classmonochromeColorManager.html</anchorfile>
      <anchor>7293c2517301681e819f2de8a6d78fec</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>depthCueColor</name>
      <anchorfile>classmonochromeColorManager.html</anchorfile>
      <anchor>c0bef6fd1532d68ddf08e97841201758</anchor>
      <arglist>(double, double, double, const VecMath::Vector&lt; 4 &gt; &amp;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>NotYetImplementedException</name>
    <filename>classNotYetImplementedException.html</filename>
    <member kind="function">
      <type></type>
      <name>NotYetImplementedException</name>
      <anchorfile>classNotYetImplementedException.html</anchorfile>
      <anchor>a674914f24f27aeece822be597dfb583</anchor>
      <arglist>(const std::string &amp;what)</arglist>
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
      <anchor>16adc37b6a48b1113858b60b861eb1c1</anchor>
      <arglist>(const VecMath::Rotation&lt; 4 &gt; &amp;R, const VecMath::Vector&lt; 4 &gt; &amp;T)</arglist>
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
    <member kind="function" virtualness="virtual">
      <type>virtual const unsigned</type>
      <name>getDefinitionSpaceDimensions</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>ddc7550215a7aa8cf5dd0522ef8fbf24</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected" virtualness="virtual">
      <type>virtual void</type>
      <name>Initialize</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>abb0df155c83971e135cc13f9fc28860</anchor>
      <arglist>()</arglist>
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
      <type>uintvec2D</type>
      <name>Surface</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>febafa6727a1d46aaf384fba88f31c1a</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ParameterFac</name>
    <filename>classParameterFac.html</filename>
    <member kind="function">
      <type>FunctionParameter *</type>
      <name>createParameterWithValue</name>
      <anchorfile>classParameterFac.html</anchorfile>
      <anchor>e842a045da1f9aae0510bbc98ae2d87f</anchor>
      <arglist>(const std::string &amp;_name, const T &amp;_value)</arglist>
    </member>
    <member kind="function">
      <type>FunctionParameter *</type>
      <name>createParameterWithDefault</name>
      <anchorfile>classParameterFac.html</anchorfile>
      <anchor>9957bbda7ea380b6165fe372d6108459</anchor>
      <arglist>(const std::string &amp;_name, const T &amp;_default, const std::string &amp;_description=&quot;&quot;)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>ParameterMap</name>
    <filename>classParameterMap.html</filename>
    <member kind="function">
      <type></type>
      <name>ParameterMap</name>
      <anchorfile>classParameterMap.html</anchorfile>
      <anchor>33cc5a5bf52240a71869e3740a7136e9</anchor>
      <arglist>(const std::string &amp;_name1, const T1 &amp;_value1)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>insertByValue</name>
      <anchorfile>classParameterMap.html</anchorfile>
      <anchor>c520b76e3dad195c928cb86610504210</anchor>
      <arglist>(const std::string _name, const T &amp;_value)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>insertByDefault</name>
      <anchorfile>classParameterMap.html</anchorfile>
      <anchor>424c66976d4797d7d4941ca9a6789db6</anchor>
      <arglist>(const std::string _name, const T &amp;_default)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>print</name>
      <anchorfile>classParameterMap.html</anchorfile>
      <anchor>10ef7c40dd90a134dbc35881dc18f168</anchor>
      <arglist>() const </arglist>
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
    <member kind="function" protection="private" virtualness="pure">
      <type>virtual bool</type>
      <name>loadFunction</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>934c4708ba3cf6054982d9b0b67e29d2</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" protection="private" virtualness="pure">
      <type>virtual bool</type>
      <name>functionPresent</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>72d965933b305fe25e9e27b9ab88fbb6</anchor>
      <arglist>(const QString &amp;)=0</arglist>
    </member>
    <member kind="function" protection="private" virtualness="pure">
      <type>virtual void</type>
      <name>writeSource</name>
      <anchorfile>classPluginCreator.html</anchorfile>
      <anchor>a951c5e85ecfdc22750cb5485c9d5b9e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="variable" protection="private">
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
    <member kind="function">
      <type></type>
      <name>PolarDialogImpl</name>
      <anchorfile>classPolarDialogImpl.html</anchorfile>
      <anchor>32ef3773ec9a225a0d8760b187d65788</anchor>
      <arglist>(QWidget *parent=0, Qt::WFlags f=0)</arglist>
    </member>
    <member kind="slot" protection="private" virtualness="virtual">
      <type>virtual bool</type>
      <name>checkValidity</name>
      <anchorfile>classPolarDialogImpl.html</anchorfile>
      <anchor>cf9f33255a1bd65a1b70475d5fc4f1a8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="private" virtualness="virtual">
      <type>virtual bool</type>
      <name>loadFunction</name>
      <anchorfile>classPolarDialogImpl.html</anchorfile>
      <anchor>e3a5c9fcd53a63338439b8ffbca02673</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual bool</type>
      <name>functionPresent</name>
      <anchorfile>classPolarDialogImpl.html</anchorfile>
      <anchor>6c55103e9be8f4068223c07934bcdcc0</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
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
      <anchor>1aefb2a16b71009f29dfa25d9ada912c</anchor>
      <arglist>(const ParameterMap &amp;parms)</arglist>
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
      <anchor>026c7ea056660e31972d3dd1062b2e92</anchor>
      <arglist>(const ParameterMap &amp;parms)</arglist>
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
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classPolynomial.html</anchorfile>
      <anchor>d77ec1bc3e000fc8d3443f5513f58c6a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
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
      <anchor>29d24610dababa3905aad2b8979a0612</anchor>
      <arglist>(const ParameterMap &amp;parms)</arglist>
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
      <anchor>8eb03b17160d1e764c0a8478b2288087</anchor>
      <arglist>(const QString &amp;name, double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, ParameterMap _parms=ParameterMap())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>unsigned &amp;</type>
      <name>getTsteps</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>13591cf37427643c8cab25ab5e8b05f5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>unsigned</type>
      <name>getTsteps</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>f90219771ce266c7ba1d6c023de1738c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>unsigned &amp;</type>
      <name>getUsteps</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>484ca78d73b9140e77dc26d626e90b88</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>unsigned</type>
      <name>getUsteps</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>c7101b04df485fc9a240a3f8415565fb</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>unsigned &amp;</type>
      <name>getVsteps</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>4c12bdcab988ba1efa81d7f23504bc9d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>unsigned</type>
      <name>getVsteps</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>011340c0780ac35ac47d952b60d244b2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getTmin</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>f9dcdf6e54c56a0875afa605bbfafff7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double</type>
      <name>getTmin</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>ab7b6a824d9a14bbb69b053642c99da4</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getTmax</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>371a8545cd85a218efa8c3d78f1679f7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double</type>
      <name>getTmax</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>b801bd043b8d2794670c20644f0c6ec3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getDt</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>a738a408ed73025d34db4ff0c4779ce1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const double &amp;</type>
      <name>getDt</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>4794a8d2423eb369a9e81f94b87cc4d6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getUmin</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>94d43f8cf311879c3d773bfceb9e04f4</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double</type>
      <name>getUmin</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>aaaf57dd55e89edc4e2594f3a54fe3c3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getUmax</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>ee1bc70a4396db3d9bbeb814c78e4ad0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double</type>
      <name>getUmax</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>e3b239f475b66574841441fb690afc4b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getDu</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>d8aa90547179197a84a55b11fa9efb59</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const double &amp;</type>
      <name>getDu</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>1d0d918a17594766d3e8719db4fc7aa9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getVmin</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>f79ee0c5a0488dddd613e65f9676b240</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double</type>
      <name>getVmin</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>da09536f21f52c76f604239aa7e5f3e9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getVmax</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>1ef508c14939017bf1a7f6953cb76069</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double</type>
      <name>getVmax</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>6a1028eba092d9744d48dac6dd5bfd77</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getDv</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>04608c269de0bb85c988f6f55c246631</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const double &amp;</type>
      <name>getDv</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>59bc0981ccdb81bae78967aa5e2cba6c</anchor>
      <arglist>() const </arglist>
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
    <member kind="variable" protection="protected" static="yes">
      <type>static double</type>
      <name>_min</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>69b1d39dab04f315703a3f3f86d1831c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static double</type>
      <name>_max</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>e63cc6ce43e4ece54428359bd8f0ae3d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static double</type>
      <name>_d</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>82f7d3dc2bbbc26555adc0601b6ec9a9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>tmin</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>b84a54ebbddb2ef66a966d604a794004</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>tmax</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>12f40b3a53fda939ff49f6913f0fba57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>dt</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>9ebc541377f753e2585c75596736dd94</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>umin</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>0a0937c7e34bfadc7acff910aed34013</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>umax</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>ae14faf7733494cac03756bdc3fe97a3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>du</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>588a2f75f5063d1986250286f961d045</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>vmin</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>d5b8a969bbaab56c26c94029d43cde71</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>vmax</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>4aa3f46c74d1e7c61a2133256250e050</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>dv</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>199b3186b86de13bfbaf00e826fa4c88</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned</type>
      <name>tsteps</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>c7d28d04a85a31d48fbacea6015f1ecf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned</type>
      <name>usteps</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>249797c5787aab5193d5af2e331ebb55</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned</type>
      <name>vsteps</name>
      <anchorfile>classRealBase.html</anchorfile>
      <anchor>3bed522cd7e0be600a9a796ccbd97b3c</anchor>
      <arglist></arglist>
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
      <anchor>b5572815bf1f02373e5fdfa5c0db300a</anchor>
      <arglist>(const QString &amp;name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>RealFunction</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>330968d75b1e8da0d272360e278799e1</anchor>
      <arglist>(const QString &amp;name, double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, ParameterMap _parms=ParameterMap())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Transform</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>dbbc82deb59fbfddd400cb4cc1a003ee</anchor>
      <arglist>(const VecMath::Rotation&lt; 4 &gt; &amp;R, const VecMath::Vector&lt; 4 &gt; &amp;T)</arglist>
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
    <member kind="function" virtualness="virtual">
      <type>virtual const unsigned</type>
      <name>getDefinitionSpaceDimensions</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>8a125d9751f338ec77d2251b82070d4b</anchor>
      <arglist>()</arglist>
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
      <type>VecMath::Vector&lt; 4 &gt;</type>
      <name>F</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>da001f73d52d3267762aed76256be0a9</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>RealFunctionFactory</name>
    <filename>classRealFunctionFactory.html</filename>
    <member kind="function">
      <type>RealFunction *</type>
      <name>createFunction</name>
      <anchorfile>classRealFunctionFactory.html</anchorfile>
      <anchor>054d9494dc6d5fa9d5c3f00d3e4e49c2</anchor>
      <arglist>(C4DView *view)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="pure">
      <type>virtual RealFunction *</type>
      <name>doCreateFunction</name>
      <anchorfile>classRealFunctionFactory.html</anchorfile>
      <anchor>aebf53e0e1747c6499455f4c284a83ae</anchor>
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
      <anchor>29a107d06398fd830afbb95ffb9098b2</anchor>
      <arglist>(unsigned _level=1, unsigned _distance=2, double _rad=0.8, VecMath::Vector&lt; 4 &gt; _center=VecMath::Vector&lt; 4 &gt;(0., 0., 0., 0.))</arglist>
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
      <anchor>c7f51aa2dcec81e24eda7f4fa1c617a9</anchor>
      <arglist>(const VecMath::Rotation&lt; 4 &gt; &amp;R, const VecMath::Vector&lt; 4 &gt; &amp;T)</arglist>
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
      <anchor>b379dd05d2113837b3101a4b7881715a</anchor>
      <arglist>(const ParameterMap &amp;parms)</arglist>
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
    <member kind="function" protection="protected" virtualness="pure">
      <type>virtual VecMath::Vector&lt; 4 &gt; &amp;</type>
      <name>f</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>184943a51b4ee95fa8fa09b01593ab01</anchor>
      <arglist>(double, double)=0</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>a</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>ef043dfe1e1798290f3745ddac512240</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>umin</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>a9926ddc4cde4aecccdc19cfc5801fc4</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>umax</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>f1e55a6bbdad3b19a981e9f3e8c4772f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>du</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>fbd1a8e0e4376c491c5e811adb4d5a41</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>vmin</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>a05d2007e03fd3669ff1be419ed537bc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>vmax</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>c4583620d0b428836d217db5ca0789fc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>dv</name>
      <anchorfile>classSteinerFunction.html</anchorfile>
      <anchor>89e75493dbbf5d12a6f87afc6263e0b5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
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
      <anchor>32fe9c7b6029853daf1da215601db5ed</anchor>
      <arglist>(const QString &amp;name)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Surface</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>f077894496ec8e23cade9cb9c3249738</anchor>
      <arglist>(const QString &amp;name, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, ParameterMap _parms=ParameterMap())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>Transform</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>fd09e20917d1089019851ea52f1fb49c</anchor>
      <arglist>(const VecMath::Rotation&lt; 4 &gt; &amp;R, const VecMath::Vector&lt; 4 &gt; &amp;T)</arglist>
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
    <member kind="function">
      <type>vec4vec2D</type>
      <name>Data</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>94d03f3097e1478093dd3a286f987562</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual const unsigned</type>
      <name>getDefinitionSpaceDimensions</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>5e4c6538614d4e5451c95e11cc6c9ebd</anchor>
      <arglist>()</arglist>
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
      <anchor>c39f68676d595d0b684c3c71f2aa72f1</anchor>
      <arglist>(const QString &amp;name, double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, ParameterMap _parms=ParameterMap())</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>unsigned &amp;</type>
      <name>getTsteps</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>761208b17975a6c343774b5ca467ed2b</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>unsigned</type>
      <name>getTsteps</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>5fd7997c43e9ffd31e2fbaab27eff772</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>unsigned &amp;</type>
      <name>getUsteps</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>d8c79625fa46d8c5ebbda58f0dd9eb5d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>unsigned</type>
      <name>getUsteps</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>6d8a3275a973b95be291716078904e54</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getTmin</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>73cd034a8689e0f9fbd796f8e7423fcb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double</type>
      <name>getTmin</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>331f915b27e433bdbcae7b23a6f95150</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getTmax</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>ac9069441800f0bbf3b85b9a7839f56f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double</type>
      <name>getTmax</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>487414ac55576adcd49b1931be389f76</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getDt</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>c1b7c91a12ac9ad433c27d8ad9f6067c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const double &amp;</type>
      <name>getDt</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>3a9373910f81b3893cc21c809ea69436</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getUmin</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>ed7d2013bca3eb15eb1abcc8e72cbd58</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double</type>
      <name>getUmin</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>abc4aff7e78d1de3add2d54f53c9f6f0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getUmax</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>5097c9fd6cd4955c2b7b29d4ed7b46bb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double</type>
      <name>getUmax</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>53633255335f97b61c5fe101f2e32dc1</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="protected">
      <type>double &amp;</type>
      <name>getDu</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>b374ba3db9a0339e6a5aaa230d1a76ca</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>const double &amp;</type>
      <name>getDu</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>7586cb2be4de82c7c9f1d55c3aa31986</anchor>
      <arglist>() const </arglist>
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
    <member kind="variable" protection="protected" static="yes">
      <type>static double</type>
      <name>_min</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>1574b2795a87891cb5d1d6245ca85ca2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static double</type>
      <name>_max</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>e25019065a91adde8916a96a93176a19</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static double</type>
      <name>_d</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>5bea58758ccf0f1a96bf1f916d479ad3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>tmin</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>fa8c885abae834903a65501324167924</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>tmax</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>b92843a431802d31e4fb5437c0ef5bec</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>dt</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>246a9dc0b6ae2741e5de384201b271fd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>umin</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>2527a0ad8040bdb3df8f9f19e85b18a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>umax</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>f2bdc4afb299c0aef8f8191ce465da25</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>double</type>
      <name>du</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>9b643ee7520fbeed4d99d69499f9f3e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned</type>
      <name>tsteps</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>eb5312872b3069a6f9c72c04a62f7942</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>unsigned</type>
      <name>usteps</name>
      <anchorfile>classSurfaceBase.html</anchorfile>
      <anchor>f50dc3d9bea41ab2db26b1b91586eab7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>SurfaceDialogImpl</name>
    <filename>classSurfaceDialogImpl.html</filename>
    <base>PluginCreator</base>
    <member kind="function">
      <type></type>
      <name>SurfaceDialogImpl</name>
      <anchorfile>classSurfaceDialogImpl.html</anchorfile>
      <anchor>65e1b1a5403b060c4fc10c657643491c</anchor>
      <arglist>(QWidget *parent=0, Qt::WFlags f=0)</arglist>
    </member>
    <member kind="slot" protection="private" virtualness="virtual">
      <type>virtual bool</type>
      <name>checkValidity</name>
      <anchorfile>classSurfaceDialogImpl.html</anchorfile>
      <anchor>c550d0adc24a6184822c8f0949f2dde8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="private" virtualness="virtual">
      <type>virtual bool</type>
      <name>loadFunction</name>
      <anchorfile>classSurfaceDialogImpl.html</anchorfile>
      <anchor>ad946f3182546f50ee84ae134d1196f1</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
      <type>virtual bool</type>
      <name>functionPresent</name>
      <anchorfile>classSurfaceDialogImpl.html</anchorfile>
      <anchor>157da54702f3a3731db11480a83d5b93</anchor>
      <arglist>(const QString &amp;)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="virtual">
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
    <member kind="function">
      <type>Surface *</type>
      <name>createSurface</name>
      <anchorfile>classSurfaceFactory.html</anchorfile>
      <anchor>46af73cb10b7c9d5254ea04215b2b38f</anchor>
      <arglist>(C4DView *view)</arglist>
    </member>
    <member kind="function" protection="private" virtualness="pure">
      <type>virtual Surface *</type>
      <name>doCreateSurface</name>
      <anchorfile>classSurfaceFactory.html</anchorfile>
      <anchor>418e211e91fc1b9bf517ef02ff4afc10</anchor>
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
      <anchor>c8d5faf8d43130e3aa8b0f58cffbab0e</anchor>
      <arglist>(const ParameterMap &amp;parms)</arglist>
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
      <anchor>eff2372bb43c897676949bd3d21cc92f</anchor>
      <arglist>(const ParameterMap &amp;parms)</arglist>
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
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>f</name>
      <anchorfile>classTorus3.html</anchorfile>
      <anchor>4b7e1986731243f42ba630be199a3327</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ui_ValuesDialog</name>
    <filename>classUi__ValuesDialog.html</filename>
    <member kind="function">
      <type>void</type>
      <name>setupUi</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>c3f35fcc3a053a5fd7d5c6972d072a7c</anchor>
      <arglist>(QDialog *ValuesDialog)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>retranslateUi</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>6e4192b89d585bbab3e1f03a0094027b</anchor>
      <arglist>(QDialog *ValuesDialog)</arglist>
    </member>
    <member kind="variable">
      <type>QWidget *</type>
      <name>layoutWidget</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>7ce2942af559fd9c0ce23621c0f769a2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QVBoxLayout *</type>
      <name>vboxLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>e83c454c1e13c61d3bb2f7ce1c05def0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QGroupBox *</type>
      <name>Grid</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>55a284a814f4c77ee1aff25ae023e7ce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QGridLayout *</type>
      <name>gridLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>4cabc3bf035e33ec8f63ec3e5f52d595</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>937f5b063063229bc2efd61f201fc917</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>TLabel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>df15da5b3e56ac116dd2cb1adde67724</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QSlider *</type>
      <name>TSlider</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>7a1d12dc830feae4457fe732698aa7d8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>TSteps</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>ff54a284c847b823a2107678fe3e5e57</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout1</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>96d7e7d12dfd94836344517044c8f282</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout2</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>8b85642c26756ee265b43652756c9898</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>TextLabel12</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>c854e1feb18409494b0efa63a5c25bdb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLineEdit *</type>
      <name>TMin</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>199c990023e9204f56e0b5cf521ab696</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout3</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>0d953398e34878e763ae9e3b7062d82b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>TextLabel11</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>473f5db97f0bf79fa3bef02e57490811</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLineEdit *</type>
      <name>TMax</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>ffe42cda468dee2608fad3e527d0222e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout4</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>45aeaa86574ea0de2f1ee0cce755e091</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>ULabel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>5aa3e3930bd101f135572c778534917a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QSlider *</type>
      <name>USlider</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>85b86034f26c7c1c205ffb45fe06fe8d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>USteps</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>da09975156384aa303eb2c4a78cb6700</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout5</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>52fb462742cc2a31f7ee4bf7d392b5f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout6</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>2ace4469873d6f5de0c62106fd222fa2</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>TextLabel12_2</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>8777e34c24107164afdb2a256b483f46</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLineEdit *</type>
      <name>UMin</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>90b5e6c1744098b439145b1dce07fa6e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout7</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>f240efc78c57df3daabe60eef0afe494</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>TextLabel11_2</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>250da7643642260be7892fe96bd56190</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLineEdit *</type>
      <name>UMax</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>cc47d392c4ba3b3fae1bba4f30e601c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout8</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>54a5e7fa03d342e3a93bd844e12dbf37</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>VLabel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>332f7a107b607d33352249b8442abb98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QSlider *</type>
      <name>VSlider</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>ca86af89757b4fbad6917e5d386b4bb8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>VSteps</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>b9838c99fe6c9d527e6a546504e909f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout9</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>8adcaade3f319fb2bcfea46ad611e6cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout10</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>ae454ffcffe2ade02f5c78e1d56616e3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>TextLabel12_2_2</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>7afedf526683c39ef8f5d875600046c8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLineEdit *</type>
      <name>VMin</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>3ed2361475ec310caa31ae7f49e191bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout11</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>b443432e6102d3fbbd7007a2a7c65eb5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>TextLabel11_2_2</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>3fa692acf363088d626861c73234939c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLineEdit *</type>
      <name>VMax</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>3fdd1149f205ad0e7d930580cecccc98</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QGroupBox *</type>
      <name>Function</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>d9f19cf3468051bbd8afde1d71c7e431</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QGridLayout *</type>
      <name>gridLayout1</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>3a1c6384782e9f4644bbb96e656d891e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>TextLabel13</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>1da2db6780d47e0c9953775592a82ad5</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QComboBox *</type>
      <name>FunctionBox</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>953f1789f3408c7527d114adf3f8d4b0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QVBoxLayout *</type>
      <name>vboxLayout1</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>bc0fe68eba06398ac2c2e48610b3aa95</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout12</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>713f42d09751223932ec5cc9c7dc3511</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout13</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>cccbfbe1db9d9c49e8c026f654257075</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>ALabel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>a191886f92d64ec1e014817e524358a0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLineEdit *</type>
      <name>A</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>2bb72b733958971b982ceb269b988d63</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout14</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>18ccda14e24d55f582a57caa1ec2f83b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>BLabel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>434ef2db91aa11fa8e67c373d29149dd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLineEdit *</type>
      <name>B</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>606babe3461172ab85f4d21a17a7df70</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout15</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>dfbe366c27f841475c7ae434d0bbeb5d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout16</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>0b9bdf2ca713824732eff993c8d59779</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>CLabel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>cec9df3bc9d167decb532e31e95d0762</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLineEdit *</type>
      <name>C</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>322bd32464ddd0209bebd0dedf1a8abc</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout17</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>015403b822699bae82da47b2211893b1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLabel *</type>
      <name>DLabel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>3e911621e133dc69130ad9a79e9713cd</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QLineEdit *</type>
      <name>D</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>1b25ab0791e849a83f429560b2403fee</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QHBoxLayout *</type>
      <name>hboxLayout18</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>df89338658e79cdf65ceda64bd0e69e8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPushButton *</type>
      <name>buttonApply</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>a957950d35fd0e2d4507f6791c17445a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPushButton *</type>
      <name>buttonOk</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>361a4d4ddb0e157519e232900fbec056</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPushButton *</type>
      <name>buttonCancel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>2b9e8e63267275699acc2e2ab91028f5</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>setupUi</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>c3f35fcc3a053a5fd7d5c6972d072a7c</anchor>
      <arglist>(QDialog *ValuesDialog)</arglist>
    </member>
    <member kind="function" protection="protected">
      <type>void</type>
      <name>retranslateUi</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>6e4192b89d585bbab3e1f03a0094027b</anchor>
      <arglist>(QDialog *ValuesDialog)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QGridLayout *</type>
      <name>gridLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>4cabc3bf035e33ec8f63ec3e5f52d595</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QVBoxLayout *</type>
      <name>AllBoundsLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>9e3fc0351aba9dcb72e40263a7f7236e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QVBoxLayout *</type>
      <name>AllParametersLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>79d3f994025217bbcc4b0db4c48e2357</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QHBoxLayout *</type>
      <name>ButtonLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>c9ea0916517c721266508b172ccff27d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QLabel *</type>
      <name>gridLabel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>0ba92dabf82c45401a131f7fd57242eb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QHBoxLayout *</type>
      <name>SliderLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>a34663ae2d36e10c2641f99120de1ffe</anchor>
      <arglist>[maxNumDimensions]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QHBoxLayout *</type>
      <name>BoundsLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>ca700dc2aae888abb4df382893cb834c</anchor>
      <arglist>[maxNumDimensions]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QHBoxLayout *</type>
      <name>MinLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>7f2230719cc87a195e5957ed0c82dc79</anchor>
      <arglist>[maxNumDimensions]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QHBoxLayout *</type>
      <name>MaxLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>9a1c3c546faa262cfe699c3938d2153e</anchor>
      <arglist>[maxNumDimensions]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QLabel *</type>
      <name>Label</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>850cd035e55450f40ac38b8bc5983dfd</anchor>
      <arglist>[maxNumDimensions]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QSlider *</type>
      <name>Slider</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>bbe855cfb32300bd78e4f6d5207336bb</anchor>
      <arglist>[maxNumDimensions]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QLabel *</type>
      <name>Steps</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>2ad387bdf5db5cf0d8fcc67e3d1a30cb</anchor>
      <arglist>[maxNumDimensions]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QLabel *</type>
      <name>MinLabel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>fc7323911b6726a0619b65efbaac2763</anchor>
      <arglist>[maxNumDimensions]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QLineEdit *</type>
      <name>Min</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>194fef6d5840168a5b7aae997f94046f</anchor>
      <arglist>[maxNumDimensions]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QLabel *</type>
      <name>MaxLabel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>27bf7aa79b5aabd2501a062f5f2fa0b8</anchor>
      <arglist>[maxNumDimensions]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QLineEdit *</type>
      <name>Max</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>0aed3c74e3407f3055447820f3cd86f1</anchor>
      <arglist>[maxNumDimensions]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QLabel *</type>
      <name>functionLabel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>64c5680f8034342c68839ba741605b66</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QHBoxLayout *</type>
      <name>ParameterLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>83926ed6f547464131e51d917b52cd2e</anchor>
      <arglist>[maxNumParameters]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QHBoxLayout *</type>
      <name>ParameterLineLayout</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>45340192c4fee6156dd523613cd3daca</anchor>
      <arglist>[maxNumParameters/parametersPerLine]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QLabel *</type>
      <name>ParameterLabel</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>e4cf1325fab23285a024abb372659ceb</anchor>
      <arglist>[maxNumParameters]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QLineEdit *</type>
      <name>Parameter</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>7212d408a6136ef3d6c9d7ed7fbbb00e</anchor>
      <arglist>[maxNumParameters]</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QPushButton *</type>
      <name>buttonApply</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>a957950d35fd0e2d4507f6791c17445a</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static const unsigned</type>
      <name>maxNumDimensions</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>96a5028f3e1b19ed10bc3b89d8602df3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static const unsigned</type>
      <name>maxNumParameters</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>1b4d3fca097cbc53827db8f18e33638b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected" static="yes">
      <type>static const unsigned</type>
      <name>parametersPerLine</name>
      <anchorfile>classUi__ValuesDialog.html</anchorfile>
      <anchor>9ec22f0535ebacd6dfd57d2790dd9eb7</anchor>
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
    <member kind="signal">
      <type>void</type>
      <name>ApplyChanges</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>0f3255a2cc79da4c6bb523da32809699</anchor>
      <arglist>(const ParameterMap &amp;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>ValuesDialogImpl</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>da76fef88c056d9145243be54f61a53a</anchor>
      <arglist>(QWidget *parent=0, Qt::WFlags f=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setFunction</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>51d28c2eca2e1e35f5aaaab4cceca1be</anchor>
      <arglist>(const std::auto_ptr&lt; Function &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>std::string</type>
      <name>print</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>c584b775af4ba6df4f5d86f55fd8d969</anchor>
      <arglist>()</arglist>
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
    <member kind="function" protection="private">
      <type>void</type>
      <name>setParameters</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>9c8ed70c102c1a781f00888c0e3c0f5b</anchor>
      <arglist>(const ParameterMap &amp;)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>ParameterMap</type>
      <name>parameters</name>
      <anchorfile>classValuesDialogImpl.html</anchorfile>
      <anchor>786bc88cfdd8ee561de2d99c98a97cb7</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>xyz2RGBColorManager</name>
    <filename>classxyz2RGBColorManager.html</filename>
    <base>ColorManager</base>
    <member kind="function">
      <type></type>
      <name>xyz2RGBColorManager</name>
      <anchorfile>classxyz2RGBColorManager.html</anchorfile>
      <anchor>5293efc1140fb401853a55fe097d6228</anchor>
      <arglist>(Function *_f)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>setFunction</name>
      <anchorfile>classxyz2RGBColorManager.html</anchorfile>
      <anchor>0a4bba66a9e813a45c81af287d80fb42</anchor>
      <arglist>(Function *_f)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>calibrateColor</name>
      <anchorfile>classxyz2RGBColorManager.html</anchorfile>
      <anchor>e234f6fc5aa3de4bb185675542ac821e</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;x, const Color &amp;_col=Color())</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual Color</type>
      <name>getColor</name>
      <anchorfile>classxyz2RGBColorManager.html</anchorfile>
      <anchor>87c08aa7c7f3a1f23488ae2cba90aad6</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;x)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>depthCueColor</name>
      <anchorfile>classxyz2RGBColorManager.html</anchorfile>
      <anchor>df18ce7e156627c77546e17833c0b4b6</anchor>
      <arglist>(double wmax, double wmin, double w, const VecMath::Vector&lt; 4 &gt; &amp;)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual std::string</type>
      <name>getContents</name>
      <anchorfile>classxyz2RGBColorManager.html</anchorfile>
      <anchor>80a3f3ccffbabf566ecf1d197d1959b8</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" protection="private">
      <type>Color</type>
      <name>computeColorFromNeighbors</name>
      <anchorfile>classxyz2RGBColorManager.html</anchorfile>
      <anchor>028115852304ac06d6dbb58a1544ab5f</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;x)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>std::pair&lt; std::vector&lt; VecMath::Vector&lt; 4 &gt; &gt;, std::vector&lt; double &gt; &gt;</type>
      <name>findClosestPoints</name>
      <anchorfile>classxyz2RGBColorManager.html</anchorfile>
      <anchor>3f2868b3d5889c2ea4118acd67f0f28e</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;, unsigned=5)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>Color</type>
      <name>averageColors</name>
      <anchorfile>classxyz2RGBColorManager.html</anchorfile>
      <anchor>aa571f6a1aeefd51b4fe88f766c0d7d8</anchor>
      <arglist>(const std::vector&lt; Color &gt; &amp;)</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>colormap</type>
      <name>col</name>
      <anchorfile>classxyz2RGBColorManager.html</anchorfile>
      <anchor>eb8683f850c9d79dc8911e0ecb8e01e8</anchor>
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
      <anchor>0e9efa24072615db758fe995335926be</anchor>
      <arglist>(const ParameterMap &amp;parms)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>virtual function_type</type>
      <name>g</name>
      <anchorfile>classzA.html</anchorfile>
      <anchor>5576b7c32870c9b5204415db7120d8e0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
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
    <name>Script::Parser</name>
    <filename>classScript_1_1Parser.html</filename>
    <member kind="function">
      <type></type>
      <name>Parser</name>
      <anchorfile>classScript_1_1Parser.html</anchorfile>
      <anchor>5b7cf8cb8670b41d7e9a98af70a4efd3</anchor>
      <arglist>(const std::string &amp;file)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>execute</name>
      <anchorfile>classScript_1_1Parser.html</anchorfile>
      <anchor>bd95bf7b3ac6458ec9b57e1a312f52e5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setView</name>
      <anchorfile>classScript_1_1Parser.html</anchorfile>
      <anchor>96ffff7b1d30842573439ba8c3ae7936</anchor>
      <arglist>(UI::View *_view)</arglist>
    </member>
    <member kind="function">
      <type>UI::View *</type>
      <name>getView</name>
      <anchorfile>classScript_1_1Parser.html</anchorfile>
      <anchor>9688b748587eb90de82009e704b24783</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="variable" protection="private">
      <type>std::vector&lt; std::string &gt;</type>
      <name>lines</name>
      <anchorfile>classScript_1_1Parser.html</anchorfile>
      <anchor>948c1f2a111017d6e1e17b71fbc4fb23</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="private">
      <type>UI::View *</type>
      <name>view</name>
      <anchorfile>classScript_1_1Parser.html</anchorfile>
      <anchor>7753442ef190b5860be24c8f18c90b24</anchor>
      <arglist></arglist>
    </member>
    <class kind="class">Script::Parser::BadCommandException</class>
  </compound>
  <compound kind="namespace">
    <name>VecMath</name>
    <filename>namespaceVecMath.html</filename>
    <class kind="class">VecMath::Matrix</class>
    <class kind="struct">VecMath::NumAxes</class>
    <class kind="struct">VecMath::NumAxes&lt; 0 &gt;</class>
    <class kind="struct">VecMath::NumAxes&lt; 1 &gt;</class>
    <class kind="class">VecMath::RotationAxes</class>
    <class kind="class">VecMath::RotationAxes&lt; 3 &gt;</class>
    <class kind="class">VecMath::RotationAxes&lt; 4 &gt;</class>
    <class kind="class">VecMath::Rotation</class>
    <class kind="class">VecMath::Vector</class>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g66177497b2b0c964a01d7be1087cdf17</anchor>
      <arglist>(std::ostream &amp;o, const Rotation&lt; D, N &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>std::istringstream &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g481900ade75f6885f522982564e1f702</anchor>
      <arglist>(std::istringstream &amp;in, Rotation&lt; D, N &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>std::ostream &amp;</type>
      <name>operator&lt;&lt;</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>gef433144f359a8cda43c2290871425b3</anchor>
      <arglist>(std::ostream &amp;o, const Vector&lt; D, N &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>std::istringstream &amp;</type>
      <name>operator&gt;&gt;</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g32efe5289273edf4fcd804d59be355b8</anchor>
      <arglist>(std::istringstream &amp;in, Vector&lt; D, N &gt; &amp;v)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D &gt;</type>
      <name>cross</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g65ec0cbac29ab530c63be146545c5532</anchor>
      <arglist>(const Vector&lt; D &gt; &amp;, const Vector&lt; D &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D &gt;</type>
      <name>cross</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g7025733deb7fc498f87ffdf8ceb93fab</anchor>
      <arglist>(const Vector&lt; D &gt; &amp;, const Vector&lt; D &gt; &amp;, const Vector&lt; D &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; 3, N &gt;</type>
      <name>vcross</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>gebb474b1869607dba1cd231e786a169d</anchor>
      <arglist>(Vector&lt; 3, N &gt; a, Vector&lt; 3, N &gt; b)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; 4, N &gt;</type>
      <name>vcross</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>gbdc5bc1e998587a215aff0c5a1a7b95d</anchor>
      <arglist>(Vector&lt; 4, N &gt; a, Vector&lt; 4, N &gt; b, Vector&lt; 4, N &gt; c)</arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>vnormalize</name>
      <anchorfile>group__VecMath.html</anchorfile>
      <anchor>g646679fba90010325c01c937abfb4ea4</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;x)</arglist>
    </member>
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
      <anchor>10a5a2dc0327ce50af18806a39e2faa0</anchor>
      <arglist>(unsigned i, unsigned j)</arglist>
    </member>
    <member kind="function">
      <type>Matrix&lt; D, N &gt;</type>
      <name>operator*=</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>fa87544cf9d0fc24402203d649ceb78b</anchor>
      <arglist>(const Matrix&lt; D, N &gt; &amp;)</arglist>
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
      <anchor>da1563139030bb5272c300bf6eaa06d1</anchor>
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
    <member kind="variable" protection="private">
      <type>N</type>
      <name>M</name>
      <anchorfile>classVecMath_1_1Matrix.html</anchorfile>
      <anchor>b05a96df5ab732804b596f5e34d3216b</anchor>
      <arglist>[D][D]</arglist>
    </member>
  </compound>
  <compound kind="struct">
    <name>VecMath::NumAxes</name>
    <filename>structVecMath_1_1NumAxes.html</filename>
    <templarg>D</templarg>
  </compound>
  <compound kind="struct">
    <name>VecMath::NumAxes&lt; 0 &gt;</name>
    <filename>structVecMath_1_1NumAxes_3_010_01_4.html</filename>
  </compound>
  <compound kind="struct">
    <name>VecMath::NumAxes&lt; 1 &gt;</name>
    <filename>structVecMath_1_1NumAxes_3_011_01_4.html</filename>
  </compound>
  <compound kind="class">
    <name>VecMath::RotationAxes</name>
    <filename>classVecMath_1_1RotationAxes.html</filename>
    <templarg>D</templarg>
    <member kind="function" static="yes">
      <type>static unsigned</type>
      <name>axis</name>
      <anchorfile>classVecMath_1_1RotationAxes.html</anchorfile>
      <anchor>903766b44203be27c2dcff5ef1c36053</anchor>
      <arglist>(unsigned which, unsigned index)</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static unsigned</type>
      <name>_axis</name>
      <anchorfile>classVecMath_1_1RotationAxes.html</anchorfile>
      <anchor>3bc210e4cd84f708c856e9d665cce3c5</anchor>
      <arglist>[2][NumAxes&lt; D &gt;::num]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VecMath::RotationAxes&lt; 3 &gt;</name>
    <filename>classVecMath_1_1RotationAxes_3_013_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static unsigned</type>
      <name>axis</name>
      <anchorfile>classVecMath_1_1RotationAxes_3_013_01_4.html</anchorfile>
      <anchor>538bfadcb7566eafbca392ddfaa89216</anchor>
      <arglist>(unsigned which, unsigned index)</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const unsigned</type>
      <name>_axis</name>
      <anchorfile>classVecMath_1_1RotationAxes_3_013_01_4.html</anchorfile>
      <anchor>1c7ca6cd3f6e35ea44eabd7fe4fad7d9</anchor>
      <arglist>[2][3]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VecMath::RotationAxes&lt; 4 &gt;</name>
    <filename>classVecMath_1_1RotationAxes_3_014_01_4.html</filename>
    <member kind="function" static="yes">
      <type>static unsigned</type>
      <name>axis</name>
      <anchorfile>classVecMath_1_1RotationAxes_3_014_01_4.html</anchorfile>
      <anchor>86e63c1c4efbe7198c03b69c67c3d79f</anchor>
      <arglist>(unsigned which, unsigned index)</arglist>
    </member>
    <member kind="variable" protection="private" static="yes">
      <type>static const unsigned</type>
      <name>_axis</name>
      <anchorfile>classVecMath_1_1RotationAxes_3_014_01_4.html</anchorfile>
      <anchor>b806e7ab482981b81d6ce27b6b2b7d5a</anchor>
      <arglist>[2][6]</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VecMath::Rotation</name>
    <filename>classVecMath_1_1Rotation.html</filename>
    <templarg>D</templarg>
    <templarg>N</templarg>
    <member kind="function">
      <type></type>
      <name>Rotation</name>
      <anchorfile>classVecMath_1_1Rotation.html</anchorfile>
      <anchor>381bea6da84c7a729c369ae5f00d84a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Rotation</name>
      <anchorfile>classVecMath_1_1Rotation.html</anchorfile>
      <anchor>8169627c23d4ecf6f8d5724a9310a8e8</anchor>
      <arglist>(N r0,...)</arglist>
    </member>
    <member kind="function">
      <type>N &amp;</type>
      <name>operator[]</name>
      <anchorfile>classVecMath_1_1Rotation.html</anchorfile>
      <anchor>983895e87df442fd68885cddac8bbb20</anchor>
      <arglist>(unsigned i)</arglist>
    </member>
    <member kind="function">
      <type>N</type>
      <name>operator[]</name>
      <anchorfile>classVecMath_1_1Rotation.html</anchorfile>
      <anchor>790e96010114d3219cf7452676389e74</anchor>
      <arglist>(unsigned i) const </arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator Matrix&lt; D, N &gt;</name>
      <anchorfile>classVecMath_1_1Rotation.html</anchorfile>
      <anchor>bada28b04afd16a77c258079463174fd</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Rotation&lt; D, N &gt; &amp;</type>
      <name>operator+=</name>
      <anchorfile>classVecMath_1_1Rotation.html</anchorfile>
      <anchor>8094dd821ed9d37dfa162d05750adbe7</anchor>
      <arglist>(const Rotation&lt; D, N &gt; &amp;)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>operator bool</name>
      <anchorfile>classVecMath_1_1Rotation.html</anchorfile>
      <anchor>7171fc9dc7023d1449d50e084265a57c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>const Vector&lt; NumAxes&lt; D &gt;::num, N &gt; &amp;</type>
      <name>r</name>
      <anchorfile>classVecMath_1_1Rotation.html</anchorfile>
      <anchor>c7a3ce61bbe973efb8724e32b5aab83b</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; NumAxes&lt; D &gt;::num, N &gt; &amp;</type>
      <name>r</name>
      <anchorfile>classVecMath_1_1Rotation.html</anchorfile>
      <anchor>c9f51647938734894ebeb55309fa55eb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable" protection="private">
      <type>Vector&lt; NumAxes&lt; D &gt;::num, N &gt;</type>
      <name>axis</name>
      <anchorfile>classVecMath_1_1Rotation.html</anchorfile>
      <anchor>234ba7e9e05403d496d5a50d9cee3334</anchor>
      <arglist></arglist>
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
      <anchor>63640f08c7793bf37aedf32e552499dd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Vector</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>35fecd02f35c28da27d509468fae1fef</anchor>
      <arglist>(N x0,...)</arglist>
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
      <anchor>a68deef6f47c2f6550ca05ce7f8bb11c</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator-</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>9d760206780943e36381f022da5ac047</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;Y) const </arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator*</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>1c92fee3076d3f646e97df2f5f246726</anchor>
      <arglist>(const N &amp;s) const </arglist>
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
      <anchor>5b21cec75070d6f476cf4217d4db3d01</anchor>
      <arglist>(const N &amp;s) const </arglist>
    </member>
    <member kind="function">
      <type>Vector&lt; D, N &gt;</type>
      <name>operator/</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>2034516bcdac81c123d76d1018a5ed47</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;X) const </arglist>
    </member>
    <member kind="function">
      <type>N</type>
      <name>sqnorm</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>c60183f68f2d8a6473c64c2e753cd053</anchor>
      <arglist>(void) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator==</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>b6e7503d7c1b1f58f59d2fd08ba3396a</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;other) const </arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>operator&lt;</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>101c57864da2145be32e255919ef1845</anchor>
      <arglist>(const Vector&lt; D, N &gt; &amp;other) const </arglist>
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
    <member kind="variable" protection="private">
      <type>N</type>
      <name>x</name>
      <anchorfile>classVecMath_1_1Vector.html</anchorfile>
      <anchor>1ede34e2355b2471d895426042351176</anchor>
      <arglist>[D]</arglist>
    </member>
  </compound>
</tagfile>