# 2012-12-05 Wed 14:33

javac=c:/java/jdk16/bin/javac.exe
java=c:/java/jdk16/bin/java.exe -cp .

clr:
	# To compile cormen 2e source
	$(javac) com/mhhe/clrs2e/*.java
	$(java)  com.mhhe.clrs2e.Main
	$(javac) drivers/*.java

clr-test::
	for i in drivers/*Test.java ;do \
	  j=$$(basename $$i) ; \
	  j=$${j%%.*} ;\
	  echo "{{""{ file=$$i; $(java) -cp '.;drivers' $$j" ;\
	  $(java) -cp '.;drivers' $$j ;\
	  echo "}}""} done=$$i" ;\
	done

clean::
	# cmd /c "del /s *.class",
	find . | grep -Pins '[.](class|obj|o|pyc|exe)$$' || true
	echo "Some classes should be kept, clean it manually"

tags::
	ctags -R .
