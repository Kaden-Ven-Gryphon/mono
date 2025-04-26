# cowgolms

### Conways Game of Life Micro Service

This is just a small project to learn about go and try out making a rest api deployed to a kubernetes cluters.

Has basic go test for cw package.

This can test creating a random 10x10 board

```
curl -i: -w "\n" localhost/rand/10/10/
```

This can run `stops` on the board.  replace `<BOARD JSON>` with the output of the rand request

```
curl -iL -w "\n" POST -H "Content-Type: application/json" --data '<BOARD JSON>' localhost/stops/
```

These assume you are runing the image on port 80, if runing the the server directly with go run, add `:8080` to `localhost` in the commands.