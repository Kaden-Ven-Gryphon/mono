"""Docstring for the main.py module.

This contains the app instance of FastAPI and adds the routers to the app

"""

from fastapi import FastAPI, Response

from .grocery import router as grocery_router
from .users import router as users_router

app = FastAPI()

app.include_router(grocery_router.router)
app.include_router(users_router.router)


@app.get("/")
def root():
	"""The default reponse to connecting to the DK api url."""
	return Response(content="root of DKAPP", status_code=200, media_type="text")
