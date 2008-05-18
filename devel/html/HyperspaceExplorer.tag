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
      <anchor>g7c3727e6f85bbbc52c0ef4cb1e1658c3</anchor>
      <arglist>(std::ostream &amp;o, const Vector&lt; D, N &gt; &amp;v)</arglist>
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
    <member kind="slot" protection="private">
      <type>void</type>
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
      <anchor>6850e75dd5a38a4ffc5d0a1f7bcb953d</anchor>
      <arglist>(double Rxy, double Rxz, double Rxw, double Ryz, double Ryw, double Rzw, double Tx, double Ty, double Tz, double Tw)</arglist>
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
      <name>Draw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>87493fb1f2d39371ddfd024f72676738</anchor>
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
      <name>setTx</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e6d27d13f4e169b7ba6203cf10cd08f1</anchor>
      <arglist>(double _tx)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>Tx</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>cf7fca5cb78ed435055ccbacab93e51e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setTy</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8e0f09a698bfa92f7e4bf75b270be67a</anchor>
      <arglist>(double _ty)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>Ty</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>20ec201e10f5a3e76a9b071f2900265d</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setTz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c1a15b4c56306bbb8157049edef25c7a</anchor>
      <arglist>(double _tz)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>Tz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f99d31e1df2f9069919598b2b31cb495</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setTw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>7d93c2b8c48bfb21dfb5f5383b84cb4f</anchor>
      <arglist>(double _tw)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>Tw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c7a93e4d63610136ec22a9af86990859</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setRxy</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e2e46dc3d53e72447a11f040e5477c03</anchor>
      <arglist>(double _rxy)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>Rxy</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6f769626e4d0e126282954abc0c73734</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setRxz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8a6943794325e4f984e992d667f9cf07</anchor>
      <arglist>(double _rxz)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>Rxz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>25c82f3ad246130d42a6a4776eabd72f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setRxw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>698394604236878bf9e8ed3dca76e975</anchor>
      <arglist>(double _rxw)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>Rxw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>737938c6d8722fb9a91f1fe9ce21514f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setRyz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>ab90430afd25a72bc169d3b3aa0c250a</anchor>
      <arglist>(double _ryz)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>Ryz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>11f24a60e5070320706c7a5147ed60c2</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setRyw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>420f87a177c3ca407a587c93f21c205f</anchor>
      <arglist>(double _ryw)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>Ryw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8f6ad32931b1b97ac4078d14b086a527</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setRzw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>a21cbaae3f7a94f18d713b118c053c78</anchor>
      <arglist>(double _rzw)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>Rzw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6e08d2a51cae63b80eb8c2db0c9376a9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_rotX</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e4dbc60f5bf18c45b79c7bd4b334b2e8</anchor>
      <arglist>(GLdouble _rx)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>GLdouble</type>
      <name>m_rotX</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>68dc52d5b2768320bff1cf6f78781ea6</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_rotY</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>7c59355a48c452868fca1610ea9c03b9</anchor>
      <arglist>(GLdouble _ry)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>GLdouble</type>
      <name>m_rotY</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>8358e725f97742d9429bdc9efc1f723f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_rotZ</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d0f8fd9c379911caeefc5d414eaed56d</anchor>
      <arglist>(GLdouble _rz)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>GLdouble</type>
      <name>m_rotZ</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>94ace7c9efc400f8738df4dae6c57ce7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_transX</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f1e7cf5da5fccc21af9ab992836d86d2</anchor>
      <arglist>(GLdouble _tx)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>GLdouble</type>
      <name>m_transX</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c40cbc6b3915cd1a9d95d8e29d7025d0</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_transY</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>64921961bdf98613e0b95a57aa644560</anchor>
      <arglist>(GLdouble _ty)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>GLdouble</type>
      <name>m_transY</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>946dff919e5cee23d259b01f73147d15</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_camZ</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c15f3ca75d9a94905505fe1fb9762278</anchor>
      <arglist>(GLdouble _cz)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>GLdouble</type>
      <name>m_camZ</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d81387b19cafe382cb8d3d6b2f420089</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setCamW</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6ff2213ad71877b3f2fad7cb4c3a32f7</anchor>
      <arglist>(double _cw)</arglist>
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
      <anchor>1d0a3b31ee9c199b02913a652d6d24a2</anchor>
      <arglist>(double _sw)</arglist>
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
      <name>R</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>26801e5f73e83593acc84edca4c3633c</anchor>
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
      <name>setTakingSpinValues</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>4d2bf540116bd55ad652af9ab6e41771</anchor>
      <arglist>(bool b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>bool</type>
      <name>TakingSpinValues</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>bc459a8072808527f7d6b211607559c7</anchor>
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
      <name>setm_LeftDownPos</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>04c0d34323df6ee2c7c5452b10f71a60</anchor>
      <arglist>(QPoint b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QPoint</type>
      <name>m_LeftDownPos</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c9c62ea844bce89c29e857f4db5a792c</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_MidDownPos</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>52600c452ca185b1ff95e718f74fcd0f</anchor>
      <arglist>(QPoint b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QPoint</type>
      <name>m_MidDownPos</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>c4889572f3aaff13a4505d96a53928b7</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setm_RightDownPos</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>a339da52e1d88c3ed8ea6595dae47f95</anchor>
      <arglist>(QPoint b)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>QPoint</type>
      <name>m_RightDownPos</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>2af17ec8f9f5cad05a400674347681d2</anchor>
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
      <name>setdxy</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>103dce7821b45de1ed01aab87ce5cff5</anchor>
      <arglist>(double _dxy)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>dxy</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>d0d0c0349cdebe561167afb10616a2d3</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setdxz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>81895ce965d669c72b581b096e9361ea</anchor>
      <arglist>(double _dxz)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>dxz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>e5688525c3f229997a75e7985fa18d50</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setdxw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>090a0c31178adbd4098b3aed7c47f390</anchor>
      <arglist>(double _dxw)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>dxw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>80dd4db75726e18632345c7728d47575</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setdyz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>a7ebb92d9f8e36dd35fb1679ea4e133b</anchor>
      <arglist>(double _dyz)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>dyz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>bf96e00d889be3e09f1d625451dab6db</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setdyw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>efb7a3489f852f8743c697f1d528a9b3</anchor>
      <arglist>(double _dyw)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>dyw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>db5a2e8f63177c47986106e14ca4c23e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setdzw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>4fa3d2afb0187c84d1e20b9f65a1df4c</anchor>
      <arglist>(double _dzw)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>dzw</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6ce4b0fce30fd409e706bf27b0361f83</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setdx</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>6bce184901b5eddbad60ece1b7f7d87c</anchor>
      <arglist>(double _dx)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>dx</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>0162fb95e2d5ced3e37b0f86c10d3969</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setdy</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>15a8dd0be3e2c708f1b63bb6e75d68de</anchor>
      <arglist>(double _dy)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>dy</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>b36c0cfffcb51062077a1e2d3668ea31</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" protection="private">
      <type>void</type>
      <name>setdz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>f936ff8b1416421636d673b2e3c76a5a</anchor>
      <arglist>(double _dz)</arglist>
    </member>
    <member kind="function" protection="private">
      <type>double</type>
      <name>dz</name>
      <anchorfile>classC4DView.html</anchorfile>
      <anchor>a47638011e3cb283af57adc01b950195</anchor>
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
      <type>double</type>
      <name>Tx</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>2e1143497ad771f69bcb3d84dc246481</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>Ty</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>937aadc3e51aae5700e29ad458bd687d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>Tz</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>dd7a50748d2af8908e789ba36abe7a56</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>Tw</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>ae0c647bf77277c24b87f6778486ee7f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>Rxy</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>95e1e5a5659fc6294cc11d8974374568</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>Rxz</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>8b23d83333a629cfe2330f93f4296d84</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>Rxw</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>4110a883dea58c1363a01d005b09e838</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>Ryz</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>89befdf3246e15700f49a71f1aabf55f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>Ryw</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>44cabd1baae3cd26314cc2704d7e5072</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>Rzw</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>1e786f009cd6f1bdeafe04125d6f3b6f</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>GLdouble</type>
      <name>m_rotX</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>6d4dc4785b3f4df70c06fbd7b5f5a3ca</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>GLdouble</type>
      <name>m_rotY</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>7e79a5f10abb48f382e9328276498a62</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>GLdouble</type>
      <name>m_rotZ</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>40a4ebb84315eb8a2c317b0be1b0e4bb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>GLdouble</type>
      <name>m_transX</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>4567faca093019bde9867d55de2f8625</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>GLdouble</type>
      <name>m_transY</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>d0ecc29a9ded087986e3c0d56ad85c9d</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>GLdouble</type>
      <name>m_camZ</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>521db46a3b0832b8c8b292ac633c0b00</anchor>
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
      <name>R</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>4c6c3408be332c0ecd3fada7f5f48da0</anchor>
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
      <name>TakingSpinValues</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>dcef4d021c507cdc6f480f9443d51f31</anchor>
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
      <type>bool</type>
      <name>CurrentlyRendering</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>bc804963c638f50c21b36fc80b2218ea</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPoint</type>
      <name>m_LeftDownPos</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>8ff8393a464478cf529951c19dff44f1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPoint</type>
      <name>m_MidDownPos</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>4a9199ba2e973c40f797654cbe0255c7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QPoint</type>
      <name>m_RightDownPos</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>63db7a403af416fb7a7ecad4ee2722e1</anchor>
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
      <type>double</type>
      <name>dxy</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>77df73669d8fcb91a99044f1de33dc83</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>dxz</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>808548b90412c3438a0d02d6e8298ac9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>dxw</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>83cad34eb72145b76e341fea812e1dce</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>dyz</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>f309fef6ba57c3bb007f4f6689244da8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>dyw</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>d06ace5af4bdf95b0871734cf07d09e9</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>dzw</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>578ef768e98dea6f4e03110f0a0db050</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>dx</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>b8e9095492654d33b17505717b978766</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>dy</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>50ca24efb925fc7353043a9ef163879c</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>double</type>
      <name>dz</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>11a5c6bb318df27e85b3deb79b64c3e7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; std::vector&lt; VecMath::Vector&lt; 4 &gt; &gt; &gt;</type>
      <name>Cross</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>a2836b5138de91ead6dbc02156e4b03b</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; std::vector&lt; VecMath::Vector&lt; 4 &gt; &gt; &gt;</type>
      <name>CrossTrans</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>8a102fbc9feaa7234b3943476274f093</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>std::vector&lt; std::vector&lt; VecMath::Vector&lt; 3 &gt; &gt; &gt;</type>
      <name>CrossScr</name>
      <anchorfile>structC4DView_1_1Impl.html</anchorfile>
      <anchor>447ba1ee42cf7280a27bf117e85eeb92</anchor>
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
    <member kind="variable">
      <type>C4DView *</type>
      <name>parent</name>
      <anchorfile>classC4DView_1_1MouseHandler4D.html</anchorfile>
      <anchor>4b4ff1cbc3a9e85f1fd5f6daaef574ea</anchor>
      <arglist></arglist>
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
      <anchor>73489c44daa1263138b2b22a782e9c53</anchor>
      <arglist>(const VecMath::Vector&lt; 4 &gt; &amp;)=0</arglist>
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
      <type>virtual unsigned</type>
      <name>getDefinitionSpaceDimensions</name>
      <anchorfile>classFunction.html</anchorfile>
      <anchor>734029fa5358d5c59bd908d98d084256</anchor>
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
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned</type>
      <name>getTsteps</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>1788b64f26f2e0b0dde1bc9d745a1e9f</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned</type>
      <name>getUsteps</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>233a5ba3e17eb319db356c300132ba85</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned</type>
      <name>getVsteps</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>1aa24c774545e7ff55b1aad7f3fce385</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>getTmin</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>77b54e5622f0036cac520dcf954b5bc9</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>getTmax</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>0a6a405664a329b2b5d0322ea3731b2e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>getUmin</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>0d905217992272a7066284511dea0d38</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>getUmax</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>77d8b699bae8111631611ce526da2f53</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>getVmin</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>bd4d6ba639eda9b45c722cf80c0be416</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual double</type>
      <name>getVmax</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>907226e84b30073b27326c86874aa53e</anchor>
      <arglist>() const </arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned</type>
      <name>getDefinitionSpaceDimensions</name>
      <anchorfile>classObject.html</anchorfile>
      <anchor>715df52e786f724d8978510873327ecf</anchor>
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
      <anchor>330968d75b1e8da0d272360e278799e1</anchor>
      <arglist>(const QString &amp;name, double _tmin, double _tmax, double _dt, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, ParameterMap _parms=ParameterMap())</arglist>
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
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned</type>
      <name>getDefinitionSpaceDimensions</name>
      <anchorfile>classRealFunction.html</anchorfile>
      <anchor>d50fe9ea4ae88d2ed607d82efffec735</anchor>
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
      <anchor>f077894496ec8e23cade9cb9c3249738</anchor>
      <arglist>(const QString &amp;name, double _umin, double _umax, double _du, double _vmin, double _vmax, double _dv, ParameterMap _parms=ParameterMap())</arglist>
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
    <member kind="function">
      <type>vec4vec2D</type>
      <name>Data</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>94d03f3097e1478093dd3a286f987562</anchor>
      <arglist>(void)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual unsigned</type>
      <name>getDefinitionSpaceDimensions</name>
      <anchorfile>classSurface.html</anchorfile>
      <anchor>40887c0b67ecc005cbc181ccda034cc0</anchor>
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
    <class kind="union">Loki::CreateStatic::MaxAlign</class>
  </compound>
  <compound kind="class">
    <name>Loki::SingletonHolder</name>
    <filename>classLoki_1_1SingletonHolder.html</filename>
    <templarg>T</templarg>
    <templarg>CreationPolicy</templarg>
    <member kind="typedef">
      <type>T</type>
      <name>ObjectType</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>2e995720b0baebf24b7cd5501099d80c</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" static="yes">
      <type>static T &amp;</type>
      <name>Instance</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>52a113a9dc9aa53a5ab777c573f9fa28</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="typedef" protection="private">
      <type>T *</type>
      <name>PtrInstanceType</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>26a6ec9e3019fc2f8406c5b3c03f0791</anchor>
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
      <type>static void</type>
      <name>DestroySingleton</name>
      <anchorfile>classLoki_1_1SingletonHolder.html</anchorfile>
      <anchor>fa306d4e67df281b85b0c932cf5186c6</anchor>
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
