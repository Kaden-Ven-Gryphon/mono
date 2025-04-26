import asyncio
import websockets

async def server(wstest, path):
	async for msg in wstest:
		msg = msg.decode("utf-8")
		print(f"Msg from client: {msg}")
		await wstest.send(f"Got your message: {msg}")

start_server = websockets.serve(server, "localhost", 5000)
print("Server started")
asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
