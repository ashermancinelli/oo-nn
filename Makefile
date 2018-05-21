
adaline1:
	g++ src/adaline/ex1.cpp -o bin/adaline1

adaline2:
	g++ src/adaline/ex2.cpp -o bin/adaline2

329:
	g++ src/329/main.cpp -o bin/329 

git:
	git add -A
	git commit -m "$(msg)"
	git push

