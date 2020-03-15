package readers

import (
	"bufio"
	"github.com/boberneprotiv/mt-server/src/event"
	"io"
	"strconv"
)

type IOReader struct {
	r io.Reader
}

func NewIOReader(r io.Reader) IOReader {
	return IOReader{
		r: r,
	}
}

func (r *IOReader) Run(events chan<- event.Event) {
	scanner := bufio.NewScanner(r.r)
	for scanner.Scan() {
		e, _ := strconv.Atoi(scanner.Text())
		events <- event.Event{Code: e}
	}
}
