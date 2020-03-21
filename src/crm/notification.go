package crm

import (
	"encoding/json"
	"github.com/boberneprotiv/mt-server/src/event"
	"github.com/gorilla/websocket"
	"net/http"
	"sync"
)

type Notification struct {
	contentFolder string
	upgrader      websocket.Upgrader

	connections      map[*websocket.Conn]bool
	connectionsMutex *sync.Mutex
}

func NewNotification() *Notification {
	return &Notification{
		upgrader:         websocket.Upgrader{},
		connections:      make(map[*websocket.Conn]bool),
		connectionsMutex: &sync.Mutex{},
	}
}

func (p *Notification) Serve() {
	http.HandleFunc("/ws", p.handler)
}

func (p *Notification) handler(w http.ResponseWriter, r *http.Request) {
	c, err := p.upgrader.Upgrade(w, r, nil)
	if err != nil {
		return
	}
	p.connectionsMutex.Lock()
	p.connections[c] = true
	p.connectionsMutex.Unlock()
	defer func() {
		p.connectionsMutex.Lock()
		c.Close()
		delete(p.connections, c)
		p.connectionsMutex.Unlock()
	}()

	for {
		mt, message, err := c.ReadMessage()
		if err != nil {
			break
		}

		if mt != websocket.TextMessage {
			break
		}

		e := event.Event{}
		err = json.Unmarshal(message, &e)

		if err != nil {
			break
		}

		p.Broadcast(e)
	}
}

func (p *Notification) Broadcast(event event.Event) {
	p.connectionsMutex.Lock()
	for c := range p.connections {
		c.WriteJSON(event)
	}
	p.connectionsMutex.Unlock()
}
