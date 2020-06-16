package event

import (
	"log"
)

type Router struct {
	handlers []Handler
}

func NewEventRouter(handlers []Handler) *Router {
	return &Router{handlers: handlers}
}

func (er *Router) Route(event Event) {
	anyHandler := false
	for _, h := range er.handlers {
		if h.Handle(event) {
			anyHandler = true
		}
	}

	if !anyHandler {
		log.Printf("No handlers found")
	}
}
