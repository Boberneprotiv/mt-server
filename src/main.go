package main

import (
	"github.com/boberneprotiv/mt-server/src/crm"
	"github.com/boberneprotiv/mt-server/src/event"
	"github.com/boberneprotiv/mt-server/src/game"
	"github.com/boberneprotiv/mt-server/src/handlers"
	"github.com/boberneprotiv/mt-server/src/readers"
	"log"
	"os"
	"path/filepath"
	"time"
)

func main() {
	game := game.NewGame(5 * time.Second)
	erouter := event.NewEventRouter([]event.Handler{
		handlers.NewChangeGameStatusHandler(2024, game),
		handlers.NewEndOfGameHandler(2025),
	})

	events := make(chan event.Event, 1)
	ereader := readers.NewIOReader(os.Stdin)
	go ereader.Run(events)

	workDir, _ := os.Getwd()
	ap := crm.NewAdminPanel(filepath.Join(workDir, "crm/static"), 8080)
	go ap.Serve()

	for {
		select {
		case <-game.StopChan:
			{
				log.Printf("Stop of game")
				events <- event.Event{Code: 2025}
			}
		case e := <-events:
			{
				erouter.Route(e)
			}
		}
	}
}
