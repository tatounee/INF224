
main = Main
pkg = swing

SOURCES = Main.java Client.java

comiled_main = ${pkg}/${main}.class


all: ${comiled_main}

run: ${comiled_main}
	java ${pkg}/${main}

swing/Main.class: ${SOURCES}
	javac -d . ${SOURCES}

clean:
	@rm -r ${pkg}
