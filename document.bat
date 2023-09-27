
mkdir graphic
cd src/server
dir /B /S *.c > ../../graphic/cscope.files
cd ../../graphic
cscope -b -c -R
tceetree -F
dot -Tpng -o full-with-library.png -Granksep="3.5 equally" tceetree.out
tceetree -F -x LIBRARY
dot -Tpng -Grankdir=LR -o full-no-library.png tceetree.out
tceetree -F -x LIBRARY -r Process
dot -Tpng -Grankdir=LR -o process.png tceetree.out 
cd ..
copy graphic\full-with-library.png docs
copy graphic\full-no-library.png docs
copy graphic\process.png docs
rmdir /S /Q graphic

doxygen .
cd docs\doxygen\latex
make 
cd ../../..
copy docs\doxygen\latex\refman.pdf .
rename refman.pdf server-reference-manual.pdf



