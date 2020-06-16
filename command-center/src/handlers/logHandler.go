package handlers

import (
	"github.com/boberneprotiv/mt-server/src/event"
	"log"
)

type LogHandler struct {
	eventCode int
	message   string
}

func NewLogHandler(eventCode int, message string) event.Handler {
	return &LogHandler{
		eventCode: eventCode,
		message:   message,
	}
}

func (h *LogHandler) Handle(event event.Event) bool {
	if h.eventCode != event.Code {
		return false
	}

	log.Printf(h.message)
	return true
}
