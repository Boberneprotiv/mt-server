package game

import (
	"context"
	"time"
)

type Game struct {
	startTime time.Time
	duration  time.Duration
	stopTimer *time.Timer

	StopChan chan bool
	stop     context.CancelFunc
}

func NewGame(duration time.Duration) *Game {
	return &Game{
		StopChan: make(chan bool),
		duration: duration,
	}
}

func (s *Game) Run() {
	s.startTime = time.Now()

	s.stopTimer = time.NewTimer(s.duration)
	ctx, cancel := context.WithCancel(context.TODO())
	s.stop = cancel

	go func() {
		select {
		case <-s.stopTimer.C:
			s.StopChan <- true
		case <-ctx.Done():
			return
		}
	}()
}

func (s *Game) Stop() {
	s.stop()
	s.stopTimer.Stop()
	s.stopTimer = nil
}

func (s *Game) IsInProgress() bool {
	return s.stopTimer != nil
}
