# kecharaBot.py
import os
import random

import discord
from dotenv import load_dotenv

import cws

load_dotenv()
TOKEN = os.getenv('DISCORD_TOKEN')
GUILD = os.getenv('DISCORD_GUILD')

client = discord.Client()

@client.event
async def on_ready():
	for guild in client.guilds:
		if guild.name == GUILD:
			break
	print(
		f'{client.user} has connected to Discord!\n'
		f'{guild.name}(id: {guild.id})'	
	)
	# Conways Soldiers
	cws.initBoard('test')


@client.event
async def on_message(message):
	if message.author == client.user:
		return

	stormlight_quotes = [
		'Life Before Death',
		'Strength Before Weakness',
		'Joureny Before Destination'
	]

	if message.content == 'stormlight':
		response = random.choice(stormlight_quotes)
		await message.channel.send(response)
	if message.content.startswith('!'):

		# CONWAYS SOLDIERS #####################################################################
		if message.content.startswith('cws', 1, 4):
			if message.content.startswith('move', 5, 9):
				x = message.content[10:11]
				y = int(message.content[12:13])
				d = message.content[14:15]
				response = '```' + cws.moveSoldier('test', x, y, d) + '```'
				await message.channel.send(response)

			if message.content.startswith('reset', 5, 10):
				cws.initBoard('test')
				response = '```' + cws.renderShort('test') + '```'
				await message.channel.send(response)

			if message.content.startswith('help', 5, 9):
				response = '!cws <command> <arguments>\nCommands:\nreset\nmove <letter> <number> <direction(u, l, r, d)>'
				await message.channel.send(response)







client.run(TOKEN)
