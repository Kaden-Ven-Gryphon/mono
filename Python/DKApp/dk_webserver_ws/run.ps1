Param(
	$Command
)
If (-Not $Command -eq '') {
	docker run --rm --volume .:/app --volume /app/.venv --publish 8000:8000 -it $(docker build -q .) "$Command"
} Else {
	
docker run \
	docker run --rm --volume .:/app --volume /app/.venv --publish 8000:8000 -it $(docker build -q .)
}