from fastapi.testclient import TestClient

from dkapi_server.main import app

client = TestClient(app)


def test_read_main():
	response = client.get("/")
	assert response.status_code == 200
	assert response.text == "root of DKAPP"
