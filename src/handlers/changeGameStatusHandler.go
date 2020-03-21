package handlers

import (
	"github.com/boberneprotiv/mt-server/src/event"
	g "github.com/boberneprotiv/mt-server/src/game"
	"log"
)

type ChangeGameStatusHandler struct {
	eventCode int
	game      *g.Game
}

func NewChangeGameStatusHandler(eventCode int, game *g.Game) event.Handler {
	return &ChangeGameStatusHandler{
		eventCode: eventCode,
		game:      game,
	}
}

func (h *ChangeGameStatusHandler) Handle(event event.Event) bool {
	if h.eventCode != event.Code {
		return false
	}

	if h.game.IsInProgress() {
		log.Printf("Game stoped")
		h.game.Stop()
	} else {
		log.Printf("Game started")
		h.game.Run()
	}

	return true
}
