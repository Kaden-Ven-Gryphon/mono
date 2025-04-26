from fastapi import APIRouter, Depends, HTTPException
from sqlalchemy.orm import Session

from ..database import SessionLocal
from . import schemas, crud
from .. import dependencies



router = APIRouter(
	prefix="/grocery",
	tags=["grocery"],
	dependencies=[],
	responses={404: {"description": "Not found"}},
)



# add item to grocery list
@router.post("/", response_model=schemas.ItemPayload)
def add_item(item: schemas.ItemPayload, db: Session = Depends(dependencies.get_db)):
	if item.quant <= 0:
		raise HTTPException(status_code=400, detail="Quantity must be greater than 0.")
	if crud.get_list_by_id(db, item.list_id) is None:
		raise HTTPException(status_code=400, detail="Grocery list with that Id does not exist")
	return crud.add_item(db, item)
	


# TODO Route to list a specific item by ID
@router.get("/{item_id}")
def list_item(item_id: int):
	pass

# Rount to list all items list
@router.get("/list/{list_id}", response_model=list[schemas.ItemPayload]| None)
def list_items(list_id: int, db: Session = Depends(dependencies.get_db)):
	return crud.get_all_items_from_list(db, list_id)


# Rount to delete a specific item by ID and list
@router.delete("/{list_id}/{item_id}", response_model=schemas.ItemPayload)
def delete_item(list_id: int, item_id: int, db: Session = Depends(dependencies.get_db)):
	return crud.remove_item_from_list_by_id(db, list_id, item_id)


# Route toggle mark item as aquired
@router.post("/mark/{list_id}/{item_id}", response_model=schemas.ItemPayload)
def mark_item(list_id: int, item_id: int, db=Depends(dependencies.get_db)):
	 return crud.mark_item_from_list_by_id(db, list_id, item_id)

# TODO implement
@router.delete("/aquire/{list_id}/{cost}", response_model=list[schemas.ItemPayload] | None)
def remove_aquired(list_id: int, cost: int, db=Depends(dependencies.get_db)):
	return crud.aquire_items_from_list(db, list_id)



# TODO Rount to change quantity of a specific item by ID
#@router.post("/{list_id}/{item_id}/{quantity}")
#def change_quantity(list_id: int, item_id: int, quantity: int, db=Depends(dependencies.get_db)):
#	return None
