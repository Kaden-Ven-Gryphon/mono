
[[README|DK App]] uses Sphinx to create its documentation based on source code docstrings


## Dependencies:

- sphinx
	- `uv add --dev sphinx`
- numpydoc
	- `uv add --dev numpydoc`


## Setup:

Run:

```
sphinx-quickstart
```

add:

```
import os
import sys
import sys.path.insert(0, os.path.abspath("../..")
```

to `conf.py`

and add: `module` to `index.rst`

Make sure that the build directory and the generated `.rst` files are added to ignore files.

```
docs/build
*.rst
!index.rst
```

## Generate Docs:

Run :

```
sphinx-apidoc -o docs/source src/
```

to generate the `.rst` files corresponding to each of the modules.
Not sure if this is necessary to run or not to be honest.

Run:

(windows)
```
.\docs\make.bat html
```
(unix)
```
./docs/make html
```

to generate the html files of the documentation.  Html can be swapped for other formats.