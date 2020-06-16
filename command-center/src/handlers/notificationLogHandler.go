package handlers

import (
	"github.com/boberneprotiv/mt-server/src/crm"
	"github.com/boberneprotiv/mt-server/src/event"
)

type NotificationLogHandler struct {
	n *crm.Notification
}

func NewNotificationLogHandler(n *crm.Notification) event.Handler {
	return &NotificationLogHandler{
		n: n,
	}
}

func (h *NotificationLogHandler) Handle(event event.Event) bool {
	h.n.Broadcast(event)
	return true
}
