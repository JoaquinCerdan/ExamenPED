# Historial de versiones
# 2.0 (17/03/2020): corregido un error que hacía que la práctica no se recompilara para algunos ficheros de prueba
#
fallos=0;
aciertos=0;
total=0;

#Si tus ficheros de prueba no comienzan por "tad", cambia "tad*.cpp" por el prefijo de tus ficheros, por ejemplo "prueba*.cpp":
for FILE in *PRUEBA/tad*.cpp ; do
	echo "Evaluando $FILE"
	#Si tu Makefile espera que el fichero que contiene el programa principal se llame tad.cpp, cambia la siguiente línea por: cp $FILE src/tad.cpp
	cp $FILE src/main.cpp
        rm -f ./main
	make
	./main > $FILE.out
	diff -b -B -i $FILE.out $FILE.sal
	if [ "$?" == "0" ]; then
		echo "OK"
		let aciertos++;
		let total++;
	else
		echo "ERROR"
		let fallos++;
		let total++;
	fi
done

echo "====Práctica====";
echo "ACIERTOS: $aciertos";
echo "FALLOS: $fallos";
echo "TOTAL: $total"
