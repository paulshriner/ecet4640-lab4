
@REM mkdir graphic
@REM cd src/server
@REM dir /B /S *.c > ../../graphic/cscope.files
@REM cd ../../graphic
@REM cscope -b -c -R
@REM tceetree -F
@REM dot -Tpng -o full-with-library.png -Granksep="3.5 equally" tceetree.out
@REM tceetree -F -x LIBRARY
@REM dot -Tpng -Grankdir=LR -o full-no-library.png tceetree.out
@REM tceetree -F -x LIBRARY -r Process
@REM dot -Tpng -Grankdir=LR -o process.png tceetree.out 
@REM cd ..
@REM copy graphic\full-with-library.png docs
@REM copy graphic\full-no-library.png docs
@REM copy graphic\process.png docs
@REM rmdir /S /Q graphic

doxygen
copy docs\LatexORMakefile docs\doxygen\latex
cd docs\doxygen\latex
del Makefile
rename LatexORMakefile Makefile
make 
cd ..\..\..
copy docs\doxygen\latex\refman.pdf .
del server-reference-manual.pdf
rename refman.pdf server-reference-manual.pdf



