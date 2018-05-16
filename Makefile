test:
	g++ testing.cpp pattern.cpp -o bin/test

git:
	git add -A
	git commit -m "$(msg)"
	git push
