package event

import "time"

type Event struct {
	Code int       `json:"code"`
	Time time.Time `json:"time"`
}

func NewEvent(code int) Event {
	return Event{
		Code: code,
		Time: time.Now(),
	}
}

const (
	GameStart = 2048
	GameEnd   = 2049
)
