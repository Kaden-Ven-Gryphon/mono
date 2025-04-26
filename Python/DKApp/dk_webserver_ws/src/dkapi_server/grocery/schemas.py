from typing import Optional

from pydantic import BaseModel, ConfigDict

class ItemBase(BaseModel):
	name: str
	list_id: int
	quant: int




class ItemPayload(BaseModel):
	model_config = ConfigDict(from_attributes=True)
	id: Optional[int]
	name: str
	list_id: int
	quant: int
	user_id:int
	use: Optional[str]
	state: int


