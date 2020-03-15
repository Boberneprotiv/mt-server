package main

import (
	"github.com/boberneprotiv/mt-server/src/event"
	"github.com/boberneprotiv/mt-server/src/handlers"
	"github.com/boberneprotiv/mt-server/src/readers"
	"os"
)

func main() {
	erouter := event.NewEventRouter([]event.Handler{
		handlers.NewLogHandler(1, "event one"),
		handlers.NewLogHandler(1, "event one-ецщ"),
		handlers.NewLogHandler(2, "event two"),
	})

	events := make(chan event.Event, 1)
	ereader := readers.NewIOReader(os.Stdin)
	go ereader.Run(events)

	for s := range events {
		erouter.Route(s)
	}
}
