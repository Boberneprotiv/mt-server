package handlers

import (
	"github.com/boberneprotiv/mt-server/src/event"
	g "github.com/boberneprotiv/mt-server/src/game"
	"log"
)

type GameStartHandler struct {
	eventCode int
	game      *g.Game
}

func NewGameStartHandler(eventCode int, game *g.Game) event.Handler {
	return &GameStartHandler{
		eventCode: eventCode,
		game:      game,
	}
}

func (h *GameStartHandler) Handle(event event.Event) bool {
	if h.eventCode != event.Code {
		return false
	}

	log.Printf("Game started")
	h.game.Run()

	return true
}
