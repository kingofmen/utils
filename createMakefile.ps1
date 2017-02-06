if (Test-Path utils.pro) {
  rm utils.pro
}
rm Makefile.*

$UBDIRS = @("geometry", "dice")
$PARENT = $PWD
$DIRS = ""
$QMAKE = "c:\Qt\5.5\mingw492_32\bin\qmake"

Foreach ($Dir in $UBDIRS) {
  cd $Dir
  &$QMAKE -project -norecursive -t lib "QMAKE_CXXFLAGS+= -Wno-unused-local-typedefs" "QMAKE_CXXFLAGS+=-std=c++11" -o "$Dir.pro"
  &$QMAKE -makefile "INCLUDEPATH+=C:\Users\Rolf\Desktop\boost_1_54_0" "LIBS+=-static-libgcc"
  $DIRS += "$PARENT\$Dir "
  cd $PARENT
}

&$QMAKE -project -t subdirs "QMAKE_CXXFLAGS+= -Wno-unused-local-typedefs" "QMAKE_CXXFLAGS+=-std=c++11" -o utils.pro -nopwd $DIRS
&$QMAKE -makefile -r "INCLUDEPATH+=C:\Users\Rolf\Desktop\boost_1_54_0" "LIBS+=-static-libgcc"
