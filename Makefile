
adaline:
	g++ src/adaline/main.cpp -o bin/adaline

329:
	g++ src/329/main.cpp -o bin/329 

git:
	git add -A
	git commit -m "$(msg)"
	git push

