test:
	g++ testing.cpp pattern.cpp -o bin/test

329:
	g++ sample3-29.cpp -o bin/329 

git:
	git add -A
	git commit -m "$(msg)"
	git push
