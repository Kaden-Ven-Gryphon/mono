# kecharaBot.py
import os
import random

import interactions
from dotenv import load_dotenv

import cws as conwayssoldier

load_dotenv()
TOKEN = os.getenv('DISCORD_TOKEN')
GUILD = os.getenv('DISCORD_GUILD')
GUILD_ID = 932774385260060702

bot = interactions.Client(TOKEN)

@bot.event
async def on_ready():
	conwayssoldier.initBoard('test')
	print("Ready")
	print("--------------------------------------")

@bot.command(
	name="ping",
	description="A ping pong test",
	scope=GUILD_ID
)
async def ping(ctx: interactions.CommandContext):
	await ctx.send("pong")



#CWS
@bot.command(
	name="cws",
	description="This description isn't seen in UI (yet?)",
	scope=GUILD_ID,
 	options=[
		interactions.Option(
			name="help",
			description="List the use and rules of cws",
			type=interactions.OptionType.SUB_COMMAND,
		),
		interactions.Option(
			name="print",
			description="print the current board",
			type=interactions.OptionType.SUB_COMMAND,
		),
		interactions.Option(
			name="reset",
			description="resets the cws board",
			type=interactions.OptionType.SUB_COMMAND,
		),
		interactions.Option(
			name="move",
			description="Play a move",
			type=interactions.OptionType.SUB_COMMAND,
			options=[
				interactions.Option(
					name="xpos",
					description="X pos A-T",
					type=interactions.OptionType.STRING,
					required=True,
				),
				interactions.Option(
					name="ypos",
					description="Y pos 0-9",
					type=interactions.OptionType.INTEGER,
					required=True,
				),
				interactions.Option(
					name="direction",
					description="u,d,l,r",
					type=interactions.OptionType.STRING,
					required=True,
				),
			],
		),
	],
)
async def cws_cmd(ctx: interactions.CommandContext, sub_command: str, xpos: str = "", ypos: int = 0, direction: str = ""):
	if sub_command == "help":
		await ctx.send("conways soldiers (cws)")
	elif sub_command == "print":
		await ctx.send("```"+conwayssoldier.renderShort(str(ctx.author.user.id))+"```")
	elif sub_command == "reset":
		conwayssoldier.initBoard(str(ctx.author.user.id))
		await ctx.send("Board reset for " + str(ctx.author.user.id))
	elif sub_command == "move":
		await ctx.send("```"+conwayssoldier.moveSoldier(str(ctx.author.user.id), xpos, ypos, direction)+"```")

bot.start()
