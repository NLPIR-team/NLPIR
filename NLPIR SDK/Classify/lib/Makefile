CFLAGS = -g -fPIC -c -DNER_PERSON -DPOS_TAGGER -DENGLISH_PARSER_INCLUDED -DOS_LINUX 
LDFLAGS = -g -fPIC -Wall -shared

LJClassifier.so:LJClassifier.o TextParser.o License.o Global.o global_linux.o Utility.o Encript.o Profile.o XMLParamReader.o PDAT.o
	g++ $(LDFLAGS) -o ../../bin/Classifier/libLJClassifier.so *.o    
	rm -rf *.o
	
LJClassifier.o: ../../Src/Classifier/API/LJClassifier.cpp   ../../Src/Classifier/API/LJClassifier.h
	g++ $(CFLAGS)  ../../Src/Classifier/API/LJClassifier.cpp  $(LDFLAGS)

TextParser.o: ../../Src/Classifier/API/TextParser.cpp   ../../Src/Classifier/API/TextParser.h
	g++ $(CFLAGS)  ../../Src/Classifier/API/TextParser.cpp  $(LDFLAGS)
	
License.o: ../../Src/License/License.cpp  ../../Src/License/License.h
	g++ $(CFLAGS) ../../Src/License/License.cpp  $(LDFLAGS)

Global.o: ../../Src/Utility/Global.cpp ../../Src/Utility/Global.h
	g++ $(CFLAGS) ../../Src/Utility/Global.cpp  $(LDFLAGS)
	 
global_linux.o: ../../Src/Utility/global_linux.cpp ../../Src/Utility/global_linux.h
	g++ $(CFLAGS) ../../Src/Utility/global_linux.cpp  $(LDFLAGS)

Utility.o: ../../Src/Utility/Utility.cpp ../../Src/Utility/Utility.h
	g++ $(CFLAGS) ../../Src/Utility/Utility.cpp  $(LDFLAGS)
	
Encript.o: ../../Src/Encript/*.cpp ../../Src/Encript/*.h
	g++ $(CFLAGS) ../../Src/Encript/*.cpp  $(LDFLAGS)
	
Profile.o: ../../Src/Utility/Profile.cpp ../../Src/Utility/Profile.h
	g++ $(CFLAGS) ../../Src/Utility/Profile.cpp  $(LDFLAGS)
		
XMLParamReader.o: ../../Src/Utility/XMLParamReader.cpp ../../Src/Utility/XMLParamReader.h
	g++ $(CFLAGS) ../../Src/Utility/XMLParamReader.cpp  $(LDFLAGS)
	
PDAT.o: ../../Src/Utility/PDAT.cpp ../../Src/Utility/PDAT.h
	g++ $(CFLAGS) ../../Src/Utility/PDAT.cpp  $(LDFLAGS)

all:libLJClassifier.so
clean:
	rm -f *.o  ../../bin/Classifier/libLJClassifier.so
	
	
