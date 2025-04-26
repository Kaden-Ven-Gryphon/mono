
## Dev scripts need access to src module

With the file structure:

```
-Project
|-devscripts
| |--script1.py
|-src
  |--Module
     |-...
```

the script that needs to be able to use the modules need to have the path to them added with
```
import os
import sys
sys.path.append(os.path.join(os.path.dirname(__file__), "../src"))
```

## Issues with typing for model.atribute == value

Needed to switch over to the new typing methods for sqlalchemy 

https://docs.sqlalchemy.org/en/20/changelog/whatsnew_20.html#new-typing-support-in-core-and-orm-stubs-extensions-no-longer-used

## Stub routes cause unprocessable content


## Docker build not working, cant find docker
Docker desktop must be running to build docker images on windows

## Pytest cannot find modules

For user created modules the pyproject.toml need to have a pythonpath to the top level module
```
[tool.pytest.ini_options]
pythonpath = "./src/"
```

For dependent modules use `uv run pytest` 

## UV failed to canonicalize script path

```
uv cache clean
uv sync -- reinstall
```

