package handlers

import (
	"github.com/boberneprotiv/mt-server/src/event"
	g "github.com/boberneprotiv/mt-server/src/game"
	"log"
)

type GameEndHandler struct {
	eventCode int
	game      *g.Game
}

func NewGameEndHandler(eventCode int, game *g.Game) event.Handler {
	return &GameEndHandler{
		eventCode: eventCode,
		game:      game,
	}
}

func (h *GameEndHandler) Handle(event event.Event) bool {
	if h.eventCode != event.Code {
		return false
	}

	log.Printf("Game stoped")
	h.game.Stop()

	return true
}
