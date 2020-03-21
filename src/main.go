package main

import (
	"github.com/boberneprotiv/mt-server/src/crm"
	"github.com/boberneprotiv/mt-server/src/event"
	"github.com/boberneprotiv/mt-server/src/handlers"
	"github.com/boberneprotiv/mt-server/src/readers"
	"os"
	"path/filepath"
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

	workDir, _ := os.Getwd()
	ap := crm.NewAdminPanel(filepath.Join(workDir, "crm/static"), 8080)
	go ap.Serve()

	for s := range events {
		erouter.Route(s)
	}
}
