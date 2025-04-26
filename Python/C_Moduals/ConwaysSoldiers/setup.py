from distutils.core import setup, Extension


modulel = Extension("cws",
			include_dirs = ["./source"],
			libraries = ["cwslib"],
			library_dirs = ["./binaries"],
			sources = ["cwsmodule.c"])


def main():
	setup(name="cws",
	version="0.0.1",
	description="Python interface for the conways soldiers c lib",
	author="Nox Noctua",
	author_email="NoxNoctua.vtg@gmail.com",
	ext_modules=[modulel])

if __name__ == "__main__":
	main()
