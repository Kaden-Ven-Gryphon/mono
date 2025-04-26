FROM golang:1.23.5

WORKDIR /app
COPY . .

RUN go build -o app

EXPOSE 8080

CMD ["./app"]