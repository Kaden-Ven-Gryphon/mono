from sqlalchemy.orm import Session
from sqlalchemy import select, update, or_, delete

from . import models, schemas

#TODO write test
def get_all_items_from_list(db: Session, list_id: int):
	"""
	get_all_items_from_list(db, list_id)

	gets all grocery items from a single grocery list from the database

	Parameters
	----------
	db : Session
		The Session class bound to the database engine
	list_id : int
		The id of the list to get the items from

	Returns
	-------
	list(Item)
		The list of grocery items with that list id
	"""
	stmt = select(models.Item).where(models.Item.list_id == list_id)
	return db.scalars(stmt).all()

#TODO write test
# get item from list by id
def get_item_from_list_by_id(db: Session, list_id: int,  id: int):
	"""
	get_item_from_list_by_name(db, list_id, name)

	gets and item from list by its name

	Parameters
	----------
	db : Session
		The Session class bound to the database engine
	list_id : int
		The id of the list to get the item from.
	id : int
		The id of the item to get
	
	Returns
	-------
	Item | None
		The item if found
	"""
	stmt = (
		select(models.Item)
		.where(models.Item.list_id == list_id, models.Item.id == id)
	)
	return db.scalars(stmt).first()


# TODO write test
# get item from list by name
def get_item_from_list_by_name(db: Session, list_id: int, name: str):
	"""
	get_item_from_list_by_name(db, list_id, name)

	gets and item from list by its name

	Parameters
	----------
	db : Session
		The Session class bound to the database engine
	list_id : int
		The id of the list to get the item from.
	name : str
		The name of the item to get
	
	Returns
	-------
	Item | None
		The item if found
	"""
	stmt = (
		select(models.Item)
		.where(models.Item.list_id == list_id, models.Item.name == name)
	)
	return db.scalars(stmt).first()

# TODO write test
# add item to database based on schema item
def add_item(db: Session, item: schemas.ItemPayload):
	"""
	add_item(db, item)

	Adds a grocery item to the database.

	Parameters
	----------
	db : Session
		The Session class bound to the database engine.
	item: ItemPayload
		The item to be added to the database, not all varibles
		of item need to be filled.
	
	Returns
	-------
	Item
		The item added to the database with uptodate quantity amount.

	Notes
	-----
	It will look for the matching item based on id, or name, and list.
	If a matching item is found it will update that item with the
	summed quantity.
	Otherwise it will create new item using the next avalible id.

	"""

	# SELECT item WHERE (name OR id) AND list
	stmt = (
		select(models.Item)
		.where(or_(models.Item.name == item.name, models.Item.id == item.id), 
		 models.Item.list_id == item.list_id)
		)
	item_in_table = db.scalars(stmt).first()

	# If an item is found
	if item_in_table is not None:
		# UPDATE item where id AND list VALUE quant
		stmt = (
			update(models.Item)
			.where(models.Item.id == item_in_table.id, models.Item.list_id == item_in_table.list_id)
			.values(quant=item_in_table.quant+item.quant)
		)
		db.execute(stmt)
	# Else create new item
	else:
		stmt = select(models.Item.id)
		rows = db.execute(stmt).all()
		
		new_item = models.Item(
			id = max((row.id for row in rows), default=0) + 1,
			name = item.name,
			list_id=item.list_id,
			quant=item.quant
		)
		db.add(new_item)
		item_in_table = new_item
	
	# Return the updated item.
	db.commit()
	db.refresh(item_in_table)
	return item_in_table


# TODO write test
def get_list_by_id(db: Session, id: int):
	#query = select(models.List).where(models.List.id == id)
	#return db.scalars(query).first()
	return 0

# TODO write test
def remove_item_from_list_by_id(db: Session, list_id: int, id: int):
	"""
	remove_item_from_list_by_id(db, list_id, id)

	Parameters
	----------
	db : Session
		The Session class bound to the database engine.
	list_id : int
		The id of the list to remove from.
	id : int
		The id of the item.
	
	Returns
	-------
	ItemPayload
		The item that was removed.
	"""

	# get item of mathcing id and list id.
	stmt = (
		delete(models.Item)
		.where(models.Item.id ==id, models.Item.list_id == list_id)
		.returning(models.Item)
	)
	
	# get remove item and get reference to item removed
	removed_item = db.scalars(stmt).first()
	if removed_item is not None:
		removed_item = schemas.ItemPayload.model_validate(removed_item)
	db.commit()
	return removed_item
	

# TODO write test and doc
def mark_item_from_list_by_id(db: Session, list_id: int, id: int):
	item = get_item_from_list_by_id(db, list_id, id)
	mark = 0
	if item is not None:
		if item.state == 0:
			mark = 1
		else:
			mark = 0
	
		stmt = (
			update(models.Item)
			.where(models.Item.list_id == list_id, models.Item.id == id)
			.values(state = mark)
			.returning(models.Item)
			)
		removed_item = db.scalars(stmt).first()
		if removed_item is not None:
			removed_item = schemas.ItemPayload.model_validate(removed_item)
		db.commit()
	return removed_item

# TODO write test and doc
def aquire_items_from_list(db: Session, list_id):
	stmt = (
		delete(models.Item)
		.where(models.Item.list_id == list_id, models.Item.state == 1)
		.returning(models.Item)
	)
	aquired_items = db.scalars(stmt).all()
	db.commit()
	return None