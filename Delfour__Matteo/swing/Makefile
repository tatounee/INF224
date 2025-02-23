
all: swing/Main.class

run: swing/Main.class
	java swing/Main

swing/Main.class: Main.java
	javac -d . Main.java

clean:
	@rm -r swing
