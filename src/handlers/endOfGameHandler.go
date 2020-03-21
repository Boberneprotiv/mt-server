package handlers

import (
	"github.com/boberneprotiv/mt-server/src/event"
	"log"
)

type EndOfGameHandler struct {
	eventCode int
}

func NewEndOfGameHandler(eventCode int) *EndOfGameHandler {
	return &EndOfGameHandler{
		eventCode: eventCode,
	}
}

func (h *EndOfGameHandler) Handle(event event.Event) bool {
	if h.eventCode != event.Code {
		return false
	}

	log.Printf("Game ended")

	return true
}
